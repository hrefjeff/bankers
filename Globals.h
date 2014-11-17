using namespace std;

//Total number of resources on system; if you change this, you need to change
//the array below (either add or remove an element)
const int resources = 4;

//Total amount of each resource available on system. Note this is NOT the
//amount currently available, rather the amount the system has if nothing is
//allocated to a process
const int resourceArray[resources] = { 3, 14, 12, 12 };

//Resources are taken from problem 7.3 in the textbook. In this instance, each
//element in the array maps to the assigned letter in the text. For example,
//index 0 is resource A, index 1 is resource B, etc.