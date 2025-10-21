#pragma once
#include <string>

std::string GetResourceDirectory()
{

#ifdef NDEBUG // Release Build
	return "assets/";
#else
	return "D:/Dev/Rain/RainGame/assets/";
#endif

}
