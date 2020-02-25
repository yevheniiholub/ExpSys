#include "MainHeader.hpp"

void	printClass(ExpSysClass cl)
{
	uint16_t iCount = 0;
	while (iCount < cl.getInstCond().size())
	{
		std::cout << cl.getInstCond()[iCount] << " " << cl.getOnlyIf()[iCount] << " " << cl.getInstRes()[iCount] << std::endl;
		iCount++;
	}
	iCount = 0;
	while (iCount < cl.getMembers().size())
	{
		std::cout << "name : " << cl.getMembers()[iCount].getName() << " status : " << cl.getMembers()[iCount].getIsTrue() << " fact: " << cl.getMembers()[iCount].getFact() << std::endl;
		iCount++;
	}
}

int		main(int iArgc, char **sArgv)
{
	std::string 				sInput;
	std::vector<std::string>	vInput;
	ExpSysClass 				expClass;

	if (iArgc == 2)
	{
		sInput = ReadInfoFromFile(sArgv[1]);				// read file in string
		vInput = ParseInfo(sInput);							// parsing
		expClass = writeInfo(vInput);
		solver(expClass);
	}
}