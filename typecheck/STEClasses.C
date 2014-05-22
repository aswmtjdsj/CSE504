#include "STEClasses.h"
#include "Value.h"
#include "ParserUtil.h"
#include "EventMatch.h"

const Type* GlobalEntry::typeCheck() {
	SymTab::iterator st_iter = symTab()->begin();
	for(; st_iter != symTab()->end(); ++st_iter) {
		if((*st_iter)->name() != "any")
			(*st_iter)->typeCheck();
	}
	vector<RuleNode*>::iterator ru_iter = rules_.begin();
	for(; ru_iter != rules_.end(); ++ru_iter) {
		//cout << "rule typecheck!" << endl;
		(*ru_iter)->typeCheck();
	}
	return NULL;
}

const Type* VariableEntry::typeCheck() {
	const Type* t_init = NULL;
	if(initVal()) {
		t_init = initVal()->typeCheck();
	}
	if(t_init) {
		if(t_init->fullName() == type()->fullName()) { // same type
		}
		else if(t_init->isSubType(type())) { // super type
		}
		else
			errMsg("Assignment between incompatible types", line(), column(), file().c_str());
	}
	return NULL;
}
const Type* FunctionEntry::typeCheck() {
	if(body())
		body()->typeCheck();
	return NULL;
}

void GlobalEntry::typePrint(ostream& out, int indent) const {
	SymTab::const_iterator st_iter = symTab()->begin();
	for(; st_iter != symTab()->end(); ++st_iter) {
		if((*st_iter)->name() != "any")
			(*st_iter)->typePrint(out, indent);
	}
	out << endl;
	vector<RuleNode*>::const_iterator ru_iter = rules_.begin();
	for(; ru_iter != rules_.end(); ++ru_iter) {
		(*ru_iter)->typePrint(out, indent);
	}
}

void VariableEntry::typePrint(ostream& out, int indent) const {
	if (initVal())
	{
		out << type()->fullName() << " " << name() << " = ";
		initVal()->typePrint(out, indent);
		out << endl;
	}
	else 
		out << type()->fullName() << " " << name() << endl;
}

void EventEntry::typePrint(ostream& out, int indent) const {

	out << "event " << name();
	if (symTab() == NULL)
	{
		out << ";";
		return;
	}
	else out << "(";
	SymTab::const_iterator iter = symTab()->begin();
	while (iter != symTab()->end())
	{
		(*iter)->type()->print(out, indent);
		out << " " << (*iter)->name();
		++iter;
		if (iter != symTab()->end())  out << ", ";
	}
	out << ");" << endl;
}

void ClassEntry::typePrint(ostream& out, int indent) const {
	out << "class " << name() << ";";
	out << endl;
}
void FunctionEntry::typePrint(ostream& out, int indent) const {
	type()->retType()->print(out, indent);
	out << " " << name() << "(";
	if (symTab() == NULL) 
	{
		out << ");" << endl;
		return ;
	}
	SymTab::const_iterator iter = symTab()->begin();
	VariableEntry* v;
	while (iter != NULL && iter != symTab()->end() && (*iter)->kind() == SymTabEntry::Kind::VARIABLE_KIND)
	{
		v = (VariableEntry*)(*iter);
		if (v->varKind() == VariableEntry::VarKind::PARAM_VAR)
		{
			out << v->type()->fullName() << " " << v->name();
			if ((++iter) != symTab()->end()) 
			{
				out << ", ";
				continue;
			}
		}
		++iter;
	}
	out << ")";

	if(body_) {
		out << "{" << endl;
		//print the variable decl
		SymTab::const_iterator it = symTab()->begin();
		while(it != symTab()->end() && (*it)->kind() == SymTabEntry::Kind::VARIABLE_KIND && 
		((VariableEntry*)(*it))->varKind() != VariableEntry::VarKind::PARAM_VAR) {
		(*it)->typePrint(out, indent);
		++it;
		out << ";" << endl;
		}
		//print the statement
		body_->typePrintWithoutBraces(out, indent+STEP_INDENT);
		out << "}" << endl;
	}
	cout << ";" << endl;
}
/*void GlobalEntry::print(ostream& out, int indent) const{};
void EventEntry::print(ostream& out, int indent) const{};
void BlockEntry::print(ostream& out, int indent) const{};
void ClassEntry::print(ostream& out, int indent) const{};
void FunctionEntry::print(ostream& out, int indent) const{};
void VariableEntry::print(ostream& out, int indent) const{};*/


void GlobalEntry::print(ostream& out, int indent) const
{
	SymTab::const_iterator iter = symTab()->begin();
	for (; iter != symTab()->end(); ++iter)
	{
		//out << (*iter)->name() << endl;
		if ((*iter)->name() != "any") (*iter)->print(out, indent);
	}
	vector<RuleNode*>::const_iterator iter1;
	for (iter1 = rules_.begin(); iter1 != rules_.end(); iter1++)
	{
		(*iter1)->print(out, indent);
		out << endl;
	}
}

void EventEntry::print(ostream& out, int indent) const
{
	out << "event " << name() << "(";
	if (symTab() == NULL) 
	{
		out << ");" << endl;
		return ;
	}
	SymTab::const_iterator iter = symTab()->begin();
	while (iter != symTab()->end())
	{
		(*iter)->type()->print(out, indent);
		out << " " << (*iter)->name();
		++iter;
		if (iter != symTab()->end())  out << ", ";
	}
	out << ");" << endl;
}

void BlockEntry::print(ostream& out, int indent) const
{

}

