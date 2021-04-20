//
// Created by רוני on 04/01/2021.
//

#ifndef DS_WET2_COURSEMANAGER_H
#define DS_WET2_COURSEMANAGER_H

#include "HashTable.h"
#include "List.h"
#include "library2.h"
#include "Course.h"
#include "Lesson.h"
#include "AVLTree.h"

class CourseManager{
private:
    HashTable<Course> courses_table;
    AVLTree<Lesson> lessons_tree;
public:
    CourseManager() = default;
    ~CourseManager() = default;
    CourseManager(const CourseManager& cm) = default;
    CourseManager& operator=(const CourseManager& cm) = default;

    StatusType AddCourse(int courseID);
    StatusType RemoveCourse(int courseID);
    StatusType AddClass(int courseID, int* classID);
    StatusType WatchClass(int courseID, int classID, int time);
    StatusType TimeViewed(int courseID, int classID, int *timeViewed);
    StatusType GetIthWatchedClass(int i, int* courseID, int* classID);
};

#endif //DS_WET2_COURSEMANAGER_H
