#pragma once

// DLLs
#ifdef GRIDCTRL_EXPORTS  
#define GRIDCTRL_API __declspec(dllexport)   
#else  
#define GRIDCTRL_API __declspec(dllimport)   
#endif

// DLLs
#ifdef MFC_UTILITIES_EXPORTS  
#define MFC_UTILITIES_API __declspec(dllexport)   
#else  
#define MFC_UTILITIES_API __declspec(dllimport)   
#endif
