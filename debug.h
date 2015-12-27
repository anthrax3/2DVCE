#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED
#include <iostream>
#define INFO 0
#define OK 1
#define WARN 2
#define BAD 3
#define FATAL 4
void message(int status, char *msg) {
    switch(status) {
        case INFO:
            std::cout << 0x0F << "INFO: " << msg << std::endl;
            break;
        case OK:
            std::cout << 0x0A << "OK: " << msg << std::endl;
            break;
        case WARN:
            std::cout << 0x0E << "WARN: " << msg << std::endl;
            break;
        case BAD:
            std::cout << 0x04 << "BAD: " << msg << std::endl;
            break;
        case FATAL:
            std::cout << 0x0C << "FATAL: " << msg << std::endl;
            break;
    }
}

#endif // DEBUG_H_INCLUDED
