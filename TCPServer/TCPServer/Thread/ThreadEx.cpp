#include "ThreadEx.h"

ThreadEx::ThreadEx(const _beginthreadex_proc_type threadFunction) : _function(threadFunction)
{
}

void ThreadEx::Run(void* args) const
{
    _beginthreadex(nullptr, 0, _function, args, 0, nullptr);
}
