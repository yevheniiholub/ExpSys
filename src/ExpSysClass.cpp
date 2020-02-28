#include "ExpSysClass.hpp"

ExpSysClass::ExpSysClass()
{
    _dFlag = 0;
    _wFlag = 0;
    _fFlag = 0;
    _sFlag = 0;
}

ExpSysClass::~ExpSysClass()
{

}

std::string					ExpSysClass::getQue(void)
{
    return _que;
}

std::string					ExpSysClass::getFacts(void)
{
    return _facts;
}

std::vector<std::string>	ExpSysClass::getInstCond(void)
{
    return _instCond;
}

std::vector<std::string>	ExpSysClass::getInstRes(void)
{
    return _instRes;
}

std::vector<uint16_t>		ExpSysClass::getOnlyIf(void)
{
    return _onlyIf;
}

std::vector<MemberClass>	ExpSysClass::getMembers(void)
{
    return _members;
}

uint16_t                    ExpSysClass::getDFlag(void)
{
    return _dFlag;
}

uint16_t                    ExpSysClass::getWFlag(void)
{
    return _wFlag;
}

uint16_t                    ExpSysClass::getFFlag(void)
{
    return _fFlag;
}

uint16_t                    ExpSysClass::getSFlag(void)
{
    return _sFlag;
}

void                        ExpSysClass::setDFlag(uint16_t nFlag)
{
    _dFlag = nFlag;
}

void                        ExpSysClass::setWFlag(uint16_t nFlag)
{
    _wFlag = nFlag;
}

void                        ExpSysClass::setFFlag(uint16_t nFlag)
{
    _fFlag = nFlag;
}

void                        ExpSysClass::setSFlag(uint16_t nFlag)
{
    _sFlag = nFlag;
}


void						ExpSysClass::setQue(std::string s)
{
    _que = s;
}

void						ExpSysClass::setFacts(std::string s)
{
    _facts = s;
}

void						ExpSysClass::setInstCond(std::vector<std::string> v)
{
    _instCond = v;
}

void						ExpSysClass::setInstRes(std::vector<std::string> v)
{
    _instRes = v;
}

void						ExpSysClass::setOnlyIf(std::vector<uint16_t> v)
{
    _onlyIf = v;
}

void						ExpSysClass::setMembers(std::vector<MemberClass> v)
{
    _members = v;
}

void						ExpSysClass::addMember(MemberClass newMember)
{
    _members.push_back(newMember);
}


void                        ExpSysClass::changeMemberStatus(uint16_t iCount, uint16_t iStatus)
{
    _members[iCount].setIsTrue(iStatus);
}

void                        ExpSysClass::changeMemberFact(uint16_t iCount, uint16_t iFact)
{
    _members[iCount].setFact(iFact);
}
