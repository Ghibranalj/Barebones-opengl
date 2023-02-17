#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#ifndef RELEASE
#define LOG(x) std::cout << x << std::endl;
#define ERROR(x) std::cerr << x << std::endl;
#else
#define LOG(x)
#define ERROR(x)
#endif


#define FATAL(x) {std::cerr << x << std::endl; exit(1);}

#endif // LOG_H_
