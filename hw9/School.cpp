#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout , std::stoi;


void School::addCourses(std::string filename){
  ifstream fin(filename);
  if (!fin.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    istringstream ss(line);

    string id;
    getline(ss, id, ',');
    string startHour;
    getline(ss, startHour, ':');
    string startMin;
    getline(ss, startMin, ',');
    string endHour;
    getline(ss, endHour, ':');
    string endMin;
    getline(ss, endMin, ',');
    string title;
    getline(ss, title);



    if (!ss.fail()) {
      Date startTime(stoi(startHour), stoi(startMin));
      Date endTime(stoi(endHour), stoi(endMin));
      courses.push_back(Course(id, title, startTime, endTime));
    } 
  }
}

// one method is provided to students; students implement all other methods
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

bool School::isEnrolled(string student_id) const{
  for(int i = 0 ; i < students.size() ; i++){
    if(student_id == students.at(i).get_id()){
      return true;
    }
  }
  return false;
}


void School::listStudents(std::ostream& os) const{
  if (students.size() == 0) {
    os << "No students" << endl;
    return;
  }
  for (Student s : students) {
    os << s.get_id() << "," << s.get_name() << endl;
  }
}

void School::listCourses(std::ostream& os) const{
  if (courses.size() == 0) {
    os << "No courses" << endl;
    return;
  }
  for (Course c : courses) {
    os << c.getID() << "," << c.getStartTime().getTime(false) << "," 
      << c.getEndTime().getTime(false) << "," <<c.getTitle() << endl;
  }
}

unsigned int School::addAttendanceData(string filename)
{
	bool course_isValid = false;
	bool student_isValid = false;
	bool date_isValid ;
	unsigned int numInvalid = 0;
	ifstream ifs(filename);
	if( !ifs.is_open() )
	{
		throw std::invalid_argument("unable to open file");
	}

	while ( !ifs.eof() )
	{
		string line;
		getline(ifs, line);
		istringstream SS(line);

		string year;
		getline(SS, year, '-');

		string month;
		getline(SS, month, '-');

		string day;
		getline(SS, day, ' ');

		string hour;
		getline(SS, hour, ':');

		string min;
		getline(SS, min, ':');

		string sec;
		getline(SS, sec, ',');

		string course_id;
		getline(SS, course_id, ',');
		string student_id;
		getline(SS, student_id);
		// check if course_id data is valid
    //cout <<courses.size() << endl;;

		if ( !SS.fail() ){
		for (Course C : courses)
		{
     // cout << C.getID() << " == " << course_id << endl;
			if (C.getID() == course_id)
			{
				course_isValid = true;
			}
		}

		// check if student_id data is valid
		for (Student S : students)
		{
			if (S.get_id() == student_id)
			{
				student_isValid = true;
			}
		}

		// check if date data is valid
		Date D(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec) );
		if ( D.isValid() )
		{
			date_isValid = true;
		}
    //cout << course_isValid << student_isValid << date_isValid << endl;
		if ( !(course_isValid && student_isValid && date_isValid) )		// if any data is invalid
		{
			numInvalid++;
			throw std::invalid_argument("did not save this record");
		}
			for (Course& C : courses)
			{
				if (C.getID() == course_id)
				{
         // cout << "this works!!!!" << endl;
					C.addAttendanceRecord(AttendanceRecord(course_id, student_id, Date(stoi(year), stoi(month), stoi(day),
						stoi(hour), stoi(min), stoi(sec))));
						break;
				}
			}
		}

	}

	return numInvalid;
}


void School::outputCourseAttendance(std::ostream& os, std::string course_id) const {
  bool found = false;
	for (Course C : courses)
	{
		if (C.getID() == course_id)
		{
			C.outputAttendance(os);
			found = true;
			break;
		}
	}

	if (!found)
	{
		throw std::invalid_argument("No records");
	}
}

void School::outputStudentAttendance(ostream& os, string student_id, string course_id) const {
  bool found = false;
	for (Course C : courses){
		if (C.getID() == course_id){
			C.outputAttendance(os, student_id);
			found = true;
			break;
		}
	}

	if (!found){
		throw std::invalid_argument("No records");
	}
}