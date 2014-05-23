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
void Optimizer::removeCSEInBlock() {
   for (auto it = blockList_.begin(); it != blockList_.end(); it++) {
       unordered_map<string, set<int>> umExpTable;
       unordered_map<string, int> umDefTable;
       map<int, int> mapAvailability;
       map<int, string> mapDestName;
       vector<EFSA*>* pCodeList = (*it)->getCodeListPtr();
       string strArithLeft, strArithRight, strArithDest;
       string strMoveFrom, strMoveDest;
       EFSA::OperandName arithOpName;

       int iOldLineNum = 0;
       //scan in order
       for (auto itc = pCodeList->begin(); itc != pCodeList->end(); itc++) {
           int iLineNum = itc - pCodeList->begin();
           auto opName = (*itc)->name();
           switch ((*itc)->operatorType()) {
           case EFSA::OperatorType::INT_ARITH:
           {
               strArithLeft = ((IntArithCode*)(*itc))->leftOperand();
               strArithRight = ((IntArithCode*)(*itc))->rightOperand();
               strArithDest = ((IntArithCode*)(*itc))->dest();
               iOldLineNum = iLineNum;
               arithOpName = opName;
               break;
           }
           case EFSA::OperatorType::FLOAT_ARITH:
           {
               strArithLeft = ((FloatArithCode*)(*itc))->leftOperand();
               strArithRight = ((FloatArithCode*)(*itc))->rightOperand();
               strArithDest = ((FloatArithCode*)(*itc))->dest();
               iOldLineNum = iLineNum;
               arithOpName = opName;
               break;
           }
           case EFSA::OperatorType::MOVE:
               strMoveFrom = ((MoveCode*)(*itc))->from();
               strMoveDest = ((MoveCode*)(*itc))->dest();
               if (strMoveFrom == strArithDest && iLineNum == iOldLineNum + 1) {
                   mapDestName[iLineNum] = strMoveDest;
                   int iAvail = max(umDefTable[strArithLeft], umDefTable[strArithRight]);
                   mapAvailability[iLineNum] = iAvail;
                   umDefTable[strMoveDest] = iLineNum;
                   string emkKey = makeExprTabKey_(arithOpName, strArithLeft, strArithRight, iAvail);
                   umExpTable[emkKey].insert(iLineNum);
               }
               break;
           default:
               break;
           }

           

       }

       map<int, string> mapNewVarList;
       for (auto itm = umExpTable.begin(); itm != umExpTable.end(); itm++) {
           if (itm->second.size() > 1) {
               for (auto its = itm->second.begin(); its != itm->second.end(); its++) {
                   if (its == itm->second.begin()) continue;
                   mapNewVarList[*its] = mapDestName[*itm->second.begin()];
               }
           }
       }

       for (auto itp = pCodeList->begin(); itp != pCodeList->end()-1; itp++) {
           int pos = itp - pCodeList->begin();
           if (mapNewVarList.find(pos + 1) == mapNewVarList.end()) continue;
           switch((*itp)->operatorType()) {
           case EFSA::OperatorType::FLOAT_ARITH:
               (*itp) = new MoveCode(EFSA::OperandName::MOVI,
                   getReg(mapNewVarList[pos + 1]), mapDestName[pos + 1]);
                   *(itp+1) = nullptr;
                   break;
           case EFSA::OperatorType::INT_ARITH:
               (*itp) = new MoveCode(EFSA::OperandName::MOVF,
                   getReg(mapNewVarList[pos + 1]), mapDestName[pos + 1]);
                   *(itp+1) = nullptr;
                   break;
           default:
               break;
           }
           
       }

       bool bExistNull = true;
       while(bExistNull) {
           for (auto itp = pCodeList->begin(); itp != pCodeList->end(); itp++) {
               if ((*itp) == nullptr) {
                   pCodeList->erase(itp);
                   break;
               }
           }
           bExistNull = false;
       }
       /*map<int, int> mapLineToExpTab;
       // convert map
       for (auto itm = umExpTable.begin(); itm != umExpTable.end(); itm++) {
           for (auto its = itm->second.begin(); its != itm->second.end(); its++) {
               mapLineToExpTab[its] = itm->first;
           }
       }

       vector<EFSA*> newCodeList;
       //scan maps
       for (auto itm = mapLineToExpTab.begin(); itm != mapLineToExpTab.end(); itm++) {
           for (auto ite = umExpTable[*itm].begin(); ite !=umExpTable[*itm].end(); ite!) {
               
           }
       }*/
   }
}
