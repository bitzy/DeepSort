#include "errmsg.h"
#include <iostream>

errMsg* errMsg::instance = NULL;
errMsg *errMsg::getInstance()
{
    if(instance == NULL) instance = new errMsg();
    return instance;
}

errMsg::errMsg()
{
}

void errMsg::out(
        std::string file,
        std::string func,
        std::string msg, bool pause)
{
    std::cout << "IN file<" << file << "> "
              << func << " : " << msg << std::endl;
    if(pause) exit(0);
}
