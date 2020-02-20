#include "ExpSysClass.hpp"

ExpSysClass::ExpSysClass()
{

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

