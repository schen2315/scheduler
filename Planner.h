#ifndef PLANNER_H
#define PLANNER_H
#include "Node.h"
#include "Vec.h"
#include "queue.h"
using namespace std;
class Planner {
public:
	//function to test prereqs
	//function to test all req and mand classes are taken
		//keep array of these classes -> 
	Planner(string required, string offered, string schedule);
	~Planner();
	void checkPrereqs();
private:
	int compareSemesters(string line1, string line2);
	void setCSCourses();
	void parseReqs(string line);
	void parseOfferings(string line, int i);
	void parseSchedule(string line);
	int findClassByName(string name);
	string removeSpaces(string input);
	int credits[26];
	int total = 0;
	int size = 0;
	//graph
	Node* graph = NULL;
	Vec<string> issues;
};

#endif




