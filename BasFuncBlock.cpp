#include"BasFuncBlock.h"
#include<math.h>
namespace BasFuncBlock {
	using namespace BasFunc;
	/**************************************************************************/
	
	void AbsFuncBlock::setTag(int t) {
		this->tag = t;
	}


	int AbsFuncBlock::getTag(){
		return tag;
	}


	bool AbsFuncBlock::isUnit() {
		switch (tag)
		{
		case ADD: case MULT: case MINU:case DIV: {
			return false;
			break;
		}
		default:return true;
			break;
		}
		return true;
	}


	bool AbsFuncBlock::isNorm() {
		return isNor;
	}

	bool AbsFuncBlock::isZero() {
		return isZer;
	}


	bool AbsFuncBlock::isOne() {
		return isOn;
	}


	bool AbsFuncBlock::isMult() {
		return isMul;
	}

	double AbsFuncBlock::getLparam() {
		return this->lparam;
	}
	
	void AbsFuncBlock::setLparam(double s) {
		this->lparam = s;
	}

	AbsFuncBlock* AbsFuncBlock::trans(AbsFuncBlock* mfb) {
		int tag = mfb->getTag();
		if (mfb->isNorm() || mfb->isOne()) {
			return static_cast<UnitFuncBlock*>(static_cast<AbsFuncBlock*>(mfb));
		}
		else if (mfb->isMult() && tag == ADD) {
			return static_cast<AddFuncBlock*>(static_cast<AbsFuncBlock*>(mfb));
		}
		else {
			return mfb;
		}
	}

	bool AbsFuncBlock::isExist(AbsFuncBlock* afb) {
		if (afb == NULL) {
			return false;
		}
		if (afb->isZero()) {
			delete afb;
			afb = NULL;
			return false;
		}
		return true;
	}


	/**************************************************************************/

	AddFuncBlock::AddFuncBlock() {
		lparam = 1.0;
	}


	AddFuncBlock::~AddFuncBlock() {
		delete afb[0];
		delete afb[1];
	}


