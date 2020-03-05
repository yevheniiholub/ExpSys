#include "MainHeader.hpp"

uint16_t              isAllNum(std::string src)
{
    uint16_t iCount;

    iCount = -1;
    if (src.empty())
        return (0);
    while (++iCount < src.length())
        if (!isdigit(src[iCount]))
            return (0);
    return (1);
}

std::string           getStandartInput()
{
    std::string res;
    std::string buff;
    uint16_t    iCount;
    uint16_t    iSize;

    std::cout << "Enter number of instruction (from 1 to 99): ";
    std::getline(std::cin, buff);
    if (isAllNum(buff) && buff.length() < 3)
        iSize = stoi(buff);
    else
    {
        std::cout << "Wrong nuber input!" <<std::endl;
        exit(1);
    }
    iCount = 0;
    while (iCount < iSize)
    {
        std::cout << "Enter instruction (" << iCount + 1 << "/" << iSize << ") :";
        std::getline(std::cin, buff);
        res += buff + "\n";
        iCount++;
    }
    std::cout << "Enter Facts :";
    std::getline(std::cin, buff);
    res += "=" + buff + "\n";
    std::cout << "Enter query :";
    std::getline(std::cin, buff);
    res += "?" + buff + "\n";
    return (res);
}

std::string            getInput(uint16_t sFlag, std::string filename)
{
    std::string res;

    if (filename.empty() && sFlag)
        res = getStandartInput();
    else if (!filename.empty() && !sFlag)
        res = ReadInfoFromFile(filename);
    else if (!filename.empty() && sFlag)
    {
        std::cout << "Use flag \"-s\" without name of file in argument" << std::endl;
        exit(1);
    }
    else if (filename.empty() && !sFlag)
    {
        std::cout << "No file name in arguments!" << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Argumet error!" << std::endl;
        exit(1);
    }
    return (res);
}

void                   init_flags(t_flags *fFlags)
{
    fFlags->fD = 0;
    fFlags->fF = 0;
    fFlags->fS = 0;
    fFlags->fW = 0;
}

std::string            resolveFlags(t_flags *fBonuses, char **argv)
{
    uint16_t        iCountArr;
    std::string     fileName;
    std::string     res;

    iCountArr = 1;
    fileName.clear();
    init_flags(fBonuses);
    while (argv[iCountArr])
    {
        if (!strcmp(argv[iCountArr], "-d") && !fBonuses->fD)
            fBonuses->fD = 1;
        else if (!strcmp(argv[iCountArr], "-s") && !fBonuses->fS)
            fBonuses->fS = 1;
        else if (!strcmp(argv[iCountArr], "-w") && !fBonuses->fW)
            fBonuses->fW = 1;
        else if (!strcmp(argv[iCountArr], "-f") && !fBonuses->fF)
            fBonuses->fF = 1;
        else
        {
            if (fileName.empty())
                fileName = argv[iCountArr];
            else
            {
                std::cout << "Wrong input parameters!" << std::endl;
                exit (1);
            }

        }
        iCountArr++;
    }
    res = getInput(fBonuses->fS, fileName);
    return (res);
}