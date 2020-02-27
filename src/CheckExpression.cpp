#include "MainHeader.hpp"

void        alphaCharCase(std::string inst, uint16_t iCount, std::vector<MemberClass> members, uint16_t *status)
{
    if (getMemberStatus(inst[iCount], members) && inst[iCount - 1] != '+' && inst[iCount - 1] != '^' && inst[iCount - 1] != '!')
    {
        printf ("\nString \"%s\" with counter %i is under case 1!\n\n", inst.c_str(), iCount);
        *status = 1;
    }
    if (getMemberFact(inst[iCount], members))
    {
        printf ("\nString \"%s\" with counter %i is under case 2!\n\n", inst.c_str(), iCount);
        *status = 1;
    }
}

void        orCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
    {
        printf("\nif (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')\n\n");
        if (getMemberStatus(instruction[iCountStr + 1], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 3!\n\n", instruction.c_str(), iCountStr);
            *status = 1;
        }
    }
    else
    {
        printf("\n!if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')\n\n");
        if (getMemberStatus(instruction[iCountStr + 2], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 4!\n\n", instruction.c_str(), iCountStr);
            *status = 1;
        }
    }
}

void        andCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (*status)
    {
        printf("\nif (status)\n\n");
        if (getMemberStatus(instruction[iCountStr + 2], members) && instruction[iCountStr + 1] == '!')
        {
            printf ("\nString \"%s\" with counter %i is under case 7!\n\n", instruction.c_str(), iCountStr);
            *status = 0;
        }
        if (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')
        {
            printf ("\nif (instruction[iCountStr + 1] >= 'A' && instruction[iCountStr + 1] <= 'Z')\n\n");
            if (!getMemberStatus(instruction[iCountStr + 1], members))
            {
                printf ("\nString \"%s\" with counter %i is under case 8!\n\n", instruction.c_str(), iCountStr);
                *status = 0;
            }
        }
    }
    else
    {
        printf ("\nString \"%s\" with counter %i is under case 9!\n\n", instruction.c_str(), iCountStr);
        *status = 0;
    }
}

void        xorCharCase(std::string instruction, uint16_t iCountStr, std::vector<MemberClass> members, uint16_t *status)
{
    if (*status)
    {
        printf ("\nif (status) %i\n\n", *status);
        if (instruction[iCountStr + 1] == '!' && !getMemberStatus(instruction[iCountStr + 2], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 10!\n\n", instruction.c_str(), iCountStr);
            *status = 0;
        }
        if (getMemberStatus(instruction[iCountStr + 1], members) && !getMemberFact(instruction[iCountStr + 1], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 11!\n\n", instruction.c_str(), iCountStr);
            *status = 0;
        }
    }
    else
    {
        printf ("\n!if (status)\n\n");
        if (instruction[iCountStr + 1] == '!' && !getMemberStatus(instruction[iCountStr + 2], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 12!\n\n", instruction.c_str(), iCountStr);
            *status = 1;
        }
        if (getMemberStatus(instruction[iCountStr + 1], members))
        {
            printf ("\nString \"%s\" with counter %i is under case 13!\n\n", instruction.c_str(), iCountStr);
            *status = 1;
        }
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
        printf("\nCycle start with data String: %s, counter: %i, ex: %i, prev: %i, status: %i, rec: %i\n\n", instruction.c_str(), iCountStr, iActive, iNeg, status, rec);
        if (instruction[iCountStr] == '|')
        {
            printf("\nelse if (instruction[iCountStr] == '|')\n\n");
            if (!status)
            {
                printf("\nif (!status)\n\n");
                orCharCase(instruction, iCountStr, members, &status);
            }
            else
            {
                printf ("\nString \"%s\" with counter %i is under case 5!\n\n", instruction.c_str(), iCountStr);
                iActive++;
            }
            if (iActive && !rec && isInLine(instruction))
            {
                printf ("\nString \"%s\" with counter %i is under case 6!\n\n", instruction.c_str(), iCountStr);
                return (1);
            }
        }
        else if (instruction[iCountStr] == ')' || instruction[iCountStr] == '(')
        {
            printf ("\nelse if (instruction[iCountStr] == ')' || instruction[iCountStr] == '(')\n\n");
            if (instruction[iCountStr] == '(')
            {
                printf ("\nif (instruction[iCountStr] == '(')\n\n");
                if (instruction[iCountStr - 1] == '!')
                    iNeg = 1;
                status = isTrue(status, 1, members, instruction.substr(iCountStr + 1, (instruction.length() + 1 - iCountStr)));
                while (iCountStr < instruction.length() && instruction[iCountStr] != ')')
                    iCountStr++;
                if (status && iNeg)
                {
                    printf ("\nString \"%s\" with counter %i is under case 14!\n\n", instruction.c_str(), iCountStr);
                    status = 0;
                }
                else if (!status && iNeg)
                {
                    printf ("\nString \"%s\" with counter %i is under case 15!\n\n", instruction.c_str(), iCountStr);
                    status = 1;
                }
            }
        }
        else if (instruction[iCountStr] >= 'A' && instruction[iCountStr] <= 'Z')
        {
            printf("\nif (instruction[iCountStr] >= 'A' && instruction[iCountStr] <= 'Z')\n\n");
            alphaCharCase(instruction, iCountStr, members, &status);
        }
        else if (instruction[iCountStr] == '+')
        {
            printf("\nelse if (instruction[iCountStr] == '+')\n\n");
            andCharCase(instruction, iCountStr, members, &status);
        }
        else if (instruction[iCountStr] == '^')
        {
            printf ("\nelse if (instruction[iCountStr] == '^')\n\n");
            xorCharCase(instruction, iCountStr, members, &status);
        }
        else
        {
            printf ("\nELSE\n\n");
            if (iCountStr - 1 < 0 && !getMemberStatus(instruction[iCountStr + 1], members))
            {
                printf ("\nString \"%s\" with counter %i is under case 16!\n\n", instruction.c_str(), iCountStr);
                status = 1;
            }
        }
        iCountStr++;
    }
    return status;
}