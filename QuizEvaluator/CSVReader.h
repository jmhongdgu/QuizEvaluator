#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <vector>

class CSVReader
{
public:
	//Note: rename svc file to txt file (simply change extension)
	//      and resave it with ANSI encoding.
	std::string separation_str_;		// split with "," and remove first " of first and last line
	std::vector<std::string> categories_;
	std::vector<std::vector<std::string>> data_lines_;

	CSVReader()
		: separation_str_("\",\"")
	{}

	std::vector<std::string> parseLineToPhrase(const std::string& input_line)
	{
		using namespace std;
		using namespace boost;

		vector<std::string> pharases;
		
		boost::algorithm::split_regex(pharases, input_line, regex("\",\""));// split line into pharases by separation str

		return pharases;
	}

	void readANSIFile(const std::string filename)
	{
		std::ifstream ifs(filename);

		if (!ifs.is_open())
		{
			std::cout << "File was not opened." << std::endl;

			return;
		}

		std::string input_line;

		if (!std::getline(ifs, input_line))
		{
			std::cout << "Cannot read first line of " << filename << std::endl;
			return;
		}
		
		input_line.erase(input_line.end() - 1);	// remove first " of this line
		input_line.erase(input_line.begin());	// remove last " of this line

		categories_ = parseLineToPhrase(input_line);

		while (std::getline(ifs, input_line))
		{
			input_line.erase(input_line.end() - 1);	// remove first " of this line
			input_line.erase(input_line.begin());	// remove last " of this line

			data_lines_.push_back(parseLineToPhrase(input_line));
		}

		ifs.close();
	}

	void printPharases(const std::vector<std::string>& phrases)
	{
		for (int i = 0; i < (int)phrases.size(); i++)
		{
			std::cout << "\"" << phrases[i] << "\"";
			if(i != (int)phrases.size() - 1) std::cout << ",";
		}

		std::cout << std::endl;
	}

	void printPharasesWithLineChanges(const std::vector<std::string>& phrases)
	{
		for (int i = 0; i < (int)phrases.size(); i++)
		{
			std::cout << "\"" << phrases[i] << "\"";
			if (i != (int)phrases.size() - 1) std::cout << std::endl;
		}
	}

	void printAll()
	{
		printPharases(categories_);

		for (int l = 0; l < (int)data_lines_.size(); l++)
		{
			printPharases(data_lines_[l]);
		}
	}

	void printCategoriesWithLineChange()
	{
		printPharasesWithLineChanges(categories_);
	}
};
