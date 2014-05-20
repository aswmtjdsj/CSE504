#include "Ast.h"					
#include "ParserUtil.h"					

extern const OpNode::OpInfo opInfo[];

const Type* ValueNode::typeCheck() {
  return type();
}
const Type* RefExprNode::typeCheck() {
  //cout << "refexprnode check!" << endl;
  return symTabEntry()->type();
}
const Type* OpNode::typeCheck() {
  //cout << "opnode check!" << endl;
  bool biOp = false;
  bool uOp = false;
  ExprNode *l = NULL, *r = NULL; // left and right operands
  const Type *tl = NULL, *tr = NULL; // type of left and right operands
  // initialize ExprNode and its type
  if(arity() == 2) {
    //cout << "enter here?" << endl;
    l = arg(0);
    r = arg(1);
    if(l != NULL) tl = l->typeCheck();
    //cout << "ok" << endl;
    if(r != NULL) tr = r->typeCheck();
    //cout << "ok" << endl;
    biOp = true;
  }
  if(arity() == 1) {
    l = arg(0);
    if(l != NULL) tl = l->typeCheck();
    uOp = true;
  }
  // check different operators

  //UMINUS, PLUS, MINUS, MULT, DIV, MOD, 
  //EQ, NE, GT, LT, GE, LE,
  //AND, OR, NOT, 
  //BITNOT, BITAND, BITOR, BITXOR, SHL, SHR,
  //ASSIGN, PRINT, INVALID

  //UMINUS
  if(opCode() == OpCode::UMINUS && uOp == true) {
    if(!Type::isNumeric(tl->tag())) {
      string err = "Incompatible type for argument 1 for operator '-'";
      errMsg(err, line(), column(), file().c_str());
    }
    if(tl->tag() == Type::UINT) {
      Type *t = new Type(Type::INT);
      l->coercedType(t);
      type((Type*)t);
    }
    else {
      type((Type*)tl);
    }
    return type();
  }
  //PLUS, MINUS, MULT, DIV
  if(opCode() >= OpCode::PLUS && opCode() <=OpCode::DIV && biOp == true) {
    bool lflag = true, rflag = true;
    const Type *t = NULL;
    string op;
    if(opCode() == OpCode::PLUS)        { op = "+"; }
    else if(opCode() == OpCode::MINUS)  { op = "-"; }
    else if(opCode() == OpCode::MULT)   { op = "*"; }
    else if(opCode() == OpCode::DIV)    { op = "/"; }

    if(!Type::isNumeric(tl->tag())) {
      string err = "Incompatible type for argument 1 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
      lflag = false;
    } 
    if(!Type::isNumeric(tr->tag())) {
      string err = "Incompatible type for argument 2 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
      rflag = false;
    }
    if(lflag == false && rflag == false) {}
    else if(tl->fullName() == tr->fullName()) {
      t = tl;
    }
    else if(tl->isSubType(tr) || lflag == false) {
      t = tr;
      l->coercedType(tr);
    }
    else if(tr->isSubType(tl) || rflag == false) {
      t = tl;
      r->coercedType(tl);
    }
    // if(opCode() == OpCode::DIV)
    //   type(new Type(Type::DOUBLE));
    // else 
      type((Type*)t);
    return type();
  }
  //MOD
  if(opCode() == OpCode::MOD && biOp == true) {
    if(!Type::isInt(tl->tag()))
      errMsg("Incompatible type for argument 1 for operator `%'", line(), column(), file().c_str());
    if(!Type::isInt(tr->tag()))
      errMsg("Incompatible type for argument 2 for operator `%'", line(), column(), file().c_str());
    if(tl->fullName() == tr->fullName());
    else if(tl->isSubType(tr) && Type::isInt(tr->tag())) {
      l->coercedType(tr);
      type((Type*)tr);
    }
    else if(tr->isSubType(tl) && Type::isInt(tl->tag())) {
      r->coercedType(tl);
      type((Type*)tl);
    }
    Type* t = new Type(Type::INT);
    type(t);
    return type();
  }
  //EQ, NE, GT, LT, GE, LE,
  if(opCode() >= OpCode::EQ && opCode() <= OpCode::LE && biOp == true) {
    // cout << line() << endl;
    // cout << tl->fullName() << endl;
    // cout << tr->fullName() << endl;
    string op;
    if(opCode() == OpCode::EQ)      { op = "=="; }
    else if(opCode() == OpCode::NE) { op = "!="; }
    else if(opCode() == OpCode::GT) { op = ">";  }
    else if(opCode() == OpCode::LT) { op = "<";  }
    else if(opCode() == OpCode::GE) { op = ">="; }
    else if(opCode() == OpCode::LE) { op = "<="; }

    if(!(Type::isNumeric(tl->tag()) || Type::isBool(tl->tag()) || Type::isString(tl->tag()))) {
      string err = "Error:Incompatible type for argument 1 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
    }
    if(!(Type::isNumeric(tr->tag()) || Type::isBool(tr->tag()) || Type::isString(tr->tag()))) {
      string err = "Error:Incompatible type for argument 2 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
    }
    Type* t = new Type(Type::BOOL);
    type((Type*)t);
    return type();
  }
  //AND, OR
  if(opCode() >= OpCode::AND && opCode() <= OpCode::OR && biOp == true) {
    string op;
    if(opCode() == OpCode::AND)     { op = "&&"; }
    else if(opCode() == OpCode::OR) { op = "||"; }
    if(!Type::isBool(tl->tag())) {
      string err = "Error:Incompatible type for argument 1 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
    }
    if(!Type::isBool(tr->tag())) {
      string err = "Error:Incompatible type for argument 1 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
    }
    Type* t = new Type(Type::BOOL);
    type((Type*)t);
    return type();
  }
  //NOT
  if(opCode() == OpCode::NOT && uOp == true) {
    Type* t = new Type(Type::BOOL);
    type((Type*)t);
    return type();
  }
  //ASSIGN
  if(opCode() == OpCode::ASSIGN && biOp == true) {
    // cout << line() << endl;
    // cout << tr->fullName() << endl;
    // cout << tl->fullName() << endl;
    if(tr->fullName() == tl->fullName()) {}
    else if(tr->isSubType(tl)) {
      r->coercedType(tl);
    }
    else
      errMsg("Assigned expression must be a subtype of target", line(), column(), file().c_str());
    Type* t = new Type(Type::BOOL);
    type(t);
    return type();
  }
  //BITNOT
  if(opCode() == OpCode::BITNOT && uOp == true) {
    if(!Type::isIntegral(tl->tag())) {
      errMsg("Incompatible type for argument 1 for operator '~'", line(), column(), file().c_str());
    }
    if(!Type::isUnsigned(tl->tag())) {
      Type* ut = new Type(Type::UINT);
      l->coercedType(ut);
      type(ut);
    }
    //type((Type*)tl);
    return type();
  }
  //BITAND, BITOR, BITXOR, SHL, SHR,
  if(opCode() >= OpCode::BITAND && opCode() <=OpCode::SHR && biOp == true) {
    bool lflag = true, rflag = true;
    const Type *t = NULL;
    string op;
    if(opCode() == OpCode::BITAND)        { op = "&"; }
    else if(opCode() == OpCode::BITOR)    { op = "|"; }
    else if(opCode() == OpCode::BITXOR)   { op = "^"; }
    else if(opCode() == OpCode::SHL)      { op = "<<"; }
    else if(opCode() == OpCode::SHR)      { op = ">>"; }

    if(!Type::isIntegral(tl->tag())) {
      string err = "Incompatible type for argument 1 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
      lflag = false;
    } 
    if(!Type::isIntegral(tr->tag())) {
      string err = "Incompatible type for argument 2 for operator '" + op + "'";
      errMsg(err, line(), column(), file().c_str());
      rflag = false;
    }
    if(lflag == false && rflag == false) {}
    else if(tl->fullName() == tr->fullName()) {
      t = tl;
    }
    else if(tl->isSubType(tr) || lflag == false) {
      t = tr;
      l->coercedType(tr);
    }
    else if(tr->isSubType(tl) || rflag == false) {
      t = tl;
      r->coercedType(tl);
    }
    t = new Type(Type::INT);
    type((Type*)t);
    return type();
  }

  return NULL;
}
const Type* RuleNode::typeCheck() {
  //cout << "rulenode check type!" << endl;
  if(pat()) {
    //cout << "checking pat" << endl;
    pat()->typeCheck();
  }
  if(reaction()) {
    //cout << "checking reaction" << endl;
    reaction()->typeCheck();
  }
  return NULL;
}
const Type* PatNode::typeCheck() {
  //cout << "patnode check!" << endl;
  switch(kind()) {
    case PatNodeKind::PRIMITIVE: break;
    case PatNodeKind::EMPTY: break;
    case PatNodeKind::NEG: {
      if(hasSeqOps()) {
        errMsg("invalid use of negation", line(), column(), file().c_str());
      }
      pat1_->typeCheck();
      break;
    }
    case PatNodeKind::SEQ:
    case PatNodeKind::OR: {
      pat1_->typeCheck();
      pat2_->typeCheck();
      break;
    }
    case PatNodeKind::STAR: {
      pat1_->typeCheck();
      break;
    }
    case PatNodeKind::UNDEFINED: break;
  }
  return NULL;
}
const Type* PrimitivePatNode::typeCheck() {
  //cout << "ppatnode check!" << endl;
  Type *ee = event()->type();
  vector<Type*>* formal = NULL;
  int formal_size = 0;
  int param_size = 0;
  if(ee->argTypes()) {
    formal = ee->argTypes();
    formal_size = formal->size();
  }
  if(params_)
    param_size = params_->size();
  if(param_size == formal_size) {
    // for(int i = 0; i < formal_size; i++) {
    //   params_->at(i)->type(formal->at(i));
    //   cout << params_->at(i)->type()->fullName();
    // }
    // cout << endl;
    // vector<VariableEntry*>::const_iterator it;
    // for(it = params_->begin(); it != params_->end(); ++it)
    //   if(*it)
    //     (*it)->typeCheck();
  }
  else {
    string s = "Event " + ee_->name() + " requires " + itoa(formal->size()) + " arguments";
    errMsg(s, line(), column(), file().c_str());
  }
  if(condition()) {
    condition()->typeCheck();
  }
  return NULL;
}
const Type* InvocationNode::typeCheck() {
  const Type* ret = NULL;
  FunctionEntry* fe = (FunctionEntry*)symTabEntry();
  vector<Type*>* formal = fe->type()->argTypes(); // formal types
  ret = fe->type()->retType(); // return type

  if(formal->size() == params_->size()) {
    for(unsigned int i = 0; i < formal->size(); i++) {
      const Type* tp = params_->at(i)->typeCheck();
      const Type* tf = formal->at(i);
      if(tp->fullName() == tf->fullName()) { }
      else if(tp->isSubType(tf)) { 
        params_->at(i)->coercedType(tf);
      }
      else {
        string err = "Type mismatch for argument " + itoa(i+1) + " to " + symTabEntry()->name();
        errMsg(err, line(), column(), file().c_str());
      }
    }
  }
  else {
    string err = itoa(formal->size()) + " arguments expected for " + symTabEntry()->name();
    errMsg(err, line(), column(), file().c_str());
  }
  return ret;
}
const Type* ExprStmtNode::typeCheck() {
  //cout << "exprstmtnode check!" << endl;
  expr_->typeCheck();
  return NULL;
}
const Type* CompoundStmtNode::typeCheck() {
  list<StmtNode*>::const_iterator iter = stmts_->begin();
  for(; iter != stmts_->end(); ++iter) {
    if(*iter != NULL) {
      (*iter)->typeCheck();
    }
    else
      break;
  }
  return NULL;
}
const Type* ReturnStmtNode::typeCheck() {
  const Type* tf = fun_->type()->retType();
  ExprNode* exp = expr_;
  const Type* tret = exp->typeCheck();
  if(tf->tag() == Type::VOID) {
    string err = "No return value expected for a void function";
    errMsg(err, line(), column(), file().c_str());
  } 
  else if(tf->fullName() == tret->fullName()) {}
  else if(tret->isSubType(tf))
    exp->coercedType(tf);
  else {
    string err = "Return value incompatible with current function's type";
    errMsg(err, line(), column(), file().c_str());
  }
  return NULL;
}
const Type* IfNode::typeCheck() {
  //cout << "IfNode" << endl;
  const Type* t = NULL; 
  if(cond()) {
    t = cond()->typeCheck();
  }
  if(t->tag() != Type::BOOL) {
      errMsg("Boolean argument expected", line(), column(), file().c_str());
  }
  //cout << line();
  if(thenStmt())
      thenStmt()->typeCheck();
  if(elseStmt())
      elseStmt()->typeCheck();
  return NULL;
}
void OpNode::typePrint(ostream& out, int indent) const{
  bool biOp = false;
  bool uOp = true;
  if(arity() == 1) uOp = true;
  if(arity() == 2) biOp = true;
  if(coercedType())
    out << "(" << coercedType()->fullName() << ")";
  //UMINUS
  if(opCode() == OpCode::UMINUS && uOp == true) {
    out << opInfo[(int)opCode_].name_;
    arg_[0]->typePrint(out, indent);
  } 
  //PLUS, MINUS, MULT, DIV, MOD,
  if(opCode() >= OpCode::PLUS && opCode() <= OpCode::MOD && biOp == true) {
    if(opCode() == OpCode::DIV || opCode() == OpCode::MOD) out << "(";
    arg_[0]->typePrint(out, indent);
    out << opInfo[(int)opCode_].name_;
    arg_[1]->typePrint(out, indent);
    if(opCode() == OpCode::DIV || opCode() == OpCode::MOD) out << ")";
  } 
  //EQ, NE, GT, LT, GE, LE,
  if(opCode() >= OpCode::EQ && opCode() <= OpCode::LE && biOp == true) {
    arg_[0]->typePrint(out, indent);
    out << opInfo[(int)opCode_].name_;
    arg_[1]->typePrint(out, indent);
  }
  //AND, OR,
  if(opCode() >= OpCode::AND && opCode() <= OpCode::OR && biOp == true) {
    cout << "(";
    arg_[0]->typePrint(out, indent);
    out << opInfo[(int)opCode_].name_;
    arg_[1]->typePrint(out, indent);
    cout << ")";
  } 
  //NOT, 
  if(opCode() == OpCode::NOT && uOp == true) {
    out << opInfo[(int)opCode_].name_;
    arg_[0]->typePrint(out, indent);
  }
  //BITNOT
  if(opCode() == OpCode::BITNOT && uOp == true) {
    out << opInfo[(int)opCode_].name_;
    arg_[0]->typePrint(out, indent);
  }
  //BITAND, BITOR, BITXOR, SHL, SHR,
  if(opCode() >= OpCode::BITAND && opCode() <= OpCode::SHR && biOp == true) {
    cout << "(";
    arg_[0]->typePrint(out, indent);
    out << opInfo[(int)opCode_].name_;
    arg_[1]->typePrint(out, indent);
    cout << ")";
  } 
  //ASSIGN, 
  if(opCode() == OpCode::ASSIGN && biOp == true) {
    arg_[0]->typePrint(out, indent);
    out << opInfo[(int)opCode_].name_;
    arg_[1]->typePrint(out, indent);
  } 
  //PRINT, INVALID
}
void ValueNode::typePrint(ostream& out, int indent) const {
  if(coercedType())
    out << "(" << coercedType()->fullName() << ")";
  value()->typePrint(out, indent);
}
void RefExprNode::typePrint(ostream& out, int indent) const {
  if(coercedType())
    out << "(" << coercedType()->fullName() << ")";
  out << symTabEntry()->type()->fullName();
}
void RuleNode::typePrint(ostream& out, int indent) const{
    pat_->print(out, indent);
    out << "-->  ";
    reaction_->typePrint(out, indent);
    out << ";;" << endl;
}
void CompoundStmtNode::typePrint(ostream& out, int indent) const {
  out << "{" << endl;
  typePrintWithoutBraces(out, indent+STEP_INDENT);
  out << "};" << endl;  
}
void CompoundStmtNode::typePrintWithoutBraces(ostream& out, int indent) const {
  list<StmtNode*>::const_iterator iter = stmts_->begin();
  for (; iter != stmts_->end(); ++iter) {
    if (*iter != NULL) {
      //prtln(out, indent);
      int n = indent;
      while(n-->0)
        out << " ";
      (*iter)->typePrint(out, indent);
      out << ";" << endl;
    }
    else break;
  }
}
void InvocationNode::typePrint(ostream& out, int indent) const {
  out << ste_->name();
  if (params_ == NULL) {
    out << "();";
    return ;
  }
  else {
    out << "(";
    vector<ExprNode*>::const_iterator iter = params_->begin();
    while (iter != params_->end()) {
      (*iter)->typePrint(out, indent);
      if ((++iter) != params_->end()) out << ", ";
    }
    out << ")";
  }
}
void ReturnStmtNode::typePrint(ostream& out, int indent) const {
  out << "return "; 
  if(expr_ != NULL) 
    expr_->typePrint(out, indent);
  else 
    out << "NULL";
}
void IfNode::typePrint(ostream& out, int indent) const {
  out << "if (";
    cond_->typePrint(out, indent);
    out << ") ";
    if (then_)
    {
      then_->typePrint(out,indent);
    }
    if (else_)
    {
        out << "else ";
        else_->typePrint(out,indent);
        //out << ";" << endl;
    }
}
void PatNode::typePrint(ostream& out, int indent) const {

}
void PrimitivePatNode::typePrint(ostream& out, int indent) const{
  
}


