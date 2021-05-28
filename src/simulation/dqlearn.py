""" simulation/dqlearn.py

 This file is part of Reinforcement Learning-based Rotary Inverted Pendulum
 Graduation Project.

 Authors:
 Qusai Hroub <qusaihroub.r@gmail.com>

 This program is free software; you can redistribute it and/or modify it
 under the terms and conditions of the GNU General Public License,
 version 3, as published by the Free Software Foundation.

 This program is distributed in the hope it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.
"""

from __future__ import absolute_import, division, print_function


import base64
import imageio
import IPython
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import PIL.Image
import pyvirtualdisplay
import gym


import tensorflow as tf


from tf_agents.agents.dqn import dqn_agent
from tf_agents.drivers import dynamic_step_driver
from tf_agents.environments import suite_gym
from tf_agents.environments import tf_py_environment
from tf_agents.eval import metric_utils
from tf_agents.metrics import tf_metrics
from tf_agents.networks import sequential
from tf_agents.networks.sequential import Sequential
from tf_agents.policies import random_tf_policy
from tf_agents.replay_buffers import tf_uniform_replay_buffer
from tf_agents.trajectories import trajectory
from tf_agents.specs import tensor_spec
from tf_agents.utils import common

import Pendulum_Env


"""## Hyperparameters"""

num_iterations = 20000 # @param {type:"integer"}


initial_collect_steps = 100  # @param {type:"integer"}
collect_steps_per_iteration = 1  # @param {type:"integer"}
replay_buffer_max_length = 100000  # @param {type:"integer"}


batch_size = 64  # @param {type:"integer"}
learning_rate = 1e-3  # @param {type:"number"}
log_interval = 200  # @param {type:"integer"}


num_eval_episodes = 10  # @param {type:"integer"}
eval_interval = 1000  # @param {type:"integer"}


env_name = 'pendulum_env-v0' # @param {type:"string"}


optimizer = tf.keras.optimizers.Adam(learning_rate=learning_rate)


train_step_counter = tf.Variable(0)


Alpha = 0.02
Epsilon = 0.2
Gamma = 0.85 #0.8 to 0.99
epsilon_discount = 0.85


def build_environments (is_cc):
    if is_cc:
        train_py_env = suite_gym.load(env_name)
        eval_py_env = suite_gym.load(env_name)
    else:
        train_py_env = suite_gym.load(env_name, lenOfTimeSeries=1)
        eval_py_env = suite_gym.load(env_name, lenOfTimeSeries=1)


    action_tensor_spec = tensor_spec.from_spec(train_py_env.action_spec())

    train_env = tf_py_environment.TFPyEnvironment(train_py_env)
    eval_env = tf_py_environment.TFPyEnvironment(eval_py_env)

    return train_env, eval_env, action_tensor_spec


def dense_layer (num_units):
    return tf.keras.layers.Dense (
        num_units,
        activation=tf.keras.activations.relu,
        kernel_initializer=tf.keras.initializers.VarianceScaling(
            scale=2.0, mode='fan_in', distribution='truncated_normal'))


def conv_layer (param):
    filters, input_shape, kernel_size = param
    return tf.keras.layers.Conv2D (
        filters = filters,
        kernel_size = kernel_size,
        input_shape = input_shape,
        activation=tf.keras.activations.relu,
        kernel_initializer=tf.keras.initializers.VarianceScaling(
          scale=2.0, mode='fan_in', distribution='truncated_normal'))


def build_q_net (fc_layer, num_actions, fc_conv_layer=None):
    q_values_layer = tf.keras.layers.Dense(
        num_actions,
        activation=None,
        kernel_initializer=tf.keras.initializers.RandomUniform(
            minval=-0.03, maxval=0.03),
        bias_initializer=tf.keras.initializers.Constant(-0.2))

    if not fc_conv_layer:
        dense_layers = [dense_layer(params) for params in fc_layer]
        q_net = sequential.Sequential(dense_layers + [q_values_layer])
        target_q_net = q_net.copy()
        return q_net, target_q_net

    dense_layers = [dense_layer(fc_layer)]
    conv_layers = [conv_layer(params) for params in fc_conv_layer]
    q_net = sequential.Sequential(conv_layers + [tf.keras.layers.Flatten()] + dense_layers + [q_values_layer])
    target_q_net = q_net.copy()
    return q_net, target_q_net


