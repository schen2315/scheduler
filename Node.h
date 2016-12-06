#ifndef NODE_H
#define NODE_H

#include "Vec.h"
class Node {
public:
	std::string name = "";
	Vec<int> prereqs;
	int credits = 0;
	std::string tags = "";
	std::string offered = "";
	std::string semester = "";
	std::string MRO = "";
	bool checked = false;
private:

};

#include "Node.cpp"

#endif