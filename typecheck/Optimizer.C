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

/*
void Optimizer::algebraEquivalence(){
	
	for (auto iter=blockList_.begin(); iter!=blockList_.end(); iter++) {
		vector<EFSA*>* codeList = (*iter)->getCodeListPtr();
		for (auto it=codeList->begin(); it!=codeList->end(); it++){
			//(*it) = new LabelCode("zdd");
			EFSA* temp = (*it);
			if (temp->operatorType()==EFSA::OperatorType::INT_ARITH){
				IntArithCode* code = (IntArithCode*) temp;
				if (code->name()==EFSA::OperandName::ADD){
					if (code->leftOperand()=="0"){
						(*it) = new MoveCode(EFSA::OperandName::MOVI, code->rightOperand(), code->dest());
						cout<<"zdd"<<endl;
					}
					else if (code->rightOperand()=="0"){
					}
				}
			}
		}
	}
}
*/

void Optimizer::codeOptimize(vector<EFSA*> codeList){
	generateBasicBlock(codeList);
  	duplicateMoveEliminate();
}

void Optimizer::printBasicBlock(ostream& os){
	for (auto iter=blockList_.begin(); iter!=blockList_.end(); iter++) {
		EFSAlist* block = (*iter);
		block->codePrint(os);
		os<<endl;
	}
}

void Optimizer::duplicateMoveEliminate(){
	
}