AstNode::AstNode(NodeType nt, int line, int column, string file):
  ProgramElem(NULL, line, column, file) 
{
	// Add your code here
    nodeType_ = nt;
}

AstNode::AstNode(const AstNode& ast): ProgramElem(ast) {
	// Add your code here
    nodeType_ = ast.nodeType_;
}

PrimitivePatNode::PrimitivePatNode(EventEntry* ee, vector<VariableEntry*>* params, ExprNode* c, int line, int column, string file)
 : BasePatNode(PatNodeKind::PRIMITIVE, line, column, file)
{
    ee_ = ee;
    params_ = params;
    cond_ = c;
}

void PrimitivePatNode::print(ostream &os, int indent) const
{
    if (ee_ == NULL) os << "(any()";
    else
    {
      vector<Type*>* at = ee_->type()->argTypes();
      os << "(";
      os << ee_->name();
      if (params_ != NULL)
      {
        os << "(";
        vector<VariableEntry*>::const_iterator iter1 = params_->begin();
        vector<Type*>::const_iterator iter2 = at->begin();
        while (iter1 != params_->end())
        {
            os << (*iter2)->fullName() << " " <<  (*iter1)->name();
            ++iter1;
            ++iter2;
            if (iter1 != params_->end()) os << ", ";
        }
        os << ")";
      }
    }
    if (cond_ != NULL)
    {
      os << "|";
      cond_->print(os, indent);
    }
    os << ")";
}

