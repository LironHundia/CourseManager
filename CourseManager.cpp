//
// Created by רוני on 04/01/2021.
//

#include "CourseManager.h"
#include "library2.h"
#include "Course.h"
#include "Lesson.h"
#include "AVLTree.h"
#include "List.h"

StatusType CourseManager::AddCourse(int courseID){
    if (courseID <= 0){
        return INVALID_INPUT;
    }
    Course new_course(courseID);
    StatusType result = courses_table.add(new_course);
    return result;
}

StatusType CourseManager::RemoveCourse(int courseID){
    if (courseID <= 0){
        return INVALID_INPUT;
    }
    Course* course_to_delete = courses_table.find(courseID);
    if (course_to_delete == nullptr){ // course doesn't exist
        return FAILURE;
    }
    int num_of_classes = course_to_delete->getNumOfClasses();
    Lesson* current_lesson;
    for (int i=0; i<num_of_classes; i++){
        current_lesson = course_to_delete->getLessonPtr(i);
        if (current_lesson != nullptr){
            lessons_tree.remove(*current_lesson);
        }
    }
    courses_table.remove(courseID);
    return SUCCESS;
}

StatusType CourseManager::AddClass(int courseID, int* classID){
    if (courseID <= 0){
        return INVALID_INPUT;
    }
    Course* current_course = courses_table.find(courseID);
    if (current_course == nullptr){
        return FAILURE;
    }
    current_course->addLesson();
    int lesson_id = (current_course->getNumOfClasses()) - 1;
    *classID = lesson_id;
    return SUCCESS;
}

StatusType CourseManager::WatchClass(int courseID, int classID, int time){
    if ((courseID <= 0) || (time <= 0) || (classID < 0)){
        return INVALID_INPUT;
    }
    Course* current_course = courses_table.find(courseID);
    if (current_course == nullptr){
        return FAILURE;
    }
    int num_of_classes = current_course->getNumOfClasses();
    if (classID + 1 > num_of_classes){
        return INVALID_INPUT;
    }
    Lesson* current_lesson = current_course->getLessonPtr(classID);
    if (current_lesson == nullptr){
        Lesson new_lesson(time, courseID, classID);
        Lesson* new_lesson_ptr;
        lessons_tree.add(new_lesson, &new_lesson_ptr);
        current_course->updateLessonArray(classID, new_lesson_ptr);
    }
    else {
        Lesson updated_lesson(*current_lesson);
        lessons_tree.remove(*current_lesson);
        updated_lesson.updateTimeWatched(time);
        Lesson* updated_lesson_ptr;
        lessons_tree.add(updated_lesson, &updated_lesson_ptr);
        current_course->updateLessonArray(classID, updated_lesson_ptr);
    }
    return SUCCESS;
}

StatusType CourseManager::TimeViewed(int courseID, int classID, int *timeViewed){
    if ((courseID <= 0) || (classID < 0)){
        return INVALID_INPUT;
    }
    Course* current_course = courses_table.find(courseID);
    if (current_course == nullptr){
        return FAILURE;
    }
    int num_of_classes = current_course->getNumOfClasses();
    if (classID + 1 > num_of_classes){
        return INVALID_INPUT;
    }
    Lesson* current_lesson = current_course->getLessonPtr(classID);
    if (current_lesson == nullptr){
        *timeViewed = 0;
    }
    else {
        *timeViewed = current_lesson->get_time();
    }
    return SUCCESS;
}

StatusType CourseManager::GetIthWatchedClass(int i, int* courseID, int* classID){
    if (i <= 0){
        return INVALID_INPUT;
    }
    Lesson* i_th_lesson = lessons_tree.select(i);
    if (i_th_lesson == nullptr){
        return FAILURE;
    }
    i_th_lesson->get_details(courseID, classID);
    return SUCCESS;
}