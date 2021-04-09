#include"BasFuncBlock.h"
namespace BasFuncBlock {
	using namespace BasFunc;
	/**************************************************************************/
	void AbsFuncBlock::setTag(int t) {
		this->tag = t;
	}


	void AbsFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
		afb[0] = afb0;
		afb[1] = afb1;
	}


	int AbsFuncBlock::getTag(){
		return tag;
	}


	bool AbsFuncBlock::isUnit() {
		switch (tag)
		{
		case ADD: case MULT: case MINU:case DIV: {
			return true;
			break;
		}
		default:return false;
			break;
		}
		return false;
	}


	/**************************************************************************/
	void AddFuncBlock::dt() {
		afb[0]->dt();
		afb[1]->dt();
	}


	std::string AddFuncBlock::rtStr() {
		std::string afb0 = afb[0]->rtStr();
		std::string afb1 = afb[1]->rtStr();
		//判断纯幂函数串是否为0。
		if (afb0.empty() && afb1.empty()) {
			return "";
		}
		else if (afb0.empty()) {
			return afb1;
		}
		else if (afb1.empty()) {
			return afb0;
		}

		if (tag == ADD) {
			afb0 = afb0 + "+";
		}
		else {
			afb0 = afb0 + "-";
		}
		afb0 = afb0 + afb1;
		return afb0;
	}


	AbsFuncBlock* AddFuncBlock::copy() {
		AbsFuncBlock* blockUnit1, * blockUnit2, * newAfb;
		newAfb = new AddFuncBlock;
		blockUnit1 = afb[0]->copy();
		blockUnit2 = afb[1]->copy();
		newAfb->load(blockUnit1, blockUnit2);
		return newAfb;
	}


	/**************************************************************************/
	void MultFuncBlock::dt() {
		AbsFuncBlock* mulUnit1, * mulUnit2, * t1, * t2;
		mulUnit1 = new MultFuncBlock;
		mulUnit2 = new MultFuncBlock;
		t1 = afb[0]->copy();
		t2 = afb[1]->copy();
		//乘法法则
		mulUnit1->load(t1, afb[1]);
		mulUnit1->setTag(MULT);
		mulUnit2->load(afb[0], t2);
		mulUnit2->setTag(MULT);
	}

	//TODO
	std::string MultFuncBlock::rtStr() {
		return "";
	}


	AbsFuncBlock* MultFuncBlock::copy() {
		AbsFuncBlock* blockUnit1, * blockUnit2, * newAfb;
		newAfb = new MultFuncBlock;
		blockUnit1 = afb[0]->copy();
		blockUnit2 = afb[1]->copy();
		newAfb->load(blockUnit1, blockUnit2);
		return newAfb;
	}


	/**************************************************************************/
	void UnitFuncBlock::dt() {
		abf->dt();
	}


	std::string UnitFuncBlock::rtStr() {
		if (tag == PWR) {
			if (abf->isZero()) {
				return "";
			}
		}
		return abf->rtStr();
	}
	


	void UnitFuncBlock::load(std::string s) {
		//单元块load需要switch
		//TODO
		if (s.find("arc") != s.npos) {

		}
		else if (s.find("ln") != s.npos) {

		}
		else if (s.find("s") != s.npos && s.find("tan") != s.npos) {

		}
		else if (s.find("^x") != s.npos) {

		}
		else {
			abf = new BasPwrFunc;
			tag = PWR;
		}
		abf->load(s);
	}


	AbsFuncBlock* UnitFuncBlock::copy() {
		AbsBasFunc* newAbf;
		UnitFuncBlock* newAfb = new UnitFuncBlock;
		newAbf = abf->copy();
		newAfb->load(newAbf->rtStr());
		return newAfb;
	}


	/**************************************************************************/
	void  NoneFuncBlock::dt() {}


	std::string NoneFuncBlock::rtStr() { return ""; }


	void NoneFuncBlock::load(std::string) {}


	AbsFuncBlock* NoneFuncBlock::copy() { return NULL; }
}