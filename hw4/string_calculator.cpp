#include <iostream>
#include <string>
#include "./string_calculator.h"


using namespace std;

unsigned int digit_to_decimal(char digit) {
    double decimal;
    decimal = digit - 48;
    if (decimal < 0 || decimal > 9){
        throw invalid_argument("value entered is not a number");
    }
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    char digit;
    if (decimal > 9)
    {
        throw invalid_argument("Number is outside of bounds");
    }
    
    digit = decimal + 48;
    return digit;
}

string trim_leading_zeros(string num) {
    string newnum;
    string posnon0; //positive non 0 numbers
  
    int firstnon0;
    firstnon0 = num.find_first_not_of("-0");
    if(firstnon0 == string::npos){
        return "0";
    }
    posnon0 = num.substr(firstnon0, num.size() - firstnon0);
    if(num.at(0) == '-'){
        newnum = '-';
        newnum.append(posnon0);
    }
    else{
        newnum = posnon0;
    }
  return newnum;
}

string add(string lhs, string rhs) {
    string final = "";
    int size;
    // getting size of empty string
    if(lhs.at(0) == '-' && rhs.at(0) != '-'){
        lhs.at(0) = '0';
        return subtract(rhs, lhs);
    }
    else if(rhs.at(0) == '-' && lhs.at(0) != '-'){
        rhs.at(0) = '0';
        return subtract(lhs, rhs);
    }
    bool bothnegative = false;
    if(lhs.at(0) == '-' && rhs.at(0) == '-'){
        rhs.at(0) = '0';
        lhs.at(0) = '0';
        bothnegative = true;
    }
    if (lhs.size() > rhs.size()){
        size = lhs.size();
        while(lhs.size() != rhs.size()){
            rhs.insert(0,"0");
        }
    }
    else{
        size = rhs.size();
        while (rhs.size() != lhs.size()){
            lhs.insert(0,"0");
        }
    }
    // intinializing final string to string of 0's with size 1 more than size of highest number
    for (int i = 0; i < size + 1; i++){
        final.push_back('0');
    }
   
    // calculating sum
    for (int i = size -1 ; i >= 0 ; i--){
        int lhsval = digit_to_decimal(lhs.at(i));
        //cout << "lhsval: " << lhsval << endl;
        int rhsval = digit_to_decimal(rhs.at(i));
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
        final.insert(0,"-");
    }
    return trim_leading_zeros(final);
}

