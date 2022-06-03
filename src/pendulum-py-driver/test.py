import pendulum_py_driver

pendulum = pendulum_py_driver.Pendulum()

while True:
    print (pendulum.get_state().get_motor_angle())

