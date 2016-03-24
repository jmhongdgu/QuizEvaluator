#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

class AnswersReader
{
public:
	std::vector<std::vector<std::string>> answers_list_;

	void read(const std::string filename)
	{
		std::ifstream ifs(filename);

		if (!ifs.is_open())
		{
			std::cout << "File was not opened." << std::endl;

			return;
		}

		std::string input_line;

		int num_line = 0;

		while (std::getline(ifs, input_line))
		{
			std::vector<std::string> strs;
			boost::split(strs, input_line, boost::is_any_of(","));

			answers_list_.push_back(strs);
		}

		ifs.close();
	}
};
