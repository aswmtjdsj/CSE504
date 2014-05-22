#include "all.h"
#include "ParserUtil.h"

class EventMatch {
public:
	EventMatch(string str) : strExitLabel_(str) {};
	EFSAlist* getMatchCodeList(GlobalEntry *ge);
	EFSAlist* getReadParamCodeList(RuleNode* pRuleNode);
	EFSA* getExitCode();

	string strExitLabel(){return strExitLabel_;}
	void strExitLabel(string str){strExitLabel_=str;}

private:
	string strExitLabel_ ;
};
