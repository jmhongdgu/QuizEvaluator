#include "AnswersReader.h"
#include "CSVReader.h"

// this is a github test

void main()
{
	CSVReader reader;
	reader.read("CSE2014 20160316 ÄûÁî Ch3_ansi.txt");

//	for (int l = 0; l < (int)reader.strs_list_.size(); l++)
	int l = 1;
	{
		for (int i = 0; i < (int)reader.strs_list_[l].size(); i++)
			std::cout << reader.strs_list_[l][i] << "|||";

		std::cout <<"ENDL"<< std::endl;
	}

	AnswersReader answers;
	answers.read("20160316_3Àå_ÄûÁî_Á¤´ä.txt");

	//for (int l = 0; l < (int)answers.answers_list_.size(); l++)
	//{
	//	for (int i = 0; i < (int)answers.answers_list_[l].size(); i++)
	//		std::cout << answers.answers_list_[l][i] << "|||";

	//	std::cout << "ENDL" << std::endl;
	//}


}