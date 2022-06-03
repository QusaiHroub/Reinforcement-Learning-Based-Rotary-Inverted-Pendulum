#include <iostream>

#include "../pstate.hh"

using namespace std;

int main () {
  PState pState, pState2;

  pState.setAt(0, 5);

  pState.setPendulumAngle(10);

  pState2 = pState;

  cout << pState[1].getValue() << endl;
  cout << pState2.getPendulumAngle() << endl;
  return 0;
}