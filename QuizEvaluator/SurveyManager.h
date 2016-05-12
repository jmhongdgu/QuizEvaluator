#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <vector>
#include <iomanip>
#include <boost/filesystem.hpp>

#include "StudentSurveyData.h"

class SurveyManager
{
public:
	std::vector<std::string> category_list_;
	std::vector<std::vector<std::string>> format_list_;	
	std::vector<StudentSurveyData> student_data_;
	std::vector<int> score_sum_per_problem_;

	void analyzeData(const std::vector<std::vector<std::string>>& data_lines)
	{
		for (int i = 0; i < (int)data_lines.size(); i++)
		{
			student_data_.push_back(StudentSurveyData(data_lines[i]));
		}

		for (int student_ix = 0; student_ix < (int)student_data_.size(); student_ix++)
		{
			StudentSurveyData& student(student_data_[student_ix]);

			for (int f = 0; f < (int)format_list_.size(); f++)
			{
				if (format_list_[f][0].compare("DATE") == 0)
				{
					//std::cout << format_list_[f][0] << std::endl;

					student.date_ = student.all_answers_[f];
				}
				else if (format_list_[f][0].compare("STUDENT_ID") == 0)
				{
					//std::cout << format_list_[f][0] << std::endl;
					student.student_id_ = student.all_answers_[f];
				}
				else if (format_list_[f][0].compare("MAC") == 0)
				{
					//std::cout << format_list_[f][0] << std::endl;
					student.mac_ = student.all_answers_[f];
				}
				else if (format_list_[f][0].compare("PC_ID") == 0)
				{
					//std::cout << format_list_[f][0] << std::endl;
					student.pc_id_ = student.all_answers_[f];
				}
				else if (format_list_[f][0].compare("IGNORE") == 0)
				{
					//std::cout << format_list_[f][0] << std::endl;
					// do nothing
				}
				else if (boost::starts_with(format_list_[f][0], "QUIZ_MATCH"))
				{
					const int point = evalQuiz(f, student.all_answers_[f]);

					student.quiz_score_ += point;
					score_sum_per_problem_[f] += point;

					// measure quiz problems with possible solutions


					//for (int sol = 1; sol < (int)format_list_[f].size(); sol++)
					//{
					//	std::string student_ans = student.all_answers_[f];
					//	std::string solution = format_list_[f][sol];

					//	if (format_list_[f][0].find("IGNORE_BLANK") > 0)
					//	{
					//		if (student.student_id_.compare("2010110427") == 0)
					//		{
					//			std::cout << "Found" << std::endl;
					//		}

					//		boost::erase_all(student_ans, " ");
					//		boost::erase_all(solution, " ");
					//	}

					//	if (student_ans.compare(solution) == 0)
					//	{
					//		student.quiz_score_++;

					//		score_sum_per_problem_[f] ++;
					//		
					//		// break;
					//	}
					//}
				}
			}

//			std::cout << std::setw(11) << student.student_id_ << " " << std::setw(5) << student.quiz_score_ << std::endl;
		}
	}

	int evalQuiz(const int f, const std::string& student_ans_input)
	{
		// measure quiz problems with possible solutions
		for (int sol = 1; sol < (int)format_list_[f].size(); sol++)
		{
			std::string student_ans = student_ans_input;
			std::string solution = format_list_[f][sol];

			if (format_list_[f][0].find("IGNORE_BLANK") != std::string::npos)
			{
				boost::erase_all(student_ans, " ");
				boost::erase_all(solution, " ");
			}

			if (student_ans.compare(solution) == 0)
			{
				return 1;
			}
		}

		return 0;
	}

	void printStatistics()
	{
		for (int i = 0; i < (int)score_sum_per_problem_.size(); i++)
		{
			if (boost::starts_with(format_list_[i][0], "QUIZ_MATCH"))
			{
				std::cout << "[Question " << i << "] " << category_list_[i] << std::endl << std::endl;

				for (int sol = 1; sol < (int)format_list_[i].size(); sol++)
				{
					std::cout << format_list_[i][sol] << std::endl;
				}

				std::cout << "Percentage of correct answers "<< (float)score_sum_per_problem_[i] / (float)student_data_.size() * 100.0f << " %" << std::endl;

				std::cout << std::endl;
			}
		}

		int sum_score = 0;
		int score_min = student_data_[0].quiz_score_;
		int score_max = student_data_[0].quiz_score_;

		for (int i = 0; i < (int)student_data_.size(); i++)
		{
			sum_score += student_data_[i].quiz_score_;

			score_min = std::min(student_data_[i].quiz_score_, score_min);
			score_max = std::max(student_data_[i].quiz_score_, score_max);
		}

		std::cout << "Max score = " << score_max << std::endl;
		std::cout << "Min score = " << score_min << std::endl;
		std::cout << "Average score = " << (float)sum_score / (float)(int)student_data_.size() << std::endl;		
	}

	void writeQuizStatistics(const std::string filename)
	{
		std::ofstream of(filename);

		for (int i = 0; i < (int)score_sum_per_problem_.size(); i++)
		{
			if (boost::starts_with(format_list_[i][0], "QUIZ_MATCH"))
			{
				of << "[Question " << i << "] " << category_list_[i] << std::endl << std::endl;

				of << "Correct answers:" << std::endl;
				
				for (int sol = 1; sol < (int)format_list_[i].size(); sol++)
				{
					of << format_list_[i][sol] << std::endl;
				}

				of << std::endl << "Percentage of correct answers " << (float)score_sum_per_problem_[i] / (float)student_data_.size() * 100.0f << " %" << std::endl;

				of << std::endl;
			}
		}

		int sum_score = 0;
		int score_min = student_data_[0].quiz_score_;
		int score_max = student_data_[0].quiz_score_;

		for (int i = 0; i < (int)student_data_.size(); i++)
		{
			sum_score += student_data_[i].quiz_score_;

			score_min = std::min(student_data_[i].quiz_score_, score_min);
			score_max = std::max(student_data_[i].quiz_score_, score_max);
		}

		of << "Max score = " << score_max << std::endl;
		of << "Min score = " << score_min << std::endl;
		of << "Average score = " << (float)sum_score / (float)(int)student_data_.size() << std::endl;

		of.close();
	}

