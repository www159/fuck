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
		workSubComb(str);	//�޸�str
		trans1(str);		//�޸�str
		trans2(str);		//���޸�str
		trans3();
	}


	void FuncLoader::trans1(std::string& str) {
		std::string conRep = "C";
		std::regex Con("([^(]|[+-])?[0-9]*\\.?[0-9]+");
		std::regex Time("([0-9\\)Ux])([a-z\\(U])"), Time2("([xU])([a-z])");
		std::string timeRep = "$1*$2";
		//�����ȫ�˺š�
		str = regex_replace(str, Time, timeRep);
		str = regex_replace(str, Time2, timeRep);
		//��ȡ����ʵ������ʵ�����У����滻ΪC;
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

			r = q;//��ʱp�ڵ�һ�������ŵ��ұ�

			while (cnt != 0 && r < len) {
				if (str[r] == '(') {
					cnt--;
				}
				if (str[r] == ')') {
					cnt++;
				}
				r++;
			}

			//��֤�����걸,��ʱq����������ŵ��ұߡ�
			FuncLoader* funcLoader = new FuncLoader;
			funcLoader->load(str.substr(q, r - q));//������Ҫ���á�
			AbsFuncBlock* absFuncBlock = funcLoader->getFinalFunc();
			delete funcLoader;

			absFuncBlock->setTag(tag);
			comQue->push(absFuncBlock);//���Ͽ����push���Ͽ顣
			str.replace(p , r - p, "U");//���滻�ĳ�����Ҫ�������š�

			p++;
			len = str.length();
		}
	}
}