#ifndef NODES_
#define NODES_

#include <iostream>
#include <string>
#include "AVLTree.h"
#include "matrix.h"

class VarValue
{
	std::string name_; // имя переменной.
	Matrix value_; // значение переменной.

public:
	VarValue (const std::string& str) : name_(str), value_ () {}
	void set (const Matrix& A)
	{
		value_ = A;
	}
	Matrix get ()
	{
		return value_;
	}

	bool operator<(const VarValue& other) const
	{
		return name_ < other.name_;
	}
	bool operator==(const VarValue& other) const
	{
		return name_ == other.name_;
	}
};

//---------------------------------------------------------

namespace global
{
	extern AVLTree<VarValue> Workspace;
}

//---------------------------------------------------------

class FormNode
{
public:
	virtual Matrix calc() const = 0;
	virtual const std::string& name() const = 0;
	virtual ~FormNode() {}
};

//---------------------------------------------------------

class NumNode : public FormNode
{
	const std::string name_;
	const Matrix value_; // значение константы.

public:
	NumNode (const Matrix& num) : name_("ans"), value_ (num) {}
	const std::string& name () const
	{
		return name_;
	}
	Matrix calc () const
	{
		return value_;
	}
};

//---------------------------------------------------------

class VarNode : public FormNode
{
	std::string name_; // имя переменной.

public:
	VarNode (const std::string& str) : name_(str)
	{
		auto pos = global::Workspace.find (VarValue (name_));

		if (pos == global::Workspace.end ())
		{
			global::Workspace.insert(VarValue (name_));
		}
	}
	const std::string& name () const
	{
		return name_;
	}
	Matrix calc () const
	{
		auto pos = global::Workspace.find(VarValue(name_));
		return (*pos).get();
	}
};

#endif // NODES_