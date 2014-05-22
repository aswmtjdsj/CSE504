#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "all.h"
#include "Value.h"
#include "ProgramElem.h"
#include "SymTab.h"
#include "SymTabEntry.h"
#include "Ast.h"

class Optimizer;

class Optimizer{
 public:
	vector<EFSAlist*> blockList(){return blockList_;};	
	void addBlock(EFSAlist* block);

	void generateBasicBlock(vector<EFSA*> codeList);
	void printBasicBlock(ostream& os);

 private:
	vector<EFSAlist*> blockList_;
};


#endif
