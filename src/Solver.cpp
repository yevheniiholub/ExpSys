#include "MainHeader.hpp"

void            showRes(ExpSysClass infoClass)
{
    uint16_t iCountStr;
    uint16_t iCountVec;

    iCountStr = 0;
    while (iCountStr < infoClass.getQue().length())
    {
        iCountVec = 0;
        while (iCountVec < infoClass.getMembers().size())
        {

            if (infoClass.getMembers()[iCountVec].getName() == infoClass.getQue()[iCountStr])
            {
                std::cout << "Member \"" << infoClass.getQue()[iCountStr] << "\" is ";
                if (infoClass.getMembers()[iCountVec].getIsTrue() && !infoClass.getMembers()[iCountVec].getFact())
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

uint16_t      isInLine(std::string instruction)
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

uint16_t    changeMember(uint16_t fact, uint16_t stat, uint8_t name, ExpSysClass *infoClass)
{
    uint16_t iCountVec;

    iCountVec = 0;
    while (iCountVec < infoClass->getMembers().size())
    {
        if (infoClass->getMembers()[iCountVec].getName() == name)
        {
            if (infoClass->getMembers()[iCountVec].getIsTrue() == stat)
                return (0);
            else
            {
                infoClass->changeMemberFact(iCountVec, fact);
                infoClass->changeMemberStatus(iCountVec, stat);
                return (1);
            }
        }
        iCountVec++;
    }
    return (0);
}

uint16_t	changeInfo(ExpSysClass *inputInfo, uint16_t rev, uint16_t index)
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
        sCond = inputInfo->getInstRes()[index];
        sRes = inputInfo->getInstCond()[index];
    }
    else
    {
        sCond = inputInfo->getInstCond()[index];
        sRes = inputInfo->getInstRes()[index];
    }
    FactRes = checkFacts(inputInfo->getMembers(), sCond);
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
            if (getMemberStatus(sRes[iCountStr], inputInfo->getMembers()))
            {
                std::cout << "Contradiction error" << std::endl;
                exit (0);
            }
        }
        iCountStr++;
    }
    return (iResult);
}

void                        printStatus(ExpSysClass *inputInfo)
{
    uint16_t iCountStr = 0;
    uint16_t iCountVec = inputInfo->getMembers().size() - 1;

    printf("\n|Name|Status|Fact|\n------------------\n");
    while (iCountVec > 0)
    {
        printf("|\"%c\" |  %i   | %i  |\n", inputInfo->getMembers()[iCountVec].getName(), inputInfo->getMembers()[iCountVec].getIsTrue(), inputInfo->getMembers()[iCountVec].getFact());
        iCountVec--;
    }
    printf("------------------\n---Instructions---\n");
    while (iCountStr < inputInfo->getInstCond().size())
    {
        printf("%s => %s | if and only if %i\n", inputInfo->getInstCond()[iCountStr].c_str(), inputInfo->getInstRes()[iCountStr].c_str(), inputInfo->getOnlyIf()[iCountStr]);
        iCountStr++;
    }
}

void						solver(ExpSysClass *inputInfo)
{
	uint16_t	iCount;
	uint16_t	iBreak;

    iCount = 0;
    iBreak = 0;
    while (iCount < inputInfo->getInstCond().size())
    {
        if (!inputInfo->getOnlyIf()[iCount])
        {
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstCond()[iCount]))
                iBreak = changeInfo(inputInfo, 0, iCount);
        }
        else
        {
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstRes()[iCount]))
                iBreak = changeInfo(inputInfo, 1, iCount);
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstCond()[iCount]))
                iBreak = changeInfo(inputInfo, 0, iCount);
        }
        iCount++;
    }
    showRes(*inputInfo);
}