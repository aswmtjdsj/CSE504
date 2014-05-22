#include "Optimizer.h"

void Optimizer::addBlock(EFSAlist* block){
	if (block!=NULL)
		blockList_.push_back(block);
}

void Optimizer::generateBasicBlock(vector<EFSA*> codeList){
	
	EFSAlist* block = NULL;
	for (auto iter=codeList.begin(); iter!=codeList.end(); iter++) {
		EFSA* code = (*iter);
	    	if (code->operatorType()==EFSA::OperatorType::LABEL){
			block = new EFSAlist();
			addBlock(block);
			block->addCode(code);
		}
		else if (code->operatorType()==EFSA::OperatorType::JUMP){
			block->addCode(code);
			block = new EFSAlist();
			addBlock(block);
		}
		else
			block->addCode(code);
	}
}

void Optimizer::algebraEquivalence(){
	/*
	for (auto iter=blockList_.begin(); iter!=blockList_.end(); iter++) {
		EFSAlist* block = (EFSAlist*)iter;
		for (auto it=block->getCodeList().begin(); it!=block->getCodeList().end(); it++) {
			EFSA* code = (*it);
			if (code->operatorType()==EFSA::OperatorType::INT_ARITH){

			}
		}
	}
	*/
}

void Optimizer::printBasicBlock(ostream& os){
	for (auto iter=blockList_.begin(); iter!=blockList_.end(); iter++) {
		EFSAlist* block = (*iter);
		block->codePrint(os);
		os<<endl;
	}
}
