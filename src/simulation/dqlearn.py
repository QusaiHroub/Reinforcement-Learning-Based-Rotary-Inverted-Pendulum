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
import os
import io
import IPython
import progressbar


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
from tf_agents.policies import policy_saver


import Pendulum_Env


"""## Hyperparameters"""

num_iterations = 20000 # @param {type:"integer"}
num_episodes = 20000


initial_collect_steps = 100  # @param {type:"integer"}
collect_steps_per_iteration = 1  # @param {type:"integer"}
replay_buffer_max_length = 100000  # @param {type:"integer"}


batch_size = 256  # @param {type:"integer"}
learning_rate = 1e-3  # @param {type:"number"}
log_interval = 200  # @param {type:"integer"}
num_epochs = 200
conv_to_percentage = 2


num_eval_episodes = 10  # @param {type:"integer"}
eval_interval = 1000  # @param {type:"integer"}


env_name = 'pendulum_env-v0' # @param {type:"string"}


optimizer = tf.keras.optimizers.Adam(learning_rate=learning_rate)


train_step_counter = tf.compat.v1.train.get_or_create_global_step()

save_dir = './save/'
policy_dir = os.path.join(save_dir, 'policy')
checkpoint_dir = os.path.join(save_dir, 'checkpoint')


Alpha = 0.02
Epsilon = 0.2
Gamma = 0.85 #0.8 to 0.99
epsilon_discount = 0.85

max_to_keep = 10


def build_environments (is_cc):
    """build enviornments for train and test

    Parameters
    ----------

    is_cc: boolean
        is environments target convolutional neural network or not.

    Returns
    -------

         An Object of State values
    """

    if is_cc:
        train_py_env = suite_gym.load(env_name)
        eval_py_env = suite_gym.load(env_name)
    else:
        train_py_env = suite_gym.load(env_name, lenOfTimeSeries=1)
        eval_py_env = suite_gym.load(env_name, lenOfTimeSeries=1)


    action_tensor_spec = tensor_spec.from_spec(train_py_env.action_spec())

    train_env = tf_py_environment.TFPyEnvironment(train_py_env)
    eval_env = tf_py_environment.TFPyEnvironment(eval_py_env)

    return train_env, train_py_env, eval_env, eval_py_env, action_tensor_spec


def dense_layer (num_units):
    """build dense layer

    Parameters
    ----------

    num_units: number
        number of units in the layer.

    Returns
    -------

         dense layer
    """

    return tf.keras.layers.Dense (
        num_units,
        activation=tf.keras.activations.relu,
        kernel_initializer=tf.keras.initializers.VarianceScaling(
            scale=2.0, mode='fan_in', distribution='truncated_normal'))


def conv_layer (param):
    """build convolutional layer

    Parameters
    ----------

    param: tuble of 3 values
        filters: number - number of filters in the layer
        input_shape: tuble of 3 numbers - dimensions of the input
        kernel_size: tuble of 2 numbers - kernel dimensions

    Returns
    -------

         convolutional layer
    """

    filters, input_shape, kernel_size = param
    return tf.keras.layers.Conv2D (
        filters = filters,
        kernel_size = kernel_size,
        input_shape = input_shape,
        activation=tf.keras.activations.relu,
        kernel_initializer=tf.keras.initializers.VarianceScaling(
          scale=2.0, mode='fan_in', distribution='truncated_normal'))


def build_q_net (fc_layer, num_actions, fc_conv_layer=None):
    """build q neural network

    Parameters
    ----------

    c_layer: tuble
        describe dense layer
    num_actions: number
        number of actions - equivalent to the number neural network outputs
    fc_conv_layer: tuble
        describe convolutional layer

    Returns
    -------

         q_net and target_q_net
    """

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
    """compute avg return - deprecated

    Parameters
    ----------

    environment: gym enironment
    policy:
    num_episodes: number

    Returns
    -------

        reward avg
    """

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
    """collect data for step - deprecated

    Parameters
    ----------

    environment: gym enironment
    policy:
    buffer: replay buffer

    Returns
    -------

    """

    time_step = environment.current_time_step()
    action_step = policy.action(time_step)
    next_time_step = environment.step(action_step.action)
    traj = trajectory.from_transition(time_step, action_step, next_time_step)

    buffer.add_batch(traj)


