#pragma once
#include <Windows.h>
#include <exception>
#include <sstream>
#include <string>

// Output to debug window. Using variadic and fold expression (C++17)
template <typename ...Args>
void DebugOut(Args... args)
{
	std::ostringstream ss;
	((ss << args), ...);
	OutputDebugString(ss.str().c_str());
}


// Custom exception class for more information debuging
class MyException : public std::exception
{
private:
	std::string msgOut;

	MyException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file) noexcept
	{
		std::ostringstream ss;
		ss << "[Exception]: " << msg << "\n";
		ss << "[Line]: " << line << "\n";
		ss << "[Func]: " << func << "\n";
		ss << "[File]: " << file << "\n";
		msgOut = ss.str();
	}

public:
	const char* what() const noexcept override { return msgOut.c_str(); }

	#pragma warning(disable:4566) // disable C4566. kind of unicode ascii converting wanring
	static void Throw(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
	{
		MyException ex(msg, line, func, file);
		DebugOut(ex.what());
		throw ex;
	}

	#define ThrowMyException(msg)							\
	MyException::Throw(msg, __LINE__, __func__, __FILE__)
};

