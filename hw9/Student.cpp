#include <iostream>
#include <string>
#include "Student.h"

using std::cout, std::endl;

Student::Student(std::string student_id, std::string name){
    id = student_id;
    this->name = name;
}

std::string Student::get_id() const{
    return id;
}

std::string Student::get_name() const{
    return name;
}

void Student::addCourse(std::string course_id){
    for(int i = 0 ; i < course_ids.size() ; i++){
        if (course_ids.at(i) == course_id){
            throw std::invalid_argument("course is a duplicate");
        }
    }
    course_ids.push_back(course_id);
}

void Student::listCourses(std::ostream& os) const{
    os << "Courses for " << id << endl;
    if(course_ids.size() > 0){
        for(int i = 0 ; i < course_ids.size() ; i++){
            os << course_ids.at(i) << endl;
        }
        
    }
    else{
        os << "No courses" << endl;
    }
}


std::ostream& operator<<(std::ostream& os , const Student& s){
    //implement
        os << "Courses for " << s.id << endl;
    if(s.course_ids.size() > 0){
        for(int i = 0 ; i < s.course_ids.size() ; i++){
            os << s.course_ids.at(i) << endl;
        }
        
    }
    else{
        os << "No courses" << endl;
    }
    return os;
}