#ifndef LOG_H_
#define LOG_H_

#include <iostream>

#ifndef RELEASE

#include <cstring>

#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG(x)                                                                 \
    std::cout << __FILENAME__ << ":" << __LINE__ << " " << x << std::endl;

#define ERROR(x)                                                               \
    std::cerr << __FILENAME__ << ":" << __LINE__ << " " << x << std::endl;

#define FATAL(x)                                                               \
    std::cerr << __FILENAME__ << ":" << __LINE__ << " " << x << std::endl;     \
    exit(1);

#else // RELEASE
#define LOG(x)
#define ERROR(x)

#define FATAL(x)                                                               \
    std::cerr << x << std::endl;                                               \
    exit(1);
#endif // RELEASE

#endif // LOG_H_
