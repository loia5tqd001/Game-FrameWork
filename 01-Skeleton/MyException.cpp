#include "MyException.h"

MyException::MyException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
{
	std::ostringstream ss;
	ss << "[Exception]: " << msg << "\n";
	ss << "[Line]: " << line << "\n";
	ss << "[Func]: " << func << "\n";
	ss << "[File]: " << file << "\n";
	msgOut = ss.str();
}

void MyException::Throw(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
{
	MyException ex(msg, line, func, file);
	DebugOut(ex.what());
	throw ex;
}