string subtract(string lhs, string rhs) {
    // equalize size of strings
    // checking if lhs is negative and rhs is positive
    if (lhs.at(0) == '-' && rhs.at(0) != '-'){
        lhs.at(0) = '0';
        string sum = add(lhs, rhs);
        sum.insert(0,"-");
        return sum;
    }
    // case where lhs is positive and rhs is negative
    if (lhs.at(0) != '-' && rhs.at(0) == '-'){
        rhs.at(0) = '0';
        string sum = add(lhs, rhs);
        return sum;
    }
    // case wjere lhs and rhs are both negative
    if(lhs.at(0) == '-' && rhs.at(0) == '-'){
        lhs.at(0) = '0';
        rhs.at(0) = '0';
        return subtract(rhs, lhs);
    }
    if (lhs.size() > rhs.size()){
        while(lhs.size() != rhs.size()){
            rhs.insert(0,"0");
        }
    }
    else{
        while (rhs.size() != lhs.size()){
            lhs.insert(0,"0");
        }
    }
    // cout << "lhs:" << lhs << endl;
    // cout << "rhs:" << rhs << endl;
    // create string of 0's
    string final = "";
    for( unsigned int i = 0 ; i < lhs.size(); i++){
        final.push_back('0');
    }
    // find which value is greater;
    bool lhsgreater = true;
    for (unsigned int i = 0 ; i < lhs.size(); i ++){
        if (digit_to_decimal(lhs.at(i)) > digit_to_decimal(rhs.at(i))){
            lhsgreater = true;
            break;
        }
        else if (digit_to_decimal(rhs.at(i)) > digit_to_decimal(lhs.at(i))){
            lhsgreater = false;
            break;
        }
    }
   // cout << "lhs>" << lhsgreater << endl;
    if (lhsgreater == 1){
        for(int i = lhs.size() - 1; i >= 0; i--){
           //cout << "I: " << i << endl;
            int lhsval = digit_to_decimal(lhs.at(i));
            int rhsval = digit_to_decimal(rhs.at(i));
            int sub;
            if (lhsval >= rhsval){
                sub = lhsval - rhsval;
                //cout << "sub" << sub << endl;
                final.at(i) = decimal_to_digit(sub);
            }
            else{
                unsigned int j = 1;
                //cout << "problem is here!!!!!!!!!!!" << endl;
                if (lhs.at(i-j) == '0'){
                    //cout << "this is executed" << endl;
                    while(lhs.at(i-j) == '0'){
                        lhs.at(i-j) = '9';
                        j++;
                        //cout << "j: " << j << endl;
                        //cout << "i: " << i << endl;
                    }
                    // cout << "ran" << endl;
                }
                //cout << "lhs at i- j " << lhs.at(i-j);
                lhs.at(i-j) = decimal_to_digit(digit_to_decimal(lhs.at(i-j)) -1);
                lhsval = digit_to_decimal(lhs.at(i));
                sub = lhsval - rhsval + 10;
                final.at(i) = decimal_to_digit(sub);
            }
        }
    }
    else{
        for(int i = lhs.size() - 1; i >= 0; i--){
            int lhsval = digit_to_decimal(lhs.at(i));
            int rhsval = digit_to_decimal(rhs.at(i));
            int sub;
            if (rhsval >= lhsval){
                sub = rhsval - lhsval;
                final.at(i) = decimal_to_digit(sub);
                //cout << "final:" << final << endl;
            }
                else{
                unsigned int j = 1;
                //cout << "problem is here!!!!!!!!!!!" << endl;
                if (rhs.at(i-j) == '0'){
                    //cout << "this is executed" << endl;
                    while(rhs.at(i-j) == '0'){
                        rhs.at(i-j) = '9';
                        j++;
                        //cout << "j: " << j << endl;
                        //cout << "i: " << i << endl;
                    }
                    // cout << "ran" << endl;
                }
                //cout << "lhs at i- j " << lhs.at(i-j);
                rhs.at(i-j) = decimal_to_digit(digit_to_decimal(rhs.at(i-j)) -1);
                rhsval = digit_to_decimal(rhs.at(i));
                sub = rhsval - lhsval + 10;
                final.at(i) = decimal_to_digit(sub);
            }
        }
        final.insert(0,"-");
    }
    
    
    return trim_leading_zeros(final);
}

string multiply(string lhs, string rhs) {
    string total = "0";
    int mult;
    int tempzero = 0;
    int carry = 0;
    bool negative = false;
    if ((rhs.at(0) != '-') && (lhs.at(0) == '-')){
        negative = true;
        lhs.at(0) = '0';
        
    }
    else if ((rhs.at(0) == '-') && (lhs.at(0) != '-')){
        negative = true;
        rhs.at(0) = '0';
    }
    else if ((rhs.at(0) == '-') && (lhs.at(0) == '-')){
        negative = false;
        rhs.at(0) = '0';
        lhs.at(0) = '0';
    }
    else{
        negative = false;
    }
    //cout << "lhs " << lhs << endl;
    //cout << "rhs " << rhs << endl;
     if (lhs.size() > rhs.size()){
        while(lhs.size() != rhs.size()){
            rhs.insert(0,"0");
        }
    }
    else{
        while (rhs.size() != lhs.size()){
            lhs.insert(0,"0");
        }
    }
   for (int i = lhs.size()-1; i >= 0; i--){
       string temp = "";
       for (int i = 0 ; i < tempzero ; i++){
           temp.append("0");
       }
       carry = 0;
       for (int k = rhs.size() -1 ; k >= 0 ; k--){
           if (k != 0){
            mult = digit_to_decimal(lhs.at(k)) * digit_to_decimal(rhs.at(i)) + carry;
            //cout << "multiplying: " << lhs.at(k) << " * " << rhs.at(i) << " + " << carry;
            int store = mult % 10;
            temp.insert(0,1,decimal_to_digit(store));
            carry = (mult - store)/ 10;
            if (mult < 10 ){
                carry = 0;
            }
           }
           else{
               mult = digit_to_decimal(lhs.at(k)) * digit_to_decimal(rhs.at(i)) + carry;
               //cout << "multiplying: " << lhs.at(k) << " * " << rhs.at(i) << " + " << carry;
               int store = mult % 10;
               temp.insert(0,1,decimal_to_digit(store));
               carry = (mult - store) / 10;
               temp.insert(0,1,decimal_to_digit(carry));
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
       total.insert(0,"-");
   }
    return total;
}
