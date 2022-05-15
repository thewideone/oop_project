#include "debug.hpp"

#include <fstream>

#ifdef DEBUG
std::ostream &dout = std::cout;
#else
// std::ofstream dev_null("/dev/null");
std::ofstream dev_null("nul");
std::ostream &dout = dev_null;
#endif