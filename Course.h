//
// Created by רוני on 01/01/2021.
//

#ifndef DS_WET2_COURSE_H
#define DS_WET2_COURSE_H

#include <iostream>
#include "Lesson.h"
#include "library2.h"

class Course{
private:
    int courseID;
    int numOfClasses;
    int lessons_array_size;
    Lesson** lessons;
public:
    Course* next;
    Course* prev;
    explicit Course(int courseID);
    ~Course();
    Course(const Course& course);
    Course& operator=(const Course& course);
    bool operator==(const Course& course);
    void print();
    int getNumOfClasses();
    int getLessonsArraySize();
    Lesson* getLessonPtr(int index); //will give us the pointer saved in index i of Lessons**
    void updateLessonArray(int classID, Lesson* updated_lesson_ptr);
    void addLesson();
    int getKey() const;
};

#endif //DS_WET2_COURSE_H
