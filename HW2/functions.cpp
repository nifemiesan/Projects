#include "functions.h"

bool is_valid_range(int a, int b) {
// TODO(student): validate input range
    if (0 > a || a > b || b > 10000){
        return false;
    }
    else{
        return true;
    }
}

int count_digit_occurrences(int number, int digit) {
  // TODO(student): return how many times digit occurs in number
   int cnt = 0;
	
	while (number > 0) {
		if (number % 10 == digit) {
			cnt++;
		}
		number /= 10;
	}
	return cnt;
}

bool has_repeated_digits(int number) {
    // TODO(student): return true if number has repeated digits
    for (int i = 0 ; i < 10; i++){
        if( count_digit_occurrences(number, i) > 1 ){
            return true;
        }
    }
    return false;
}

int count_valid_numbers(int a, int b) {
    // TODO(student): return count of valid numbers in range

    int cnt = 0;
    for (int i = a; i <= b ; i++){
        if (has_repeated_digits(i) == true){
            cnt += 1;
        }
    }
    return cnt;
}
