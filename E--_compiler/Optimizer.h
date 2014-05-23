#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "all.h"
#include "Value.h"
#include "ProgramElem.h"
#include "SymTab.h"
#include "SymTabEntry.h"
#include "Ast.h"
#include "ParserUtil.h"

class Optimizer;

class Optimizer{
 public:
	vector<EFSAlist*> blockList(){return blockList_;};	
	void addBlock(EFSAlist* block);
	void generateBasicBlock(vector<EFSA*> codeList);
	void duplicateMoveEliminate();
	void codeOptimize(vector<EFSA*> codeList);
	void printBasicBlock(ostream& os);
	void removeCSEInBlock();

 private:
	vector<EFSAlist*> blockList_;
	string makeExprTabKey_(EFSA::OperandName opName, string strLeft, string strRight, int iLastDef) 
	{
		return numToString((int)opName) + strLeft + strRight + numToString(iLastDef);
	}
};




#endif
