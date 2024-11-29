#include <cstring>
#include "functions.h"

const FuncInfo FTable[] = {
	{128, "zeros"},
	{129, "ones"},
	{130, "eye"},
	{131, "linspace"},
	{132, "vertcat"},
	{133, "horzcat"},
	{134, "transpose"},
	{135, "det"},
	{136, "inv"},
	{137, "sum"},
	{138, "prod"},
	{139, "min"},
	{140, "max"},
	{141, "disp"} 
};

unsigned char find (const char* str)
{
	for (int i = 0; i < 14; ++i)
	{
		if (strcmp (FTable[i].name_, str) == 0)
			return FTable[i].sym_;
	}

	return '\0';
}