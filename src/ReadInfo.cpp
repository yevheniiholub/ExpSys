#include "MainHeader.hpp"

std::vector<std::string> 		RemoveComents(std::vector<std::string> vInput)
{
	uint16_t	iCountVec;
	uint16_t	iCountStr;

	iCountVec = 0;
	while (iCountVec < vInput.size())
	{
		iCountStr = 0;
		while (iCountStr < vInput[iCountVec].length())
		{
			if (vInput[iCountVec][iCountStr] == '#')
				while (iCountStr < vInput[iCountVec].length())
					vInput[iCountVec].pop_back();
			else
				iCountStr++; 
		}
		iCountVec++;
	}
	return (vInput);
}

uint16_t	isAlpha(char cCharacter)
{
	if (cCharacter <= 'Z' && cCharacter >= 'A')
		return (1);
	return (0);
}

std::string	ReadInfoFromFile(std::string sFileName)
{
	std::string		sBuff;
	std::ifstream	ifsFile(sFileName);
	std::string		sResult;

	if (ifsFile.fail())
	{
		std::cout << "Cannot open file :" << sFileName << "!" << std::endl;
		exit (0);
	}
	while (std::getline(ifsFile, sBuff)){
		sResult += sBuff + "\n";
	}
	ifsFile.close();
	return (sResult);
}

std::vector<std::string> SplitString(std::string sInput)
{
    uint16_t					iCountI;
	std::vector<std::string>	vRes;
    std::string					sBuff;

    iCountI = 0;
    while(iCountI < sInput.length())
	{
		if (sInput[iCountI] != '\n'){
			if (sInput[iCountI] != ' ')
				sBuff.push_back(sInput[iCountI]);
		}
		else {
			if (sBuff.length() > 0)
				vRes.push_back(sBuff);
			sBuff.clear();
		}
		iCountI++;
	}
	return vRes;
}

void		CheckForValid(std::string sSrc)
{
	uint16_t	iCount;

	iCount = 0;
	while (iCount < sSrc.length())
	{
		if (sSrc[iCount] == '(' || sSrc[iCount] == ')' ||
			sSrc[iCount] == '<' || sSrc[iCount] == '=' ||
			sSrc[iCount] == '>' || sSrc[iCount] == '+' ||
			sSrc[iCount] == '^' || sSrc[iCount] == '|' ||
			sSrc[iCount] == '!' || sSrc[iCount] == '?' ||
			sSrc[iCount] == ' ' || sSrc[iCount] == '\t'||
			isAlpha(sSrc[iCount]) || sSrc[iCount] == '\n')
			iCount++;
		else {
			std::cout << "Syntax error!" << std::endl;
			exit(0);
		}
	}
}

void		CheckValidVec(std::vector<std::string> vSrc)
{
	uint16_t			iCount;

	iCount = 0;
	while (iCount < vSrc.size())
	{
		CheckForValid(vSrc[iCount]);
		iCount++;
	}
}

std::vector<std::string>		ParseInfo(std::string sInput)
{
	std::vector<std::string>	vInput;

	vInput = SplitString(sInput);
	vInput = RemoveComents(vInput);
	CheckValidVec(vInput);
	return vInput;
}