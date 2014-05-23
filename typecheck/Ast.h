#ifndef AST_H
#define AST_H

#include "all.h"
#include "Value.h"
#include "ProgramElem.h"
#include "SymTabEntry.h"

extern int intReg[REG_SIZE];
extern int floatReg[REG_SIZE];

class BlockEntry;
class EventEntry;
class FunctionEntry;
class LabelEntry;
class OpNode;
class PatNode;
class PrimitivePatNode;
class RulezNode;
class SymTabEntry;
class VariableEntry;
class EFSA;
class EFSAlist;
extern int labelNum;

/*****************************************************************************
   Here is the class hierarchy:
                                               ProgramElem
											       |
                                                AstNode
     +--------------------------------------------+----------------+
     |		         |                 |                           | 
 BasePatNode      ExprNode          RuleNode                    StmtNode
     |               |                                             |
     |               |                                             |
     |      +---------+----------+-----------+                     |
     |      |         |          |           |                     |
     |  RefExprNode  OpNode  ValueNode  InvocationNode             |
     |                                                             |
     |                                      +---------------+------+-----+
     |                                      |               |            |
     |                                 ExprStmtNode   CompoundStmtNode IfNode
     |
     |
   +-+------------------+
   |                    |
   |                    |
PrimitivePatNode    PatNode

******************************************************************************/
    
class AstNode: public ProgramElem {
 public:
  enum class NodeType  {
    PAT_NODE,
    EXPR_NODE, 
    REACTION_NODE, 
    STMT_NODE, 
    SEQUENCE_NODE, 
    RULE_NODE
  };

 public: 
  AstNode(NodeType nt, int line=0, int column=0, string file="");
  AstNode(const AstNode&); // copy constructor 
  virtual ~AstNode() {};
  //virtual AstNode* clone() = 0;

  NodeType nodeType() const { return nodeType_;}

  virtual const Type* typeCheck() { return NULL; };
  virtual void typePrint(ostream& os, int indent=0) const {};

  virtual void print(ostream& os, int indent=0) const=0;
  //zdd
  //virtual EFSA* codeGen() {return NULL;};

  virtual void renameRV(string prefix) {}; // new names start with given prefix
  virtual bool operator==(const AstNode&) const { return false; };
  virtual bool operator!=(const AstNode& a) const 
  { return !operator==(a); };
  
 private: 
  NodeType nodeType_;
  const AstNode* operator=(const AstNode& other); /* disable asg */
  EFSA* interCode_;
};

inline ostream& operator<<(ostream& os, const AstNode& an) {
  an.print(os);
  return os;
};

/****************************************************************/
class ExprNode: public AstNode {
 public:
  enum class ExprNodeType   {
    REF_EXPR_NODE, 
    OP_NODE, 
    VALUE_NODE, 
    INV_NODE
   };

 public:
  ExprNode(ExprNodeType et, const Value* val=0, int line=0, int column=0,
		   string file=""); // val is saved, but not copied
  ExprNode(const ExprNode&);
  virtual ~ExprNode() {};
 
  virtual ExprNode* clone() const=0;

  ExprNodeType exprNodeType() const { return exprType_;};
  void exprNodeType(ExprNodeType t) { exprType_ = t; };

  const Value* value() const { return val_; }

  const Type* coercedType() const { return coercedType_; }
  void coercedType(const Type* type) { coercedType_ = type; }

  void print(ostream& os, int indent=0) const=0;

  //zdd
  virtual EFSAlist* codeGen()=0;
  int regNum() {return regNum_;};
  void regNum(int n) {regNum_=n;};
  int regIF() {return regIF_;};
  void regIF(int n) {regIF_=n;};

 private:
  ExprNodeType exprType_;
  const Value *val_; // reference semantics for val_ and coercedType_
  const Type* coercedType_; 
  //zdd
  int regNum_;
  int regIF_;
};

/****************************************************************/
class RefExprNode: public ExprNode {
 public:
  RefExprNode(string ext, const SymTabEntry* ste=NULL, 
	      int line=0, int column=0, string file="");
  RefExprNode(const RefExprNode&);
  ExprNode* clone() const { return new RefExprNode(*this); }

  ~RefExprNode() {};

  string ext() const { return ext_;};
  void ext(string str) { ext_ = str;}; 

  const SymTabEntry* symTabEntry() const { return sym_;};
  void symTabEntry(const SymTabEntry *ste)  { sym_ = ste;};

