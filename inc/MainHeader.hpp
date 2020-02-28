#ifndef MAINHEADER
# define MAINHEADER

# include <cstring>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "ExpSysClass.hpp"
# include "MemberClass.hpp"

std::string 				ReadInfoFromFile(std::string sFileName);
std::vector<std::string>	ParseInfo(std::string sInput);
ExpSysClass					writeInfo(std::vector<std::string> sInputInfo);
void						solver(ExpSysClass *inputInfo);
uint16_t	                isTrue(uint16_t status, uint16_t rec, std::vector<MemberClass> members, std::string instruction);
uint16_t                    getMemberStatus(uint8_t name, std::vector<MemberClass> members);
uint16_t                    getMemberFact(uint8_t name, std::vector<MemberClass> members);
uint16_t                    isInLine(std::string instruction);
std::string                 resolveFlags(ExpSysClass *infoClass, char **argv);

#endif