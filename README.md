# CourseManager
CourseManager provides a system to manage courses with multiple lessons using several monitoring features - such as the number of the classes, getting the most-watched class or the i'th most watched class and so on - in efficient way (time-complexity wise)
The purpose is to implement several data structeres that will eventually help us manage a system of courses.
The project includes implementing of AVL-rank tree, list and hash table (without using STL library).

(Note - the implementation of the functions and data structures is in C++, though the functions signatures is in C)
The functions list and complexity:

**void* Init()** 
  - initialize an empty CourseManager data structure.

**StatusType AddCourse( void* DS, int courseID)**
  - adding a new course to the system, with courseID identifier. Will contain 0 lessons.

**StatusType RemoveCourse( void* DS, int courseID)**
  - erasing course -courseID- and all of it's lessons from the CourseManager.

**StatusType AddClass( void* DS, int courseID, int* classID)**
  - adding a new lesson to course -courseID-. ClassID will be provided with the new lesson's identifier.

**StatusType WatchClass( void* DS, int courseID, int classID, int time)**
  - indicates that lesson with the classID, from course -courseID- has been watched for -time- minutes.

**StatusType TimeViewed( void* DS, int courseID, int classID, int* timeViewed)**
  - returns to timeViewed the total sum of minutes in which lesson -classID- from course -courseID- has been watched.

**StatusType GetIthWatchedClass( void* DS, int i, int* courseID, int* classID)**
  - returns in classID the i'th most watched lesson in the CourseManager in total. The levels of priorities are: 
  1. time watched in total (descending order) 
  2. courseID (ascending order)
  3. classID (ascending order)

**void Quit( void ** DS)**
- release the CourseManager structure.
