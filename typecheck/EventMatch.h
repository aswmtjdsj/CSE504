#include "all.h"
#include "ParserUtil.h"

class EventMatch {
public:
	const EFSAlist* getMatchCodeList(GlobalEntry *ge);
	const EFSAlist* getReadParamCodeList(PrimitivePatNode *ppn);
	const EFSA* getExitCode();
private:
	string strExitLabel_ = "EXIT";
};