  void print(ostream& os, int indent=0) const;

  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  //zdd
  EFSAlist* codeGen();
  
 private:
  string ext_;
  const SymTabEntry* sym_;
};

/****************************************************************/

#define MAX_OP_ARITY 2

class OpNode: public ExprNode {
 public:
  enum class OpCode {
    UMINUS, PLUS, MINUS, MULT, DIV, MOD, 
    EQ, NE, GT, LT, GE, LE,
    AND, OR, NOT, 
    BITNOT, BITAND, BITOR, BITXOR, SHL, SHR,
    ASSIGN, PRINT, INVALID
  };
    
  enum class OpPrintType {PREFIX, INFIX, POSTFIX};
  struct OpInfo {
    OpCode code_;
    const char* name_;
    int arity_;
		int needParen_;
    OpPrintType prtType_;
    Type::TypeTag argType_[3]; 
    // operators with > 2 args can be supported
    // only if types of args k through N are identical, for 1 <= k <= 3, 
    // and are given by argType[k-1]
    Type::TypeTag outType_;
		const char *typeConstraints_;
  };

 public:
  static const int VARIABLE = 100;
 public:
  OpNode(OpCode op, ExprNode *l, ExprNode *r=NULL,
	 int line=0, int column=0, string file="");
  OpNode(const OpNode&);
  ExprNode* clone() const { return new OpNode(*this); }
  ~OpNode() {};

  OpCode opCode() const { return opCode_;};
  const ExprNode* arg(unsigned int i) const 
    { return (i < arg_.size())? arg_[i] : NULL; };
  unsigned int arity() const { return arity_; }

  void opCode(OpCode a) { opCode_ = a; };
  ExprNode* arg(unsigned int i) 
    { return (i < arg_.size())? arg_[i] : NULL; };
  vector<ExprNode*>* args() 
    { return &arg_; }

  void print(ostream& os, int indent=0) const;  

  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  //zdd
  EFSAlist* codeGen();
  int tempIntVarAlloc();
  int tempFloatVarAlloc();
  void tempIntVarRelease(int i);
  void tempFloatVarRelease(int i);
  
 private: 
  unsigned int arity_;
  OpCode   opCode_;
  vector<ExprNode*> arg_;
};

/****************************************************************/

class ValueNode: public ExprNode {
 public:
  ValueNode(Value* val=0, int line=0, int column=0, string file="")
    : ExprNode(ExprNode::ExprNodeType::VALUE_NODE, val, line,column,file) {
    if (val != NULL) type((Type*)(val->type()));
  }
  ValueNode(const ValueNode& val): ExprNode(val) {};
  ExprNode* clone() const { return new ValueNode(*this); }
  ~ValueNode() {};

  void print(ostream& os, int indent=0) const;

  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  //zdd
  EFSAlist* codeGen();
 private:
  /* val_ field is already included in ExprNode, so no new data members */
};

/****************************************************************/

class InvocationNode: public ExprNode {
  // Used to represent function invocation
 public:
  InvocationNode(const SymTabEntry *ste, vector<ExprNode*>* param=0, 
		 int line=0, int column=0, string file="");
  InvocationNode(const InvocationNode&);
  ExprNode* clone() const  { return new InvocationNode(*this); }
  ~InvocationNode() {};

  const SymTabEntry* symTabEntry() const { return ste_; };

  const vector<ExprNode*>* params() const { return params_;};
  vector<ExprNode*>* params() { return params_;}
  void params(vector<ExprNode*>* args){ params_ = args;};
  const ExprNode* param(unsigned int i) const 
    { return (params_ != NULL && i < params_->size())? (const ExprNode*)((*params_)[i]) : NULL; };
  ExprNode* param(unsigned int i)
    { return (ExprNode*)((const InvocationNode*)this->param(i));}
  void param(ExprNode* arg, unsigned int i) 
    { if (params_ != NULL && i < params_->size()) (*params_)[i] = arg;};

  void print(ostream& os, int indent=0) const;

  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;

  //zdd
  EFSAlist* codeGen();
 private:
  vector<ExprNode*>* params_;
  const SymTabEntry *ste_; // reference semantics
};

/****************************************************************/
// There are 3 kinds of PatNodes:
//   PrimitivePatNodes are of the form: event|cond
//   AtomicPatNodes consist of PrimitivePatNodes with one or more "||"
//      operators, plus an optional negation symbol
//   PatNodes consist of PatNodes or AtomicPatNodes composed with
//      ".", "||" and "*" operators
// We have a single base class for pattern nodes called BasePatNode. In
// addition, the functionality of Atomic and PatNodes have been
// combined into a single class PatNode.

