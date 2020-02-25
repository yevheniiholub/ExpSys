#include "MainHeader.hpp"

void            showRes(ExpSysClass infoClass)
{
    uint16_t iCountStr;
    uint16_t iCountVec;

    iCountStr = 0;
    iCountVec = 0;
    while (iCountStr < infoClass.getQue().length())
    {
        while (iCountVec < infoClass.getMembers().size())
        {
            if (infoClass.getMembers()[iCountVec].getName() == infoClass.getQue()[iCountStr])
            {
                std::cout << "Member \"" << infoClass.getQue()[iCountStr] << "\" is ";
                if (infoClass.getMembers()[iCountVec].getIsTrue() && infoClass.getMembers()[iCountVec].getFact())
                    std::cout << "true!" << std::endl;
                else if (infoClass.getMembers()[iCountVec].getIsTrue() && infoClass.getMembers()[iCountVec].getFact())
                    std::cout << "ambiguous..." << std::endl;
                else
                    std::cout << "false!" << std::endl;

            }
            iCountVec++;
        }
        iCountStr++;
    }
}

static uint16_t checkFacts(std::vector<MemberClass> members, std::string instruction)
{
    uint16_t iCountStr;
    uint16_t iCountVec;

    iCountStr = 0;
    while (iCountStr < instruction.length())
    {
        iCountVec = 0;
        while (iCountVec < members.size())
        {
            if (members[iCountVec].getName() == instruction[iCountStr])
            {
                if (members[iCountVec].getFact() == 1)
                    return (1);
            }
            iCountVec++;
        }
        iCountStr++;
    }
    return (0);
}

static uint16_t isInLine(std::string instruction)
{
    uint16_t iCountStr;
    uint16_t iCountCol;
    uint16_t iCountOr;

    iCountStr = 0;
    iCountCol = 0;
    iCountOr = 0;
    while (iCountStr < instruction.length())
    {
        if (instruction[iCountStr] == '|')
            iCountOr++;
        if (instruction[iCountStr] == '(')
            iCountCol++;
        iCountStr++;
    }
    if (iCountOr & !iCountCol)
        return (1);
    return (0);
}

uint16_t    getMemberStatus(uint8_t name, std::vector<MemberClass> members)
{
    uint16_t iCountVec;

    iCountVec = 0;
    while (iCountVec < members.size())
    {
        if (members[iCountVec].getName() == name && members[iCountVec].getIsTrue())
            return 1;
        iCountVec++;
    }
    return 0;
}

uint16_t    getMemberFact(uint8_t name, std::vector<MemberClass> members)
{
    uint16_t iCountVec;

    iCountVec = 0;
    while (iCountVec < members.size())
    {
        if (members[iCountVec].getName() == name && members[iCountVec].getIsTrue())
            return (members[iCountVec].getFact());
        iCountVec++;
    }
    return 0;
}

uint16_t    changeMember(uint16_t fact, uint16_t stat, uint8_t name, ExpSysClass infoClass)
{
    uint16_t iCountVec;

    iCountVec = 0;
    while (iCountVec < infoClass.getMembers().size())
    {
        if (infoClass.getMembers()[iCountVec].getName() == name)
        {
            if (infoClass.getMembers()[iCountVec].getIsTrue() == stat)
                return (0);
            else
            {
                infoClass.getMembers()[iCountVec].setFact(fact);
                infoClass.getMembers()[iCountVec].setIsTrue(stat);
                return (1);
            }
        }
        iCountVec++;
    }
    return (0);
}

uint16_t	changeInfo(ExpSysClass inputInfo, uint16_t rev, uint16_t index)
{
    std::string sCond;
    std::string sRes;
    uint16_t    FactRes;
    uint16_t    iCountStr;
    uint16_t    iResult;

    iCountStr = 0;
    iResult = 0;
    if (rev)
    {
        sCond = inputInfo.getInstRes()[index];
        sRes = inputInfo.getInstCond()[index];
    }
    else
    {
        sCond = inputInfo.getInstCond()[index];
        sRes = inputInfo.getInstRes()[index];
    }
    FactRes = checkFacts(inputInfo.getMembers(), sCond);
    while (iCountStr < sRes.length())
    {
        if (sRes[iCountStr] >= 'A' && sRes[iCountStr] <= 'Z')
        {
            if (sRes[iCountStr - 1] != '!')
            {
                if (sRes[iCountStr - 1] == '|' || sRes[iCountStr + 1] == '|' || sRes[iCountStr - 1] == '^' || sRes[iCountStr + 1] == '^' || FactRes)
                    iResult += changeMember(1, 1, sRes[iCountStr], inputInfo);
                else
                    iResult += changeMember(0, 1, sRes[iCountStr], inputInfo);
            }
        }
        if (sRes[iCountStr - 1] == '!')
        {
            if (getMemberStatus(sRes[iCountStr], inputInfo.getMembers()))
            {
                std::cout << "Contradiction error" << std::endl;
                exit (0);
            }
        }
        iCountStr++;
    }
    return (iResult);
}

