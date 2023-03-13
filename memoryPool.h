#ifndef _MEMORY_POOL_
#define _MEMORY_POOL
#include<map>

constexpr unsigned MAX_MEMORY = 1024;

//����������ṹ

class MemoryBlock {
public:
	//ָ����һ���ڴ��ָ��
	MemoryBlock* pNext=nullptr;
	MemoryAlloc* pAlloc=nullptr;
};

class MemoryAlloc {
public:
	MemoryAlloc(unsigned _unitCount, unsigned _unitSize);
	~MemoryAlloc();
	void initMemAlloc();
	//�����ڴ�
	void* allocMem(size_t nSize);
	void freeMem(void* block);
private:
	//����Block
	char* pMemoryAlloc;
	//Block��Header
	MemoryBlock* pBlockHeader;
	//Block��Ԫ����
	unsigned unitCount;
	//��ȥBlock�Ĵ�С
	unsigned unitSize;
};

//����ģʽ
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
