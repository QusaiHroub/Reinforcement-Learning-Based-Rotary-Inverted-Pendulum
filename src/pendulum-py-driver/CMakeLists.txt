PYTHON_ADD_MODULE(pendulum_py_driver pendulum-py-driver.cc)
FILE(COPY test.py DESTINATION .)
ADD_TEST(NAME Pendulum-Driver-test COMMAND ${PYTHON_EXECUTABLE} test.py)