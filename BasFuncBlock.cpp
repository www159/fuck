#include"BasFuncBlock.h"
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

	bool AbsFuncBlock::isMult() {
		return isMul;
	}

	double AbsFuncBlock::getLparam() {
		return this->lparam;
	}
	
	void AbsFuncBlock::setLparam(double s) {
		this->lparam = s;
	}

	AbsFuncBlock* AbsFuncBlock::setMult(AbsFuncBlock* mfb) {
		int tag = mfb->getTag();

		if (mfb->isMult() && tag == ADD) {
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
			AbsFuncBlock* t = setMult(afb[1]);
			afb[1] = t;
		}
		if (e0) {
			afb[0]->dt();
			AbsFuncBlock* t = setMult(afb[0]);
			afb[0] = t;
		}
		//求完导之后清除0项
		isExist(afb[0]), isExist(afb[1]);
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

		AbsFuncBlock* t0 = NULL, *t1 = NULL;
		AbsFuncBlock* subBlock0, *subBlock1, *afb0 = afb[0], *afb1 = afb[1];
		//乘法比较简单，两个都不为0；
		t0 = afb0->copy();
		t1 = afb1->copy();
		t0->dt();
		t1->dt();
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

		//因为新元一定是完整乘法式，因此不需要setMult
		subBlock0 = new MultFuncBlock;
		subBlock0->load(t0, afb1);
		subBlock1 = new MultFuncBlock;
		subBlock1->load(afb0, t1);
		tag = ADD;
		afb[0] = subBlock0;
		afb[1] = subBlock1;
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
		newAfb->setLparam(lparam);
		return newAfb;
	}

	/**************************************************************************/

	PwrFuncBlock ::~PwrFuncBlock() {
		delete afb[0];
		delete afb[1];
	}

	void PwrFuncBlock::dt() {
		bool e0 = isExist(afb[0]), e1 = isExist(afb[1]);
		if (!e1) {
			delete afb[0];
			afb[0] = NULL;
			isNor = true;
			setLparam(1.0);
		}
		if (!e0) {
			delete afb[1];
			afb[1] = NULL;
			isZer = true;
		}

	}

	std::string PwrFuncBlock::rtStr() {
		if (isZer) {
			return "";
		}
		//TODO需要特判乘法，并将其转换为加法块。
		int tag0 = afb[0]->getTag(), 
			tag1 = afb[1]->getTag();
		bool t0, t1;
		std::s1 = afb[0]->rtStr(),
	
	}

	void load(std::string s);

	AbsFuncBlock* copy();


	/**************************************************************************/
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


	AbsFuncBlock* NoneFuncBlock::copy() { return NULL; }
}