//This file generates intermediate code for event matching
//Yansong

#include "EventMatch.h"

//Generating main part of matching
EFSAlist* EventMatch::getMatchCodeList(GlobalEntry *ge) {
	elCodeList_ = new EFSAlist();

	// output error info
/*	elCodeList_->addCode(new LabelCode(LABEL_EVENT_ERR_TOO_MANY, 1));	
	printString_("Input:Line ");
	printReg_(getReg(EVENT_INPUT_NUM_REG));
	printString_(":Too many parameters input!\\n");
*/
	// match begin
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMP, nullptr,
		new LabelCode(LABEL_EVENT_MATCH_BEGIN)));
	elCodeList_->addCode(new LabelCode(LABEL_EVENT_MATCH_BEGIN, 1));

	//IN R998
	elCodeList_->addCode(new InCode(EFSA::OperandName::IN, getReg(EVENT_NAME_REG)));
	elCodeList_->addCode(new MoveCode(EFSA::OperandName::MOVI, "0", getReg(EVENT_STATE_REG)));
	
	//count input
/*	elCodeList_->addCode(new IntArithCode(IntArithCode::OperandNum::BINARY,
		EFSA::OperandName::ADD, getReg(EVENT_INPUT_NUM_REG), 
		getReg(EVENT_INPUT_NUM_REG), "1"));*/

	//JMPC EQ R998 10 EXIT
	IntRelationCode* ircpCond = new IntRelationCode(EFSA::OperandName::EQ,
		getReg(EVENT_NAME_REG), EXIT_INPUT_ASCII);
	LabelCode* lcpExitLabel = new LabelCode(strExitLabel());
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMPC, ircpCond, lcpExitLabel));
#ifdef EVENT_DEBUG
	printString_("Input Event: ");
	printReg_(getReg(EVENT_NAME_REG));
#endif
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
#ifdef EVENT_DEBUG
	printString_("(");
#endif
	for (auto it = ptrTypeVector->begin(); it != ptrTypeVector->end(); it++) {
#ifdef EVENT_DEBUG
		if (it != ptrTypeVector->begin()) printString_(", ");
#endif
		auto type = *it;
		if (type->isInt(type->tag())) {
			elCodeList_->addCode(new InCode(EFSA::OperandName::INI, 
				getReg(iCurIReg)));
				printReg_(getReg(iCurIReg));
				iCurIReg++;
		}
		if (type->isFloat(type->tag())) {
			elCodeList_->addCode(new InCode(EFSA::OperandName::INF,
				getReg(iCurFReg, 1)));
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
#ifdef EVENT_DEBUG
	printString_(")\n");
#endif
	// if too many parameters input
/*	elCodeList_->addCode(new InCode(EFSA::OperandName::INI, getReg(iCurIReg)));
	ircpCond = new IntRelationCode(EFSA::OperandName::NE, getReg(iCurIReg),
		EVENT_INPUT_NEXT_ASCII);
	LabelCode* lcpErrTooMany = new LabelCode(LABEL_EVENT_ERR_TOO_MANY);
	elCodeList_->addCode(new JumpCode(EFSA::OperandName::JMPC, ircpCond,
		lcpErrTooMany));
*/
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
	string strTarget = str;
	elCodeList_->addCode(new PrintCode(EFSA::OperandName::PRTS, strTarget));
}

EFSAlist* EventMatch::getLineNumPrintCode(RuleNode* pRuleNode) {
#ifdef EVENT_DEBUG
	elCodeList_ = new EFSAlist();
	printString_("Event in Line " + numToString(pRuleNode->line()) + " matched\n");
	return elCodeList_;
#else
	return nullptr;
#endif
}

EFSAlist* EventMatch::getInitializer() {
/*	elCodeList_ = new EFSAlist();
	// initialize input count reg
	elCodeList_->addCode(new MoveCode(EFSA::OperandName::MOVI, "0",
		getReg(EVENT_INPUT_NUM_REG)));
	return elCodeList_;*/
	return nullptr;
}
