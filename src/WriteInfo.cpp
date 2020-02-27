#include "MainHeader.hpp"

uint16_t				isUniqueMem(std::vector<MemberClass> inMem, uint8_t name)
{
	uint16_t iCount;

	iCount = 0;
	while (iCount < inMem.size())
	{
		if (inMem[iCount].getName() == name)
			return 0;
		iCount++;
	}
	return 1;
}

void					writeMembers(ExpSysClass *infoClass)
{
	uint16_t iCountStr;
	uint16_t iCountVec;

	iCountStr = -1;
	while (++iCountStr < infoClass->getFacts().length())
		if (isUniqueMem(infoClass->getMembers(), infoClass->getFacts()[iCountStr]))
			infoClass->addMember(MemberClass(infoClass->getFacts()[iCountStr], 1, 0));
	iCountStr = -1;
	while (++iCountStr < infoClass->getQue().length())
		if (isUniqueMem(infoClass->getMembers(), infoClass->getQue()[iCountStr]))
			infoClass->addMember(MemberClass(infoClass->getQue()[iCountStr], 0, 0));
	iCountVec = -1;
	while (++iCountVec < infoClass->getInstCond().size())
	{
		iCountStr = -1;
		while (++iCountStr < infoClass->getInstCond()[iCountVec].length())
			if (infoClass->getInstCond()[iCountVec][iCountStr] >= 'A' &&
				infoClass->getInstCond()[iCountVec][iCountStr] <= 'Z')
				if (isUniqueMem(infoClass->getMembers(), infoClass->getInstCond()[iCountVec][iCountStr]))
					infoClass->addMember(MemberClass(infoClass->getInstCond()[iCountVec][iCountStr], 0, 0));
	}
	iCountVec = -1;
	while (++iCountVec < infoClass->getInstRes().size())
	{
		iCountStr = -1;
		while (++iCountStr < infoClass->getInstRes()[iCountVec].length())
			if (infoClass->getInstRes()[iCountVec][iCountStr] >= 'A' &&
				infoClass->getInstRes()[iCountVec][iCountStr] <= 'Z')
				if (isUniqueMem(infoClass->getMembers(), infoClass->getInstRes()[iCountVec][iCountStr]))
					infoClass->addMember(MemberClass(infoClass->getInstRes()[iCountVec][iCountStr], 0, 0));
	}
}

int						CheckProcessedString(std::string sInput)
{
	uint16_t iCount;

	iCount = 0;
	while (iCount < sInput.length())
	{
		if ((sInput[iCount] >= 'A' && sInput[iCount] <= 'Z') ||
			sInput[iCount] == '(' || sInput[iCount] == ')' ||
			sInput[iCount] == '^' || sInput[iCount] == '+' ||
			sInput[iCount] == '|' || sInput[iCount] == '!'||
			sInput[iCount] == '=' || sInput[iCount] == '\n')
			iCount++;
		else
		{
			std::cout << "\"" << sInput[iCount] << "\"" << std::endl;
			std::cout << "instruction error!" << std::endl;
			exit(0);
		}
	}
	return 0;
}

ExpSysClass				WriteInputInfo(std::string que, std::string fac, std::vector<std::string> inst)
{
	ExpSysClass					ResToReturn;
	uint16_t					iCountVec;
	std::vector<std::string>	vCond;
	std::vector<std::string>	vRes;
	std::vector<uint16_t>		vOnlyIf;
	

	iCountVec = 0;
	ResToReturn.setFacts(fac);
	ResToReturn.setQue(que);
	while (iCountVec < inst.size())
	{
		if (inst[iCountVec].find("<=>") > 0 && inst[iCountVec].find("<=>") < inst[iCountVec].size())
		{
			vCond.push_back(inst[iCountVec].substr(0, inst[iCountVec].find("<=>")));
			vRes.push_back(inst[iCountVec].substr((inst[iCountVec].find("<=>") + 3), (inst[iCountVec].size() - inst[iCountVec].find("<=>"))));
			vOnlyIf.push_back(1);
		}
		else if (inst[iCountVec].find("=>") > 0 && inst[iCountVec].find("=>") < inst[iCountVec].size())
		{
			vCond.push_back(inst[iCountVec].substr(0, inst[iCountVec].find("=>")));
			vRes.push_back(inst[iCountVec].substr((inst[iCountVec].find("=>") + 2), (inst[iCountVec].size() - inst[iCountVec].find("<=>"))));
			vOnlyIf.push_back(0);
		}
		else
		{
			std::cout << "instruction error!" << std::endl;
			exit(0);
		}
		if (CheckProcessedString(vRes[iCountVec]) || CheckProcessedString(vCond[iCountVec]))
		{
			std::cout << "instruction error!" << std::endl;
			exit(0);
		}
		iCountVec++;
	}
	ResToReturn.setInstCond(vCond);
	ResToReturn.setInstRes(vRes);
	ResToReturn.setOnlyIf(vOnlyIf);
	writeMembers(&ResToReturn);
	return ResToReturn;
}

void					sortInfo(std::string *que, std::string *fac, std::vector<std::string> *inst, std::vector<std::string> sInputInfo)
{
	uint16_t	iCountVec;

	iCountVec = 0;
	while(iCountVec < sInputInfo.size())
	{
		if (sInputInfo[iCountVec].length() == 0)
			;
		else if (sInputInfo[iCountVec][0] == '?')
			*que += sInputInfo[iCountVec].substr(1, sInputInfo[iCountVec].length());
		else if (sInputInfo[iCountVec][0] == '=')
			*fac += sInputInfo[iCountVec].substr(1, sInputInfo[iCountVec].length());
		else
			inst->push_back(sInputInfo[iCountVec]);
		iCountVec++;
	}
}

ExpSysClass				writeInfo(std::vector<std::string> sInputInfo)
{
	ExpSysClass					InfoToWork;
	std::string					que;
	std::string					fac;
	std::vector<std::string>	inst;

	sortInfo(&que, &fac, &inst, sInputInfo);
	InfoToWork = WriteInputInfo(que, fac, inst);
	return InfoToWork;
}