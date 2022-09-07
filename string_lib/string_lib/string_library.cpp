#include "pch.h"
#include "string_library.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>

#ifdef string_lib_EXPORT
#define string_lib_API __declspec(dllexport)
#else
#define string_lib_API __declspec(dllimport)
#endif

#define no_init_all

///////////////// Functions //////////////////////

bool ascCmp(const std::pair<const int, int>& a, const std::pair<const int, int>& b)
{
	return a.second < b.second;
}


bool dscCmp(const std::pair<const int, int>& a, const std::pair<const int, int>& b)
{
	return a.second > b.second;
}

std::string find_file_in_path(std::string path) {
	std::string file_path_with_name;
	std::string filename;
	std::cout << "List of files in given dir: " << std::endl;

	for (const auto& entry : std::filesystem::directory_iterator{ path }) {
		std::cout << entry.path().filename().string() << std::endl;
		if (entry.path().filename().string().find(".txt") != std::string::npos) {
			filename = entry.path().filename().string();
			file_path_with_name = entry.path().string();
		}

	}
	std::cout << '\n';

	return file_path_with_name;
}


int char_to_num(char ch) {
	int charNumber = -1;
	if ((ch - '0') <= 9 && (ch - '0') >= 0) {

		charNumber = ch - '0';
		return charNumber;

	}
	else if ((ch - 'A') < 6 && (ch - 'A') >= 0) {
		charNumber = 10 + (ch - 'A');
		return charNumber;
	}
	else if ((ch - 'a') < 6 && (ch - 'a') >= 0) {
		charNumber = 10 + (ch - 'a');
		return charNumber;
	}
	else
		return -1;
}


int string_to_int(std::string str) {
	int number = 0;
	int i = 0;
	bool isNegative = false;
	if (int(str[0]) == 45) {
		isNegative = true;
		i = 1;
	}
	while (str[i] != '\0') {
		if (str[i] > 57 || str[i] < 48)
			return -1;

		number = number * 10 + char_to_num(str[i]);
		i++;

	}
	if (isNegative)
		number = -number;

	return number;
}



int hextext_to_int(std::string str) {
	int number = 0;
	int tempNum = 0;
	int total_bits = str.size() * 4;
	int sign_bit = 1 << (total_bits - 1);

	for (char ch : str) {
		if (ch == '-')
			return -1;
		tempNum = char_to_num(ch);
		if (tempNum == -1)
			return -1;
		number = number * 16 + tempNum;
	}

	bool isNegative = (number & sign_bit) >> total_bits - 1;
	if (!isNegative)
		return number;
	return   (number - 2 * sign_bit);

}

////////////////////// Classes /////////////////////////////////

CmdOption::CmdOption(int& argc, char* argv[]) {
	for (int i = 1; i < argc; ++i)
		this->tokens.push_back(std::string(argv[i]));
};

	

const std::string& CmdOption::setCmdOption(const std::string& opt) {
		std::vector<std::string>::const_iterator it;
		it = std::find(this->tokens.begin(), this->tokens.end(), opt);
		if (it != this->tokens.end() && ++it != this->tokens.end()) {
			return *it;
		}
		static const std::string empty_string("");
		return empty_string;

	}


string_lib_API DecParser::DecParser() {};
int DecParser::parse_word(std::string word) {
	return string_to_int(word);
}

string_lib_API HexParser::HexParser() {};
int HexParser::parse_word(std::string word) {
	return hextext_to_int(word);
}

Processor::Processor(IParser* parser) {
	this->parser = parser;
};

void Processor::parse(std::vector<std::vector<std::string>>& file_data) {
	std::vector<int> int_of_txt;
	int line = 1;
	for (const auto& words : file_data)
	{
		for (int i = 0; i < words.size(); i++) {
			int intVal = parser->parse_word(words.at(i));
			if (intVal != -1) {
				int_of_txt.emplace_back(intVal);
				line_value_data.emplace_back(line, intVal);
			}
			else {
				invalid_lines_dict.insert(std::pair<int, bool>(line, true));
			}
		}
		line++;
	}
}
void Processor::sort(bool(*sortFncPtr)(const std::pair<const int, int>&, const std::pair<const int, int>&)) {
	std::sort(this->line_value_data.begin(), this->line_value_data.end(), sortFncPtr);
}
void Processor::print_discard() {
	for (const auto&[line, val] : this->invalid_lines_dict) {
		if (val) {
			std::cout << "Line \t" << line << "\tcontained invalid data" << std::endl;
		}
	}
	std::cout << "\n";
}
void Processor::print_results(bool content_first) {
 	for (auto itr = this->line_value_data.begin(); itr != this->line_value_data.end(); ++itr) {
		if (this->invalid_lines_dict.count(itr->first) > 0) continue;
		if (content_first) {
			std::cout << itr->second <<  '\t'  << itr->first << std::endl;
		}
		else {
			std::cout << itr->first << '\t' << itr->second << std::endl;
		}

	}
	std::cout << "\n";
}
void Processor::run(std::vector<std::vector<std::string>>& file_data, std::string discarded, std::string line_n, bool(*sortFncPtr)(const std::pair<const int, int>&, const std::pair<const int, int>&)) {
	this->parse(file_data);
	this->sort(sortFncPtr);
	if (discarded == "first") 
		this->print_discard();
	this->print_results(line_n != "first");
	if (discarded != "first")
		this->print_discard();

}