bool PrimitivePatNode::hasSeqOps() const
{
    return 1;
}

bool PrimitivePatNode::hasNeg() const
{
    return 1;
}

bool PrimitivePatNode::hasAnyOrOther() const
{
    return 1;
}


RuleNode::RuleNode(BlockEntry *re, BasePatNode* pat, StmtNode* reaction, int line, int column, string file)
 : AstNode(AstNode::NodeType::RULE_NODE, line, column, file)
{
    rste_ = re;
    pat_ = pat;
    reaction_ = reaction;
}

void RuleNode::print(ostream& os, int indent) const
{
    pat_->print(os, indent);
    os << "-->  ";
    reaction_->print(os, indent);
    os << ";;";
}

PatNode::PatNode(int line, int column, string file)
 : BasePatNode(PatNodeKind::UNDEFINED, line, column, file)
{

}

PatNode::PatNode(PatNodeKind pk, BasePatNode *p1, BasePatNode*p2, int line, int column, string file)
 : BasePatNode(pk, line, column, file)
{
    pat1_ = p1;
    pat2_ = p2;
}

void PatNode::print(ostream& os, int indent) const
{

    os << "(";
    if (kind() == PatNodeKind::PRIMITIVE)
    {
        os << ")";
        return ;
    }
    if (kind() == PatNodeKind::EMPTY)
    {
        os << ")";
        return ;        
    }
    if (kind() == PatNodeKind::NEG)
    {
        os << "!";
        pat1_->print(os,indent);
        os << ")";
        return ;
    }
    if (kind() == PatNodeKind::SEQ)
    {
        pat1_->print(os, indent);
        os << ":";
        pat2_->print(os, indent);
        os << ")";
        return ;        
    }
    if (kind() == PatNodeKind::OR)
    {
        pat1_->print(os, indent);
        os << "\\/";
        pat2_->print(os, indent);
        os << ")";
        return ;        
    }
    if (kind() == PatNodeKind::STAR)
    {
        pat1_->print(os, indent);
        os << "**";
        os << ")";
        return ;        
    }
    if (kind() == PatNodeKind::UNDEFINED)
    {
        os << ")";
        return ;
    }
}

