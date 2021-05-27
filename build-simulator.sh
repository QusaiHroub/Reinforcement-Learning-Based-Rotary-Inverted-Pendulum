# build-simulator.sh
#
# This file is part of Reinforcement Learning-based Rotary Inverted Pendulum
# Graduation Project.
#
# Authors:
# Qusai Hroub <qusaihroub.r@gmail.com>
#
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 3, as published by the Free Software Foundation.
#
# This program is distributed in the hope it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.

utilsdir="./simulator/utils/"
pythoninterfacedir="./simulator/python-interface/utils/"

### Check for dirs, if not found create theme using the mkdir ##
[ ! -d "$utilsdir" ] && mkdir -p "$utilsdir"
[ ! -d "$pythoninterfacedir" ] && mkdir -p "$pythoninterfacedir"

### Create obj file for each c++ file ##
g++ -c -fmodules-ts -fPIC "./src/utils/math.cc" -o "./simulator/utils/math.o"
g++ -c -fmodules-ts -fPIC "./src/utils/state.cc" -o "./simulator/utils/state.o"
g++ -c -fmodules-ts -fPIC "./src/python-interface/utils/math.cc" -o "./simulator/python-interface/utils/math.o"
g++ -c -fmodules-ts -fPIC "./src/python-interface/utils/state.cc" -o "./simulator/python-interface/utils/state.o"

### link obj files ##
g++ -fmodules-ts -shared -Wl,-soname math.so, "./simulator/utils/math.o" "./simulator/python-interface/utils/math.o" -o "./simulator/utils/math.so"
g++ -fmodules-ts -shared -Wl,-soname state.so, "./simulator/utils/math.o" "./simulator/utils/state.o" "./simulator/python-interface/utils/state.o" -o "./simulator/utils/state.so"

### copy python files into its new dir ##
cp "./src/python-interface/utils/umath.py" "./simulator/utils/umath.py"
cp "./src/python-interface/utils/ustate.py" "./simulator/utils/ustate.py"
cp "./src/python-interface/utils/__init__.py" "./simulator/utils/__init__.py"
cp "./src/simulation/pendulum_env.py" "./simulator/pendulum_env.py"
cp "./src/simulation/main.py" "./simulator/main.py"
cp "./src/simulation/dqlearn.py" "./simulator/dqlearn.py"


### cleanup ##
rm -rf "./simulator/python-interface/"
rm "./simulator/utils/math.o" "./simulator/utils/state.o"
