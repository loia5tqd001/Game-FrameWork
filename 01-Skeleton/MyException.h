#pragma once
#include <exception>

// Custom exception class for more information debuging
class MyException : public std::exception
{
private:
	std::string msgOut;

	MyException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
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

	#pragma warning(disable:4566) // unicode - ascii converting wanring
	static void Throw(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
	{
		MyException ex(msg, line, func, file);
		Debug::Out(ex.what());
		throw ex;
	}

	#define ThrowMyException(msg) MyException::Throw(msg, __LINE__, __func__, __FILE__)
};

