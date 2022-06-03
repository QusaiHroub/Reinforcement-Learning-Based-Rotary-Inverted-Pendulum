#include <iostream>

#include "../state.cc"

#include "../../../utils/pstate.hh"
#include "../../../utils/type.hh"

using namespace std;

int main () {
  PState *pstate = State_new(1, 1, 1, 1);

  State_set_pendulum_angle(pstate, 10);

  cout << State_get_at(pstate, 0) << endl;
  cout << State_get_pendulum_angle(pstate) << endl;

  return 0;
}