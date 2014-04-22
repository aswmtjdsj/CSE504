#include "STEClasses.h"
#include "Value.h"
#include "ParserUtil.h"

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
const Type* GlobalEntry::typeCheck()
{
	if (symTab() != NULL)
	{
		//SymTab::iterator iter;
		for (SymTab::iterator iter = symTab()->begin(); iter != symTab()->end(); ++iter)
		{
			if ((*iter)->name() != "any") cout << "this is an checked item!" << endl;
		}
	}
	return NULL;
}

void GlobalEntry::typePrint(ostream& out, int indent) const
{
	if (symTab() != NULL)
	{
		//for (SymTab::iterator iter = symTab()->begin(); iter != symTab()->end(); ++iter)
		//{
		//	if ((*iter)->name() != "any") (*iter)->typePrint(out, indent);
		//}
	}
}

void EventEntry::print(ostream& out, int indent) const
{
	out << "event " << name() << "(";
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

const Type* EventEntry::typeCheck()
{
	return NULL;
}


void EventEntry::typePrint(ostream&, int indent) const
{
	;
}

void BlockEntry::print(ostream& out, int indent) const
{

}

const Type* BlockEntry::typeCheck()
{
	return NULL;
}

void BlockEntry::typePrint(ostream&, int indent) const
{
	;
}

void ClassEntry::print(ostream& out, int indent) const
{
	out << "class " << name() << ";";
	out << endl;

}

const Type* ClassEntry::typeCheck()
{
	return NULL;
}

void ClassEntry::typePrint(ostream&, int indent) const
{
	;
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

void FunctionEntry::typePrint(ostream&, int indent) const
{
	;
}

const Type* FunctionEntry::typeCheck()
{
	return NULL;
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

const Type* VariableEntry::typeCheck()
{
	const Type *te=NULL;
    if (initVal()) {
		te = initVal()->typeCheck();
	}
	//const Type* ty = initVal()->typeCheck();
	return NULL;
}

void VariableEntry::typePrint(ostream&, int indent) const
{
	;
}