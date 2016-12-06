#include <iostream>
#include "Planner.h"
#include "Vec.h"
#include <fstream>
#include <sstream>
using namespace std;
Planner::Planner(string required, string offered, string schedule) {
	string line;
	//first get # of classes
	ifstream classes(offered);
	for(;getline(classes, line);) size++;
	classes.close();
	graph = new Node[size];
	//set the size
	//initialize the graph
	for(int i=0;i < 26; i++) {
		credits[i] = 0;
	}
	ifstream required_stream(required);
	ifstream offered_stream(offered);
	ifstream schedule_stream(schedule);
	//offered
	for(int i=0 ;getline(offered_stream, line);i++) {
		parseOfferings(line, i);
	}
	
	
	//required
	
	for(;getline(required_stream, line);) {
		parseReqs(line);
	}
	
	//schedule
	for(;getline(schedule_stream, line);) {
		parseSchedule(line);
	}
	setCSCourses();	//set the prereqs of all the other CS courses
	/*
	for(int i=0; i < size; i++) {
		cout << graph[i].name << " " << graph[i].credits 
		<< " " << graph[i].tags 
		<< graph[i].MRO << " " 
		<< graph[i].offered << " " << graph[i].semester << " ";
		graph[i].prereqs.print();
		cout << endl;
	}
	*/
	required_stream.close();
	offered_stream.close();
	schedule_stream.close();
}
Planner::~Planner() {
	delete [] graph;
}
void Planner::parseReqs(string line) {
	stringstream stream(line);
	string word;
	stream >> word;
	if(word == "TOTAL") {
		stream >> word;
		total = stoi(word);
	} else if(word ==  "CREDIT") {
		string temp;
		stream >> word;
		stream >> temp;
		credits[word.at(0) - 'A'] = stoi(temp);
	} else if(word == "COURSE") {
		//find the course by name
		//find the other prereqs courses -> this is going to be really inefficient
		stream >> word;
		int node = findClassByName(word);
		if(node != -1) {
			stream >> word;
			graph[node].MRO = word;
			while(stream >> word) {
				int prereq = findClassByName(word);
				if(prereq != -1)
				graph[node].prereqs.push_back(prereq);
			}
		}
	} else if(word == "CHOOSE") {
		//figure out later for program 2
	}
}
void Planner::parseOfferings(string line, int i) {
	stringstream stream(line);
	string word;
	stream >> word;
	graph[i].name = word;
	stream >> word;
	graph[i].credits = stoi(word);
	stream >> word;
	graph[i].offered = word;
	if(stream >> word) graph[i].tags = word;
};
void Planner::parseSchedule(string line) {
	stringstream stream(line);
	string semester;
	string course;
	stream >> semester;
	while(stream >> course) {
		int node = findClassByName(course);
		if(node != -1)		
		graph[node].semester = semester;
		else {
			string issue = course + " planned to be taken semester " + semester + " because it is not an offered course."; 
			issues.push_back(issue);
		}
		//maybe append that the course the person is trying to take doesn't exist
	}
}
int Planner::findClassByName(string name) {
	//name = removeSpaces(name);
	//cout << name << endl;
	for(int i=0; i < size; i++) {
		if(graph[i].name == name) return i;
	}
	//throw std::invalid_argument("class could not be found by name");
	return -1;
}
void Planner::setCSCourses() {
	Vec<int> prereqs;
	for(int i=0; i < size; i++) {
		if(/*graph[i].name.substr(0, 2) == "CS" &&*/ (graph[i].MRO == "R")) {
			prereqs.push_back(i);
		}
	}
	for(int i=0; i < size; i++) {
		if(graph[i].name.substr(0,2) == "CS" && (graph[i].MRO == "")) {
			graph[i].prereqs = prereqs;
			//graph[i].prereqs.print();
		}
	}
}
void Planner::checkPrereqs() {
	//for all nodes in the graph 
	queue<int> q;
	for(int i=0; i < size; i++) {
		//if a node is taken and has not been checked yet
		if(graph[i].checked == false && graph[i].semester != "") {
			//add it to the queue 
			q.push(i);
			//while queue is not empty
			while(!q.empty()) {
				int course = q.front();
				q.pop();
				Vec<int> prereqs = graph[course].prereqs;
				//cout << graph[course].name << " ";
				for(int j=0; j < prereqs.size(); j++) {
					//check all of its prerequisites
					if(compareSemesters(graph[course].semester, graph[prereqs[j]].semester) == 1) /*do nothing*/;
					else if(compareSemesters(graph[course].semester, graph[prereqs[j]].semester) == -1) {
						issues.push_back(graph[course].name + " cannot be taken if "
							+ graph[prereqs[j]].name + " is taken after it.");
					} else if(compareSemesters(graph[course].semester, graph[prereqs[j]].semester) == -2) {
						issues.push_back(graph[course].name + " cannot be taken because "
							+ graph[prereqs[j]].name + "is not taken at all.");
					} else if(compareSemesters(graph[course].semester, graph[prereqs[j]].semester) == 0) {
						issues.push_back(graph[course].name + " cannot be taken while taking "
							+ graph[prereqs[j]].name + " at the same time.");
					}
						//push back any prerequisite issues found		
					//cout << graph[prereqs[j]].name << " ";
					//add its prerequisites to the queue
					if(graph[prereqs[j]].checked == false && graph[prereqs[j]].semester != "") {
						q.push(prereqs[j]);
					}
				}
				//cout << endl;
				graph[course].checked = true;
			}
		}
	}
	if(issues.size() != 0) {
		cout << "Bad plan. Here's why:" << endl;
		for(int i=0; i < issues.size(); i++) cout << issues[i] << endl;
	} else {
		cout << "Good plan. Get to work." << endl;
	}
}
// string Planner::removeSpaces(string input)
// {
//   input.erase(std::remove(input.begin(),input.end(),' '),input.end());
//   return input;
// }
int Planner::compareSemesters(string line1, string line2) {
	if(line2 == "") return -2;	//not taken
	int year1 = stoi(line1.substr(1, line1.length() - 1));
	int year2 = stoi(line2.substr(1, line2.length() - 1));
	if(year1 > year2) return 1;	//satisfied
	else if(year1 == year2) {
		if(line1.substr(0,1) == line2.substr(0,1)) return 0;	//not satisfied
		else if(line1.substr(0,1) == "F") return 1;
		else {
			return -1;
		}
	} else {
		return -1;	//not satisfied
	}
};




