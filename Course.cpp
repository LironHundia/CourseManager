//
// Created by רוני on 26/11/2020.
//

#include "Course.h"
#include <iostream>
#include "library2.h"
#include "Lesson.h"
using std::cout;
using std::endl;

Course::Course(int courseID) : courseID(courseID), numOfClasses(0), lessons_array_size(1), lessons(nullptr),
                                                 next(nullptr), prev(nullptr) {
    lessons = new Lesson*[lessons_array_size];
    for (int i=0; i<lessons_array_size; i++){
        lessons[i] = nullptr;
    }
}

Course::~Course(){
    delete[] lessons;
}

Course::Course(const Course& course) : courseID(course.courseID), numOfClasses(course.numOfClasses), lessons_array_size(course.lessons_array_size),
                                       lessons(nullptr), next(course.next), prev(course.prev) {
    lessons = new Lesson*[lessons_array_size];
    for (int i=0; i<lessons_array_size; i++){
        lessons[i] = course.lessons[i];
    }
}

Course& Course::operator=(const Course& course){
    if (this == &course){
        return *this;
    }
    delete[] lessons;
    lessons = new Lesson*[course.lessons_array_size];
    next = course.next;
    prev = course.prev;
    courseID = course.courseID;
    numOfClasses = course.numOfClasses;
    lessons_array_size = course.lessons_array_size;
    for (int i=0; i<lessons_array_size; i++){
        lessons[i] = course.lessons[i];
    }
    return *this;
}

bool Course::operator==(const Course& course){
    if (courseID == course.courseID){
        return true;
    }
    return false;
}

void Course::print(){
    std::cout << "Course number " << courseID << " with " << numOfClasses << " classes. Array size is: " << lessons_array_size << "." << std::endl;
    for(int i=0 ; i < lessons_array_size ;i++){
        if(lessons[i] == nullptr){
            cout <<"Lesson is null! for index "<< i << endl;
        }
        else {
            lessons[i]->print();
        }
    }
}

int Course::getNumOfClasses() {
    return numOfClasses;
}

int Course::getLessonsArraySize(){
    return lessons_array_size;
}

Lesson* Course::getLessonPtr(int index) {
    return lessons[index];
}

void Course::updateLessonArray(int classID, Lesson* updated_lesson_ptr){
    lessons[classID] = updated_lesson_ptr;
}

void Course::addLesson(){
    lessons[numOfClasses] = nullptr;
    numOfClasses++;
    if (numOfClasses == lessons_array_size){
        Lesson** new_lessons_array = new Lesson*[lessons_array_size*2];
        for (int i=0; i<lessons_array_size; i++){
            new_lessons_array[i] = lessons[i];
        }
        for (int i=lessons_array_size; i<lessons_array_size*2; i++){
            new_lessons_array[i] = nullptr;
        }
        delete[] lessons;
        lessons = new_lessons_array;
        lessons_array_size = lessons_array_size * 2;
    }
}

int Course::getKey() const{
    return courseID;
}