	void printPharasesWithLineChanges(const std::vector<std::string>& phrases)
	{
		for (int i = 0; i < (int)phrases.size(); i++)
		{
			std::cout << "\"" << phrases[i] << "\"";
			if (i != (int)phrases.size() - 1) std::cout << std::endl;
		}
	}
	
	void writeAllStudentQuizResult(const std::string& path)
	{
		for (int i = 0; i < (int)student_data_.size(); i++)
		{
			writeStudentWithID(student_data_[i], path + student_data_[i].student_id_ + std::string(".txt"));
		}
	}

	void writeStudentWithID(const StudentSurveyData& student, const std::string& filename)
	{
		std::ofstream ofs(filename);

		ofs << "Student ID " << student.student_id_ << std::endl;
		ofs << "Quiz data " << student.date_ << std::endl;

		int num_all_quiz = 0;

		for (int f = 0; f < (int)format_list_.size(); f++)
		{
			if (boost::starts_with(format_list_[f][0], "QUIZ_MATCH"))
			{
				num_all_quiz++;

				// measure quiz problems with possible solutions

				int score_this_problem = evalQuiz(f, student.all_answers_[f]);

				ofs << score_this_problem << " " << student.all_answers_[f] << std::endl;
			}
		}

		ofs << "Total score is " << student.quiz_score_ << " of " << num_all_quiz << " problems" << std::endl;

		ofs.close();
	}

	void writeAllStudentQuizScore(const std::string& path, const std::string& student_file)
	{
		std::ifstream fin(student_file);
		std::ofstream ofs(path);

		std::string stu_id;

		int pos;
		while (std::getline(fin, stu_id))
		{
			pos = findStudent(stu_id);
			if (pos == -1)
				ofs << std::endl;
			else
				ofs << student_data_[pos].quiz_score_ << std::endl;				
		}

		

		fin.close();

		
		//for (int i = 0; i < (int)student_data_.size(); i++)
		//	ofs << student_data_[i].student_id_ << " " << student_data_[i].quiz_score_ << std::endl;
		
		ofs.close();
	}

	int findStudent(std::string id)
	{
		for (int i = 0; i < (int)student_data_.size(); i++)
		{
			if (id == student_data_[i].student_id_)
				return i;
		}
		return -1;
	}



	void printStudentWithID(const std::string student_id_str)
	{
		int student_ix = 0;
		for (; student_ix < (int)student_data_.size(); student_ix++)
		{
			if (student_id_str.compare(student_data_[student_ix].student_id_) == 0)
				break;
		}

		if (student_ix >= (int)student_data_.size())
			std::cout << "Student was not found" << std::endl;

		const StudentSurveyData& student(student_data_[student_ix]);

		std::cout <<"Student ID "<< student.student_id_ << std::endl;
		std::cout << "Quiz data " << student.date_ << std::endl;

		int num_all_quiz = 0;

		for (int f = 0; f < (int)format_list_.size(); f++)
		{
			if (boost::starts_with(format_list_[f][0], "QUIZ_MATCH"))
			{
				num_all_quiz++;

				// measure quiz problems with possible solutions

				int score_this_problem = 0;
				for (int sol = 1; sol < (int)format_list_[f].size(); sol++)//sol = 0 is the flag
				{
					if (student.all_answers_[f].compare(format_list_[f][sol]) == 0)
					{
						score_this_problem++;
					}
				}

				std::cout << score_this_problem << " " << student.all_answers_[f] << std::endl;
			}
		}

		std::cout << "Total score is " << student.quiz_score_ <<" of "<< num_all_quiz <<" problems" << std::endl;
	}

	void readFormat(const std::string filename)
	{
		using namespace std;
		using namespace boost;

		std::ifstream ifs(filename);

		if (!ifs.is_open())
		{
			std::cout << "File was not opened." << std::endl;

			return;
		}

		std::string input_line;

		while (std::getline(ifs, input_line))
		{
			input_line.erase(input_line.end() - 1);	// remove first " of this line
			input_line.erase(input_line.begin());	// remove last " of this line

			std::vector<std::string> strs;
			boost::algorithm::split_regex(strs, input_line, regex("\",\""));// split line into pharases by separation str

			format_list_.push_back(strs);
		}

		ifs.close();

		score_sum_per_problem_.resize(format_list_.size());

		for (int i = 0; i < (int)score_sum_per_problem_.size(); i++)
		{
			score_sum_per_problem_[i] = 0;
		}
	}

	void printPharases(const std::vector<std::string>& phrases)
	{
		for (int i = 0; i < (int)phrases.size(); i++)
		{
			std::cout << "\"" << phrases[i] << "\"";
			if (i != (int)phrases.size() - 1) std::cout << ",";
		}

		std::cout << std::endl;
	}

	void printFormat()
	{
		for (int i = 0; i < (int)format_list_.size(); i++)
		{
			printPharases(format_list_[i]);
		}
	}
};
