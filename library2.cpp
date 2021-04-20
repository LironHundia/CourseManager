//
// Created by רוני on 01/01/2021.
//

#include "library2.h"
#include "CourseManager.h"

void *Init(){
    CourseManager* cm;
    try{
        cm = new CourseManager();
    } catch(std::bad_alloc& e){
        return nullptr;
    }
    return (void*)cm;
}

StatusType AddCourse(void* DS, int courseID){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->AddCourse(courseID);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

StatusType RemoveCourse(void *DS, int courseID){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->RemoveCourse(courseID);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

StatusType AddClass(void* DS, int courseID, int* classID){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->AddClass(courseID, classID);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->WatchClass(courseID, classID, time);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->TimeViewed(courseID, classID, timeViewed);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    CourseManager* cm = (CourseManager*)DS;
    StatusType result;
    try{
        result = cm->GetIthWatchedClass(i, courseID, classID);
    } catch (std::bad_alloc& e){
        result = ALLOCATION_ERROR;
    }
    return result;
}

void Quit(void** DS){
    CourseManager* cm = (CourseManager*)(*DS);
    delete cm;
    *DS = nullptr;
}