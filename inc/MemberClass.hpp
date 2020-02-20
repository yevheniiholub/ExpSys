#ifndef MEMBERCLASS
# define MEMBERCLASS

# include <iostream>
# include <fstream>
# include <string>
# include <vector>

class MemberClass
{
public:
	MemberClass();
	MemberClass(uint8_t newName, uint16_t newIsTrue, uint16_t newFact);
	~MemberClass();
	uint8_t		getName(void);
	uint16_t	getIsTrue(void);
	uint16_t	getFact(void);
	void		setName(uint8_t c);
	void		setIsTrue(uint16_t c);
	void		setFact(uint16_t i);

private:
	uint8_t		_name;
	uint16_t	_isTrue;
	uint16_t	_fact;
};

#endif