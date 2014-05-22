#include "STEClasses.h"
#include "Value.h"
#include "ParserUtil.h"
#include "EventMatch.h"

const Type* GlobalEntry::typeCheck() {
	SymTab::iterator st_iter = symTab()->begin();
	while (st_iter != symTab()->end())
	{
		if ((*st_iter)->name() != "any")
			(*st_iter)->typeCheck();
		++st_iter;
	}
	vector<RuleNode*>::iterator ru_iter = rules_.begin();
	while (ru_iter != rules_.end())
	{
		(*ru_iter)->typeCheck();
		++ru_iter;
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

void GlobalEntry::typePrint(ostream& out, int indent) const 
{
	SymTab::const_iterator st_iter = symTab()->begin();
	while(st_iter != symTab()->end())
	{
		if((*st_iter)->name() != "any")
			(*st_iter)->typePrint(out, indent);		
		++st_iter;
	}
	out << endl;
	vector<RuleNode*>::const_iterator ru_iter = rules_.begin();
	while (ru_iter != rules_.end())
	{
		(*ru_iter)->typePrint(out, indent);
		++ru_iter;
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

void GlobalEntry::print(ostream& out, int indent) const
{
	SymTab::const_iterator iter = symTab()->begin();
	while (iter != symTab()->end())
	{
		if ((*iter)->name() != "any") (*iter)->print(out, indent);
		++iter;
	}
	vector<RuleNode*>::const_iterator iter1 = rules_.begin();
	while (iter1 != rules_.end())
	{
		(*iter1)->print(out, indent);
		out << endl;
		iter1++;
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
			string l2 = LABEL_PREFIX+std::to_string(labelNum);
			labelNum++;
			(*iter)->ruleLabel(l1);
			(*iter)->ruleSkipLabel(l2);
		}
	}	
	
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

        codeList->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, new LabelCode("MatchBegin")));
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

	//Event Match
	EventMatch em(LABEL_PROG_EXIT);
	codeList->addCodeList(em.getMatchCodeList(this));

    // jump by function-name-label
    LabelCode* label = new LabelCode("SP_INIT", TAR_LB);
    codeList->addCode(label);
	// SP init
	string from = std::to_string(0);
	//string dest = "R"+std::to_string(SP_REG);
	string dest = getReg(SP_REG, INT_FLAG);
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
	EventMatch em1(LABEL_PROG_EXIT);
	codeList->addCode(em1.getExitCode());

	codeList->dealDuplicateLabel();
	
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

    // get sp
    string sp_reg_name = getReg(SP_REG, INT_FLAG);

    // init local var
	SymTab::iterator st_iter = symTab()->begin();
    vector < pair<int,int> > local_var_reg_num_array;
	for(; st_iter != symTab()->end(); ++st_iter) {
        if((*st_iter)->kind() == SymTabEntry::Kind::VARIABLE_KIND) {
            codeList->addCodeList(((VariableEntry*)(*st_iter))->codeGen());

            local_var_reg_num_array.push_back(make_pair(((VariableEntry*)(*st_iter))->regNum(), ((VariableEntry*)(*st_iter))->regIF()));
        }
	}
    
    // pop stack to load AP to LV
    for(auto ridx = local_var_reg_num_array.rbegin(); ridx != local_var_reg_num_array.rend(); ridx++) {
        // sub sp by 1 -> pop
        IntArithCode* sub_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, sp_reg_name, sp_reg_name, std::to_string(1));
        codeList->addCode(sub_code);

        // 
        string param_reg_name = getReg(ridx->first, ridx->second);
        if(ridx->second == FLOAT_FLAG) {
            MoveCode * ldfspp_param = new MoveCode(EFSA::OperandName::LDF, param_reg_name, sp_reg_name);
            codeList->addCode(ldfspp_param);
        }
        else if(ridx->second == INT_FLAG) {
            MoveCode * ldispp_param = new MoveCode(EFSA::OperandName::LDI, param_reg_name, sp_reg_name);
            codeList->addCode(ldispp_param);
        }
    }

    // compound statement code gen
    // inside:: return statement to pop return 
    codeList->addCode(new LabelCode("//BodyBegin"));
    codeList->addCodeList(body()->codeGen());
    codeList->addCode(new LabelCode("//BodyEnd"));

    // release local var
    for(auto idx = local_var_reg_num_array.begin(); idx != local_var_reg_num_array.end(); idx++) {
        if(idx->second == FLOAT_FLAG) {
            EFSA::floatRegFree(idx->first);
        }
        else if(idx->second == INT_FLAG) {
            EFSA::intRegFree(idx->first);
        }
    }

    // pop jump back label

    // sub sp by 1 -> pop
    IntArithCode* sub_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, sp_reg_name, sp_reg_name, std::to_string(1));
    codeList->addCode(sub_code);

    // get new temp register
    int temp_reg = EFSA::intRegAlloc();
    //temp_reg_name = "R"+std::to_string(temp_reg);
    string temp_reg_name = getReg(temp_reg, INT_FLAG);

    MoveCode * ldispp_l = new MoveCode(EFSA::OperandName::LDI, temp_reg_name, sp_reg_name); // dest, from
    codeList->addCode(ldispp_l);

    // jump to label ( function return address)
    LabelCode* label_reg = new LabelCode(temp_reg_name);
    JumpCode* jumpCode = new JumpCode(EFSA::OperandName::JMPI, NULL, label_reg);
    codeList->addCode(jumpCode);
    
    // eliminate temp reg
    EFSA::intRegFree(temp_reg);

    return codeList;
}
