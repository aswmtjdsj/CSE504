#include "ParserUtil.h"

static int variableCount = 333;     
EventEntry *any, *other;
extern int yylineno;
int yycolumnno;

static void 
errPrint(ErrorST code, const string& sym) {
  switch (code) {
  case DUPLICATE_SYM:
	errMsgLn("Redefinition of name " + sym);
	break;
  case SYM_NOT_PRESENT:
	errMsgLn("Undeclared symbol `" + sym + "'");
	break;
  case INVALID_SCOPE:
	errMsgLn("Definition of `" + sym +"' is invalid in " + 
		   stm.currentScope()->name());
	break;
  default:
	break;
  }
}

ErrorST insertSymbolErrCheck(SymTabEntry* se) {
  ErrorST err = stm.insert(se);
  errPrint(err, se->name());
  return err;
}

void enterScopeErrCheck(SymTabEntry* se) {
  errPrint(stm.enterScope(se), se->name());
}

string newName(const string& type) {
  string s("__");
  s +=type+"__"+ itoa(variableCount++);
  return s;
}

string itoa(int i) {
  char a[20];
  sprintf(a, "%d", i);
  return string(a);
}

// @return string register string in format RXXX for int reg, FXXX for float reg
// Yansong
string getReg(string strOldReg) {
	if (strOldReg.length() == 4) return strOldReg;
	string strNewReg = strOldReg.substr(0, 1);
	for (auto i = 0; i < 4 - strOldReg.length(); i++) {
		strNewReg += "0";
	}
	strNewReg += strOldReg.substr(1);
	return strNewReg;
}

// @return string register string in format RXXX for int reg, FXXX for float reg
// @param int iType, 0 for int, 1 for float
// Yansong
string getReg(int iRegNumber, int iType) {
	string strRegName = numToString(iRegNumber);
	for (auto i = 0; i < 3 - strRegName.length(); i++) {
		strRegName = "0" + strRegName;
	}

	switch (iType) {
	case 0:
		strRegName = "R" + strRegName;
		break;
	case 1:
		strRegName = "F" + strRegName;
		break;
	}
	return strRegName;
}

string numToString(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