class BasePatNode: public AstNode {
 public:
  enum class PatNodeKind {PRIMITIVE, EMPTY, NEG, SEQ, OR, STAR, UNDEFINED};

 public:
  BasePatNode(PatNodeKind pk, int ln=0, int col=0, string f=""):
	AstNode(AstNode::NodeType::PAT_NODE, ln, col, f) {
	parent_ = NULL; root_ = NULL; patKind_ = pk;};
  BasePatNode(const BasePatNode& bpn): AstNode(bpn) {
	patKind_ = bpn.patKind_; parent_ = bpn.parent_; root_ = bpn.root_;}
  ~BasePatNode() {};
  //virtual BasepatNode* clone() const { return new BasePatNode(*this);}	

  PatNodeKind kind() const { return patKind_; };
  void kind(PatNodeKind p) {patKind_ = p;}

  const BasePatNode* parent() const { return parent_; } 
  BasePatNode* parent() { return parent_;} 

  virtual bool hasSeqOps() const=0;
  virtual bool hasNeg() const=0;
  virtual bool hasAnyOrOther() const=0;
  virtual bool isNegatable() const {
	return ((!hasSeqOps()) && (!hasNeg())); }

 private:
  PatNodeKind patKind_;
  BasePatNode* parent_;
  BasePatNode* root_;
};

/****************************************************************/

class PrimitivePatNode: public BasePatNode {
 public:
  PrimitivePatNode(EventEntry* ee, vector<VariableEntry*>* params, 
				   ExprNode* c=NULL,
				   int line=0, int column=0, string file="");
  //PrimitivePatNode(const PrimitivePatNode& ppn);
  ~PrimitivePatNode() {};
  //BasePatNode* clone() { return new PrimitivePatNode(*this); }

  const EventEntry* event() const { return ee_; }
  EventEntry* event() { return ee_; }

  const vector<const VariableEntry*>* params() const { 
	return (vector<const VariableEntry*>*)params_; }
  vector<VariableEntry*>* params() { return params_; }

  const ExprNode* cond() const { return cond_; }
  ExprNode* cond() { return cond_; }
  void cond(ExprNode* c) { cond_ = c;}

  ExprNode* condition() { return condition_; }
  const ExprNode* condition() const { return condition_; }

  const list<const OpNode*>& asgs() const { 
	return (list<const OpNode*>&)asgs_; }  
  list<OpNode*>& asgs() { return asgs_; }  

  bool hasSeqOps() const;
  bool hasNeg() const;
  bool hasAnyOrOther() const;

  //-const Type* typeCheck();
  void print(ostream& os, int indent=0) const; 
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
 private:

  EventEntry* ee_;
  vector<VariableEntry*>* params_;
  /* cond_ may contain assignments as well as other expressions */
  /* condition_ contains all expresions in cond_ other than assignments */
  ExprNode* cond_;      
  ExprNode* condition_; 
  list<OpNode*> asgs_;
};

/****************************************************************/
class PatNode: public BasePatNode {
 public: 
  PatNode(int line=0, int column=0, string file="");
  PatNode(PatNodeKind pk, BasePatNode *p1, BasePatNode*p2=NULL, int line=0, int column=0, string file="");
  
  ~PatNode() {};
  //AstNode* clone() 
  //  { return new PatNode(*this); }

  const BasePatNode* pat1() const { return pat1_; }
  BasePatNode* pat1() { return pat1_; }
  const BasePatNode* pat2() const { return pat2_; }
  BasePatNode* pat2() { return pat2_; }

  bool hasNeg() const;
  bool hasSeqOps() const;
  bool hasAnyOrOther() const;

  void print(ostream& os, int indent=0) const; 
  const Type* typeCheck();
  void typePrint(ostream& os, int indent=0) const;
 private: 
  PatNode(const PatNode&);

  BasePatNode *pat1_;
  BasePatNode *pat2_;
};


/****************************************************************/

class StmtNode: public AstNode {
 public:
  enum class StmtNodeKind { ILLEGAL=-1, EXPR, IF, COMPOUND, RETURN, WHILE};
 public: 
  StmtNode(StmtNodeKind skm, int line=0, int column=0, string file=""):
	AstNode(AstNode::NodeType::STMT_NODE, line,column,file) { skind_ = skm; };
  ~StmtNode() {};
  //AstNode* clone() 
  //  { return new StmtNode(*this); }

