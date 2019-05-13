#pragma once

class ISingleton
{
protected:
	ISingleton(int dumpVarToDelDefCtor) noexcept {}
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
};
