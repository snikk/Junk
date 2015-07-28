#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

template <T>
class MemoryPool {
public:
    void init();
    void init(int capacity);

private:
    T* head;
    T* end;
    T*
};

#endif
