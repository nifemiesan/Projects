// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}
//   rule of "3"
//     my_string copy constructor
my_string::my_string(const my_string& other){
    _capacity = other._capacity;
    _size = other._size;
    delete[] _data;
    _data = new char[_size];
    for(unsigned int i = 0 ; i < _size ; i++){
        _data[i] = other._data[i];
    }
}
// c-string copy constructor
my_string::my_string(const char* other){

    if(other){
        _size = 0;
        while(other[_size] != '\0'){
            _size++;
        }
        delete[] _data;
        _data = new char[_size];
        for(unsigned int i = 0 ; i < _size ; i++){
            _data[i] = other[i];

        _capacity = _size;

    }
    else{
        _size = 0;
        _capacity = 0;
        _data = nullptr;
    }
}

//     destructor
my_string::~my_string(){
    delete[] _data;
    _size = 0;
    _capacity = 0;
    _data = nullptr;
}
//   copy assignement operator
my_string& my_string::operator=(const my_string& rhs){

    if(this != &rhs){
        delete[] _data;
        _data = new char[rhs._size];
        for(unsigned int i = 0 ; i < rhs._size ; i++){
            _data[i] = rhs._data[i];
        }
        _capacity = rhs._capacity;
        _size = rhs._size;
    }
    return *this;
}


void my_string::increasedatacapacity(){
    if(_capacity == 0){
        _capacity = 1;
        char* newdata = new char[_capacity];
        delete[] _data;
        _data= newdata;
        _size = 0;
        newdata = nullptr;
    }
    else{
        _capacity *= 2;
        char* newdata = new char[_capacity];
        for(unsigned int i = 0 ; i < _size ; i++){
            newdata[i] = _data[i];
        }
        delete[] _data;
        _data = newdata;
        newdata = nullptr;
    }
}

// element access
//   at
char& my_string::at(size_type index){
    if(index < _size){
        return _data[index];
    }
    else{
        throw std::invalid_argument("index is out of bounds");
    }
}
const char& my_string::at(size_type index) const{
    if(index < _size){
        return _data[index];
    }
    else{
        throw std::invalid_argument("index is out of bounds");
    }
}

my_string my_string::insert(size_type index , char charToInsert){
    if(index > _size){
        throw std::invalid_argument("index is out of bounds");
    }
    char* temparry = new char[_size + 1];
    for(unsigned int i = 0 ; i < index ; i++){
        temparry[i] = _data[i];
    }
    temparry[index] = charToInsert;
    for(unsigned int i = index ; i < _size ; i++){
        temparry[i+1] = _data[i];
    }
    _size++;
    _capacity = _size+1;
    delete[] _data;
    _data = temparry;
    temparry = nullptr;
    return _data;
}

my_string my_string::append(my_string stringToAppend){
    char* temparry = new char[stringToAppend._size + _size];
    for(unsigned int i = 0 ; i < _size ; i++){
        temparry[i] = _data[i]; 
    }
    for(unsigned int i = 0 ; i < stringToAppend._size ; i++){
        temparry[i + _size] = stringToAppend[i];
    }
    delete[] _data;
    _data = temparry;
    temparry = nullptr;
    _size += stringToAppend._size;
    _capacity = stringToAppend._size + _size;
    return _data;
}

my_string my_string::push_back(char charToPushback){
    if(_size == _capacity){
        increasedatacapacity();
    }
    _data[_size] = charToPushback;
    _size++;
    return _data;
}


//   operator[]

// capacity
//   empty
bool my_string::empty() const {
    if(_size == 0){
        return true;
    } 
    else{
        return false;
    }
}
//   size
my_string::size_type my_string::size() const{
     return _size;
}

// operations
//   concatenation
//     my_string + my_string (non-member, friend)
//     my_string + c-string (non-member, friend)
//     my_string + char (non-member, friend)
//     c-string + my_string (non-member, friend)
//     char + my_string (non-member, friend)
//     my_string += my_string
//     my_string += c-string
//     my_string += char

// search
//   find
my_string::size_type my_string::find_first_not_of(my_string x){
    for(unsigned int i = 0 ; i < _size ; i++){
        if(_data[i] != x._data[0]){
            return i;
        }
        else{
            for(unsigned int j = 0 ; j < x._size ; j++){
                if(_data[i+j] != x._data[j]){
                    return i +j;
                }
            }
        }
    }
    return -1;
}



char& my_string::operator[] (size_type index){
    return _data[index];
}

const char& my_string::operator[](size_type index) const{
    return _data[index];
}


std::ostream& operator<<(std::ostream& os, const my_string& str){
    
    if(str.size() > 0){
        for(unsigned int i = 0 ; i < str.size() ; i++){
            os << str[i];
        }
    }
    else{
        os << "";
    }
    return os;
}

std::istream& operator>>(std::istream& is, my_string& str){
   char ch;
  while (is.get(ch) && ch != '\n')
    str.push_back(ch);
  return is;
}



bool operator==(const my_string& lhs, const my_string& rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }
    for(unsigned int i = 0 ; i < lhs.size() ; i++){
        if(lhs.at(i) != rhs.at(i)){
            return false;
        }
    }
    return true;
}

bool operator==(const my_string& lhs, const char* rhs){
    return(lhs == my_string(rhs));
}

bool operator!=(const my_string& lhs, const char* rhs){
    return (!(lhs == my_string(rhs)));
}
bool operator!=(const my_string& lhs , const my_string& rhs){
    return (!(lhs == rhs));
}

my_string& my_string::operator+=(const my_string& rhs){
     char* temparry = new char[rhs._size + _size];
    for(unsigned int i = 0 ; i < _size ; i++){
        temparry[i] = _data[i]; 
    }
    for(unsigned int i = 0 ; i < rhs._size ; i++){
        temparry[i + _size] = rhs[i];
    }
    delete[] _data;
    _data = temparry;
    temparry = nullptr;
    _size += rhs._size;
    _capacity = rhs._size + _size;
    return *this;
}


  my_string& my_string::operator+=(char rhs){
      if(_size == _capacity){
        increasedatacapacity();
    }
    _data[_size] = rhs;
    _size++;
    return *this;
  }


// non-member functions
//   relational operators
//     my_string == my_string
//     my_string == c-string
//   stream operators
//     ostream instertion operator
//     istream extraction operator
//     getline
//   numeric conversions
//     to_string







// my_istringstream methods

my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
