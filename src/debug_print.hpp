#ifndef _DEBUG_PRINT_HPP_
#define _DEBUG_PRINT_HPP_

#include <iostream>

#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#endif /* _DEBUG_PRINT_HPP_ */