#ifndef LOG_H_
#define LOG_H_

#ifndef RELEASE
#include <iostream>
#define LOG(x) std::cout << x << std::endl;
#define ERROR(x) std::cerr << x << std::endl;
#else
#define LOG(x)
#define ERROR(x)
#endif

#endif // LOG_H_
