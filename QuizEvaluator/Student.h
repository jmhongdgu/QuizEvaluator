#pragma once

#include <string>
#include <vector>

class Student
{
public:
	std::string ID_;
	std::vector<std::string> answers_;
	int point_sum_;

	Student()
		: point_sum_(0)
	{}
};