  StmtNodeKind stmtNodeKind() const { return skind_;}

  void print(ostream& os, int indent) const = 0;

  //zdd
  virtual EFSAlist* codeGen() = 0;

 private:
  StmtNodeKind skind_;
};

/****************************************************************/

class ReturnStmtNode: public StmtNode {
 public:
  ReturnStmtNode(ExprNode *e, FunctionEntry* fe, 
				 int line=0, int column=0, string file=""):
    StmtNode(StmtNode::StmtNodeKind::RETURN,line,column,file) { expr_ = e; fun_ = fe;};
  ~ReturnStmtNode() {};

  void print(ostream& os, int indent) const {
	os << "return "; 
	if(expr_ != NULL) expr_->print(os, indent); else os << "NULL";};
  const Type* typeCheck();
  void typePrint(ostream& os, int indent) const;

  //zdd
  EFSAlist* codeGen();
 private:
  ExprNode* expr_;
  FunctionEntry* fun_;
};

/****************************************************************/

class ExprStmtNode: public StmtNode {
 public:
  ExprStmtNode(ExprNode* e, int line=0, int column=0, string file=""):
    StmtNode(StmtNode::StmtNodeKind::EXPR,line,column,file) { expr_ = e; };
  ~ExprStmtNode() {};
  //AstNode* clone() 
  //  { return new ExprStmtNode(*this); }

  void print(ostream& os, int indent) const { 
	if (expr_ != NULL) { expr_->print(os, indent); }};
  void typePrint(ostream& os, int indent) const {
  if(expr_ != NULL) { expr_->typePrint(os,indent); }};
  const Type* typeCheck();

  //zdd
  EFSAlist* codeGen();
 private:
  ExprNode* expr_;
};

/****************************************************************/

class CompoundStmtNode: public StmtNode{
 public: 
  CompoundStmtNode(list<StmtNode*> *Slist, int ln=0, int col=0, string fl=""):
	StmtNode(StmtNode::StmtNodeKind::COMPOUND, ln,col,fl) { stmts_ = Slist;};
  ~CompoundStmtNode() { };
  //AstNode* clone() 
  //  { return new CompoundStmtNode(*this); }

  const list<StmtNode*>* stmts() const { return stmts_;}

  list<StmtNode*>* stmts() { return stmts_;}
  void add(StmtNode *s) 
    { if(stmts_ != NULL) stmts_->push_back(s); };
  
  void  printWithoutBraces(ostream& os, int indent) const;
  void  print(ostream& os, int indent) const;

  const Type* typeCheck();
  void typePrint(ostream& out, int indent) const;
  void typePrintWithoutBraces(ostream& os, int indent) const;

  //zdd
  EFSAlist* codeGen();

 private:
  CompoundStmtNode(const CompoundStmtNode&);

  list<StmtNode*>   *stmts_;
};

/****************************************************************/

class IfNode: public StmtNode{
 public: 
  
  IfNode(ExprNode* cond, StmtNode* thenStmt, 
		 StmtNode* elseStmt=NULL, int line=0, int column=0, string file="");
  ~IfNode(){};
  //AstNode* clone() 
  //  { return new IfNode(*this); }

  const ExprNode* cond() const {return cond_;}
  const StmtNode* elseStmt() const { return else_;};
  const StmtNode* thenStmt() const  { return then_;};

  ExprNode* cond() {return cond_;}      
  StmtNode* elseStmt() { return else_;};
  StmtNode* thenStmt() { return then_;};

  void print(ostream& os, int indent) const;
  const Type* typeCheck();
  void typePrint(ostream& os, int indent) const;

  //zdd
  EFSAlist* codeGen();
 private: 
  ExprNode *cond_;
  StmtNode *then_, *else_;

  IfNode(const IfNode&);
};

/****************************************************************/

class RuleNode: public AstNode {
 public:
  RuleNode(BlockEntry *re, BasePatNode* pat, StmtNode* reaction, 
	   int line=0, int column=0, string file="");
  ~RuleNode() {};
  //AstNode* clone() 
  //  { return new RuleNode(*this); }

  const BlockEntry* ruleEntry() const { return rste_; };
  BlockEntry* ruleEntry() { return rste_; };

  const BasePatNode* pat() const { return pat_; };
  BasePatNode* pat() { return pat_; };              

  const StmtNode* reaction() const { return reaction_; };   
  StmtNode* reaction() { return reaction_; };   

