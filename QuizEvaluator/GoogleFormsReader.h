#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

class GoogleFormsReader
{
public:
	//Note: rename svc file to txt file (simply change extension)
	//      and resave it with ANSI encoding.

	std::vector<std::vector<std::string>> strs_list_;

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
			//		std::cout << input_line << std::endl;

			std::vector<std::string> strs;
			boost::split(strs, input_line, boost::is_any_of(","));

			for (int i = 0; i < (int)strs.size(); i++)
			{
				strs[i].erase(strs[i].end() - 1); // remove last "
				strs[i].erase(strs[i].begin());   // remove first "
			}

			strs_list_.push_back(strs);
		}

		ifs.close();
	}

};
