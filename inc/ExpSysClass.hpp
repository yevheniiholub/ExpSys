#ifndef EXPSYSCLASS
# define EXPSYSCLASS

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "MemberClass.hpp"

class MemberClass;

class ExpSysClass
{
    public:
        ExpSysClass                 ();
        ~ExpSysClass                ();
        std::string				    getQue(void);
        std::string				    getFacts(void);
        std::vector<std::string>    getInstCond(void);
        std::vector<std::string>    getInstRes(void);
        std::vector<uint16_t>	    getOnlyIf(void);
        std::vector<MemberClass>    getMembers(void);
        void                        clearMembers(void);
        void					    setQue(std::string s);
        void					    setFacts(std::string s);
        void					    setInstCond(std::vector<std::string> v);
        void					    setInstRes(std::vector<std::string> v);
        void					    setOnlyIf(std::vector<uint16_t> v);
        void					    setMembers(std::vector<MemberClass> v);
        void					    addMember(MemberClass newMember);
        void                        changeMemberStatus(uint16_t iCount, uint16_t iStatus);
        void                        changeMemberFact(uint16_t iCount, uint16_t iFact);

    private:
        std::string					_que;
        std::string					_facts;
        std::vector<uint16_t>		_onlyIf;
        std::vector<MemberClass>	_members;
        std::vector<std::string>	_instCond;
        std::vector<std::string>	_instRes;
};

#endif