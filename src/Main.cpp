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

uint16_t		checkBreak(ExpSysClass *inputInfo)
{
	if (!inputInfo->getFFlag())
		return (1);
	return (0);
}

int		main(int iArgc, char **sArgv)
{
	std::string 				sInput;
	std::vector<std::string>	vInput;
	ExpSysClass 				expClass;
	uint16_t					iBreak;

	iBreak = 0;
	if (iArgc == 1)
		showUsage();
	else
	{
		printf ("Flag stat -d %i -s %i -w %i -f %i\n", expClass.getDFlag(), expClass.getSFlag(), expClass.getWFlag(), expClass.getFFlag());
		sInput = resolveFlags(&expClass, sArgv);
		vInput = ParseInfo(sInput);
		expClass = writeInfo(vInput);
		printf ("Flag stat -d %i -s %i -w %i -f %i\n", expClass.getDFlag(), expClass.getSFlag(), expClass.getWFlag(), expClass.getFFlag());
		// while (1)
		// {
		// 	solver(&expClass);
		// 	iBreak = checkBreak(&expClass);
		// 	if (iBreak)
		// 		break ;
		// }
	}
}
	