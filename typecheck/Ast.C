#include "Ast.h"					
#include "ParserUtil.h"					
#include "EventMatch.h"

int iMatchLabelInRule = 0; //Yansong
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
    //PRINT
    if (opCode() == OpCode::PRINT)
    {
        if (tl != NULL)
        {
            if (!(Type::isNumeric(tl->tag()) || Type::isString(tl->tag())))
            {
                errMsg("wrong print format!", line(), column(), file().c_str());
            }
            else
            {
                type((Type *)tl);
                return type();
            }

        }
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

WhileNode::WhileNode(ExprNode* cond, StmtNode* whileStmt, int line, int column, string file) :
    StmtNode(StmtNode::StmtNodeKind::WHILE, line, column, file) 
{
    cond_ = cond;
    stmt_ = whileStmt;
    //loop_inv_stmt_ = NULL;
}


void WhileNode::print(ostream& os, int indent) const{
    os << "while (";
    if(cond_)
        cond_->print(os,indent);
    os << ") ";
    if(stmt_) {
        stmt_->print(os,indent);
        if (stmt_->stmtNodeKind() != StmtNode::StmtNodeKind::COMPOUND) {
            os << ";";
            prtln(os, indent);
        }
    }
}


int RuleNode::regAlloc() {
    for (int i=AVAIL_REG_SIZE+1; i<=EVENT_NAME_REG_SIZE; i++){
        if (intReg[i]==0){
            intReg[i]=1;
            regNum(i);
            return i;
        }
    }
    return REG_FAILED;
}

void EFSAlist::dealDuplicateLabel(){    
    int markList[codeList.size()];
    for (int i=0; i<codeList.size(); i++)
        markList[i]=0;
    vector<EFSA*>::iterator iter=codeList.begin();
    while (iter!=codeList.end()){
        vector<EFSA*>::iterator iter1 = iter;
        iter1++;
        if (iter1==codeList.end())
            break;
        if ((*iter)->operatorType()==EFSA::OperatorType::LABEL && (*iter1)->operatorType()==EFSA::OperatorType::LABEL){
            markList[(int)(iter-codeList.begin())]=1;
        }
        ++iter;
    }

    iter = codeList.begin();
    int j =1;
    for (int i=0; i<codeList.size(); i++){
        if (markList[i]==1){
            codeList.insert (iter+i+j,1,new PrintCode(EFSA::OperandName::PRTS, "\"\""));
            iter=codeList.begin();
            j++;
        }
    }
    iter = codeList.begin() + codeList.size();
    codeList.insert (iter,1,new PrintCode(EFSA::OperandName::PRTS, "\"\""));
}


void EFSAlist::codePrint(ostream& os) {
    vector <EFSA*>::iterator it = codeList.begin();
    for(;it!=codeList.end();it++) {
        (*it)->codePrint(os);
    }
}

void IntArithCode::codePrint(ostream& os) {
    if (operandNum_==IntArithCode::OperandNum::BINARY){	
        switch(name()){	//ADD, SUB, DIV, MUL, MOD, NEG, AND, OR and XOR
            case EFSA::OperandName::ADD:
                os<<"ADD";
                break;
            case EFSA::OperandName::SUB:
                os<<"SUB";
                break;
            case EFSA::OperandName::DIV:
                os<<"DIV";
                break;
            case EFSA::OperandName::MUL:
                os<<"MUL";
                break;
            case EFSA::OperandName::MOD:
                os<<"MOD";
                break;
            case EFSA::OperandName::AND:
                os<<"AND";
                break;
            case EFSA::OperandName::OR:
                os<<"OR";
                break;
            case EFSA::OperandName::XOR:
                os<<"XOR";
                break;
            default:
                break;

        }
        os<<" "<<leftOperand()<<" "<<rightOperand()<<" "<<dest()<<endl;
    }
}

void FloatArithCode::codePrint(ostream& os) {
    if (operandNum_==FloatArithCode::OperandNum::BINARY){	
        switch(name()){	//FADD, FSUB, FDIV, FMUL, FNEG
            case EFSA::OperandName::FADD:
                os<<"FADD";
                break;
            case EFSA::OperandName::FSUB:
                os<<"FSUB";
                break;
            case EFSA::OperandName::FDIV:
                os<<"FDIV";
                break;
            case EFSA::OperandName::FMUL:
                os<<"FMUL";
                break;
            default:
                break;

        }
        os<<" "<<leftOperand()<<" "<<rightOperand()<<" "<<dest()<<endl;
    }
}

void IntRelationCode::codePrint(ostream& os){
    switch (name()){
        case EFSA::OperandName::GT:
            os<<"GT"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::GE:
            os<<"GE"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::UGT:
            os<<"UGT"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::UGE:
            os<<"UGE"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::EQ:
            os<<"EQ"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::NE:
            os<<"NE"<<" "<<left_<<" "<<right_;
            break;
        default:
            break;
    }
}

void FloatRelationCode::codePrint(ostream& os){
    switch (name()){
        case EFSA::OperandName::FGT:
            os<<"FGT"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::FGE:
            os<<"FGE"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::FEQ:
            os<<"FEQ"<<" "<<left_<<" "<<right_;
            break;
        case EFSA::OperandName::FNE:
            os<<"FNE"<<" "<<left_<<" "<<right_;
            break;
        default:
            break;
    }
}

void LabelCode::codePrint(ostream& os){
    os<<name_;
    if (target_==1)
        os<<":";
    else
        os<<endl;
    /*
       if (name_=="RuleEnd")
       os<<endl;
       };*/
        }

void MoveCode::codePrint(ostream& os) {		//MOVL, MOVS
    switch (name()){
        case EFSA::OperandName::LDI:
            os<<"LDI"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::LDF:
            os<<"LDF"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::STI:
            os<<"STI"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::STF:
            os<<"STF"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::MOVI:
            os<<"MOVI"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::MOVL:
            os<<"MOVL"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::MOVF:
            os<<"MOVF"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::MOVIF:
            os<<"MOVIF"<<" "<<from_<<" "<<dest_<<endl;
            break;
        case EFSA::OperandName::MOVS:
            os<<"MOVS"<<" "<<from_<<" "<<dest_<<endl;
            break;
        default:
            break;
    }
}

void JumpCode::codePrint(ostream& os){
    switch(name())
    {
        case EFSA::OperandName::JMP:
            os<<"JMP"<<" ";
            label_->codePrint(os);
            break;
        case EFSA::OperandName::JMPI:
            os<<"JMPI"<<" ";
            label_->codePrint(os);
            break;
        case EFSA::OperandName::JMPC:
            os<<"JMPC"<<" ";
            cond_->codePrint(os);
            os<<" ";
            label_->codePrint(os);
            break;
        default:
            break;
    }
}

//Yansong
void InCode::codePrint(ostream& os) {
    switch (name()) {
        case EFSA::OperandName::IN:
            os << "IN " << strReg_ << endl;
            break;
        case EFSA::OperandName::INF:
            os << "INF " << strReg_ << endl;
            break;
        case EFSA::OperandName::INI:
            os << "INI " << strReg_ << endl;
            break;
        default:
            break;
    }
}

void PrintCode::codePrint(ostream &os) {
    switch(name()) {
        case EFSA::OperandName::PRTS:
            os << "PRTS " << str_ << endl;
            break;
        case EFSA::OperandName::PRTI:
            os << "PRTI " << reg_ << endl;
            break;
        case EFSA::OperandName::PRTF:
            os << "PRTF " << reg_ << endl;
            break;
        default:
            break;
    }
}

void EFSAlist::addCodeList(EFSAlist* codes) {
    if (codes!=NULL){
        vector <EFSA*>::iterator it = codes->codeList.begin();
        for(;it!=codes->codeList.end();it++) {
            codeList.push_back((*it));
        }
    }
}

void EFSAlist::addCode(EFSA* code) {
    if (code!=NULL)
        codeList.push_back(code);
}

EFSA* EFSAlist::getLastCode() {
    return codeList.back();
}

void EFSAlist::removeLastCode() {
    codeList.pop_back();
}

EFSAlist* RuleNode::codeGen() {
    EFSAlist* codeList = NULL;
    codeList = new EFSAlist();
    /*
       string l1 = LABEL_PREFIX+std::to_string(labelNum);
       labelNum++;
       codeList->addCode(new LabelCode(l1, 1));
       ruleLabel(l1);
       */
    codeList->addCode(new LabelCode(ruleLabel(), 1));

    EventMatch em(LABEL_PROG_EXIT);
    codeList->addCodeList(em.getReadParamCodeList(this)); //em, Yansong
    codeList->addCode(new LabelCode(ruleSkipLabel(), 1));
    codeList->addCodeList(reaction()->codeGen());	

    //codeList->addCode(new LabelCode("RuleEnd", 1));
    //codeList->addCode(new JumpCode(EFSA::OperandName::JMP, NULL, new LabelCode(GLOBAL_BEGIN)));
    //Yansong
    codeList->addCode(new MoveCode(EFSA::OperandName::MOVI, "1", getReg(EVENT_STATE_REG)));
    codeList->addCode(new JumpCode(EFSA::OperandName::JMP, NULL,
                new LabelCode("Match" + numToString(iMatchLabelInRule))));
    iMatchLabelInRule++;	

    return codeList;
}

EFSAlist* ReturnStmtNode::codeGen() {
    EFSAlist* codeList = NULL;
    codeList = new EFSAlist();
    codeList->addCodeList(expr_->codeGen());

    // get sp
    string sp_reg_name = getReg(SP_REG, INT_FLAG);

    // sub sp by 1 -> pop
    IntArithCode* sub_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::SUB, sp_reg_name, sp_reg_name, std::to_string(1));
    codeList->addCode(sub_code);

    // store return value to stack
    string ret_value_reg_name = getReg(expr_->regNum(), expr_->regIF());
    if(expr_->regIF() == FLOAT_FLAG) {
        MoveCode * stfr_sp = new MoveCode(EFSA::OperandName::STF, ret_value_reg_name, sp_reg_name);
        codeList->addCode(stfr_sp);
    }
    else if(expr_->regIF() == INT_FLAG) {
        MoveCode * stir_sp = new MoveCode(EFSA::OperandName::STI, ret_value_reg_name, sp_reg_name);
        codeList->addCode(stir_sp);
    }

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

    string l1 = LABEL_PREFIX+std::to_string(labelNum);
    labelNum++;
    string l2 = LABEL_PREFIX+std::to_string(labelNum);
    labelNum++;
    JumpCode* jumpCode1 = new JumpCode(EFSA::OperandName::JMPC, conditionCode, new LabelCode(l1));
    codeList->addCode(jumpCode1);
    if (elseStmt()!=NULL){
        EFSAlist* list = elseStmt()->codeGen();
        if (list!=NULL)
            codeList->addCodeList(list);
    }
    JumpCode* jumpCode2 = new JumpCode(EFSA::OperandName::JMP, NULL, new LabelCode(l2));
    codeList->addCode(jumpCode2);
    codeList->addCode(new LabelCode(l1,1));
    if (thenStmt()!=NULL){
        EFSAlist* list = thenStmt()->codeGen();
        if (list!=NULL)
            codeList->addCodeList(list);
    }
    codeList->addCode(new LabelCode(l2,1));

    return codeList;
}