  void print(ostream& os, int indent=0) const;
  void typePrint(ostream& os, int indent=0) const;
  const Type* typeCheck();

  int regNum() const { return regNum_; };
  void regNum(int n) { regNum_=n; };

  string ruleLabel() const { return ruleLabel_; };
  void ruleLabel(string str) { ruleLabel_=str; };
  string ruleSkipLabel() const { return ruleSkipLabel_; };
  void ruleSkipLabel(string str) { ruleSkipLabel_ = str; };
  
  int regAlloc();

  //zdd
  EFSAlist* codeGen();
 private:
  BlockEntry    *rste_;
  BasePatNode *pat_;
  StmtNode *reaction_;
  int regNum_;
  string ruleLabel_;
  string ruleSkipLabel_;
   
  RuleNode(const RuleNode&);
};


/****************************************************************/

class EFSA {
 public:
  
  enum class OperatorType {
    INT_ARITH,
    FLOAT_ARITH,
    INT_RELATION,
    FLOAT_RELATION,
    PRINT,
    JUMP,
    MOVE,
    INPUT,
    LABEL,
    IN
  };

  enum class OperandName {
    ADD, SUB, DIV, MUL, MOD, NEG, AND, OR, XOR, FADD, FSUB, FDIV, FMUL, FNEG, GT, GE,
    UGT, UGE, EQ, NE, FGT, FGE, FEQ, FNE, LABEL, MOVL, MOVS, MOVI, MOVF, MOVIF, LDI, 
    LDF, STI, STF, JMP, JMPC, JMPI, JMPCI, IN, INF, INI, PRTS, PRTI, PRTF
  };

  virtual void codePrint(ostream& os) = 0;
  
  EFSA(EFSA::OperandName name, OperatorType type) {
    name_ = name;
    operatorType_ = type;
  };

  OperandName name() const { return name_; };
  void name(OperandName str) { name_=str; };

  OperatorType operatorType() const { return operatorType_;};
  void operatorType(OperatorType t) { operatorType_ = t; };

  static int intRegAlloc() {
      for (int i=0; i<AVAIL_REG_SIZE; i++){
          if (intReg[i]==0){
              intReg[i] = 1;
              return i;
          }
      }
      return REG_FAILED;
  }

  static int floatRegAlloc() {
      for (int i=0; i<AVAIL_REG_SIZE; i++){
          if (floatReg[i]==0){
              floatReg[i] = 1;
              return i;
          }
      }
      return REG_FAILED;
  }

  static void intRegFree(int i) {
      intReg[i] = 0;
  }

  static void floatRegFree(int i) {
      floatReg[i] = 0;
  }

 private:
  OperandName name_;
  OperatorType operatorType_;
};


/****************************************************************/
class EFSAlist{
 public:

   void addCodeList(EFSAlist* codes);
   void addCode(EFSA* code);
   EFSA* getLastCode();
   void removeLastCode();
   void codePrint(ostream& os);
   vector<EFSA*> getCodeList(){return codeList;};
   void dealDuplicateLabel();
   vector<EFSA*>* getCodeListPtr(){ return &codeList; };
   void setCodeList(vector<EFSA*> list){codeList=list;};

 private:
   vector<EFSA*> codeList;
};


/****************************************************************/

class IntArithCode: public EFSA {
 public:

  enum class OperandNum {
    UNARY,
    BINARY
  };

  IntArithCode(IntArithCode::OperandNum operandNum, EFSA::OperandName name, string dest, string leftOperand, string rightOperand):
    EFSA(name, EFSA::OperatorType::INT_ARITH) { operandNum_ = operandNum; dest_ = dest; leftOperand_ = leftOperand; rightOperand_ = rightOperand;};

  OperandNum operandNum() const { return operandNum_;};
  void operandNum(OperandNum n) { operandNum_ = n; };

  string leftOperand(){return leftOperand_;};
  void leftOperand(string n){leftOperand_ = n;};

  string rightOperand(){return rightOperand_;};
  void rightOperand(string n){rightOperand_ = n;};

  string dest(){return dest_;};
  void dest(string n){dest_ = n;};

  void codePrint(ostream& os);

 private:
  OperandNum operandNum_;
  string leftOperand_;
  string rightOperand_;
  string dest_;
};


/****************************************************************/

class FloatArithCode: public EFSA {
 public:

  enum class OperandNum {
    UNARY,
    BINARY
  };

