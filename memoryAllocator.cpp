#include "memoryAllocator.h"
#include"memoryPool.h"
void* operator new(size_t nSize){
	MemoryPool::getInstance().allocMem(nSize);
}

void* operator new[](size_t nSize){
	MemoryPool::getInstance().allocMem(nSize);
}

void operator delete(void* nSize){
	MemoryPool::getInstance().freeMem(nSize);
}

void operator delete[](void* nSize){
	MemoryPool::getInstance().freeMem(nSize);
}
