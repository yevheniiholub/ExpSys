#include "MainHeader.hpp"

void            showRes(ExpSysClass infoClass, t_flags fBonuses)
{
    uint16_t        iCountStr;
    uint16_t        iCountVec;
    std::string     sRes;
    std::ofstream   fileOut("output_expSys.txt");

    iCountStr = 0;
    while (iCountStr < infoClass.getQue().length())
    {
        iCountVec = 0;
        while (iCountVec < infoClass.getMembers().size())
        {

            if (infoClass.getMembers()[iCountVec].getName() == infoClass.getQue()[iCountStr])
            {
                sRes += "Member \"";
                sRes.push_back(infoClass.getQue()[iCountStr]);
                sRes += "\" is ";
                if (infoClass.getMembers()[iCountVec].getIsTrue() && !infoClass.getMembers()[iCountVec].getFact())
                    sRes += "true!\n";
                else if (infoClass.getMembers()[iCountVec].getIsTrue() && infoClass.getMembers()[iCountVec].getFact())
                    sRes += "ambiguous...\n";
                else
                    sRes += "false!\n";

            }
            iCountVec++;
        }
        iCountStr++;
    }
    if (fBonuses.fW)
    {
        if (fileOut.fail())
        {
            std::cout << "Error creating file! :(" << std::endl;
            exit(1);
        }
        else
        {
            fileOut << sRes;
            fileOut.close();
        }
    }
    else
        std::cout << sRes; 
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

uint16_t    changeMember(uint16_t fact, uint16_t stat, uint8_t name, ExpSysClass *infoClass, t_flags fBonuses)
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
                if (fBonuses.fD)
                {
                    std::cout << "Now member : " << infoClass->getMembers()[iCountVec].getName();
                    if (fact)
                        std::cout << " is ambigious!" << std::endl;
                    else
                        std::cout << " is true!" << std::endl;
                }
                infoClass->changeMemberFact(iCountVec, fact);
                infoClass->changeMemberStatus(iCountVec, stat);
                return (1);
            }
        }
        iCountVec++;
    }
    return (0);
}

uint16_t	changeInfo(ExpSysClass *inputInfo, uint16_t rev, uint16_t index, t_flags fBonuses)
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
                    iResult += changeMember(1, 1, sRes[iCountStr], inputInfo, fBonuses);
                else
                    iResult += changeMember(0, 1, sRes[iCountStr], inputInfo, fBonuses);
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

void						solver(ExpSysClass *inputInfo, t_flags fBonuses)
{
	uint16_t	iCount;
	uint16_t	iBreak;

    iCount = 0;
    iBreak = 0;
    while (iCount < inputInfo->getInstCond().size())
    {
        if (fBonuses.fD)
            std::cout << "\nNow consider instruction \"" << inputInfo->getInstCond()[iCount] << "\" and consequence \"" << inputInfo->getInstRes()[iCount] << "\" ";
        if (!inputInfo->getOnlyIf()[iCount])
        {
            if (fBonuses.fD)
                std::cout << "With simple implementation condition" << std::endl;
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstCond()[iCount], fBonuses))
                iBreak = changeInfo(inputInfo, 0, iCount, fBonuses);
        }
        else
        {
            if (fBonuses.fD)
                std::cout << "With \"if and only if\" implementation condition" << std::endl;
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstRes()[iCount], fBonuses))
                iBreak = changeInfo(inputInfo, 1, iCount, fBonuses);
            if (isTrue(0, 0, inputInfo->getMembers(), inputInfo->getInstCond()[iCount], fBonuses))
                iBreak = changeInfo(inputInfo, 0, iCount, fBonuses);
        }
        iCount++;
    }
    showRes(*inputInfo, fBonuses);
}