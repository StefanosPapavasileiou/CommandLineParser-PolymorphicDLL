#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>
#include "string_library.h"

int main(int argc, char* argv[])
{
	
	CmdOption input(argc, argv);

	// Init some options for the user 

	const std::string path_of_txt = input.setCmdOption("-f");
	const std::string notation = input.setCmdOption("-format");	
	const std::string discarded = input.setCmdOption("-discard");
	const std::string line_n = input.setCmdOption("-line");
	const std::string sorting_alg = input.setCmdOption("-sort");

	// sortFncPtr points to the proper cmp function based on input -sort arg

	bool(*sortFncPtr)(const std::pair<const int, int>&, const std::pair<const int, int>&);
	std::map<std::string, CmdOption::SortingType> mapStringToSort = {
		{"ascending", CmdOption::SortingType::Ascending},
		{"descending", CmdOption::SortingType::Descending},
	};
	 
	
	CmdOption::SortingType sortType = mapStringToSort[sorting_alg];

	// Default sort  - Ascending order
	sortFncPtr = ascCmp;

	switch (sortType)
	{
	case CmdOption::SortingType::Ascending: {
		sortFncPtr = ascCmp;
		break; }
	case CmdOption::SortingType::Descending:{
		sortFncPtr = dscCmp;
		break;}
	}	

	std::string append_filename_on_path = find_file_in_path(path_of_txt);
	std::ifstream txt_file(append_filename_on_path, std::ios::binary);
	std::vector<std::vector<std::string>> file_data;

	if (!txt_file) {
		std::cerr << "File not found" << std::endl;
		return 1;
	}
	for (std::string line_data; std::getline(txt_file, line_data); )
	{
		file_data.push_back(std::vector<std::string>());
		std::istringstream iss(line_data);
		for (std::string individ_word; iss >> individ_word; )
			file_data.back().push_back(individ_word);
	}	
	
	Processor* processor;

	if (notation == "dec") {
		processor = new Processor(new DecParser());
		processor->run(file_data, discarded, line_n, sortFncPtr);
	}
	if (notation == "hex") {
		processor = new Processor(new HexParser());
		processor->run(file_data, discarded, line_n, sortFncPtr);
	}
	return 0;
}