bool PatNode::hasSeqOps() const
{
    if (kind() == PatNodeKind::SEQ) return true;
    return false;
    //anything else?
}

bool PatNode::hasNeg() const
{
    if (kind() == PatNodeKind::NEG) return true;
    return false;
}

bool PatNode::hasAnyOrOther() const
{
    if (kind() == PatNodeKind::OR) return true;
    return false;
}


/****************************************************************/

ExprNode::ExprNode(ExprNodeType et, const Value* val, int line, int column, string file)
 : AstNode(AstNode::NodeType::EXPR_NODE, line, column, file)
{
	// Add your code here
    exprType_ = et;
    val_ = val;
    regNum_ = -1;
}


ExprNode::ExprNode(const ExprNode& e) : AstNode(e)
{
	// Add your code here
    coercedType_ = e.coercedType_;
    val_ = e.val_;
}

RefExprNode::RefExprNode(string ext, const SymTabEntry* ste, int line, int column, string file)
 : ExprNode(ExprNodeType::REF_EXPR_NODE, 0, line, column, file)
 {
    ext_ = ext;
    sym_ = ste;
 }

RefExprNode::RefExprNode(const RefExprNode& nnod)
 : ExprNode(ExprNodeType::REF_EXPR_NODE, 0, nnod.line(), nnod.column(), nnod.file())
 {
    ext_ = nnod.ext_;
    sym_ = nnod.sym_; 
 }

