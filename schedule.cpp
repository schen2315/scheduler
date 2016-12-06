#include "Planner.h"
#include "Vec.h"
#include "queue.h"
#include <iostream>
using namespace std;
//queue test

int main(int argc, char** argv) {
	Planner p(argv[1], argv[2], argv[3]);
	p.checkPrereqs();
	// Planner p("./Prog3_Test_Cases/Requirements1.txt", 
	// 	"./Prog3_Test_Cases/Offered1.txt", "./Prog3_Test_Cases/Schedule1.txt");
	// p.checkPrereqs();
	// cout << endl;
	// Planner q("./Prog3_Test_Cases/Requirements1.txt", 
	// 	"./Prog3_Test_Cases/Offered1.txt", "./Prog3_Test_Cases/Schedule3_prereq.txt");
	// q.checkPrereqs();
	// cout << endl;
	// Planner r("./Prog3_Test_Cases/Requirements1.txt", 
	// 	"./Prog3_Test_Cases/Offered1.txt", "./Prog3_Test_Cases/Schedule4_prereq.txt");
	// r.checkPrereqs();
	return 0;
}