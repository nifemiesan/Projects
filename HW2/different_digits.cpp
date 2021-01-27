#include <iostream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
    // TODO(student): print prompt for input
    cout << "Enter numbers 0 < a <= b <= 10000: ";
    // TODO(student): read the numbers from standard input
    int a = 0; 
    int b = 0;
    cin >> a;
    cin >> b;
    // TODO(student): validate input (and reprompt on invalid input)
   while (is_valid_range(a,b) == false){
    cout << "Invalid input" << endl;
    cout << "Enter numbers 0 < a <= b <= 10000: ";
    cin >> a;
    cin >> b;
   }
   
    // TODO(student): compute and display solution
    int validnum = count_valid_numbers(a , b);
    cout << "There are " << validnum << " valid numbers between " << a << " and " << b << endl;
    return 0;
}
