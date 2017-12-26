#ifndef ERRMSG_H
#define ERRMSG_H
#include <stddef.h>
#include <string>

class errMsg
{    
public:
    static errMsg* getInstance();
    void out(std::string file,
                std::string func,
                std::string msd,
                bool pause = true);
private:
    errMsg();
    errMsg(const errMsg&);
    errMsg& operator=(const errMsg&);

    static errMsg* instance;    
};

#endif // ERRMSG_H
