#include "CLogger.h"

int main()
{
    CLogger::Instance().SetLogFilePath("D:\\test.log");   
    std::string sz;   
    while (1)
    {        
        std::getline(std::cin, sz);
        CLogger::Instance() << sz;
    }
    getchar();
    return 0;
}