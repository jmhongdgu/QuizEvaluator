#include "SurveyManager.h"
#include "CSVReader.h"


// this is a github test

using namespace std;

void main( int argc, char *argv[] )
{
	std::string data_file, format_file, statistic_file_, result_file_1, result_file_2, result_folder_, folder_name_, num_class_;
	data_file = "quiz.txt";
	format_file = "format.txt";
	statistic_file_ = "quiz_statistics.txt";
	result_file_1 = "01_excel_format_result.txt";
	result_file_2 = "02_excel_format_result.txt";
	folder_name_ = "CES2014";
	result_folder_ = "CES2014";
	
	if (argc == 2)
	{
		printf("not enough parameter\n");
		printf("QuizEvaluator.exe [quiz filename] [format filename]\n");
		return ;
	}
	if (argc == 3)
	{
		data_file = argv[1];
		format_file = argv[2];
	}
	else if (argc == 4)
	{
		data_file = argv[1];
		format_file = argv[2];
		folder_name_ = argv[3];
	}


	
	statistic_file_ = folder_name_ + "/" + folder_name_ + "_" + statistic_file_;
	result_file_1 = folder_name_ + "/" + result_file_1;
	result_file_2 = folder_name_ + "/" + result_file_2;

	result_folder_ = folder_name_ + "/";
	
	boost::filesystem::create_directory(folder_name_);

	CSVReader reader;
	reader.readANSIFile(data_file);//no blank in file name
//	reader.printAll();
//	reader.printCategoriesWithLineChange();

	SurveyManager survey_manager;
	
	survey_manager.readFormat(format_file);
//	survey_manager.printFormat();
	survey_manager.category_list_ = reader.categories_;
	survey_manager.analyzeData(reader.data_lines_);

//	survey_manager.printStudentWithID("2012111382");
//	survey_manager.printStudentWithID("2016112152");
//	survey_manager.printStatistics();
	
	survey_manager.writeAllStudentQuizResult(result_folder_);
	survey_manager.writeQuizStatistics(statistic_file_);
	survey_manager.writeAllStudentQuizScore(result_file_1, "student1.txt");
	survey_manager.writeAllStudentQuizScore(result_file_2, "student2.txt");
	// file out
	// summary pts of all students (pt summary, etc)
	// score of each student
	// if student didnt' attend, score should be 0. (no show report), average, % of each problems, graphs.
}