EFSAlist* WhileNode::codeGen()
{
    EFSAlist* codeList = NULL;
    codeList = new EFSAlist();

    string l1 = LABEL_PREFIX+std::to_string(labelNum);
    labelNum++;
    string l2 = LABEL_PREFIX+std::to_string(labelNum);
    labelNum++;
    string l3 = LABEL_PREFIX+std::to_string(labelNum);
    labelNum++;
    codeList->addCode(new LabelCode(l1,1));

    codeList->addCodeList(cond()->codeGen());
    EFSA* conditionCode = codeList->getLastCode();
    codeList->removeLastCode();
    JumpCode* jumpCode1 = new JumpCode(EFSA::OperandName::JMPC, conditionCode, new LabelCode(l2));
    codeList->addCode(jumpCode1);
    JumpCode* jumpCode2 = new JumpCode(EFSA::OperandName::JMP, NULL, new LabelCode(l3));
    codeList->addCode(jumpCode2);
    codeList->addCode(new LabelCode(l2,1));
    if (whileStmt()!=NULL){
        EFSAlist* list = whileStmt()->codeGen();
        if (list!=NULL)
            codeList->addCodeList(list);
    }
    JumpCode* jumpCode3 = new JumpCode(EFSA::OperandName::JMP, NULL, new LabelCode(l1));
    codeList->addCode(jumpCode3);
    codeList->addCode(new LabelCode(l3,1));
    return codeList;
}

