#include "all.h"
#include "ParserUtil.h"

class EventMatch {
public:
	EventMatch(string str) : strExitLabel_(str) { elCodeList_ = nullptr; };
	EFSAlist* getMatchCodeList(GlobalEntry *ge);
	EFSAlist* getReadParamCodeList(RuleNode* pRuleNode);
	EFSA* getExitCode();

	string strExitLabel(){return strExitLabel_;}
	void strExitLabel(string str){strExitLabel_=str;}

private:
	void printReg_(string strReg);
	void printString_(string str);
	string strExitLabel_ ;
	EFSAlist* elCodeList_;
};
