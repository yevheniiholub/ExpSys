#include <MemberClass.hpp>

MemberClass::MemberClass()
{

}

MemberClass::MemberClass(uint8_t newName, uint16_t newIsTrue, uint16_t newFact)
{ 
    _name = newName;
    _isTrue = newIsTrue;
    _fact = newFact;
}

MemberClass::~MemberClass()
{

}

uint8_t		MemberClass::getName(void)
{
	return _name;
}

uint16_t	MemberClass::getIsTrue(void)
{
	return _isTrue;
}

uint16_t	MemberClass::getFact(void)
{
	return _fact;
}

void		MemberClass::setName(uint8_t c)
{
    _name = c;
}

void		MemberClass::setIsTrue(uint16_t c)
{
    _isTrue = c;
}

void		MemberClass::setFact(uint16_t i)
{
    _fact = i;
}
