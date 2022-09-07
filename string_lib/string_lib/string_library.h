#pragma once
#include <string>
#include <map>
#include <vector>
#define no_init_all



#ifdef string_lib_EXPORT
#define string_lib_API __declspec(dllexport)
#else
#define string_lib_API __declspec(dllimport)
#endif



extern "C" string_lib_API  bool ascCmp(const std::pair<const int, int>& a, const std::pair<const int, int>& b);
extern "C" string_lib_API  bool dscCmp(const std::pair<const int, int>& a, const std::pair<const int, int>& b);
extern "C" string_lib_API  std::string find_file_in_path(std::string path);
extern "C" string_lib_API int string_to_int(std::string str);
extern "C" string_lib_API int hextext_to_int(std::string str);




extern "C"  class string_lib_API CmdOption {
public:

	CmdOption(int& argc, char* argv[]) ;

	std::vector<std::string> tokens;

	const std::string& setCmdOption(const std::string& opt);

	enum class SortingType {
		Ascending,
		Descending,
	};
};

extern "C" string_lib_API class IParser{
	public:
		virtual int parse_word(std::string word)=0;
};


extern "C" string_lib_API class DecParser:public IParser{
public:
	string_lib_API DecParser() ;
	int parse_word(std::string word);
};

extern "C" string_lib_API class HexParser:public IParser{
public:
	string_lib_API HexParser();
	int parse_word(std::string word);
		
	};

extern "C" class string_lib_API Processor {
public:
	Processor(IParser* parser);

	std::map<int, bool> invalid_lines_dict;
	std::vector<std::pair<int, int>> line_value_data;
	IParser* parser;
	bool(*cmpFunc)(const std::pair<const int, int>&, const std::pair<const int, int>&);
	void parse(std::vector<std::vector<std::string>>&  file_data);
	void sort(bool(*sortFncPtr)(const std::pair<const int, int>&, const std::pair<const int, int>&));
	void print_discard();
	void print_results(bool content_first = true);
	void run(std::vector<std::vector<std::string>>& file_data, std::string discarded, std::string line_n, bool(*sortFncPtr)(const std::pair<const int, int>&, const std::pair<const int, int>&));

};