EFSAlist* RefExprNode::codeGen() {
    regNum(((VariableEntry*)sym_)->regNum());
    regIF(((VariableEntry*)sym_)->regIF());
    return NULL;
}


int OpNode::tempIntVarAlloc() {
    for (int i=0; i<=AVAIL_REG_SIZE; i++){
        if (intReg[i]==0){
            intReg[i] = 1;
            return i;
        }
    }
    return REG_FAILED;
}

int OpNode::tempFloatVarAlloc() {
    for (int i=0; i<=AVAIL_REG_SIZE; i++){
        if (floatReg[i]==0){
            floatReg[i] = 1;
            return i;
        }
    }
    return REG_FAILED;
}

void OpNode::tempIntVarRelease(int i) {
    intReg[i] = 0;
}

void OpNode::tempFloatVarRelease(int i) {
    floatReg[i] = 0;
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
    if (opCode()==OpNode::OpCode::PLUS  || opCode()==OpNode::OpCode::MINUS || opCode()==OpNode::OpCode::MULT || opCode()==OpNode::OpCode::DIV){
        EFSA::OperandName iOperandName;
        EFSA::OperandName fOperandName;
        switch (opCode()){
            case OpNode::OpCode::PLUS:  iOperandName=EFSA::OperandName::ADD; fOperandName=EFSA::OperandName::FADD; break;
            case OpNode::OpCode::MINUS:  iOperandName=EFSA::OperandName::SUB; fOperandName=EFSA::OperandName::FSUB; break;
            case OpNode::OpCode::MULT:  iOperandName=EFSA::OperandName::MUL; fOperandName=EFSA::OperandName::FMUL; break;
            case OpNode::OpCode::DIV:  iOperandName=EFSA::OperandName::DIV; fOperandName=EFSA::OperandName::FDIV; break;
            default: break;
        }
        if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()!=-1){	//expr op expr
            if (arg_[0]->regIF()==0){	//int
                //string leftReg = "R"+std::to_string(arg_[0]->regNum());
                //string rightReg = "R"+std::to_string(arg_[1]->regNum());
                string leftReg = getReg(arg_[0]->regNum(), 0);
                string rightReg = getReg(arg_[1]->regNum(), 0);

                int optFlag = -1;
                if (leftReg==rightReg && opCode()==OpNode::OpCode::MINUS)
                    optFlag = 0;

                int destRegNum = tempIntVarAlloc();
                //string destReg = "R"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 0);

                if (arg_[0]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[0]->regNum());
                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[1]->regNum());

                IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
                regNum(destRegNum);
                regIF(0);
            }
            else if (arg_[0]->regIF()==1){	//float
                //string leftReg = "F"+std::to_string(arg_[0]->regNum());
                //string rightReg = "F"+std::to_string(arg_[1]->regNum());
                string leftReg = getReg(arg_[0]->regNum(), 1);
                string rightReg = getReg(arg_[1]->regNum(), 1);

                int destRegNum = tempFloatVarAlloc();
                //string destReg = "F"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 1);
                if (arg_[0]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[0]->regNum());
                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[1]->regNum());

                FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, fOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
                regNum(destRegNum);
                regIF(1);
            }
        }
        else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr op value
            if (arg_[0]->regIF()==0){	//int
                //string leftReg = "R"+std::to_string(arg_[0]->regNum());
                string leftReg = getReg(arg_[0]->regNum(), 0);

<<<<<<< HEAD
                string rightReg = "";
                ValueNode* vn = (ValueNode*)arg_[1];
                Type* type = vn->type();
                int optFlag = -1;
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    rightReg = std::to_string(vn->value()->ival());
                    if (((opCode()==OpNode::OpCode::PLUS || opCode()==OpNode::OpCode::MINUS) && rightReg=="0") || ((opCode()==OpNode::OpCode::MULT || opCode()==OpNode::OpCode::DIV) && rightReg=="1"))
                        optFlag = 0;
                    else if (opCode()==OpNode::OpCode::MULT && rightReg=="0")
                        optFlag = 1;
=======
                    if (optFlag==0){
                        MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, "0", destReg);
                        codeList->addCode(code);
                    }
                    else{
                        IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                        codeList->addCode(code);
                    }
                    regNum(destRegNum);
                    regIF(0);