def collect_data(environment, policy, buffer, steps):
    """collect data for steps - deprecated

    Parameters
    ----------

    environment: gym enironment
    policy:
    buffer: replay buffer
    steps:

    Returns
    -------

         dense layer
    """

    for _ in range(steps):
        collect_step(environment, policy, buffer)


def train (agent, iterator, collect_driver, train_checkpointer):
    """train

    Parameters
    ----------

    agent:
    iterator:
    collect_driver:
    train_checkpointer:

    Returns
    -------

    """

    agent.train_step_counter.assign(0)

    for _ in range(num_episodes):
        bar = progressbar.ProgressBar(maxval=num_epochs/conv_to_percentage, widgets=[progressbar.Bar('=', '[', ']'), ' ', progressbar.Percentage()])
        bar.start()

        for step in range (num_epochs):

            collect_driver.run()

            experience, unused_info = next(iterator)
            train_loss = agent.train(experience).loss

            if step % conv_to_percentage == 0:
                bar.update(step / conv_to_percentage + 1)

        step = agent.train_step_counter.numpy()

        print('step = {0}: loss = {1}'.format(step, train_loss))


def embed_gif(gif_buffer):
    """Embeds a gif file in the notebook."""
    tag = '<img src="data:image/gif;base64,{0}"/>'.format(base64.b64encode(gif_buffer).decode())
    return IPython.display.HTML(tag)


def run_episodes_and_create_video(policy, eval_tf_env, eval_py_env):
    num_episodes = 3
    frames = []
    for _ in range(num_episodes):
        time_step = eval_tf_env.reset()
        frames.append(eval_py_env.render())
        while not time_step.is_last():
            action_step = policy.action(time_step)
            time_step = eval_tf_env.step(action_step.action)
            frames.append(eval_py_env.render())
    gif_file = io.BytesIO()
    imageio.mimsave(gif_file, frames, format='gif', fps=60)
    IPython.display.display(embed_gif(gif_file.getvalue()))


def run_dqlearn (is_cc, checkpointer_restor = False, load_tf_policy = False):
    """run deep q-learn

    Parameters
    ----------

    is_cc: boolean
        is environments target convolutional neural network or not.
    checkpointer_restor: boolean
        load saved check pointer restore
    load_tf_policy: boolean
        load saved tf policy

    Returns
    -------

        save the latest checkpointer and tf_policy
    """

    train_env, train_py_env, eval_env, eval_py_env, action_tensor_spec = build_environments (is_cc)
    num_actions = action_tensor_spec.maximum - action_tensor_spec.minimum + 1

    if load_tf_policy:
        agent = tf.compat.v2.saved_model.load(policy_dir)
        agent.q_network.summary()
    else:
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
            epsilon_greedy=Epsilon,
            target_update_period=num_epochs)

        agent.initialize()
        target_q_net.summary()

    eval_policy = agent.policy
    collect_policy = agent.collect_policy

    random_policy = random_tf_policy.RandomTFPolicy(train_env.time_step_spec(),
                                                    train_env.action_spec())

    #compute_avg_return(eval_env, random_policy, num_eval_episodes)

    replay_buffer = tf_uniform_replay_buffer.TFUniformReplayBuffer(
        data_spec=agent.collect_data_spec,
        batch_size=train_env.batch_size,
        max_length=replay_buffer_max_length)

    collect_driver = dynamic_step_driver.DynamicStepDriver(
        train_env,
        agent.collect_policy,
        observers=[replay_buffer.add_batch],
        num_steps=collect_steps_per_iteration)

    train_checkpointer = common.Checkpointer(
        ckpt_dir=checkpoint_dir,
        max_to_keep=max_to_keep,
        agent=agent,
        policy=agent.policy,
        replay_buffer=replay_buffer,
        global_step=train_step_counter
    )

    if checkpointer_restor:
        train_checkpointer.initialize_or_restore()

    tf_policy_saver = policy_saver.PolicySaver(agent.policy)

    train_checkpointer.save(train_step_counter)

    collect_driver.run()

    dataset = replay_buffer.as_dataset(
        num_parallel_calls=3,
        sample_batch_size=batch_size,
        num_steps=2).prefetch(3)

    iterator = iter(dataset)

    train(agent, iterator, collect_driver, train_checkpointer)

    tf_policy_saver.save(policy_dir)

    print ('global_step:', train_step_counter)
    run_episodes_and_create_video(agent.policy, eval_env, eval_py_env)
    