uint16_t	isTrue(uint16_t status, uint16_t rec, std::vector<MemberClass> members, std::string instruction)
{
    uint16_t iCountStr;
    uint16_t iActive;
    uint16_t iNeg;

    iCountStr = 0;
    iActive = 0;
    iNeg = 0;
    while (iCountStr < instruction.length())
    {
        if (instruction[iCountStr] >= 'A' && instruction[iCountStr] <= 'Z')
        {
            if (getMemberStatus(instruction[iCountStr], members) && instruction[iCountStr - 1] != '+' && instruction[iCountStr - 1] != '^', instruction[iCountStr - 1] != '!')
                status = 1;
            if (getMemberFact(instruction[iCountStr], members))
                status = 1;
        }
        else if (instruction[iCountStr] == '|')
        {
            if (!status)
            {
                if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
                {
                    if (getMemberStatus(instruction[iCountStr + 1], members))
                        status = 1;
                }
                else
                {
                    if (getMemberStatus(instruction[iCountStr + 2], members))
                        status = 1;
                }
            }
            else
                iActive++;
            if (iActive && !rec && isInLine(instruction))
                return (1);
        }
        else if (instruction[iCountStr] == '+')
        {
            if (status)
            {
                if (getMemberStatus(instruction[iCountStr + 2], members) && instruction[iCountStr + 1] == '!')
                    status = 0;
                if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
                    if (getMemberStatus(instruction[iCountStr + 1], members))
                        status = 0;
            }
            else
                status = 0;
        }
        else if (instruction[iCountStr] == '^')
        {
            if (status)
            {
                if (instruction[iCountStr + 1] != '!' && !getMemberStatus(instruction[iCountStr + 2], members))
                    status = 0;
                if (getMemberStatus(instruction[iCountStr + 1], members) && !getMemberFact(instruction[iCountStr + 1], members))
                    status = 0;
            }
            else
            {
                if (instruction[iCountStr + 1] != '!' && !getMemberStatus(instruction[iCountStr + 2], members))
                    status = 1;
                if (getMemberStatus(instruction[iCountStr + 1], members))
                    status = 1;
            }
        }
        else if (instruction[iCountStr] == ')' || instruction[iCountStr] == '(')
        {
            if (instruction[iCountStr] == '(')
            {
                if (instruction[iCountStr - 1] == '!')
                    iNeg = 1;
                status = isTrue(status, 1, members, instruction.substr(iCountStr + 1, (instruction.length() + 1 - iCountStr)));
                while (iCountStr < instruction.length() && instruction[iCountStr] != ')')
                    iCountStr++;
                if (status && iNeg)
                    status = 0;
                else if (!status && iNeg)
                    status = 1;
            }
        }
        else
            if (iCountStr - 1 < 0 && !getMemberStatus(instruction[iCountStr + 1], members))
                status = 1;
        iCountStr++;
    }
    return status;
}

void						solver(ExpSysClass inputInfo)
{
	uint16_t	iCount;
	uint16_t	iBreak;

	while (true)
	{
		iCount = 0;
		iBreak = 0;
		while (iCount < inputInfo.getInstCond().size())
		{
			if (!inputInfo.getOnlyIf()[iCount])
			{
				if (isTrue(0, 0, inputInfo.getMembers(), inputInfo.getInstCond()[iCount]))
					iBreak = changeInfo(inputInfo, 0, iCount);
			}
			else
			{
                if (isTrue(0, 0, inputInfo.getMembers(), inputInfo.getInstRes()[iCount]))
					iBreak = changeInfo(inputInfo, 1, iCount);
                if (isTrue(0, 0, inputInfo.getMembers(), inputInfo.getInstCond()[iCount]))
					iBreak = changeInfo(inputInfo, 0, iCount);
			}
            iCount++;
		}
        std::cout << "herddde" << std::endl;
        if (!iBreak)
            break ;
	}
    showRes(inputInfo);
}