  FloatArithCode(FloatArithCode::OperandNum operandNum, EFSA::OperandName name, string dest, string leftOperand, string rightOperand):
    EFSA(name, EFSA::OperatorType::FLOAT_ARITH) { operandNum_ = operandNum; dest_ = dest; leftOperand_ = leftOperand; rightOperand_ = rightOperand;};

  OperandNum operandNum() const { return operandNum_;};
  void operandNum(OperandNum n) { operandNum_ = n; };

  string leftOperand(){return leftOperand_;};
  void leftOperand(string n){leftOperand_ = n;};

  string rightOperand(){return rightOperand_;};
  void rightOperand(string n){rightOperand_ = n;};

  string dest(){return dest_;};
  void dest(string n){dest_ = n;};

  void codePrint(ostream& os);

 private:
  OperandNum operandNum_;
  string leftOperand_;
  string rightOperand_;
  string dest_;
};


/****************************************************************/

class IntRelationCode: public EFSA {
 public:

  IntRelationCode(EFSA::OperandName name, string left, string right):
    EFSA(name, EFSA::OperatorType::INT_RELATION) {left_=left; right_=right;};

  string left(){return left_;};
  void left(string n){left_ = n;};

  string right(){return right_;};
  void right(string n){right_ = n;};

  void codePrint(ostream& os);

 private:
  string left_;
  string right_;
};


/****************************************************************/

class FloatRelationCode: public EFSA {
 public:

  FloatRelationCode(EFSA::OperandName name, string left, string right):
    EFSA(name, EFSA::OperatorType::FLOAT_RELATION) {left_=left; right_=right;};

  string left(){return left_;};
  void left(string n){left_ = n;};

  string right(){return right_;};
  void right(string n){right_ = n;};


  void codePrint(ostream& os);

 private:
  string left_;
  string right_;
};


/****************************************************************/

class LabelCode: public EFSA {
 public:
  LabelCode(string name, int target=0):
    EFSA(EFSA::OperandName::LABEL, EFSA::OperatorType::LABEL){name_=name; target_=target;};

  void codePrint(ostream& os);
  
  string name(){return name_;};
  void name(string n){name_ = n;};

  int target(){return target_;};
  void target(int n){target_ = n;};

 private:
  string name_;
  int target_;	//1: target label	0: not target label, used in JMP/JMPC
};

/****************************************************************/

class MoveCode: public EFSA {
 public:
  MoveCode(EFSA::OperandName name, string from, string dest):
    EFSA(name, EFSA::OperatorType::MOVE) { from_ = from; dest_ = dest; };

  string from(){return from_;};
  void from(string n){from_ = n;};

  string dest(){return dest_;};
  void dest(string n){dest_ = n;};

  void codePrint(ostream& os);

 private:
  string from_;
  string dest_;
};


/****************************************************************/

class JumpCode: public EFSA {
 public:
  JumpCode(EFSA::OperandName name, EFSA* cond, LabelCode* label):
    EFSA(name, EFSA::OperatorType::JUMP) { cond_ = cond; label_ = label; };

  EFSA* cond(){return cond_;};
  void cond(EFSA* n){cond_ = n;};

  LabelCode* label(){return label_;};
  void label(LabelCode* n){label_ = n;};

  void codePrint(ostream& os);

 private:
  EFSA* cond_;
  LabelCode* label_;
};

/****************************************************************/
//Yansong
class InCode: public EFSA {
public:
	InCode(EFSA::OperandName name, string strRegName) : EFSA(name, EFSA::OperatorType::IN) { strReg_ = strRegName; };
	void codePrint(ostream& os);
private:
	string strReg_;
};

/****************************************************************/

//Yansong
class PrintCode: public EFSA {
public:
	PrintCode(EFSA::OperandName name, string str, string strReg = "") : EFSA(name, EFSA::OperatorType::PRINT), str_(str), reg_(strReg) {};
	void codePrint(ostream &os);
private:
	string str_;
	string reg_;
    string parseEscape_(string str);
};

/****************************************************************/

class WhileNode: public StmtNode
{
  public:

    WhileNode(ExprNode* cond, StmtNode* WhileStmt, int line=0, int column=0, string file="");
    ~WhileNode(){};

    ExprNode* cond() {return cond_;}
    StmtNode* whileStmt() { return stmt_;};

    void print(ostream& os, int indent) const;
    EFSAlist* codeGen();

  private:
    ExprNode *cond_;
    StmtNode *stmt_;

    WhileNode(const WhileNode&);
};
#endif