void RefExprNode::print(ostream &os, int indent) const
{
    os << ext();
} 

void ValueNode::print(ostream& os, int indent) const
{
    value()->print(os, indent);
}

InvocationNode::InvocationNode(const SymTabEntry *ste, vector<ExprNode*>* param, int line, int column, string file)
 : ExprNode(ExprNodeType::INV_NODE, NULL, line, column, file)
{
    ste_ = ste;
    params_ = param;
}

InvocationNode::InvocationNode(const InvocationNode &n)
 : ExprNode(n)
{
    ste_ = n.ste_;
    params_ = n.params_;
}

void InvocationNode::print(ostream& os, int indent) const
{
    os << ste_->name();
    if (params_ == NULL) 
    {
        os << "();";
        return ;
    }
    else
    {
        os << "(";
        vector<ExprNode*>::const_iterator iter = params_->begin();
        while (iter != params_->end())
        {
            (*iter)->print(os, indent);
            if ((++iter) != params_->end()) os << ", ";
        }
        os << ")";
    }

}
/****************************************************************/
extern const OpNode::OpInfo opInfo[] = {
  // print name, arity, paren_flag, fixity, arg types, out type, constraints
  //
  // Paren_flag -- opnode->print() outputs is surrounded by parenthesis if 
  // this flag is set. As set below, the expression may not print correctly
  // in some rare cases, e.g., ~(b * c) will get printed as ~b * c,
  // which actually corresponds to (~b)*c. To ensure that things get printed
  // correctly all the time, more paren_flags should be set to 1, but this
  // will lead to more clutter in printed output. Basically, what we have done
  // here is to look are expressions by type -- arithmetic, relational, 
  // boolean, bit operations, etc. Within each type, the highest priority 
  // operator is printed without paren. This will work correctly, as long
  // as the language doesn't permit mixing of different types of expressions.
  // But this assumption doesn't always hold, as in the example above. Also,
  // there is an exception to this general approach in the case of unary minus
  // and * -- since (-a)*b and -(a*b) have the same meaning, we can exclude
  // paren for * without an error.
  //
  // Codes for constraints:
  // first character:
  //    N: No additional constraint over what is given by argTypes
  //    I: all arguments must have identical type
  //    S: one of the arguments must have a type that is a supertype of
  //        of all other arguments. All other arguments require a coercion 
  //        operation to be introduced so as to convert their type to S.
  //    s: one of the arguments must have a type that is a subtype of
  //        of all other arguments. 
  //    L: all list arguments (and list output) must have same type. In 
  //        addition, all non-list arguments (and output) must have same 
  //        type as that of elements in these lists
  //    T: all tuple arguments to the function must have same type.
  //    A: (assignment). Type of second argument must be a subtype of
  //       the first argument
  //
  // second character:
  //    O: output type is the same as out type. (In the following cases,
  //        the output type need not be equal to out type, but a subtype
  //        of it.) Since a TypeTag provides complete type information only
  //        for primitive types, `O' is applicable only in this case.
  //    digit: output type is the same as that of the digit'th argument
  //       In this case, a third character may be used, the code for
  //       which is as follows:
  //         'e' denotes that the output is of type alpha, where
  //             the type of digit'th argument is list(alpha)
  //         'l' denotes that the output is of type list(alpha), where
  //             alpha is the type of the digit'th argument.
  //    S: The output type is the same as that of the argument with the
  //        most general type. (Typically used with first character 'S')
  //    s: The output type is the same as that of the argument with the
  //        least general type. (Typically used with first character 'S')
  //    P: The output type is the product of the types of all arguments
  //    p: The output type is a component of the input tuple type. The
  //        following character specifies the component. A digit k specifies
  //        that the component number as k. The character 'a' indicates that
  //        the component number is given by an integer argument to the
  //        operator. The argument number is given by the following digit.
  //        'p' can be used only in conjunction with first character 'P'.
  //    L: Output type is the same as type of list arguments. Can be used
  //        only in conjunction with first character L.
  //    e: Output type is the same as type of element of list arguments. 
  //        Can be used only in conjunction with first character L.
  //
  {OpNode::OpCode::UMINUS, "-",  1, 0, OpNode::OpPrintType::PREFIX, {Type::SIGNED}, Type::SIGNED, "N1"},
  {OpNode::OpCode::PLUS, "+",  2, 1, OpNode::OpPrintType::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC, "SS"},
  {OpNode::OpCode::MINUS, "-",  2, 1, OpNode::OpPrintType::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC, "SS"},
  {OpNode::OpCode::MULT, "*",  2, 0, OpNode::OpPrintType::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC, "SS"},
  {OpNode::OpCode::DIV, "/",  2, 1, OpNode::OpPrintType::INFIX, {Type::NUMERIC, Type::NUMERIC}, Type::NUMERIC, "SS"},
  {OpNode::OpCode::MOD, "%",  2, 1, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "S2"},
  {OpNode::OpCode::EQ, "==", 2, 0, OpNode::OpPrintType::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL, "SO"},
  {OpNode::OpCode::NE, "!=", 2, 0, OpNode::OpPrintType::INFIX, {Type::PRIMITIVE, Type::PRIMITIVE}, Type::BOOL, "SO"},
  {OpNode::OpCode::GT, ">",  2, 0, OpNode::OpPrintType::INFIX, {Type::SCALAR, Type::SCALAR}, Type::BOOL, "SO"},
  {OpNode::OpCode::LT, "<",  2, 0, OpNode::OpPrintType::INFIX, {Type::SCALAR, Type::SCALAR}, Type::BOOL, "SO"},
  {OpNode::OpCode::GE, ">=", 2, 0, OpNode::OpPrintType::INFIX, {Type::SCALAR, Type::SCALAR}, Type::BOOL, "SO"},
  {OpNode::OpCode::LE, "<=", 2, 0, OpNode::OpPrintType::INFIX, {Type::SCALAR, Type::SCALAR}, Type::BOOL, "SO"},
  {OpNode::OpCode::AND, "&&",  2, 1, OpNode::OpPrintType::INFIX, {Type::BOOL, Type::BOOL}, Type::BOOL, "NO"},
  {OpNode::OpCode::OR, "||",  2, 1, OpNode::OpPrintType::INFIX, {Type::BOOL, Type::BOOL}, Type::BOOL, "NO"},
  {OpNode::OpCode::NOT, "!",  1, 0, OpNode::OpPrintType::PREFIX, {Type::BOOL}, Type::BOOL, "NO"}, 
  {OpNode::OpCode::BITNOT, "~",  1, 0, OpNode::OpPrintType::PREFIX, {Type::INTEGRAL}, Type::INTEGRAL, "N1"},
  {OpNode::OpCode::BITAND, "&",  2, 1, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "Ss"},
  {OpNode::OpCode::BITOR, "|",  2, 1, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "SS"},
  {OpNode::OpCode::BITXOR, "^",  2, 0, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "SS"},
  {OpNode::OpCode::SHL, "<<", 2, 1, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "N1"},
  {OpNode::OpCode::SHR, ">>", 2, 1, OpNode::OpPrintType::INFIX, {Type::INTEGRAL, Type::INTEGRAL}, Type::INTEGRAL, "N1"},
  {OpNode::OpCode::ASSIGN, "=",  2, 0, OpNode::OpPrintType::INFIX, {Type::NATIVE, Type::NATIVE}, Type::VOID, "AO"},
  {OpNode::OpCode::PRINT, "print", OpNode::VARIABLE, 1, OpNode::OpPrintType::PREFIX, {Type::NATIVE}, Type::VOID, "NO"},
  {OpNode::OpCode::INVALID, "invalid",            0, 0, OpNode::OpPrintType::PREFIX, {}, Type::ERROR, "NO"}
};

