#pragma once

#include <infos.h>

class mutex
{
public:
    mutex() : lock_(0) {}

    void lock()
    {
        //
        syscall(Syscall::SYS_FUTEX_WAIT, (unsigned long)&lock_);
    }

    void unlock() {}

private:
    uint32_t lock_;
};

template <class T>
class unique_lock
{
public:
    unique_lock(T &m)
    {
        m.lock();
    }

    ~unique_lock()
    {
        m.unlock();
    }
};
