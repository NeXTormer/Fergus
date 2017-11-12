#pragma once


#ifdef FERGUS_DEBUG
#define GLCall(x)	fgClearError();\
					x;\
					fgLogError(#x, __FILE__, __LINE__)
#else
#define GLCall(x)	x
#endif