OpNode::OpNode(OpCode op, ExprNode* a1, ExprNode* a2, 
			   int ln, int col, string file):
  ExprNode(ExprNode::ExprNodeType::OP_NODE, NULL, ln,col,file) {
    opCode_ = op;
    if (a1 != NULL) {
	   arity_ = 1;
	   arg_.push_back(a1);
	   if (a2 != NULL) {
	     arity_++;
	     arg_.push_back(a2);
	   }
  }
}

OpNode::OpNode(const OpNode &other):
  ExprNode(other) {
  arity_ = other.arity();
  opCode_ = other.opCode();
  for (unsigned int i=0; (i < other.arity()); i++) {
    if (other.arg_[i]) {
      arg_.push_back((other.arg_[i])->clone());
    } 
	else {
      arg_.push_back(NULL);
    }
  }
}

void 
OpNode::print(ostream& os, int indent) const {
	int iopcode = static_cast<int>(opCode_);
  if (opInfo[iopcode].prtType_ == OpNode::OpPrintType::PREFIX) {
	os << opInfo[iopcode].name_;
	if (arity_ > 0) {
	  if (opInfo[iopcode].needParen_) 
		os << '(';
	  for (unsigned i=0; i < arity_-1; i++) {
		if (arg_[i])
		  arg_[i]->print(os, indent);
	    else os << "NULL";
		os << ", ";
	  }
      if (arg_[arity_-1])
		arg_[arity_-1]->print(os, indent);
	  else os << "NULL";
	  if (opInfo[iopcode].needParen_) 
		os << ") ";
	}
  }
  else if ((opInfo[iopcode].prtType_ == OpNode::OpPrintType::INFIX) && (arity_ == 2)) {
	if (opInfo[iopcode].needParen_) 
	  os << "(";
	if(arg_[0])
	  arg_[0]->print(os, indent);
	else os << "NULL";
	os << opInfo[iopcode].name_; 
	if(arg_[1])
	  arg_[1]->print(os, indent);
	else os << "NULL";
	if (opInfo[iopcode].needParen_) 
	  os << ")";
  }
  else internalErr("Unhandled case in OpNode::print");
}

IfNode::IfNode(ExprNode* cond, StmtNode* thenStmt, StmtNode* elseStmt, int line, int column, string file)
 : StmtNode(StmtNode::StmtNodeKind::IF, line, column, file)
{
    cond_ = cond;
    then_ = thenStmt;
    else_ = elseStmt;
}

void IfNode::print(ostream &os, int indent) const
{
    os << "if (";
    cond_->print(os, indent);
    os << ") ";
    if (then_)
    {
      then_->print(os,indent);
    }
    if (else_)
    {
        os << "else ";
        else_->print(os,indent);
        os << ";" << endl;
    }
}

void CompoundStmtNode::printWithoutBraces(ostream& os, int indent) const
{
    list<StmtNode*>::const_iterator iter;
    for (iter = stmts_->begin(); iter != stmts_->end(); ++iter)
    {
        if (*iter != NULL)
        {
          (*iter)->print(os, indent);
          os << ";" << endl;
        }
        else break;
    }
}

void CompoundStmtNode::print(ostream& os, int indent) const
{
    os << "{";
    printWithoutBraces(os, indent);
    os << "};" << endl;
}

//zdd

EFSAlist* RuleNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	codeList->addCode(new LabelCode("RuleBegin"));

	codeList->addCodeList(reaction()->codeGen());	

	codeList->addCode(new LabelCode("RuleEnd"));
	return codeList;
}

EFSAlist* ReturnStmtNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	return codeList;
}