>>>>>>> 1cf963daa33ef40d8661691ca7ebfe77729b946d
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    rightReg = std::to_string(vn->value()->dval());
                }
<<<<<<< HEAD

                int destRegNum = tempIntVarAlloc();
                //string destReg = "R"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 0);
                if (arg_[0]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[0]->regNum());
                if (optFlag==0){
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, leftReg, destReg);
                    codeList->addCode(code);
=======
            }
            else if (arg_[0]->regNum()!=-1 && arg_[1]->regNum()==-1){	//expr op value
                if (arg_[0]->regIF()==0){	//int
                    //string leftReg = "R"+std::to_string(arg_[0]->regNum());
                    string leftReg = getReg(arg_[0]->regNum(), 0);

                    string rightReg = "";
                    ValueNode* vn = (ValueNode*)arg_[1];
                    Type* type = vn->type();
                    int optFlag = -1;
                    if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                        rightReg = std::to_string(vn->value()->ival());
                        if (((opCode()==OpNode::OpCode::PLUS || opCode()==OpNode::OpCode::MINUS) && rightReg=="0") || ((opCode()==OpNode::OpCode::MULT || opCode()==OpNode::OpCode::DIV) && rightReg=="1"))
                            optFlag = 0;
                        else if (opCode()==OpNode::OpCode::MULT && rightReg=="0")
                            optFlag = 1;
                        else if (opCode()==OpNode::OpCode::MULT && rightReg=="2")
                            optFlag = 2;
                    }
                    else if (type->tag()==Type::TypeTag::DOUBLE){
                        rightReg = std::to_string(vn->value()->dval());
                    }

                    int destRegNum = tempIntVarAlloc();
                    //string destReg = "R"+std::to_string(destRegNum);
                    string destReg = getReg(destRegNum, 0);
                    if (arg_[0]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[0]->regNum());
                    if (optFlag==0){
                            MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, leftReg, destReg);
                            codeList->addCode(code);
                    }
                    else if (optFlag==1){
                            MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, "0", destReg);
                            codeList->addCode(code);
                    }
                    else if (optFlag==2){
                            IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, leftReg, leftReg);
                            codeList->addCode(code);  
                    }
                    else{
                            IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                            codeList->addCode(code);                           
                    }
                    regNum(destRegNum);
                    regIF(0);
>>>>>>> 1cf963daa33ef40d8661691ca7ebfe77729b946d
                }
                else if (optFlag==1){
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, "0", destReg);
                    codeList->addCode(code);
                }
                else{
                    IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                    codeList->addCode(code);                           
                }
                regNum(destRegNum);
                regIF(0);
            }
<<<<<<< HEAD
            else if (arg_[0]->regIF()==1){	//float
                //string leftReg = "F"+std::to_string(arg_[0]->regNum());
                string leftReg = getReg(arg_[0]->regNum(), 1);
                string rightReg = "";
                ValueNode* vn = (ValueNode*)arg_[1];
                Type* type = vn->type();
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    rightReg = std::to_string(vn->value()->ival());
=======
            else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value op expr
                if (arg_[1]->regIF()==0){	//int
                    //string rightReg = "R"+std::to_string(arg_[1]->regNum());
                    string rightReg = getReg(arg_[1]->regNum(), 0);
                    string leftReg = "";
                    ValueNode* vn = (ValueNode*)arg_[0];
                    Type* type = vn->type();
                    int optFlag = -1;
                    if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                        leftReg = std::to_string(vn->value()->ival());
                        if ((opCode()==OpNode::OpCode::PLUS && leftReg=="0") || (opCode()==OpNode::OpCode::MULT && leftReg=="1"))
                                optFlag = 0;
                         else if (opCode()==OpNode::OpCode::MULT && leftReg=="0")
                                optFlag = 1;
                         else if (opCode()==OpNode::OpCode::MULT && leftReg=="2")
                                optFlag = 2;
                    }
                    else if (type->tag()==Type::TypeTag::DOUBLE){
                        leftReg = std::to_string(vn->value()->dval());
                    }

                    int destRegNum = tempIntVarAlloc();
                    //string destReg = "R"+std::to_string(destRegNum);
                    string destReg = getReg(destRegNum, 0);
                    if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[1]->regNum());

                    if (optFlag==0){
                        MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, rightReg, destReg);
                        codeList->addCode(code);
                    }
                    else if (optFlag==1){
                        MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, "0", destReg);
                        codeList->addCode(code);
                    }
                    else if (optFlag==2){
                            IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, destReg, rightReg, rightReg);
                            codeList->addCode(code);  
                    }
                    else{
                        IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                        codeList->addCode(code);
                    }
                    regNum(destRegNum);
                    regIF(0);
