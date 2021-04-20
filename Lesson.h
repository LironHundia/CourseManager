//
// Created by רוני on 31/12/2020.
//

#ifndef DS_WET2_LESSON_H
#define DS_WET2_LESSON_H

class Lesson{
private:
    int time_watched;
    int courseID;
    int lessonID;
public:
    Lesson* top;
    Lesson* right;
    Lesson* left;
    int height;
    int rank;
    Lesson(int time_watched, int courseID, int lessonID);
    ~Lesson();
    Lesson(const Lesson& lesson);
    Lesson& operator=(const Lesson& lesson);
    bool operator<(const Lesson& lesson);
    bool operator==(const Lesson& lesson);
    void updateTimeWatched(int time);
    void print();
    int get_time();
    void add_current_to_arrays(int* courses, int* classes, int* counter, int total_to_print);
    void get_details(int* course_id, int* class_id);
};

#endif //DS_WET2_LESSON_H