void ClassEntry::print(ostream& out, int indent) const
{
	out << "class " << name() << ";";
	out << endl;

}

void FunctionEntry::print(ostream& out, int indent) const
{
	type()->retType()->print(out, indent);
	out << " " << name() << "(";
	if (symTab() == NULL) 
	{
		out << ");" << endl;
		return ;
	}
	SymTab::const_iterator iter = symTab()->begin();
	VariableEntry* v;
	while (iter != NULL && iter != symTab()->end() && (*iter)->kind() == SymTabEntry::Kind::VARIABLE_KIND)
	{
		v = (VariableEntry*)(*iter);
		if (v->varKind() == VariableEntry::VarKind::PARAM_VAR)
		{
			out << v->type()->fullName() << " " << v->name();
			if ((++iter) != symTab()->end()) 
			{
				out << ", ";
				continue;
			}
		}
		++iter;
	}
	out << ")";
	out << ";" << endl;

}

void VariableEntry::print(ostream& out, int indent) const
{
	if (initVal())
	{
		out << type()->name() << " " << name() << " = ";
		initVal()->print(out, indent);
		out << ";" << endl;
	}
	else out << type()->name() << " " << name() << ";" << endl;
}

//zdd
EFSAlist* GlobalEntry::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	
	codeList->addCode(new LabelCode(GLOBAL_BEGIN, 1));

	//Alloc reg for rule name		
	vector<RuleNode*>::const_iterator iter = rules_.begin();
	for (;iter!=rules_.end();++iter) {
		if ((*iter)) {
			int regNum = (*iter)->regAlloc();
			PrimitivePatNode* pn = (PrimitivePatNode*)((*iter)->pat());
			codeList->addCode(new MoveCode(EFSA::OperandName::MOVI, numToString(static_cast<int>(pn->event()->name()[0])), getReg(regNum, 0)));
			//generate rule label
			string l1 = LABEL_PREFIX+std::to_string(labelNum);
			labelNum++;
			(*iter)->ruleLabel(l1);
		}
	}	

	//Event Match
	EventMatch em("EXIT");
	codeList->addCodeList(em.getMatchCodeList(this));
	
	// Variable Init
	if (symTab()){
		SymTab::iterator it = symTab()->begin();
		for (;it!=symTab()->end();++it) {
			if ((*it) && (*it)->kind() == SymTabEntry::Kind::VARIABLE_KIND) {
				VariableEntry* ve = (VariableEntry*)(*it);
				EFSAlist* cl = ve->codeGen();
				if (cl!=NULL)
					codeList->addCodeList(cl);
			}
		}
	}

	// FUNCTION Init
	if (symTab()){
		SymTab::iterator it = symTab()->begin();
		for (;it!=symTab()->end();++it) {
			if ((*it) && (*it)->kind() == SymTabEntry::Kind::FUNCTION_KIND) {
				FunctionEntry* ve = (FunctionEntry*)(*it);
				EFSAlist* cl = ve->codeGen();
				if (cl!=NULL)
					codeList->addCodeList(cl);
			}
		}
	}

    // jump by function-name-label
    LabelCode* label = new LabelCode("SP_INIT", TAR_LB);
    codeList->addCode(label);
	// SP init
	string from = std::to_string(0);
	//string dest = "R"+std::to_string(SP_REG);
	string dest = getReg(SP_REG, 0);
	MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, from, dest);
	codeList->addCode(code);

	// Rules
	vector<RuleNode*>::const_iterator it = rules_.begin();
	for (;it!=rules_.end();++it) {
		if ((*it)) {
			codeList->addCodeList((*it)->codeGen());
		}
	}	

	//Event Match
	EventMatch em1("EXIT");
	codeList->addCode(em1.getExitCode());
	
	return codeList;
}

EFSAlist* VariableEntry::codeGen() {
	int regNum = regAlloc();
	if (initVal()) {
		EFSAlist* codeList = new EFSAlist();
		if (initVal()->exprNodeType()==ExprNode::ExprNodeType::VALUE_NODE || initVal()->exprNodeType()==ExprNode::ExprNodeType::REF_EXPR_NODE){
			OpNode* on = new OpNode(OpNode::OpCode::ASSIGN, new RefExprNode(name(), this), initVal());
			codeList->addCodeList(on->codeGen());
		}
		else{ 
			OpNode* on = new OpNode(OpNode::OpCode::ASSIGN, new RefExprNode(name(), this), initVal());
			codeList->addCodeList(on->codeGen());
		}
		return codeList;
	}	
	return NULL;
}

 
int VariableEntry::regAlloc(){
	
	if (type()->tag()==Type::TypeTag::UINT || type()->tag()==Type::TypeTag::INT || type()->tag()==Type::TypeTag::INT){
		for (int i=0; i<=AVAIL_REG_SIZE; i++){
			if (intReg[i]==0){
				intReg[i] = 1;
				regNum_ = i;
				regIF_ = INT_FLAG;
				return i;
			}
                }
	}
	if (type()->tag()==Type::TypeTag::DOUBLE){
		for (int i=0; i<=AVAIL_REG_SIZE; i++)
			if (floatReg[i]==0){
				floatReg[i]=1;
				regNum_ = i;
				regIF_ = FLOAT_FLAG;
				return i;
			}
	}
	return -1;
}

EFSAlist* FunctionEntry::codeGen() {
    EFSAlist* codeList = new EFSAlist();

    // jump by function-name-label
    LabelCode* label = new LabelCode(name(), TAR_LB);
    codeList->addCode(label);
    
    return codeList;
}
