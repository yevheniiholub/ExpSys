#ifndef MAINHEADER
# define MAINHEADER

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "ExpSysClass.hpp"
# include "MemberClass.hpp"

std::string 				ReadInfoFromFile(std::string sFileName);
std::vector<std::string>	ParseInfo(std::string sInput);
ExpSysClass					writeInfo(std::vector<std::string> sInputInfo);

#endif