//This file generates intermediate code for event matching
//Yansong

#include "EventMatch.h"

//Generating main part of matching
EFSAlist* EventMatch::getMatchCodeList(GlobalEntry *ge) {
	elCodeList_ = new EFSAlist();
	elCodeList_->addCode(new LabelCode("MatchBegin", 1));
	//IN R998
	elCodeList_->addCode(new InCode(EFSA::OperandName::IN, getReg(EVENT_NAME_REG)));
	elCodeList_->addCode(new MoveCode(EFSA::OperandName::MOVI, "0", getReg(EVENT_STATE_REG)));
	printString_("Input Event: ");
	printReg_(getReg(EVENT_NAME_REG));
	
	//JMPC EQ R998 10 EXIT
	IntRelationCode* ircpCond = new IntRelationCode(EFSA::OperandName::EQ,
		getReg(EVENT_NAME_REG), EXIT_INPUT_ASCII);
	LabelCode* lcpExitLabel = new LabelCode(strExitLabel());
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMPC, ircpCond, lcpExitLabel));

	int iCnt = 0;
	//jump to rules by event name
	vector<RuleNode*> rules = ge->rules();
	for (auto it = rules.begin(); it != rules.end(); it++) {
		LabelCode* lcpLabel = new LabelCode((*it)->ruleLabel());
		//"any" events
		PrimitivePatNode* pPatNode = (PrimitivePatNode*)((*it)->pat());
		if (pPatNode->event() == NULL) {
			elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, lcpLabel));
		} else {
		//usual events
			int iRegNum = (*it)->regNum();
			IntRelationCode *ircpCond = new IntRelationCode(
				EFSA::OperandName::EQ, getReg(iRegNum), getReg(EVENT_NAME_REG));
			elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMPC,
				ircpCond, lcpLabel));
		}	
		elCodeList_->addCode(new LabelCode("Match" + numToString(iCnt), 1)); 
		iCnt++;
	}
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, 
		new LabelCode("MatchBegin")));
	return elCodeList_;
}

//Generating code for reading parameters
EFSAlist* EventMatch::getReadParamCodeList(RuleNode* pRuleNode) {
	int iRegNum = EVENT_PARAM_REG_MAX - EVENT_PARAM_REG_MIN + 1;
	//assign registers from low to high
	int iIRegMin = EVENT_PARAM_REG_MIN;
	int iIRegMax = EVENT_PARAM_REG_MIN + iRegNum / 2 - 1;
	int iFRegMin = iIRegMax + 1;
	int iFRegMax = EVENT_PARAM_REG_MAX;

	elCodeList_ = new EFSAlist;
	// any
	PrimitivePatNode* ppn = (PrimitivePatNode*)(pRuleNode->pat());
	auto ptrTypeVector = ppn->event()->type()->argTypes();
	if (ptrTypeVector == nullptr) {
		return nullptr;
	}
	
	IntRelationCode *ircpCond = new IntRelationCode(EFSA::OperandName::EQ,
		getReg(EVENT_STATE_REG), "1");
	LabelCode* lcpSkipLabel = new LabelCode(pRuleNode->ruleSkipLabel());
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMPC,
		ircpCond, lcpSkipLabel));

	int iCurIReg = iIRegMin;
	int iCurFReg = iFRegMin;
	printString_("(");
	for (auto it = ptrTypeVector->begin(); it != ptrTypeVector->end(); it++) {
		if (it != ptrTypeVector->begin()) printString_(", ");
		auto type = *it;
		if (type->isInt(type->tag())) {
			elCodeList_->addCode(new InCode(EFSA::OperandName::INI, 
				getReg(iCurIReg)));
				printReg_(getReg(iCurIReg));
				iCurIReg++;
		}
		if (type->isFloat(type->tag())) {
			elCodeList_->addCode(new InCode(EFSA::OperandName::INF,
				getReg(iCurFReg)));
				printReg_(getReg(iCurFReg, 1));
				iCurFReg++;
		}
		if (iCurIReg > iIRegMax || iCurFReg > iFRegMax) {
			cerr << "Due to register resource limitation, parameters of an event cannot exceed " 
			<< numToString(iIRegMax - iIRegMin + 1) << " for integers or " 
			<< numToString(iFRegMax - iFRegMin + 1) << " for floats." << endl;
			break;
		}
	}
	printString_(")\\n");
	return elCodeList_;
}

EFSA* EventMatch::getExitCode() {
	return new LabelCode(strExitLabel(), 1);
}

void EventMatch::printReg_(string strReg) {
	auto opName = EFSA::OperandName::PRTI;
	if (strReg.substr(0, 1) == "F") {
		opName = EFSA::OperandName::PRTF;
	}
	elCodeList_->addCode(new PrintCode(opName, "", strReg));
}

void EventMatch::printString_(string str) {
	string strTarget = "\"" + str + "\"";
	elCodeList_->addCode(new PrintCode(EFSA::OperandName::PRTS, strTarget));
}
