#ifndef _MEMORY_POOL_
#define _MEMORY_POOL
#include<map>

constexpr unsigned MAX_MEMORY = 1024;

//本质是链表结构

class MemoryBlock {
public:
	//指向下一块内存的指针
	MemoryBlock* pNext=nullptr;
	MemoryAlloc* pAlloc=nullptr;
};

class MemoryAlloc {
public:
	MemoryAlloc(unsigned _unitCount, unsigned _unitSize);
	~MemoryAlloc();
	void initMemAlloc();
	//分配内存
	void* allocMem(size_t nSize);
	void freeMem(void* block);
private:
	//申请Block
	char* pMemoryAlloc;
	//Block的Header
	MemoryBlock* pBlockHeader;
	//Block单元数量
	unsigned unitCount;
	//除去Block的大小
	unsigned unitSize;
};

//单例模式
class MemoryPool {
public:
	static MemoryPool& getInstance ();
	void* allocMem(size_t nSize);
	void freeMem(void* block);
private:
	MemoryPool();
	MemoryAlloc memoryAlloc64;
	MemoryAlloc memoryAlloc128;
	MemoryAlloc memoryAlloc256;
	MemoryAlloc memoryAlloc512;
	MemoryAlloc memoryAlloc1024;
	std::map<unsigned, MemoryAlloc*> memoryAllocMap;

	MemoryPool(const MemoryPool& mempool) = delete;
	MemoryPool& operator=(const MemoryPool& mempool) = delete;
};

#endif // !_MEMORY_POOL_
