//
// Created by רוני on 31/12/2020.
//

#include "Lesson.h"
#include <iostream>
using std::cout;
using std::endl;

Lesson::Lesson(int time_watched, int courseID, int lessonID) : time_watched(time_watched), courseID(courseID), lessonID(lessonID),
                                                               top(nullptr), right(nullptr), left(nullptr), height(0), rank(1){} //Changed

Lesson::~Lesson(){}

Lesson::Lesson(const Lesson& lesson): time_watched(lesson.time_watched), courseID(lesson.courseID), lessonID(lesson.lessonID),
                                      top(lesson.top), right(lesson.right), left(lesson.left), height(lesson.height), rank(lesson.rank){} //Changed

Lesson& Lesson::operator=(const Lesson& lesson){
    if (this == &lesson){
        return *this;
    }
    top = lesson.top;
    right = lesson.right;
    left = lesson.left;
    time_watched = lesson.time_watched;
    courseID = lesson.courseID;
    lessonID = lesson.lessonID;
    height = lesson.height;
    rank = lesson.rank;
    return *this;
}

bool Lesson::operator<(const Lesson& lesson){
    if (time_watched > lesson.time_watched){
        return true;
    }
    else if (time_watched==lesson.time_watched && courseID < lesson.courseID){
        return true;
    }
    else if (time_watched==lesson.time_watched && courseID==lesson.courseID && lessonID < lesson.lessonID){
        return true;
    }
    return false;
}

bool Lesson::operator==(const Lesson& lesson){
//lessons are identical if their courseID and lessonID are equal
    if (courseID == lesson.courseID && lessonID == lesson.lessonID){
        return true;
    }
    return false;
}

void Lesson::updateTimeWatched(int time){
    time_watched += time;
}

void Lesson::print(){
    /*std::cout << " Watched for "<< time_watched << " minutes. of course number " << courseID << " class number " << lessonID <<
                " Height is: " << height << std::endl;*/
    cout << "lessonID: " << lessonID << ", courseID: " << courseID << ", time: " << time_watched << ", height: " << height << ", rank: " << rank << endl;
}

int Lesson::get_time(){
    return time_watched;
}

void Lesson::add_current_to_arrays(int* courses, int* classes, int* counter, int total_to_print){
    *courses = courseID;
    *classes = lessonID;
    (*counter)++;
}

void Lesson::get_details(int* course_id, int* class_id) {
    if (course_id == nullptr || class_id == nullptr){
        cout << "course_id or class_id pointers are set to null!" << endl;
        return;
    }
    *course_id = courseID;
    *class_id = lessonID;
}
