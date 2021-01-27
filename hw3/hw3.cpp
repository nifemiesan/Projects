#include <iostream>
#include <cstdlib>
using namespace std;

int SumBetween(int low, int high) {
  int value = 0;
  if (low > high){
    throw std::invalid_argument("low is greater that high");
  }
  std::cout << "Low: " << low << std::endl;
  std::cout << "High: " << high << std::endl;
  if (abs(low) > high ){
      for(int n = low; n <= -(high +1) ; n++){
          value +=n;
      }
    
    if (value < INT32_MIN - low){
        throw std::overflow_error("overflow error");
    }
    if (value > INT32_MAX -  high){
        throw std::overflow_error("overflow error");
    }
  }

  else
  {
      for(int n = -(low-1) ; n <= high ; n++)
      value += n;
       if (value < INT32_MIN - low){
        throw std::overflow_error("overflow error");
    }
      if (value > INT32_MAX -  high){
        throw std::overflow_error("overflow error");
    }

  }
  
  
  return value;
}
