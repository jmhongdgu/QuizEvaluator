#include "SurveyManager.h"
#include "CSVReader.h"


// this is a github test

using namespace std;

void main()
{
	CSVReader reader;
	reader.readANSIFile("CSE2014_20160316/CSE2014_20160316_ansi.txt");
//	reader.printAll();
//	reader.printCategoriesWithLineChange();

	SurveyManager survey_manager;
	survey_manager.readFormat("CSE2014_20160316/CSE2014_20160316_formats.txt");
//	survey_manager.printFormat();
	survey_manager.category_list_ = reader.categories_;
	survey_manager.analyzeData(reader.data_lines_);

	survey_manager.printStudentWithID("2016112146");
	survey_manager.printStudentWithID("2016112152");
	survey_manager.printStatistics();
	survey_manager.writeQuizStatistics("CSE2014_20160316/CSE2014_20160316_quiz_statistics.txt");
	survey_manager.writeAllStudentQuizResult("CSE2014_20160316/");

	// file out
	// summary pts of all students (pt summary, etc)
	// score of each student
	// if student didnt' attend, score should be 0. (no show report), average, % of each problems, graphs.
}