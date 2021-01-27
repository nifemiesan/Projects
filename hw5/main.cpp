#include <iostream>
#include <fstream>
#include <string>
#include "taxi_trips.h"
using namespace std;

int main() {

  // TODO(student): implement
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  ifstream ifs;
  ifs.open(filename);
  if(!ifs.is_open()){
    cout << "Can't open " << filename;
    return 1;
  }
  string taxi_id[MAX_TRIPS];
  double trip_seconds[MAX_TRIPS];
  double trip_miles[MAX_TRIPS];
  double trip_fare[MAX_TRIPS];
  double trip_tip[MAX_TRIPS];
  string payment_type[MAX_TRIPS];
  
  string taxi_idin;
  double trip_secondsin;
  double trip_milesin;
  double trip_farein;
  double trip_tipin;
  string payment_typein;
  bool inputdata = true;
  int sz = 0;
  string valid_types[4] = {"CreditCard", "Cash" , "NoCharge", "Unknown"};
  int numinvalid;
  while(!ifs.eof()){
    inputdata = true;
    ifs >> taxi_idin;
    ifs >> trip_secondsin;
    ifs >> trip_milesin;
    ifs >> trip_farein;
    ifs >> trip_tipin;
    ifs >> payment_typein;
   // cout << "Input: " << taxi_idin << " " << trip_secondsin << " " << trip_milesin << " " << trip_farein << " " << trip_tipin << " " << payment_typein << endl;
    if(trip_secondsin > (24 * 60 * 60)){
      inputdata = false;
    }
    else if(trip_milesin > 1500){
      inputdata = false;
    }
    else if((trip_farein + trip_tipin) > 5000){
      inputdata = false;
    } 
    else if(!is_payment_valid(payment_typein,valid_types , 4)){
      inputdata = false;
    }
    else if (trip_secondsin + trip_milesin == 0 && trip_farein != 0){
      inputdata = false;
    }
    else{
      inputdata = true;
    }
    //cout << "true or false: " << inputdata << endl;
    if (inputdata == true){
      taxi_id[sz] = taxi_idin;
      trip_seconds[sz] = trip_secondsin;
      trip_miles[sz] = trip_milesin; 
      trip_fare[sz] = trip_farein;
      trip_tip[sz] = trip_tipin;
      payment_type[sz] = payment_typein;
      sz++;
    }
    else{
      numinvalid++;
    }
  }

cout << "Number of trips: " << sz << endl;
cout << "Number of trips with invalid data: " << numinvalid << endl;
cout << "Duration: max " << max(trip_seconds, sz) << " min " << min(trip_seconds, sz) << " avg " << average(trip_seconds, sz)  << " mode " << mode(trip_seconds,sz) << endl;
cout << "Distance: max " << max(trip_miles, sz) << " min " << min(trip_miles, sz) << " avg " << average(trip_miles, sz)  << " mode " << mode(trip_miles,sz) << endl;
cout << "Fare: max " << max(trip_fare, sz) << " min " << min(trip_fare, sz) << " avg " << average(trip_fare, sz)  << " mode " << mode(trip_fare,sz) << endl;
cout << "Tip: max " << max(trip_tip, sz) << " min " << min(trip_tip, sz) << " avg " << average(trip_tip, sz)  << " mode " << mode(trip_tip,sz) << endl;
cout << "Length of longest sequence without tips: " << length_longest_seq_zeros(trip_tip, sz) << endl;
  return 0;
}