EFSAlist* ExprStmtNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();	
	codeList->addCodeList(expr_->codeGen());
	
	return codeList;
}

EFSAlist* CompoundStmtNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist(); 
	list<StmtNode*>::const_iterator iter;
	for (iter = stmts()->begin(); iter != stmts()->end(); ++iter)
	{
		if (*iter != NULL)
		{
			codeList->addCodeList((*iter)->codeGen());
		}
		else break;
	}
	return codeList;
}

EFSAlist* IfNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	codeList->addCodeList(cond()->codeGen());
	EFSA* conditionCode = codeList->getLastCode();
	codeList->removeLastCode();
	
	string l1 = "Label"+std::to_string(labelNum);
	labelNum++;
	string l2 = "Label"+std::to_string(labelNum);
	labelNum++;
	LabelCode* label1 = new LabelCode(l1);
	LabelCode* label2 = new LabelCode(l2);
	JumpCode* jumpCode1 = new JumpCode(EFSA::OperandName::JMPC, conditionCode, label1);
	codeList->addCode(jumpCode1);
	if (elseStmt()!=NULL){
		EFSAlist* list = elseStmt()->codeGen();
		if (list!=NULL)
			codeList->addCodeList(list);
	}
	JumpCode* jumpCode2 = new JumpCode(EFSA::OperandName::JMP, NULL, label2);
	codeList->addCode(jumpCode2);
	codeList->addCode(label1);
	if (thenStmt()!=NULL){
		EFSAlist* list = thenStmt()->codeGen();
		if (list!=NULL)
			codeList->addCodeList(list);
	}
	codeList->addCode(label2);
 	
	return codeList;
}

EFSAlist* RefExprNode::codeGen() {
	regNum(((VariableEntry*)sym_)->regNum());
	regIF(((VariableEntry*)sym_)->regIF());
	return NULL;
}


