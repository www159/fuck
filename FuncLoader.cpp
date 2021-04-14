#include "FuncLoader.h"
namespace FuncDre {



	FuncLoader::FuncLoader() {
		conQue = new std::queue<AbsFuncBlock*>;
		comQue = new std::queue<AbsFuncBlock*>;
		bacQue = new std::queue<AbsFuncBlock*>;
	}



	FuncLoader::~FuncLoader() {
		delete conQue;
		delete comQue;
		delete bacQue;
	}



	void FuncLoader::load(std::string str) {
		workSubComb(str);	//修改str
		trans1(str);		//修改str
		trans2(str);		//不修改str
		trans3();
	}


	void FuncLoader::trans1(std::string& str) {
		std::string conRep = "C";
		std::regex Con("([^(]|[+-])?[0-9]*\\.?[0-9]+");
		std::regex Time("([0-9\\)Ux])([a-z\\(U])"), Time2("([xU])([a-z])");
		std::string timeRep = "$1*$2";
		//添加完全乘号。
		str = regex_replace(str, Time, timeRep);
		str = regex_replace(str, Time2, timeRep);
		//提取所有实数放入实数队列，并替换为C;
		std::sregex_iterator pos(str.begin(), str.end(), Con), end;
		while (pos != end) {
			ConFuncBlock* conFuncBlock = new ConFuncBlock;
			conFuncBlock->setNum(TransForm::str2d(pos->str()));
			conFuncBlock->setTag(CON);
			conQue->push(conFuncBlock);
			pos++;
		}
		str = regex_replace(str, Con, "C");
	}



	void FuncLoader::trans2(std::string str) {
		AddStack = new std::stack<AbsFuncBlock*>;
		MulStack = new std::stack<AbsFuncBlock*>;

		delete AddStack;
		delete MulStack;
	}



	int FuncLoader::isSign(char c) {
		switch (c) {
		case 'C': return CON;
		case 'U': return UNI;
		case 'x': return VAR;
		case '+': return ADD;
		case '-': return MINU;
		case '*': return MULT;
		case '/': return DIV;
		case '^': return PWR;
		case '(': return LINC;
		case ')': return RINC;
		default : return -1;
		}
	}



	void FuncLoader::workSubComb(std::string& str) {
		int len = str.length(), p = 0, q = 0, r = 0;
		int cnt = 0, tag = DEAFULTTAG;
		while (q < len) {

			while (p < len) {
				if (str[p] == 's') {
					tag = SIN;
					break;
				}
				if (str[p] == 'c') {
					tag = COS;
					break;
				}
				if (str[p] == 't') {
					tag = TAN;
					break;
				}
				if (str[p] == 'l') {
					tag = LOGBLOCK;
					break;
				}
				p++;
			}

			if (p >= len) {
				return;
			}

			q = p;

			while (cnt == 0 && q < len) {
				if (str[q] == '(') {
					cnt--;
				}
				q++;
			}

			r = q;//此时p在第一个左括号的右边

			while (cnt != 0 && r < len) {
				if (str[r] == '(') {
					cnt--;
				}
				if (str[r] == ')') {
					cnt++;
				}
				r++;
			}

			//保证括号完备,此时q在最大右括号的右边。
			FuncLoader* funcLoader = new FuncLoader;
			funcLoader->load(str.substr(q, r - q));//长度需要斟酌。
			AbsFuncBlock* absFuncBlock = funcLoader->getFinalFunc();
			delete funcLoader;

			absFuncBlock->setTag(tag);
			comQue->push(absFuncBlock);//复合块队列push复合块。
			str.replace(p , r - p, "U");//被替换的长度需要加上括号。

			p++;
			len = str.length();
		}
	}
}