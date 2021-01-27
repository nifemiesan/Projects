// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl , std::invalid_argument;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): put your existing implementation here
    double decimal;
    decimal = digit - 48;
    if (decimal < 0 || decimal > 9){
        throw invalid_argument("value entered is not a number");
    }
    return decimal;
    return 0;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): put your existing implementation here
    char digit;
    if (decimal > 9)
    {
        throw invalid_argument("Number is outside of bounds");
    }
    
    digit = decimal + 48;
    return digit;
    return '\0';
}

my_string trim_leading_zeros(const my_string& num) {
    // TODO(student): put your existing implementation here
   my_string newstring;
    unsigned int pos = 0;
    if (num.at(0) == '0'){ 
        while ( (num.at(pos) == '0')){
            pos++; 
            if (pos == num.size()){
                return "0";
            };
        }

        for (unsigned int j = pos; j < num.size(); j++){
            newstring.push_back(num.at(j));
        }
    }
    else if (num.at(0) == '-'){
        newstring.push_back('-');
        if (num.at(1) == '0'){
            pos = 1;
            while (num.at(pos) == '0' ){
                pos++; 
                if (pos == num.size()){
                    return "0";
                }
            }
            for (unsigned int j = pos; j < num.size(); j++){
                newstring.push_back(num.at(j));
            } 
        }
        else{ 
            for (unsigned int i = 1; i < num.size(); i++){
                newstring.push_back(num.at(i));
            }
        }
    }
    else{
        for (unsigned int i = 0; i < num.size(); i++){
            newstring.push_back(num.at(i));
        }
    }
    return newstring;
}
my_string add(const my_string& lhs,const my_string& rhs) {
    // TODO(student): put your existing implementation here
    my_string copylhs = lhs;
    my_string copyrhs = rhs;
    my_string final = "";
    int size;
    // getting size of empty string
    if(copylhs.at(0) == '-' && copyrhs.at(0) != '-'){
        copylhs.at(0) = '0';
        return subtract(copyrhs, copylhs);
    }
    else if(copyrhs.at(0) == '-' && copylhs.at(0) != '-'){
        copyrhs.at(0) = '0';
        return subtract(copylhs, copyrhs);
    }
    bool bothnegative = false;
    if(copylhs.at(0) == '-' && copyrhs.at(0) == '-'){
        copyrhs.at(0) = '0';
        copylhs.at(0) = '0';
        bothnegative = true;
    }
    if (copylhs.size() > copyrhs.size()){
        size = copylhs.size();
        while(copylhs.size() != copyrhs.size()){
            copyrhs.insert(0,'0');
        }
    }
    else{
        size = copyrhs.size();
        while (copyrhs.size() != copylhs.size()){
            copylhs.insert(0,'0');
        }
    }
    // intinializing final string to string of 0's with size 1 more than size of highest number
    for (int i = 0; i < size + 1; i++){
        final.push_back('0');
    }
   
    // calculating sum
    for (int i = size -1 ; i >= 0 ; i--){
        int lhsval = digit_to_decimal(copylhs.at(i));
        //cout << "lhsval: " << lhsval << endl;
        int rhsval = digit_to_decimal(copyrhs.at(i));
        //cout << "rhsval:: " << rhsval << endl;
        int sum = lhsval + rhsval + digit_to_decimal(final.at(i +1));
        //cout << "sum: " << sum << endl;
        int tensplace = 0; //tens place
        if (sum > 9){
            sum = sum -10;
            final.at(i + 1) = decimal_to_digit(sum);
            tensplace = digit_to_decimal(final.at(i)) + 1;
            //cout << "tens place:" << tensplace << "i: " << i << endl;
            final.at(i) = decimal_to_digit(tensplace);
        }
        else{
        final.at(i+1) = decimal_to_digit(sum) ;
        }
    } 
    if (bothnegative == true){
        final.insert(0,'-');
    }
    return trim_leading_zeros(final);
}

