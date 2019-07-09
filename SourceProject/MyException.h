#pragma once

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
		Debug::Out(what());
	}

public:
	const char* what() const noexcept override { return msgOut.c_str(); }

	template <typename ...Args>
	static void Throw(UINT line, LPCSTR func, LPCSTR file, Args... msgs)
	{
		std::ostringstream ss;
		((ss << msgs << " "), ...);
		throw MyException(ss.str().c_str(), line, func, file);
	}

	#define ThrowMyException(...)      MyException::Throw(__LINE__, __func__, __FILE__, __VA_ARGS__)
	#define AssertUnreachable          assert( false )
	#define AssertMessage(expr, msg)   if ( !(expr) ) ThrowMyException(msg)
};
