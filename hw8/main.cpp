// main.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;

int main() {
    // cout << "String Calculator" << endl;
    // cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // my_string lhs;
    // my_string rhs;
    // char sym;
    // my_string ans;
    // cin >> lhs;
    // while (lhs != "quit" || lhs != "q"){
    //     cin >> sym;
    //     cin >> rhs;
    //     cout << ">> " << endl <<"ans =" << endl << endl;

    //     if (sym == '+'){
    //         ans = add(lhs,rhs);
    //     }
    //     else if (sym == '-'){
    //         ans = subtract(lhs,rhs);
    //     }
    //     else if (sym == '*'){
    //         ans = multiply(lhs,rhs);
    //     }
    //     cout << "    " << ans << endl  << endl;
    //     cin >> lhs;
    //     if (lhs == "quit" || lhs == "q"){
    //         cout << ">> " << endl << "farvel!" << endl << endl;
    //         return 0;
    //     }
    // }


   
    my_string str1;
    my_string str2;
    str1 = "10";
    str2 = "9";
    
    cout << (str1 != str2);
    

    cin >> str2;
    //my_string str3 = str1.insert(0,'0');
    //cout << str3;
   
//    //str1 = trim_leading_zeros(str1);
  //  cout << "trim leading zeros: " << str1 ;
//     //str1.push_back('0');
//     cout << "str1 + 0 " << str1;

}

