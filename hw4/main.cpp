#include <iostream>
#include <string>
#include <limits>
#include "string_calculator.h"

using namespace std;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI

  string lhs;
  string rhs;
  char sym;
  string ans;
  cin >> lhs;
while (lhs != "quit" || lhs != "q"){
  cin >> sym;
  cin >> rhs;
  cout << ">> " << endl <<"ans =" << endl << endl;

  if (sym == '+'){
    ans = add(lhs,rhs);
  }
  else if (sym == '-'){
    ans = subtract(lhs,rhs);
  }
  else if (sym == '*'){
    ans = multiply(lhs,rhs);
  }
  cout << "    " << ans << endl  << endl;
  cin >> lhs;
  if (lhs == "quit" || lhs == "q"){
    cout << ">> " << endl << "farvel!" << endl << endl;
    return 0;
  }
}
}

