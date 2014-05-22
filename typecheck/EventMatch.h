#include "all.h"
#include "ParserUtil.h"

class EventMatch {
public:
	EFSAlist* getMatchCodeList(GlobalEntry *ge);
	EFSAlist* getReadParamCodeList(PrimitivePatNode *ppn);
	EFSA* getExitCode();
private:
	string strExitLabel_ = "EXIT";
};