def compute_avg_return(environment, policy, num_episodes=10):

    total_return = 0.0
    for _ in range(num_episodes):

        time_step = environment.reset()
        episode_return = 0.0

        while not time_step.is_last():
            action_step = policy.action(time_step)
            time_step = environment.step(action_step.action)
            episode_return += time_step.reward
            environment.render()
            total_return += episode_return

    avg_return = total_return / num_episodes
    return avg_return.numpy()[0]


def collect_step(environment, policy, buffer):
    time_step = environment.current_time_step()
    print(time_step)
    action_step = policy.action(time_step)
    print(action_step)
    next_time_step = environment.step(action_step.action)
    traj = trajectory.from_transition(time_step, action_step, next_time_step)

    buffer.add_batch(traj)


def collect_data(env, policy, buffer, steps):
    for _ in range(steps):
        collect_step(env, policy, buffer)


def train (agent,train_env, eval_env, replay_buffer):
    agent.train_step_counter.assign(0)

    avg_return = compute_avg_return(eval_env, agent.policy, num_eval_episodes)
    returns = [avg_return]

    for _ in range(num_iterations):

        collect_data(train_env, agent.collect_policy, replay_buffer, collect_steps_per_iteration)

        experience, unused_info = next(iterator)
        train_loss = agent.train(experience).loss

        step = agent.train_step_counter.numpy()

        if step % log_interval == 0:
            print('step = {0}: loss = {1}'.format(step, train_loss))

        if step % eval_interval == 0:
            avg_return = compute_avg_return(eval_env, agent.policy, num_eval_episodes)
            print('step = {0}: Average Return = {1}'.format(step, avg_return))
            returns.append(avg_return)


def run_dqlearn (is_cc):
    train_env, eval_env, action_tensor_spec = build_environments (is_cc)
    num_actions = action_tensor_spec.maximum - action_tensor_spec.minimum + 1

    if is_cc:
        fc_layer_params = (128)
        fc_conv_layer_params = ((32, (10, 4, 1), (4, 4)), (64, (7, 1, 32), (4, 1)))
        q_net, target_q_net = build_q_net (fc_conv_layer=fc_conv_layer_params,
                                            fc_layer=fc_layer_params,
                                            num_actions=num_actions)
    else:
        fc_layer_params = (4, 100, 50)
        q_net, target_q_net = build_q_net (fc_layer=fc_layer_params, num_actions=num_actions)

    agent = dqn_agent.DqnAgent(
        train_env.time_step_spec(),
        train_env.action_spec(),
        q_network=q_net,
        target_q_network=target_q_net,
        optimizer=optimizer,
        td_errors_loss_fn=common.element_wise_squared_loss,
        train_step_counter=train_step_counter,
        gamma=Gamma,
        epsilon_greedy=Epsilon)

    agent.initialize()

    eval_policy = agent.policy
    collect_policy = agent.collect_policy

    random_policy = random_tf_policy.RandomTFPolicy(train_env.time_step_spec(),
                                                    train_env.action_spec())

    #compute_avg_return(eval_env, random_policy, num_eval_episodes)

    replay_buffer = tf_uniform_replay_buffer.TFUniformReplayBuffer(
        data_spec=agent.collect_data_spec,
        batch_size=train_env.batch_size,
        max_length=replay_buffer_max_length)

    collect_data(train_env, random_policy, replay_buffer, initial_collect_steps)

    train(agent, train_env, eval_env, replay_buffer)



