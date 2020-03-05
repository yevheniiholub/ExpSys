#include "MainHeader.hpp"

void	showUsage()
{
	printf("/************** expert_system usage: ******************/\n");
	printf("/                                                      /\n");
	printf("/ ./expert_system [filename] [flags]                   /\n");
	printf("/                                                      /\n");
	printf("/----------------------/FLAGS/-------------------------/\n");
	printf("/ -d     debug mode                                    /\n");
	printf("/ -s     standart input mode                           /\n");
	printf("/ -w     output in file                                /\n");
	printf("/ -f     iteractive fact validation                    /\n");
	printf("/******************************************************/\n");
}

void		checkBreak(t_flags *fBonuses, ExpSysClass *expClass)
{
    std::string buff;
	uint16_t	iCount;

	iCount = 0;
	std::cout << "Enter new facts (A-Z) or \"exit\": ";
    std::getline(std::cin, buff);
	if (!buff.find("exit"))
		fBonuses->fF = 0;
	else
	{
		while (iCount < buff.length())
		{
			if (!isAlpha(buff[iCount]))
			{
				std::cout << "Invalind fact name!" << std::endl;
				exit (1);
			}
			iCount++;
		}
		expClass->setFacts(buff);
		expClass->clearMembers();
		writeMembers(expClass);
	}
}

int		main(int iArgc, char **sArgv)
{
	t_flags						fBonuses;
	std::string 				sInput;
	std::vector<std::string>	vInput;
	ExpSysClass 				expClass;

	if (iArgc == 1)
		showUsage();
	else
	{
		sInput = resolveFlags(&fBonuses, sArgv);
		vInput = ParseInfo(sInput);
		expClass = writeInfo(vInput);
		while (1)
		{
			solver(&expClass, fBonuses);
			if (!fBonuses.fF)
		 		break ;
			checkBreak(&fBonuses, &expClass);
			if (!fBonuses.fF)
		 		break ;
		}
	}
}
	