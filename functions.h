#ifndef FUNC_
#define FUNC_

struct FuncInfo
{
	unsigned char sym_; // ���������� ��� �������.
	const char* name_; // ��� �������.
};

extern const FuncInfo FTable[];

unsigned char find (const char* str);

#endif // FUNC_