/*
    all the operation:
    UMINUS, PLUS, MINUS, MULT, DIV, MOD, 
    EQ, NE, GT, LT, GE, LE,
    AND, OR, NOT, 
    BITNOT, BITAND, BITOR, BITXOR, SHL, SHR,
    ASSIGN, PRINT, INVALID
*/
/* 
    intermediate code:
    ADD, SUB, DIV, MUL, MOD, NEG, AND, OR, XOR, FADD, FSUB, FDIV, FMUL, FNEG, GT, GE,
    UGT, UGE, EQ, NE, FGT, FGE, FEQ, FNE, LABEL, MOVL, MOVS, MOVI, MOVF, MOVIF, LDI, 
    LDF, STI, STF
*/
EFSAlist* OpNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	EFSAlist* temp1 = arg_[0]->codeGen();
	EFSAlist* temp2 = arg_[1]->codeGen();
	if (temp1!=NULL)
		codeList->addCodeList(temp1);
	if (temp2!=NULL)
		codeList->addCodeList(temp2);

	//ADD, SUB, DIV, MUL, MOD, NEG, AND, OR and XOR.
	switch (opCode()){
		case OpNode::OpCode::PLUS:
			if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()!=-1){	//expr+expr
				if (arg_[0]->regIF()==0){	//int
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, EFSA::OperandName::FADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr+value
				if (arg_[0]->regIF()==0){	//int
				
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value+expr
				if (arg_[1]->regIF()==0){	//int
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[1]->regIF()==1){	//float
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FADD, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()==-1){	//value+value
					string leftReg = "";
					string rightReg = "";
					string destReg = "";
					regNum(999);
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					bool flag = false;
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					vn = (ValueNode*)arg_[1];
					type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					if (flag){
						destReg = "F999";
						regIF(1);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FADD, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
					else{
						destReg = "R999";
						regIF(0);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
			}
			break;

		case OpNode::OpCode::MINUS:
			if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()!=-1){	//expr+expr
				if (arg_[0]->regIF()==0){	//int
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, EFSA::OperandName::FSUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr+value
				if (arg_[0]->regIF()==0){	//int
				
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FSUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value+expr
				if (arg_[1]->regIF()==0){	//int
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[1]->regIF()==1){	//float
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FSUB, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()==-1){	//value+value
					string leftReg = "";
					string rightReg = "";
					string destReg = "";
					regNum(999);
					
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					bool flag = false;
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					vn = (ValueNode*)arg_[1];
					type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					if (flag){
						destReg = "F999";
						regIF(1);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FSUB, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
					else{
						destReg = "R999";
						regIF(0);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}

			}
			break;

		case OpNode::OpCode::MULT:
			if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()!=-1){	//expr+expr
				if (arg_[0]->regIF()==0){	//int
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::MUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, EFSA::OperandName::FMUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr+value
				if (arg_[0]->regIF()==0){	//int
				
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::MUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FMUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value+expr
				if (arg_[1]->regIF()==0){	//int
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::MUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[1]->regIF()==1){	//float
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FMUL, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()==-1){	//value+value
					string leftReg = "";
					string rightReg = "";
					string destReg = "";
					regNum(999);
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					bool flag = false;
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					vn = (ValueNode*)arg_[1];
					type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					if (flag){
						destReg = "F999";
						regIF(1);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FMUL, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
					else{
						destReg = "R999";
						regIF(0);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::MUL, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
			}
			break;

		case OpNode::OpCode::DIV:
			if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()!=-1){	//expr+expr
				if (arg_[0]->regIF()==0){	//int
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::DIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string destReg = "R999";
					FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, EFSA::OperandName::FDIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr+value
				if (arg_[0]->regIF()==0){	//int
				
					string leftReg = "R"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::DIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[0]->regIF()==1){	//float
					string leftReg = "F"+std::to_string(arg_[0]->regNum());
					string rightReg = "";
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FDIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value+expr
				if (arg_[1]->regIF()==0){	//int
					string rightReg = "R"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "R999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::DIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(0);
				}
				else if (arg_[1]->regIF()==1){	//float
					string rightReg = "F"+std::to_string(arg_[1]->regNum());
					string leftReg = "";
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
					}
					string destReg = "F999";
					IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FDIV, destReg, leftReg, rightReg);
					codeList->addCode(code);
					regNum(999);
					regIF(1);
				}
			}
			else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()==-1){	//value+value
					string leftReg = "";
					string rightReg = "";
					string destReg = "";
					regNum(999);
					ValueNode* vn = (ValueNode*)arg_[0];
					Type* type = vn->type();
					bool flag = false;
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						leftReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						leftReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					vn = (ValueNode*)arg_[1];
					type = vn->type();
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						rightReg = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						rightReg = std::to_string(vn->value()->dval());
						flag = true;
					}
					if (flag){
						destReg = "F999";
						regIF(1);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::FDIV, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
					else{
						destReg = "R999";
						regIF(0);
						IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::DIV, destReg, leftReg, rightReg);
						codeList->addCode(code);
					}
			}
			break;
		
		case OpNode::OpCode::ASSIGN:
			if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0) {	//intReg=?
				if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0) {	//move int/reg to register: MOVI <valueOrReg> <intreg>
					string from = "R"+std::to_string(arg_[1]->regNum());
					string dest = "R"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, from, dest);
					codeList->addCode(code);
				}
				else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1) {	//move float to int reg: MOVIF <freg> <intreg>
					string from = "F"+std::to_string(arg_[1]->regNum());
					string dest = "R"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVIF, from, dest);
					codeList->addCode(code);
				}
				else if (arg_[1]->regNum()==-1)	{	//move int/reg to register: MOVI <valueOrReg> <intreg>
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					string from = "";
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						from = std::to_string(vn->value()->ival());
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						from = std::to_string(vn->value()->dval());	//double, could split with .
					}
					string dest = "R"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, from, dest);
					codeList->addCode(code);
				}
			}
			else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1) {	//floatReg=?
				if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1) {	//move float to register: MOVF <valueOrReg> <freg>
					string from = "F"+std::to_string(arg_[1]->regNum());
					string dest = "F"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVF, from, dest);
					codeList->addCode(code);
				}
				else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0) {	//move int to float reg: MOVIF <intreg> <freg>
					string from = "R"+std::to_string(arg_[1]->regNum());
					string dest = "F"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVIF, from, dest);
					codeList->addCode(code);
				}
				else if (arg_[1]->regNum()==-1)	{	//move float to register: MOVF <valueOrReg> <freg>
					ValueNode* vn = (ValueNode*)arg_[1];
					Type* type = vn->type();
					string from = "";
					if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						from = std::to_string(vn->value()->ival());	//int, could add .
					}
					else if (type->tag()==Type::TypeTag::DOUBLE){
						from = std::to_string(vn->value()->dval());	
					}
					string dest = "F"+std::to_string(arg_[0]->regNum());
					MoveCode* code = new MoveCode(EFSA::OperandName::MOVF, from, dest);
					codeList->addCode(code);
				}
			}
			break;

		/*
		case OpNode::OpCode::GT:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GT, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::GE:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GE, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::UGT:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::UGT, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::UGE:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::UGE, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::EQ:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::EQ, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::NE:	//int
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "R"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "R"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::NE, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::FGT:	//float
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::FGT, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::FGE:	//float
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::FGE, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::FEQ:	//float
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::FEQ, left, right);
			codeList->addCode(code);
			break;
		}

		case OpNode::OpCode::FNE:	//float
		{
			string left="";
			if (arg_[0]->regNum()!=-1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::FNE, left, right);
			codeList->addCode(code);
			break;
		}*/
		//EQ, NE, GT, LT, GE, LE,
		case OpNode::OpCode::EQ:{
			string left="";
			if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
				left = "R"+std::to_string(arg_[0]->regNum());
			else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0)
				right = "R"+std::to_string(arg_[1]->regNum());
			else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::EQ, left, right);
			codeList->addCode(code);
			break;
		}
		case OpNode::OpCode::NE:{
			string left="";
			if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
				left = "R"+std::to_string(arg_[0]->regNum());
			else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0)
				right = "R"+std::to_string(arg_[1]->regNum());
			else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::NE, left, right);
			codeList->addCode(code);
			break;
		}
		case OpNode::OpCode::GT:{
			string left="";
			if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
				left = "R"+std::to_string(arg_[0]->regNum());
			else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0)
				right = "R"+std::to_string(arg_[1]->regNum());
			else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GT, left, right);
			codeList->addCode(code);
			break;
		}
		case OpNode::OpCode::GE:{
			string left="";
			if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
				left = "R"+std::to_string(arg_[0]->regNum());
			else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
				left = "F"+std::to_string(arg_[0]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[0];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			string right="";
			if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0)
				right = "R"+std::to_string(arg_[1]->regNum());
			else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
				right = "F"+std::to_string(arg_[1]->regNum());
			else {
				ValueNode* vn = (ValueNode*)arg_[1];
				Type* type = vn->type();
				if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
						left = std::to_string(vn->value()->ival());	
				}
				else if (type->tag()==Type::TypeTag::DOUBLE){
						left = std::to_string(vn->value()->dval());	
				}
			}
			IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GE, left, right);
			codeList->addCode(code);
			break;
		}
		default:
			break;
	}
	
	return codeList;
}

EFSAlist* ValueNode::codeGen() {
	return NULL;
}

EFSAlist* InvocationNode::codeGen() {
	EFSAlist* codeList = NULL;
	codeList = new EFSAlist();
	return codeList;
}