my_string subtract(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
  // equalize size of strings
    // checking if lhs is negative and rhs is positive
    my_string copylhs = lhs;
    my_string copyrhs = rhs;

    if (copylhs.at(0) == '-' && copyrhs.at(0) != '-'){
        copylhs.at(0) = '0';
        my_string sum = add(copylhs, copyrhs);
        //cout <<"in function lhs: " << copylhs << " rhs: " << copyrhs << endl;
        //cout << "sum: " << sum << endl;
        sum.insert(0,'-');
        return sum;
    }
    // case where lhs is positive and rhs is negative
    if (copylhs.at(0) != '-' && copyrhs.at(0) == '-'){
        copyrhs.at(0) = '0';
        my_string sum = add(copylhs, copyrhs);
        return sum;
    }
    // case wjere lhs and rhs are both negative
    if(copylhs.at(0) == '-' && copyrhs.at(0) == '-'){
        copylhs.at(0) = '0';
        copyrhs.at(0) = '0';
        return subtract(copyrhs, copylhs);
    }
    if (copylhs.size() > copyrhs.size()){
        while(copylhs.size() != copyrhs.size()){
            copyrhs.insert(0,'0');
        }
    }
    else{
        while (copyrhs.size() != copylhs.size()){
            copylhs.insert(0,'0');
        }
    }
    // cout << "lhs:" << lhs << endl;
    // cout << "rhs:" << rhs << endl;
    // create string of 0's
    my_string final = "";
    for( unsigned int i = 0 ; i < copylhs.size(); i++){
        final.push_back('0');
    }
    // find which value is greater;
    bool lhsgreater = true;
    for (unsigned int i = 0 ; i < copylhs.size(); i ++){
        if (digit_to_decimal(copylhs.at(i)) > digit_to_decimal(copyrhs.at(i))){
            lhsgreater = true;
            break;
        }
        else if (digit_to_decimal(copyrhs.at(i)) > digit_to_decimal(copylhs.at(i))){
            lhsgreater = false;
            break;
        }
    }
   // cout << "lhs>" << lhsgreater << endl;
    if (lhsgreater == 1){
        for(int i = copylhs.size() - 1; i >= 0; i--){
           //cout << "I: " << i << endl;
            int lhsval = digit_to_decimal(copylhs.at(i));
            int rhsval = digit_to_decimal(copyrhs.at(i));
            int sub;
            if (lhsval >= rhsval){
                sub = lhsval - rhsval;
                //cout << "sub" << sub << endl;
                final.at(i) = decimal_to_digit(sub);
            }
            else{
                unsigned int j = 1;
                //cout << "problem is here!!!!!!!!!!!" << endl;
                if (copylhs.at(i-j) == '0'){
                    //cout << "this is executed" << endl;
                    while(copylhs.at(i-j) == '0'){
                        copylhs.at(i-j) = '9';
                        j++;
                        //cout << "j: " << j << endl;
                        //cout << "i: " << i << endl;
                    }
                    // cout << "ran" << endl;
                }
                //cout << "lhs at i- j " << lhs.at(i-j);
                copylhs.at(i-j) = decimal_to_digit(digit_to_decimal(copylhs.at(i-j)) -1);
                lhsval = digit_to_decimal(copylhs.at(i));
                sub = lhsval - rhsval + 10;
                final.at(i) = decimal_to_digit(sub);
            }
        }
    }
    else{
        for(int i = copylhs.size() - 1; i >= 0; i--){
            int lhsval = digit_to_decimal(copylhs.at(i));
            int rhsval = digit_to_decimal(copyrhs.at(i));
            int sub;
            if (rhsval >= lhsval){
                sub = rhsval - lhsval;
                final.at(i) = decimal_to_digit(sub);
                //cout << "final:" << final << endl;
            }
                else{
                unsigned int j = 1;
                //cout << "problem is here!!!!!!!!!!!" << endl;
                if (copyrhs.at(i-j) == '0'){
                    //cout << "this is executed" << endl;
                    while(copyrhs.at(i-j) == '0'){
                        copyrhs.at(i-j) = '9';
                        j++;
                        //cout << "j: " << j << endl;
                        //cout << "i: " << i << endl;
                    }
                    // cout << "ran" << endl;
                }
                //cout << "lhs at i- j " << lhs.at(i-j);
                copyrhs.at(i-j) = decimal_to_digit(digit_to_decimal(copyrhs.at(i-j)) -1);
                rhsval = digit_to_decimal(copyrhs.at(i));
                sub = rhsval - lhsval + 10;
                final.at(i) = decimal_to_digit(sub);
            }
        }
        final.insert(0,'-');
    }
    
    
    return trim_leading_zeros(final);
}

my_string multiply(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    my_string total = "0";
    my_string copylhs = lhs;
    my_string copyrhs = rhs;
    int mult;
    int tempzero = 0;
    int carry = 0;
    bool negative = false;
    if ((copyrhs.at(0) != '-') && (copylhs.at(0) == '-')){
        negative = true;
        copylhs.at(0) = '0';
        
    }
    else if ((copyrhs.at(0) == '-') && (copylhs.at(0) != '-')){
        negative = true;
        copyrhs.at(0) = '0';
    }
    else if ((copyrhs.at(0) == '-') && (copylhs.at(0) == '-')){
        negative = false;
        copyrhs.at(0) = '0';
        copylhs.at(0) = '0';
    }
    else{
        negative = false;
    }
    //cout << "lhs " << lhs << endl;
    //cout << "rhs " << rhs << endl;
     if (copylhs.size() > copyrhs.size()){
        while(copylhs.size() != copyrhs.size()){
            copyrhs.insert(0,'0');
        }
    }
    else{
        while (copyrhs.size() != copylhs.size()){
            copylhs.insert(0,'0');
        }
    }
   for (int i = copylhs.size()-1; i >= 0; i--){
       my_string temp = "";
       for (int i = 0 ; i < tempzero ; i++){
           temp.append("0");
       }
       carry = 0;
       for (int k = copyrhs.size() -1 ; k >= 0 ; k--){
           if (k != 0){
            mult = digit_to_decimal(copylhs.at(k)) * digit_to_decimal(copyrhs.at(i)) + carry;
            //cout << "multiplying: " << lhs.at(k) << " * " << rhs.at(i) << " + " << carry;
            int store = mult % 10;
            temp.insert(0,decimal_to_digit(store));
            carry = (mult - store)/ 10;
            if (mult < 10 ){
                carry = 0;
            }
           }
           else{
               mult = digit_to_decimal(copylhs.at(k)) * digit_to_decimal(copyrhs.at(i)) + carry;
               //cout << "multiplying: " << lhs.at(k) << " * " << rhs.at(i) << " + " << carry;
               int store = mult % 10;
               temp.insert(0,decimal_to_digit(store));
               carry = (mult - store) / 10;
               temp.insert(0,decimal_to_digit(carry));
               if(mult < 10){
                   carry = 0 ; 
               }
           }
          // cout << " multipy at k" << mult << " at " << k << endl;
       }
      // cout << "temp" << temp << endl;
       tempzero++;
       total = add(total, temp);
   }
   if (negative == true){
       total.insert(0,'-');
   }
    return total;
}
