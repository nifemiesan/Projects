#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout , std::string, std::ostream;


AttendanceRecord::AttendanceRecord(string course_id, string student_id, Date time) :
    course_id(course_id), student_id(student_id), time(time) {}

ostream& operator<<(ostream& os, const AttendanceRecord& Ar){
    os << Ar.getDate().getMonth() << "-" << Ar.getDate().getDay() << "-" <<Ar.getDate().getYear() << " "
    << Ar.getDate().getHour() << ":" << Ar.getDate().getMin() << ":" << Ar.getDate().getSec()
    << "," << Ar.getCourseID() << "," << Ar.getStudentID() << std::endl;
    return os;
}