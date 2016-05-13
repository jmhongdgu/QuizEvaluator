#pragma once

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>

class StudentSurveyData
{
public:
	std::string date_;
	std::string student_id_;
	std::string mac_;
	std::string pc_id_;

	std::vector<std::string> all_answers_;

	int quiz_score_;

	StudentSurveyData()
		: quiz_score_(0)
	{}

	StudentSurveyData(const std::vector<std::string>& all_answers_input)
		: quiz_score_(0), all_answers_(all_answers_input)
	{}
};
