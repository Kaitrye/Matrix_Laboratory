#ifndef FUNC_
#define FUNC_

struct FuncInfo
{
	unsigned char sym_; // уникальный код функции.
	const char* name_; // имя функции.
};

extern const FuncInfo FTable[];

unsigned char find (const char* str);

#endif // FUNC_