#include "AbsFuncBlock.h"
namespace FuncDre {

	/*
	*	抽象函数
	*/
	AbsFuncBlock::~AbsFuncBlock(){

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