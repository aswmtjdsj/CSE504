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
	for (auto it=blockList_.begin(); it!=blockList_.end(); it++) {
		vector<EFSA*>* codeList = (*it)->getCodeListPtr();
		int markList[codeList->size()];
		for (int i=0; i<codeList->size(); i++)
		        markList[i]=0;
		vector<EFSA*>::iterator iter=codeList->begin();
		int n=1;
		while (iter!=codeList->end()){
		        vector<EFSA*>::iterator iter1 = iter;
		        iter1++;
		        if (iter1==codeList->end())
		                    break;
		         if ((*iter)->operatorType()==EFSA::OperatorType::MOVE && (*iter1)->operatorType()==EFSA::OperatorType::MOVE && ((*iter)->name()==(*iter1)->name())){
		                    MoveCode* code1 = (MoveCode*)(*iter);
		                    MoveCode* code2 = (MoveCode*)(*iter1);
		                    if (code1->dest()==code2->from()){
		                    	markList[(int)(iter-codeList->begin())]=n;
		                    	markList[(int)(iter1-codeList->begin())]=n;
		                    }
		                    else
		                  	n++;
			}
			else
		                  n++;
		 	++iter;
		}
		/*
		for (int i=0; i<codeList->size(); i++)
		        cout<<markList[i]<<endl;
		*/
		vector<EFSA*> tempList;
		int begin = -1;
		int end = -1;
		for (int i=0; i<codeList->size(); i++){
			if (begin==-1 && markList[i]!=0){
				begin = i;
			}
			else if (begin!=-1 && markList[i]==markList[i-1] && markList[i]!=markList[i+1]){
				end = i;
				MoveCode* beginCode = (MoveCode*)((*codeList)[begin]);
				MoveCode* endCode = (MoveCode*)((*codeList)[end]);
				MoveCode* code = new MoveCode (beginCode->name(), beginCode->from(), endCode->dest());
				tempList.push_back(code);
				begin = -1;
				end = -1;
			}
			else if (markList[i]==0)
				tempList.push_back(codeList->at(i));
		}

		// deal with MOV R R     from and dest are same
		vector<EFSA*>::iterator iter2=tempList.begin();
		while (iter2!=tempList.end()){
			bool flag = false;
			if ((*iter2)->operatorType()==EFSA::OperatorType::MOVE && ((*iter2)->name()==EFSA::OperandName::MOVI || (*iter2)->name()==EFSA::OperandName::MOVF)){
				MoveCode* code = (MoveCode*)(*iter2);
				if (code->from()==code->dest()){
					tempList.erase(iter2);
					flag = true;
				}
			}	
			if (flag)
				iter2 = tempList.begin();
			else
				iter2++;
		}

		 (*it)->setCodeList(tempList);
		 //cout<<endl;

	}

}