	void AddFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
		afb[0] = afb0;
		afb[1] = afb1;
	}


	void AddFuncBlock::dt() {

		if (isNor) {
			isZer = true;
			return;
		}

		int tag0, tag1;
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);

		if (!e0 && !e1) {
			isZer = true;
			return;
		}
		if (e1) {
			afb[1]->dt();
			AbsFuncBlock* t = trans(afb[1]);
			afb[1] = t;
		}
		if (e0) {
			afb[0]->dt();
			AbsFuncBlock* t = trans(afb[0]);
			afb[0] = t;
		}
		//求完导之后清除0项
		isExist(afb[0]), isExist(afb[1]);
		if (afb[0]->isNorm() && afb[1]->isNorm()) {
			lparam = afb[0]->getLparam() + afb[1]->getLparam();
			delete afb[0];
			delete afb[1];
			afb[0] = NULL, afb[1] = NULL;
			isNor = true;
		}
	}


	std::string AddFuncBlock::rtStr() {
		//判断纯幂函数串是否为0。
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		//虽然不太可能出现，只会出现在根部
		if (!e0 && !e1) {
			isZer = true;
			return "";
		}
		if (!e1) {
			return afb[0]->rtStr();
		}
		if (!e0) {
			return afb[1]->rtStr();
		}
		std::string afb0 = afb[0]->rtStr(), afb1 = afb[1]->rtStr();
		
		//加减函数块不用考虑常数。
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
		AbsFuncBlock* blockUnit0 = NULL, * blockUnit1 = NULL, * newAfb = NULL;
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		//这种情况也不太可能出现
		if (!e0 && !e1) {
			return NULL;
		}
		if (e0) {
			blockUnit0 = afb[0]->copy();
		}
		if (e1) {
			blockUnit1 = afb[1]->copy();
		}
		newAfb = new AddFuncBlock;
		
		newAfb->load(blockUnit1, blockUnit1);
		newAfb->setTag(tag);
		newAfb->setLparam(lparam);

		return newAfb;
	}



	/**************************************************************************/

	MultFuncBlock::MultFuncBlock() {
		isMul = true;
		lparam = 1.0;
	}


	MultFuncBlock::~MultFuncBlock(){
		delete afb[0];
		delete afb[1];
	}


	void MultFuncBlock::dt() {
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]), flag = false;
		if (!e0 || !e1) {
			isZer = true;
			return;
		}

		AbsFuncBlock* t0 = NULL, *t1 = NULL, *t;
		AbsFuncBlock* subBlock0, *subBlock1, *afb0 = afb[0], *afb1 = afb[1];
		//乘法比较简单，两个都不为0；
		t0 = afb0->copy();
		t1 = afb1->copy();
		t0->dt();
		t = trans(t0);
		t0 = t;
		t1->dt();
		t = trans(t1);
		t1 = t;
		//如果求完导为空
		e0 = isExist(t0);
		e1 = isExist(t1);

		if (!e0 && !e1) {
			isZer = 0;
		}

		if (!e1) {
			afb[0] = t0;
			afb[1] = afb1;
			return;
		}
		if (!e0) {
			afb[0] = afb[0];
			afb[1] = t1;
			return;
		}

		//因为新元一定是完整乘法式，因此不需要trans
		subBlock0 = new MultFuncBlock;
		subBlock0->load(t0, afb1);
		subBlock1 = new MultFuncBlock;
		subBlock1->load(afb0, t1);
		tag = ADD;
		afb[0] = subBlock0;
		afb[1] = subBlock1;

		//如果两项都为常数，那么变成常数。
		if (afb[0]->isNorm() && afb[1]->isNorm()) {
			lparam = afb[0]->getLparam() * afb[1]->getLparam();
			delete afb[0];
			delete afb[1];
			afb[0] = NULL, afb[1] = NULL;
			isNor = true;
 		}
	}

	//TODO 未实现常数归并
	std::string MultFuncBlock::rtStr() {
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		if (!e0 || !e1) {
			isZer = true;
			return "";
		}
		//返回字符不修改函数内容
		std::string afb1 = afb[0]->rtStr();
		std::string afb2 = afb[1]->rtStr();
 		int tag1 = afb[0]->getTag(),
			tag2 = afb[1]->getTag();
	

		std::string rt;
		if (tag1 / 10 <= 1) {
			rt = "(" + afb1;
			rt = rt + ")";
		}
		else {
			rt = afb1;
		}
		
		rt = rt + "*";

		if (tag2 / 10 <= 1) {
			rt = rt + "(";
			rt = rt + afb2;
			rt = rt + ")";
		}
		else {
			rt = rt+ afb2;
		}

		return rt;
	}


	void MultFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
		afb[0] = afb0;
		afb[1] = afb1;
		//TODO归并参数
	}


	AbsFuncBlock* MultFuncBlock::copy() {
		AbsFuncBlock* blockUnit1 = NULL, * blockUnit2 = NULL, * newAfb = NULL;
		bool e0 = isExist(afb[0]);
		bool e1 = isExist(afb[1]);
		if (!e0 || !e1) {
			isZer = 0;
			return NULL;
		}
		newAfb = new MultFuncBlock;
		newAfb->setTag(tag);
		//NULL化已经在dt()中完成
		blockUnit1 = afb[0]->copy();
		blockUnit2 = afb[1]->copy();
		newAfb->load(blockUnit1, blockUnit2);
		return newAfb;
	}

	/**************************************************************************/

	PwrFuncBlock::PwrFuncBlock() {
		lparam = 1.0;
	}


	PwrFuncBlock ::~PwrFuncBlock() {
		delete afb[0];
		delete afb[1];
	}


	void PwrFuncBlock::dt() {
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		//如果幂不存在，那么永远为1。
		if (!e1) {
			delete afb[0];
			afb[0] = NULL;
			isNor = true;
			setLparam(1.0);
			return;
		}
		//如果0不存在，那么永远是0。
		if (!e0) {
			delete afb[1];
			afb[1] = NULL;
			isZer = true;
			return;
		}
		//如果都存在
		e0 = afb[0]->isNorm(), e1 = afb[1]->isNorm();
		if (e0 && e1) {
			isZer = true;
			return;
		}
		//幂函数
		//TODO 未完成的复合幂函数
		if (e1) {
			double s1 = afb[1]->getLparam();
			lparam *= s1;
			afb[1]->setLparam(s1 - 1);
			if (s1 == 2) {
				isNor = false;
				isOn = true;
			}
			else if(s1 == 1) {
				isNor = true;
				lparam = 1.0;
			}
			return;
		}
		//指函数
		if (e0) {
			return;
		}
		//幂指函数
	}

	std::string PwrFuncBlock::rtStr() {
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		if (!e1) {
			isNor = true;
			return "1";
		}
		if (!e0) {
			isZer = true;
			return "";
		}
		//TODO 没有为幂函数的子项添加括号
		std::string rt;
		rt = afb[0]->rtStr();
		rt = rt + "^";
		rt = rt + afb[1]->rtStr();
		return rt;
	}


	void PwrFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
		afb[0] = afb0;
		afb[1] = afb1;
		//TODO归并参数
	}


	AbsFuncBlock* PwrFuncBlock::copy() {
		AbsFuncBlock* newAfb, * subBlock0, * subBlock1;
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		if (!e0) {
			delete afb[1];
			isZer = true;
			return NULL;
		}
		if (!e1) {
			delete afb[0];
			UnitFuncBlock* uafb = new UnitFuncBlock;
			uafb->load("1.0");
			return uafb;
		}
		subBlock0 = afb[0]->copy();
		subBlock1 = afb[1]->copy();
		newAfb = new PwrFuncBlock;
		newAfb->load(subBlock0, subBlock1);
		return newAfb;
	}


	/**************************************************************************/
	UnitFuncBlock::UnitFuncBlock() {
		tag = UNIT;
	}
	UnitFuncBlock::~UnitFuncBlock() {
		
	}

	//单变量求导一定为常数
	void UnitFuncBlock::dt() {
		if (isZer) {
			return;
		}
		if (isNor) {
			isZer = true;
		}
		return;
		isNor = true;
	}


	std::string UnitFuncBlock::rtStr() {
		if (isZer) {
			return "";
		}
		if (isNor) {
			return d2str(lparam);
		}
		return "x";
	}
	


	void UnitFuncBlock::load(std::string s) {
		if (isNum(s)) {
			isNor = true;
			lparam = str2d(s);
		}
	}


	void UnitFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {

	}


	AbsFuncBlock* UnitFuncBlock::copy() {
		AbsFuncBlock* newAfb = new UnitFuncBlock;
		newAfb->setTag(UNIT);
		newAfb->setLparam(lparam);
		return newAfb;
	}

	double UnitFuncBlock::str2d(std::string s) {
		int p = 0, len = 5;
		double f = 1;
		double ans = 0;
		double tai = 0;
		double eps = 1e-6;
		if (s[p] == '-') {
			f = -f;
			p++;
		}
		if (s[p] == '+') {
			p++;
		}
		while (s[p] != '.' && p != s.size()) {
			ans = ans * 10 + ((double)s[p] - '0');
			p++;
		}
		if (p == s.length()) {
			return f * ans;
		}
		p++;
		while (len-- && p != s.length()) {
			tai = tai * 10 + s[p] - '0';
			p++;
		}
		while (tai > 1) {
			tai /= 10;
		}
		ans += tai;
		return ans * f;
	}


	std::string UnitFuncBlock::ridz(std::string s) {
		int p = s.length() - 1;
		int t = s.length() - 2;
		while (s[p] != '.' && p) {
			p--;
		}
		if (p == 0) {
			return s;
		}

		while (s[t] == '0' && s[t + 1] == '0') {
			t--;
		}
		if (s[t] == '.') {
			t--;
		}
		return s.substr(0, t + 1);
	}


	std::string UnitFuncBlock::d2str(double x) {
		return ridz(std::to_string(x));
	}


	bool UnitFuncBlock::isNum(std::string s) {
		for (int i = 0; i < s.size(); i++) {
			if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-' || s[i] == '.') {
				continue;
			}
			return false;
		}
		return true;
	}

	/**************************************************************************/
	NoneFuncBlock::~NoneFuncBlock(){}


	void  NoneFuncBlock::dt() {}


	std::string NoneFuncBlock::rtStr() { return ""; }


	void NoneFuncBlock::load(std::string) {}


	void NoneFuncBlock::load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {

	}


	AbsFuncBlock* NoneFuncBlock::copy() { return NULL; }
}