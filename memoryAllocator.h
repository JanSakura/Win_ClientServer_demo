#ifndef _MEMORY_ALLOCATOR_
#define _MEMORY_ALLOCATOT_

void* operator new(size_t nSize);
void* operator new[](size_t nSize);

void operator delete(void* nSize);
void operator delete[](void* nSize);

#endif // !_MEMORY_ALLOCATOR_
