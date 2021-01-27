#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;

Course::Course(string id, string title, Date startTime, Date endTime) : 
  id(id), title(title), startTime(startTime), endTime(endTime) {}

void Course::addAttendanceRecord(AttendanceRecord ar) {
    // cout << "ar.getDate() >= startTime" << (ar.getDate() >= startTime) << endl;
    // cout << (ar.getDate() <= endTime) << endl;
    // cout << "start  ar end " << startTime.getHour() << " " << startTime.getMin() << endl;
    // cout << ar.getDate().getHour() << " " << ar.getDate().getMin() << endl;
    // cout <<  endTime.getHour() << " " << endTime.getMin() << endl;
    if (ar.getDate() >= startTime && ar.getDate() <= endTime){
        attendanceRecords.push_back(ar);
    }
    else{
        throw std::invalid_argument("did not save record");
    }
    
}



void Course::outputAttendance(ostream& os) const {
  if (attendanceRecords.empty()) {
    os << "No records" << endl;
    return;
  }
  for (AttendanceRecord ar : attendanceRecords) {
      os << ar.getDate().getDateTime() << "," << ar.getCourseID() 
      << "," << ar.getStudentID() << endl;
  }
} 

void Course::outputAttendance(ostream& os, string student_id) const{
    if (attendanceRecords.empty()){
        os << "No records" << endl;
        return;
    }
    bool recordsForStudent = false;
  for (AttendanceRecord ar : attendanceRecords) {
    if (ar.getStudentID() == student_id) {
      os << ar.getDate().getDateTime() << "," << ar.getCourseID() << "," << ar.getStudentID() << endl;
      recordsForStudent = true;
    }
  }
  if (!recordsForStudent) {
    os << "No records" << endl;
  }
}

std::ostream& operator<<(std::ostream& os , const Course& c){
     if (c.attendanceRecords.empty()){
        os << "No records" << endl;
    }
    else{

        bool recordsForStudent = false;
        for (AttendanceRecord ar : c.attendanceRecords) {
            if (ar.getStudentID() == c.id) {
                os << ar.getDate().getDateTime() << "," << ar.getCourseID() << "," << ar.getStudentID() << endl;
                recordsForStudent = true;
            }
        }
        if (!recordsForStudent) {
            os << "No records" << endl;
        }
    }
    return os;
}