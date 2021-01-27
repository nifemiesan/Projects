#include <stdexcept>
#include <string>
using namespace std;
#include "taxi_trips.h"


bool is_payment_valid(string type, string valid_types[], unsigned int size) {
  // TODO(student): implement
  if (size <= 0){
    throw invalid_argument("size cannot be zero");
  }
  for(unsigned int i = 0; i < size; i++){
    if(type == valid_types[i]){
      return true;
    }
  }
  return false;
}

double max(double values[], unsigned int size) {
  // TODO(student): implement
  if (size <= 0){
    throw invalid_argument("size cannot be zero");
  }
  double max = values[0];
  for(unsigned int i = 0; i < size ; i++){
    if (values[i] > max){
      max = values[i];
    }
  }
  return max;
}

double min(double values[], unsigned int size) {
  // TODO(student): implement
   if (size <= 0){
    throw invalid_argument("size cannot be zero");
  }
  double min = values[0];
  for(unsigned int i = 0; i < size ; i++){
    if (values[i] < min){
      min = values[i];
    }
  }
  return min;
}

double average(double values[], unsigned int size) {
  // TODO(student): implement
  if (size <= 0){
    throw invalid_argument("size cannot be zero");
  }
  double sum = 0 ;
  for(unsigned int i = 0; i < size ; i++){
    sum += values[i];
  }
double avg = sum / size;
  return avg;
}

double mode(double values[], unsigned int size) {
  // TODO(student): implement
  if (size <= 0){
    throw invalid_argument("size must be greater than zero");
  }
  int maxcnt = 0;
  int cnt = 0;
  double val = 0;
  double mode = 0;
  for (unsigned int i = 0 ; i < size; i++){
    val = values[i];
    cnt = 0;
    for(unsigned int j = 0 ; j < size ; j++){
      if (val == values[j]){
        cnt++;
      }
    }
    if(cnt > maxcnt){
      maxcnt = cnt;
      mode = val;
    }
  }
  return mode;
}

unsigned int length_longest_seq_zeros(double values[], unsigned int size) {
  // TODO(student): implement
  if (size <= 0){
    throw invalid_argument("size canno be zero");
  }
  int maxzero = 0;
  int zerocnt = 0;
  for(unsigned int i = 0; i < size ; i++){
    if(values[i] == 0){
      zerocnt++;
      
      if(zerocnt > maxzero){
        maxzero = zerocnt;
      }
    }
    else{
      zerocnt = 0;
    }
  }

  return maxzero;
}