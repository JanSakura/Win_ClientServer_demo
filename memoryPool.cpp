#include"memoryPool.h"
#include<iostream>
#include<assert.h>

MemoryAlloc::MemoryAlloc(unsigned _unitCount, unsigned _unitSize):
	unitCount(_unitCount),unitSize(_unitSize),pMemoryAlloc(nullptr),pBlockHeader(nullptr){
	initMemAlloc();
}

MemoryAlloc::~MemoryAlloc(){
	if (pMemoryAlloc) {
		free(pMemoryAlloc);
	}
}

void MemoryAlloc::initMemAlloc(){
	//���ǿ�ָ�룬ֱ�ӱ���
	assert(pMemoryAlloc == nullptr);
	//ʹ����ԭʼ��C�ķ����ڴ棬new�Ѿ��Լ�������
	pMemoryAlloc = (char*)malloc(unitCount * (unitSize + sizeof(MemoryBlock)));
	if (!pMemoryAlloc) {
		std::cout << "Memory initAlloc func fail" << std::endl;
		return;
	}
	pBlockHeader = (MemoryBlock*)pMemoryAlloc;
	for (unsigned i = 0; i < unitCount; ++i) {
		//�ȷ����ڴ�
		MemoryBlock* pMemoryBlock = (MemoryBlock*)(pMemoryAlloc + i * (unitSize + sizeof(MemoryBlock)));
		pMemoryBlock->pAlloc = this;
		//�ٽ�������
		if (i != unitCount - 1) {
			pMemoryBlock->pNext = (MemoryBlock*)(pMemoryAlloc + (i + 1) * (unitSize + sizeof(MemoryBlock)));
		}
		else {
			pMemoryBlock->pNext = nullptr;
		}
		
	}
}

void* MemoryAlloc::allocMem(size_t nSize){
	if (pBlockHeader) {
		MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)malloc(nSize + sizeof(MemoryBlock)));
		pMemoryBlock->pAlloc = nullptr;
		pMemoryBlock->pNext = nullptr;
		return (char*)pMemoryBlock + sizeof(MemoryBlock);
	}
	else {
		char* pRet = (char*)pBlockHeader + sizeof(MemoryBlock);
		pBlockHeader = pBlockHeader->pNext;
		return pRet;
	}
}

void MemoryAlloc::freeMem(void* block){
	MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)block - sizeof(MemoryBlock));
	pMemoryBlock->pNext = pBlockHeader;
	pMemoryBlock = pBlockHeader;
}


//C++11��֮���д��
//instance����̫�󣬷����ջ���
MemoryPool& MemoryPool::getInstance(){
	static MemoryPool instance;
	return instance;
}

void* MemoryPool::allocMem(size_t nSize){
	if (nSize < MAX_MEMORY) {
		unsigned num = 32;
		unsigned i = 6;
		while ((num = num * 2) < nSize) {
			++i;
		}
		return memoryAllocMap[i]->allocMem(nSize);
	}
	else {
		//�Ӹ�MemoryBlock����
		MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)malloc(nSize + sizeof(MemoryBlock)));
		if (!pMemoryBlock) {
			return nullptr;
		}
		else {
			pMemoryBlock->pAlloc = nullptr;
			pMemoryBlock->pNext = nullptr;
			return pMemoryBlock+sizeof(MemoryBlock);
		}
	}
}

void MemoryPool::freeMem(void* block){
	MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)block - sizeof(MemoryBlock));
	if (!pMemoryBlock->pAlloc) {
		//Ϊ��ָ��ֱ���ͷ�
		free(pMemoryBlock);
	}
	else {
		pMemoryBlock->pAlloc->freeMem(block);
	}
}

MemoryPool::MemoryPool():
	memoryAlloc64(64,10),memoryAlloc128(128,10),memoryAlloc256(256,10),memoryAlloc512(512,10),memoryAlloc1024(1024,10) {
	memoryAllocMap.insert(std::pair<unsigned, MemoryAlloc*>(6, &memoryAlloc64));
	memoryAllocMap.insert(std::pair<unsigned, MemoryAlloc*>(7, &memoryAlloc128));
	memoryAllocMap.insert(std::pair<unsigned, MemoryAlloc*>(8, &memoryAlloc256));
	memoryAllocMap.insert(std::pair<unsigned, MemoryAlloc*>(9, &memoryAlloc512));
	memoryAllocMap.insert(std::pair<unsigned, MemoryAlloc*>(10, &memoryAlloc1024));
}