>>>>>>> 1cf963daa33ef40d8661691ca7ebfe77729b946d
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    rightReg = std::to_string(vn->value()->dval());
                }

                int destRegNum = tempFloatVarAlloc();
                //string destReg = "F"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 1);
                if (arg_[0]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[0]->regNum());

                FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, fOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
                regNum(destRegNum);
                regIF(1);
            }
        }
        else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()!=-1){	//value op expr
            if (arg_[1]->regIF()==0){	//int
                //string rightReg = "R"+std::to_string(arg_[1]->regNum());
                string rightReg = getReg(arg_[1]->regNum(), 0);
                string leftReg = "";
<<<<<<< HEAD
=======
                string rightReg = "";
                string destReg = "";

                ValueNode* vn1 = (ValueNode*)arg_[0];
                Type* type1 = vn1->type();
                bool flag1 = false;
                if (type1->tag()==Type::TypeTag::DOUBLE){
                    flag1 = true;
                }
                ValueNode* vn2 = (ValueNode*)arg_[1];
                Type* type2 = vn2->type();
                bool flag2 = false;
                if (type2->tag()==Type::TypeTag::DOUBLE){
                    flag2 = true;
                }
                if (flag1 || flag2){      //float
                    double i = 0.0;
                    double j = 0.0;
                    if (flag1)
                        i = vn1->value()->dval();
                    else
                        i = vn1->value()->ival();
                    if (flag2)
                        j = vn2->value()->dval();
                    else
                        j = vn2->value()->ival();
                    double result = i + j;

                    int r = tempFloatVarAlloc();
                    regNum(r);
                    destReg = getReg(r, 1);
                    regIF(1);
                    //FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, fOperandName, destReg, leftReg, rightReg);
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVF, std::to_string (result), destReg);
                    codeList->addCode(code);
                }
                else{
                    int i = vn1->value()->ival();
                    int j = vn2->value()->ival();
                    int result = i + j;

                    int r = tempIntVarAlloc();
                    regNum(r);
                    //destReg = "R"+std::to_string(r);
                    destReg = getReg(r, 0);
                    regIF(0);
                    //IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, std::to_string (result), destReg);
                    codeList->addCode(code);
                }
                /*
>>>>>>> 1cf963daa33ef40d8661691ca7ebfe77729b946d
                ValueNode* vn = (ValueNode*)arg_[0];
                Type* type = vn->type();
                int optFlag = -1;
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    leftReg = std::to_string(vn->value()->ival());
                    if ((opCode()==OpNode::OpCode::PLUS && leftReg=="0") || (opCode()==OpNode::OpCode::MULT && leftReg=="1"))
                        optFlag = 0;
                    else if (opCode()==OpNode::OpCode::MULT && leftReg=="0")
                        optFlag = 1;
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    leftReg = std::to_string(vn->value()->dval());
                }

                int destRegNum = tempIntVarAlloc();
                //string destReg = "R"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 0);
                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[1]->regNum());

                if (optFlag==0){
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, rightReg, destReg);
                    codeList->addCode(code);
                }
                else if (optFlag==1){
                    MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, "0", destReg);
                    codeList->addCode(code);
                }
                else{
                    IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                    codeList->addCode(code);
                }
<<<<<<< HEAD
                regNum(destRegNum);
                regIF(0);
            }
            else if (arg_[1]->regIF()==1){	//float
                //string rightReg = "F"+std::to_string(arg_[1]->regNum());
                string rightReg = getReg(arg_[1]->regNum(), 1);
                string leftReg = "";
                ValueNode* vn = (ValueNode*)arg_[0];
                Type* type = vn->type();
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    leftReg = std::to_string(vn->value()->ival());
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    leftReg = std::to_string(vn->value()->dval());
                }
                int destRegNum = tempFloatVarAlloc();
                //string destReg = "F"+std::to_string(destRegNum);
                string destReg = getReg(destRegNum, 1);
                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[1]->regNum());

                FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, fOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
                regNum(destRegNum);
                regIF(1);
=======
                */
>>>>>>> 1cf963daa33ef40d8661691ca7ebfe77729b946d
            }
        }
        else if (arg_[0]->regNum()==-1 && arg_[1]->regNum()==-1){	//value op value
            string leftReg = "";
            string rightReg = "";
            string destReg = "";

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
                int r = tempFloatVarAlloc();
                regNum(r);
                //destReg = "F"+std::to_string(r);
                destReg = getReg(r, 1);
                regIF(1);
                FloatArithCode* code = new FloatArithCode(FloatArithCode::OperandNum::BINARY, fOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
            }
            else{
                int r = tempIntVarAlloc();
                regNum(r);
                //destReg = "R"+std::to_string(r);
                destReg = getReg(r, 0);
                regIF(0);
                IntArithCode* code = new IntArithCode(IntArithCode::OperandNum::BINARY, iOperandName, destReg, leftReg, rightReg);
                codeList->addCode(code);
            }
        }
    }

    else if (opCode()==OpNode::OpCode::ASSIGN){
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0) {	//intReg=?
            if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0) {	//move int/reg to register: MOVI <valueOrReg> <intreg>
                //string from = "R"+std::to_string(arg_[1]->regNum());
                //string dest = "R"+std::to_string(arg_[0]->regNum());
                string from = getReg(arg_[1]->regNum(), 0);
                string dest = getReg(arg_[0]->regNum(), 0);
                MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, from, dest);
                codeList->addCode(code);

                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[1]->regNum());
            }
            else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1) {	//move float to int reg: MOVIF <freg> <intreg>
                //string from = "F"+std::to_string(arg_[1]->regNum());
                string from = getReg(arg_[1]->regNum(), 1);
                //string dest = "R"+std::to_string(arg_[0]->regNum());
                string dest = getReg(arg_[0]->regNum(), 0);
                MoveCode* code = new MoveCode(EFSA::OperandName::MOVIF, from, dest);
                codeList->addCode(code);

                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[1]->regNum());
            }
            else if (arg_[1]->regNum()==-1)	{	//move literal to register: MOVI <valueOrReg> <intreg>
                ValueNode* vn = (ValueNode*)arg_[1];
                Type* type = vn->type();
                string from = "";
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    from = std::to_string(vn->value()->ival());
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    from = std::to_string(vn->value()->dval());	//double, could split with .
                }
                //string dest = "R"+std::to_string(arg_[0]->regNum());
                string dest = getReg(arg_[0]->regNum(), 0);
                MoveCode* code = new MoveCode(EFSA::OperandName::MOVI, from, dest);
                codeList->addCode(code);
            }
        }
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1) {	//floatReg=?
            if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1) {	//move float to register: MOVF <valueOrReg> <freg>
                //string from = "F"+std::to_string(arg_[1]->regNum());
                //string dest = "F"+std::to_string(arg_[0]->regNum());
                string from = getReg(arg_[1]->regNum(), 1);
                string dest = getReg(arg_[0]->regNum(), 1);

                MoveCode* code = new MoveCode(EFSA::OperandName::MOVF, from, dest);
                codeList->addCode(code);

                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempFloatVarRelease(arg_[1]->regNum());
            }
            else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0) {	//move int to float reg: MOVIF <intreg> <freg>
                //string from = "R"+std::to_string(arg_[1]->regNum());
                string from = getReg(arg_[1]->regNum(), 0);
                //string dest = "F"+std::to_string(arg_[0]->regNum());
                string dest = getReg(arg_[0]->regNum(), 1);
                MoveCode* code = new MoveCode(EFSA::OperandName::MOVIF, from, dest);
                codeList->addCode(code);

                if (arg_[1]->exprNodeType()==ExprNode::ExprNodeType::OP_NODE)
                    tempIntVarRelease(arg_[1]->regNum());
            }
            else if (arg_[1]->regNum()==-1)	{	//move literal to register: MOVF <valueOrReg> <freg>
                ValueNode* vn = (ValueNode*)arg_[1];
                Type* type = vn->type();
                string from = "";
                if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                    from = std::to_string(vn->value()->ival());	//int, could add .
                }
                else if (type->tag()==Type::TypeTag::DOUBLE){
                    from = std::to_string(vn->value()->dval());	
                }
                //string dest = "F"+std::to_string(arg_[0]->regNum());
                string dest = getReg(arg_[0]->regNum(), 1);
                MoveCode* code = new MoveCode(EFSA::OperandName::MOVF, from, dest);
                codeList->addCode(code);
            }
        }
    }
    //EQ, NE, GT, GE
    else if (opCode()==OpNode::OpCode::EQ){
        string left="";
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)	//intreg
            //left = "R"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 0);
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)	//floatreg
            //left = "F"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 1);
        else {	//literal
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
        if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==0)	//intreg
            //right = "R"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 0);
        else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)	//floatreg
            //right = "F"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 1);
        else {	//literal
            ValueNode* vn = (ValueNode*)arg_[1];
            Type* type = vn->type();
            if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                right = std::to_string(vn->value()->ival());	
            }
            else if (type->tag()==Type::TypeTag::DOUBLE){
                right = std::to_string(vn->value()->dval());	
            }
        }
        IntRelationCode* code = new IntRelationCode(EFSA::OperandName::EQ, left, right);
        codeList->addCode(code);
    }
    else if (opCode()==OpNode::OpCode::NE){
        string left="";
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
            //left = "R"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 0);
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
            //left = "F"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 1);
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
            //right = "R"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 0);
        else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
            //right = "F"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 1);
        else {
            ValueNode* vn = (ValueNode*)arg_[1];
            Type* type = vn->type();
            if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                right = std::to_string(vn->value()->ival());	
            }
            else if (type->tag()==Type::TypeTag::DOUBLE){
                right = std::to_string(vn->value()->dval());	
            }
        }
        IntRelationCode* code = new IntRelationCode(EFSA::OperandName::NE, left, right);
        codeList->addCode(code);
    }
    else if (opCode()==OpNode::OpCode::GT){
        string left="";
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
            //left = "R"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 0);
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
            //left = "F"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 1);
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
            //right = "R"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 0);
        else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
            //right = "F"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 1);
        else {
            ValueNode* vn = (ValueNode*)arg_[1];
            Type* type = vn->type();
            if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                right = std::to_string(vn->value()->ival());	
            }
            else if (type->tag()==Type::TypeTag::DOUBLE){
                right = std::to_string(vn->value()->dval());	
            }
        }
        IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GT, left, right);
        codeList->addCode(code);
    }
    else if (opCode()==OpNode::OpCode::GE){
        string left="";
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==0)
            //left = "R"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 0);
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==1)
            //left = "F"+std::to_string(arg_[0]->regNum());
            left = getReg(arg_[0]->regNum(), 1);
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
            //right = "R"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 0);
        else if (arg_[1]->regNum()!=-1 && arg_[1]->regIF()==1)
            //right = "F"+std::to_string(arg_[1]->regNum());
            right = getReg(arg_[1]->regNum(), 1);
        else {
            ValueNode* vn = (ValueNode*)arg_[1];
            Type* type = vn->type();
            if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                right = std::to_string(vn->value()->ival());	
            }
            else if (type->tag()==Type::TypeTag::DOUBLE){
                right = std::to_string(vn->value()->dval());	
            }
        }
        IntRelationCode* code = new IntRelationCode(EFSA::OperandName::GE, left, right);
        codeList->addCode(code);
    }
    else if (opCode()==OpNode::OpCode::PRINT){
        cout << "kiukiu" << endl;
        string target="";
        PrintCode* code = NULL;
        if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==INT_FLAG) // print int
        {
            //left = "R"+std::to_string(arg_[0]->regNum());
            target = getReg(arg_[0]->regNum(), INT_FLAG);
            code = new PrintCode(EFSA::OperandName::PRTI, "", target);
        }
        else if (arg_[0]->regNum()!=-1 && arg_[0]->regIF()==FLOAT_FLAG) // print loat
        {
            //left = "F"+std::to_string(arg_[0]->regNum());
            target = getReg(arg_[0]->regNum(), FLOAT_FLAG);
            code = new PrintCode(EFSA::OperandName::PRTF, "", target);
        }
        else { // print literal
            ValueNode* vn = (ValueNode*)arg_[0];
            Type* type = vn->type();
            if (type->tag()==Type::TypeTag::UINT || type->tag()==Type::TypeTag::INT || type->tag()==Type::TypeTag::SIGNED){
                target = std::to_string(vn->value()->ival());	
                code = new PrintCode(EFSA::OperandName::PRTI, target, "");
            }
            else if (type->tag()==Type::TypeTag::DOUBLE){
                target = std::to_string(vn->value()->dval());	
                code = new PrintCode(EFSA::OperandName::PRTF, target, "");
            }
            else if (type->tag()==Type::TypeTag::STRING){
                target = vn->value()->sval();
                code = new PrintCode(EFSA::OperandName::PRTS, target, "");
            }
        }
        codeList->addCode(code);
    }

    return codeList;
}

