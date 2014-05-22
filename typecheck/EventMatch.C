#include "all.h"
#include "ParserUtil.h"

EFSAlist* eventMatch(GlobalEntry *ge) {
	const string strExitLabel = "EXIT";
	//EFSAlist* elCodeList = new EFSAlist();
	//elCodeList->addCode(new LabelCode("Globalbegin", 1));
	//IN R998
/*	elCodeList->addCode(new InCode(EFSA::OperandName::IN, getReg(EVENT_NAME_REG)));
	//JMPC EQ R998 0 EXIT
	IntRelationCode* ircpCond = new IntRelationCode(EFSA::OperandName::EQ,
		getReg(EVENT_NAME_REG), "0");
	LabelCode* lcpExitLabel = new LabelCode(strExitLabel);
	elCodeList->addCode(new JumpCode(EFSA::OperandName::JMPC, ircpCond, lcpExitLabel));

	//jump to rules by event name
	vector<RuleNode*> rules = ge->rules();
	for (auto it = rules.begin(); it != rules.end(); it++) {
		LabelCode* lcpLabel = new LabelCode((*it)->label());
		//"any" events
		PrimitivePatNode* pPatNode = (PrimitivePatNode*)((*it)->pat());
		if (pPatNode->event() == NULL) {
			elCodeList->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, lcpLabel));
		} else {
		//usual events
			int iRegNum = (*it)->regNum();
			IntRelationCode *ircpCond = new IntRelationCode(
				EFSA::OperandName::EQ, getReg(iRegNum), getReg(EVENT_NAME_REG));
			elCodeList->addCode(new JumpCode(EFSA::OperandName::JMPC,
				ircpCond, lcpLabel));
		}	
	}
*/
}
