#include "AbsFuncBlock.h"
namespace FuncDre {

	/*
	*	抽象函数
	*/
	AbsFuncBlock::~AbsFuncBlock(){

	}

	int AbsFuncBlock::hashCode() {
		return BASBLOCK;
	}

	int AbsFuncBlock::getTag() {
		return this->tag;
	}

	void AbsFuncBlock::setTag(int tag) {
		this->tag = tag;
	}



	/*
	*	常数函数块
	*/
	ConFuncBlock::~ConFuncBlock() {

	}

	int ConFuncBlock::hasCode() {
		std::string str = TransForm::d2str(num);
		int hash, i;
		for (hash = str.length(), i = 0; i < str.length(); ++i)
			hash = (hash << 4) ^ (hash >> 28) ^ str[i];
		return (hash % 99999989);
	}

	double ConFuncBlock::getNum() {
		return num;
	}

	void ConFuncBlock::setNum(double num) {
		this->num = num;
	}



	/*
	*	运算函数块
	*/
	OperFuncBlock::OperFuncBlock() {
		FuncContainer = new std::list<AbsFuncBlock*>;
	}

	OperFuncBlock::~OperFuncBlock() {
		for (std::list<AbsFuncBlock*>::iterator it = FuncContainer->begin(); it != FuncContainer->end(); it++) {
			delete* it;
		}
		delete FuncContainer;
	}

	int OperFuncBlock::hashCode() {
		int hash;
		std::list<AbsFuncBlock*>::iterator it = FuncContainer->begin();
		for (hash = FuncContainer->size(); it != FuncContainer->end(); it++)
			hash = (hash << 4) ^ (hash >> 28) ^ (*it)->hashCode();
		return (hash % 99999989);
	}

	std::list<AbsFuncBlock*>* OperFuncBlock::getContainer() {
		return this->FuncContainer;
	}

	void OperFuncBlock::addFunc(AbsFuncBlock* absFuncBlock) {
		FuncContainer->push_back(absFuncBlock);
	}



	/*
	*	通用函数块
	*	函数真鸡儿多
	*/

	GnlFuncBlock::GnlFuncBlock() {
		BottomBlock = new OperFuncBlock;
		TopBlock = new OperFuncBlock;
	}

	GnlFuncBlock::~GnlFuncBlock() {
		delete BottomBlock;
		delete TopBlock;
	}

	int GnlFuncBlock::hashCode() {
		int hash1 = BottomBlock->hashCode(),
			hash2 = TopBlock->hashCode();
		return	(hash1 << 4) ^ (hash2 >> 28);
	}

	std::list<AbsFuncBlock*>* GnlFuncBlock::getBottomContainer() {
		return BottomBlock->getContainer();
	}

	void GnlFuncBlock::addBottomFunc(AbsFuncBlock* absFuncBlock) {
		BottomBlock->addFunc(absFuncBlock);
	}

	std::list<AbsFuncBlock*>* GnlFuncBlock::getTopContainer() {
		return TopBlock->getContainer();
	}

	void GnlFuncBlock::addTopFunc(AbsFuncBlock* absFuncBlock) {
		TopBlock->addFunc(absFuncBlock);
	}
}