EFSAlist* ValueNode::codeGen() {
    return NULL;
}

EFSAlist* InvocationNode::codeGen() {
    /*
     * return address
     +* |
     +* |
     +* V
     +* return value 
     +* |
     +* |
     +* V
     +* AP
     * */

    EFSAlist* codeList = NULL;
    codeList = new EFSAlist();
    codeList->addCode(new LabelCode("//CallBegin"));

    // push return address
    string l_ret = "L"+std::to_string(labelNum);
    labelNum++;

    // move label to reg
    int temp_reg = EFSA::intRegAlloc();
    //string temp_reg_name = "R"+std::to_string(temp_reg);
    string temp_reg_name  = getReg(temp_reg, 0);
    MoveCode * movl_reg = new MoveCode(EFSA::OperandName::MOVL, l_ret, temp_reg_name);
    codeList->addCode(movl_reg);
    EFSA::intRegFree(temp_reg);

    // move reg to sp->mem_addr
    //string sp_reg = "R"+std::to_string(SP_REG);
    string sp_reg = getReg(SP_REG, INT_FLAG);
    MoveCode * stir_sp = new MoveCode(EFSA::OperandName::STI, temp_reg_name, sp_reg);
    codeList->addCode(stir_sp);

    // add sp by 1 -> push
    IntArithCode* add_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, sp_reg, sp_reg, std::to_string(1));
    codeList->addCode(add_code);

    FunctionEntry * function_def = (FunctionEntry *)symTabEntry();
    // push return var, nothing inside yet
    const Type * ret_value_entry = function_def->type()->retType();
    // suppose no void function return 
    if(Type::isFloat(ret_value_entry->tag())) {
        int ret_reg = EFSA::floatRegAlloc();
        regNum(ret_reg);
        regIF(FLOAT_FLAG);
    }
    else if(Type::isInt(ret_value_entry->tag())) {
        int ret_reg = EFSA::intRegAlloc();
        regNum(ret_reg);
        regIF(INT_FLAG);
    }
    // add sp by 1 -> push
    IntArithCode* push_ret_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, sp_reg, sp_reg, std::to_string(1));
    codeList->addCode(push_ret_code);

    // push actual param

    vector<ExprNode*>* ap = params();
    // from right to left
    for (auto iter = ap->rbegin(); iter!=ap->rend(); iter++){
        if((*iter)->exprNodeType() == ExprNode::ExprNodeType::VALUE_NODE) {
            //cout<<(*iter)->value()->ival()<<endl;
            if(Type::isInt((*iter) -> type() -> tag())) {
                int param_val = (*iter)->value()->ival();
                // move int val to reg
                temp_reg = EFSA::intRegAlloc();
                //temp_reg_name = "R"+std::to_string(temp_reg);
                temp_reg_name = getReg(temp_reg, 0);
                MoveCode * movi_reg = new MoveCode(EFSA::OperandName::MOVI, std::to_string(param_val), temp_reg_name);
                codeList->addCode(movi_reg);

                // move reg to sp->memory
                MoveCode * stir_sp = new MoveCode(EFSA::OperandName::STI, temp_reg_name, sp_reg);
                codeList->addCode(stir_sp);

                EFSA::intRegFree(temp_reg);

            }
            else if(Type::isFloat((*iter) -> type() -> tag())) {
                float param_val = (*iter)->value()-> dval();
                // move float val to sp->memory
                temp_reg = EFSA::floatRegAlloc();
                //temp_reg_name = "F"+std::to_string(temp_reg);
                temp_reg_name = getReg(temp_reg, 1);
                MoveCode * movf_reg = new MoveCode(EFSA::OperandName::MOVF, std::to_string(param_val), temp_reg_name);
                codeList->addCode(movf_reg);

                // move reg to sp->memory
                MoveCode * stfr_sp = new MoveCode(EFSA::OperandName::STF, temp_reg_name, sp_reg);
                codeList->addCode(stfr_sp);

                EFSA::intRegFree(temp_reg);

            }
        }
        else if((*iter)->exprNodeType() == ExprNode::ExprNodeType::REF_EXPR_NODE || (*iter)->exprNodeType() == ExprNode::ExprNodeType::OP_NODE) {
            if((*iter)->exprNodeType() == ExprNode::ExprNodeType::REF_EXPR_NODE) {
                (*iter)->codeGen();
            }
            else if((*iter)->exprNodeType() == ExprNode::ExprNodeType::OP_NODE) {
                codeList->addCodeList((*iter)->codeGen());
            }
            int param_reg = (*iter)->regNum();
            if((*iter)->regIF() == INT_FLAG) {
                //string param_reg_int = "R"+std::to_string(param_reg);
                string param_reg_int = getReg(param_reg, 0);
                MoveCode * stir_sp = new MoveCode(EFSA::OperandName::STI, param_reg_int, sp_reg);
                codeList->addCode(stir_sp);
            }
            else if((*iter)->regIF() == FLOAT_FLAG) {
                //string param_reg_float = "F"+std::to_string(param_reg);
                string param_reg_float = getReg(param_reg, 1);
                MoveCode * stfr_sp = new MoveCode(EFSA::OperandName::STF, param_reg_float, sp_reg);
                codeList->addCode(stfr_sp);
            }
        }

        // add sp by 1 -> push
        IntArithCode* add_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, sp_reg, sp_reg, std::to_string(1));
        codeList->addCode(add_code);
    }

    // jump to function by function-name-label
    LabelCode* label = new LabelCode(((FunctionEntry *)symTabEntry())->name());
    JumpCode* jumpCode = new JumpCode(EFSA::OperandName::JMP, NULL, label);
    codeList->addCode(jumpCode);

    // return label
    LabelCode * label_return = new LabelCode(l_ret, TAR_LB);
    codeList->addCode(label_return);

    // get return value from sp->memory to register
    // get new temp register
    temp_reg = EFSA::intRegAlloc();
    //temp_reg_name = "R"+std::to_string(temp_reg);
    temp_reg_name = getReg(temp_reg, INT_FLAG);

    // move sp to reg
    MoveCode * movsp_r = new MoveCode(EFSA::OperandName::MOVI, sp_reg, temp_reg_name);
    codeList->addCode(movsp_r);

    // add reg by 1 -> return value addr
    IntArithCode* add_reg_code = new IntArithCode(IntArithCode::OperandNum::BINARY, EFSA::OperandName::ADD, temp_reg_name, temp_reg_name, std::to_string(1));
    codeList->addCode(add_reg_code);

    // ldi sp+1->memory to ret_reg
    int ret_reg = regNum();
    string ret_reg_name;

    if(Type::isFloat(ret_value_entry->tag())) {
        //ret_reg_name = "F"+std::to_string(ret_reg);
        ret_reg_name = getReg(ret_reg, FLOAT_FLAG);
        MoveCode * ldfspp_ret = new MoveCode(EFSA::OperandName::LDF, temp_reg_name, ret_reg_name); // dest, from
        codeList->addCode(ldfspp_ret);
        //delete ldfspp_ret;

        // eliminate temp reg
        EFSA::intRegFree(temp_reg);
    }
    else if(Type::isInt(ret_value_entry->tag())) {
        //ret_reg_name = "R"+std::to_string(ret_reg);
        ret_reg_name = getReg(ret_reg, INT_FLAG);
        MoveCode * ldispp_ret = new MoveCode(EFSA::OperandName::LDI, temp_reg_name, ret_reg_name); // dest, from
        codeList->addCode(ldispp_ret);
        //delete ldispp_ret;

        // eliminate temp reg
        EFSA::floatRegFree(temp_reg);
    }

    codeList->addCode(new LabelCode("//CallEnd"));

    return codeList;
}
