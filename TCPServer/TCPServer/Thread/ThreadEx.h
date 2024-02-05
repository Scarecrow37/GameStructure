#pragma once
#include <process.h>

class ThreadEx
{
public:
    ThreadEx(_beginthreadex_proc_type threadFunction);

    void Run(void* args) const;
private:
    _beginthreadex_proc_type _function;
};
