#include <iostream>

#include "../pstate.hh"
#include "../q_table.hh"

using namespace std;

int main () {
  PState pState;

  pState.setAt(1, 5.5);

  QTable qTable;

  qTable.set(pState, 1, 2);

  pState.setAt(1, 5.3);


  float q = qTable.get(pState, 1);

  cout << q << endl;
  return 0;
}