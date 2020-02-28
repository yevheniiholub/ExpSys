#include "MainHeader.hpp"

void        alphaCharCase(std::string inst, uint16_t iCount, std::vector<MemberClass> members, uint16_t *status)
{
    if (getMemberStatus(inst[iCount], members) && inst[iCount - 1] != '+' && inst[iCount - 1] != '^' && inst[iCount - 1] != '!')
        *status = 1;
    if (getMemberFact(inst[iCount], members))
        *status = 1;
}

void        orCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
    {
        if (getMemberStatus(instruction[iCountStr + 1], members))
            *status = 1;
    }
    else
        if (getMemberStatus(instruction[iCountStr + 2], members))
            *status = 1;
}

void        andCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (*status)
    {
        if (getMemberStatus(instruction[iCountStr + 2], members) && instruction[iCountStr + 1] == '!')
            *status = 0;
        if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
            if (!getMemberStatus(instruction[iCountStr + 1], members))
                *status = 0;
    }
    else
        *status = 0;
}

void        xorCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (*status)
    {
        if (instruction[iCountStr + 1] == '!' && !getMemberStatus(instruction[iCountStr + 2], members))
            *status = 0;
        if (getMemberStatus(instruction[iCountStr + 1], members) && !getMemberFact(instruction[iCountStr + 1], members))
            *status = 0;
    }
    else
    {
        if (instruction[iCountStr + 1] == '!' && !getMemberStatus(instruction[iCountStr + 2], members))
            *status = 1;
        if (getMemberStatus(instruction[iCountStr + 1], members))
            *status = 1;
    }
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
        if (instruction[iCountStr] == '|')
        {
            if (!status)
                orCharCase(instruction, iCountStr, members, &status);
            else
                iActive++;
            if (iActive && !rec && isInLine(instruction))
                return (1);
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
        else if (instruction[iCountStr] >= 'A' && instruction[iCountStr] <= 'Z')
            alphaCharCase(instruction, iCountStr, members, &status);
        else if (instruction[iCountStr] == '+')
            andCharCase(instruction, iCountStr, members, &status);
        else if (instruction[iCountStr] == '^')
            xorCharCase(instruction, iCountStr, members, &status);
        else
            if (iCountStr - 1 < 0 && !getMemberStatus(instruction[iCountStr + 1], members))
                status = 1;
        iCountStr++;
    }
    return status;
}