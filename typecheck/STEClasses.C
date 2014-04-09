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
