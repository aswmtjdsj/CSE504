//This file generates intermediate code for event matching
//Yansong

#include "EventMatch.h"

//Generating main part of matching
EFSAlist* EventMatch::getMatchCodeList(GlobalEntry *ge) {
	EFSAlist* elCodeList = new EFSAlist();
	elCodeList->addCode(new LabelCode("MatchBegin", 1));
	//IN R998
	elCodeList->addCode(new InCode(EFSA::OperandName::IN, getReg(EVENT_NAME_REG)));
	//JMPC EQ R998 0 EXIT
	IntRelationCode* ircpCond = new IntRelationCode(EFSA::OperandName::EQ,
		getReg(EVENT_NAME_REG), "0");
	LabelCode* lcpExitLabel = new LabelCode(strExitLabel());
	elCodeList->addCode(new JumpCode(EFSA::OperandName::JMPC, ircpCond, lcpExitLabel));

	int iCnt = 0;
	//jump to rules by event name
	vector<RuleNode*> rules = ge->rules();
	for (auto it = rules.begin(); it != rules.end(); it++) {
		LabelCode* lcpLabel = new LabelCode((*it)->ruleLabel());
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
		elCodeList->addCode(new LabelCode("Match" + numToString(iCnt), 1)); 
		iCnt++;
	}
	elCodeList->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, 
		new LabelCode("MatchBegin")));
	return elCodeList;
}

//Generating code for reading parameters
EFSAlist* EventMatch::getReadParamCodeList(PrimitivePatNode *ppn) {
	int iRegNum = EVENT_PARAM_REG_MAX - EVENT_PARAM_REG_MIN + 1;
	//assign registers from low to high
	int iIRegMin = EVENT_PARAM_REG_MIN;
	int iIRegMax = EVENT_PARAM_REG_MIN + iRegNum / 2 - 1;
	int iFRegMin = iIRegMax + 1;
	int iFRegMax = EVENT_PARAM_REG_MAX;

	EFSAlist* elCodeList = new EFSAlist;
	// any
	auto ptrTypeVector = ppn->event()->type()->argTypes();
	if (ptrTypeVector == nullptr) {
		return nullptr;
	}
	
	int iCurIReg = iIRegMin;
	int iCurFReg = iFRegMax;
	for (auto it = ptrTypeVector->begin(); it != ptrTypeVector->end(); it++) {
		auto type = *it;
		if (type->isInt(type->tag())) {
			elCodeList->addCode(new InCode(EFSA::OperandName::INT, 
				getReg(iCurIReg)));
				iCurIReg++;
		}
		if (type->isFloat(type->tag())) {
			elCodeList->addCode(new InCode(EFSA::OperandName::INF,
				getReg(iCurFReg)));
				iCurFReg++;
		}
		if (iCurIReg > iIRegMax || iCurFReg > iFRegMax) {
			cerr << "Due to register resource limitation, parameters of an event cannot exceed " 
			<< numToString(iIRegMax - iIRegMin + 1) << " for integers or " 
			<< numToString(iFRegMax - iIRegMin + 1) << " for floats." << endl;
			break;
		}
	}
	return elCodeList;
}

EFSA* EventMatch::getExitCode() {
	return new LabelCode(strExitLabel(), 1);
}
