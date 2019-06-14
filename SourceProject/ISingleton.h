#pragma once

class ISingleton
{
protected:
	ISingleton(void* delDefCtor) { assert(delDefCtor == NULL); }
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
};
