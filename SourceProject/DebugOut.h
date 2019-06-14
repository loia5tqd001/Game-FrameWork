#pragma once

struct Debug
{
	// Use variadic template and fold expression
	template <typename ...Args>
	static void Out(Args... args)
	{
		std::ostringstream ss;
		((ss << args << " "), ...),	ss << "\n";
		OutputDebugString(ss.str().c_str());
	}

	static void out(char *fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		char dbg_out[4096];
		vsprintf_s(dbg_out, fmt, argp);
		va_end(argp);
		OutputDebugString(dbg_out);
	}
};
