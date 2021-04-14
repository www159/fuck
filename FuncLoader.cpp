#include "FuncLoader.h"
namespace FuncDre {



	FuncLoader::FuncLoader() {
		conQue		=	new std::queue<AbsFuncBlock*>;
		comQue		=	new std::queue<AbsFuncBlock*>;
		bacQue		=	new std::queue<int>;
		AddStack	=	new std::stack<AbsFuncBlock*>;
		MulStack	=	new std::stack<AbsFuncBlock*>;
	}



	FuncLoader::~FuncLoader() {
		delete conQue;
		delete comQue;
		delete bacQue;
		delete AddStack;
		delete MulStack;
	}



	void FuncLoader::load(std::string str) {
		workSubComb(str);	//�޸�str
		trans1(str);		//�޸�str
		trans2(str);		//���޸�str
		trans3();
	}


	void FuncLoader::trans1(std::string& str) {
		std::regex Con("[-]?[0-9]*\\.?[0-9]+"),
				   Time("([0-9\\)Ux])([x\\(U])"),
				   Minu("([)xU\\d])(\\-)([(xU\\d])"),
				   Minu2("^(-)([xU])"),
				   Pos("(\\()(\\+)([\\dxU])"),
				   Pos2("^(\\+)([Ux\\d])");

		std::string posRep("$1$3"),
					posRep2("$2"),
					timeRep = "$1*$2",
					minuRep = "$1+(-1)*$3",
					minuRep2 = "(-1)*$2";

		str = regex_replace(str, Minu, minuRep);	//������(���Ǹ���)ת��Ϊ(-1)*
		str = regex_replace(str, Minu2, minuRep2);	//ת����ʼ����
		str = regex_replace(str, Time, timeRep);	//�����ȫ��
		str = regex_replace(str, Pos, posRep);		//ȥ����Ч����
		str = regex_replace(str, Pos2, posRep2);	//ȥ����ͷ��Ч����

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
		int len = str.length(), sign;
		std::stack<int>* temStack = new std::stack<int>;

		for (int i = 0; i < len; i++) {
			sign = isSign(str[i]);

			if (sign == CON || sign == UNI || sign == VAR) {
				bacQue->push(sign);
			}
			else {
				switch (sign) {

				case LINC: {
					temStack->push(sign);
					break;
				}
				case RINC: {//��֤���ųɶԳ��֡�
					while (temStack->top() != LINC) {
						bacQue->push(temStack->top());
						temStack->pop();
					}
					temStack->pop();
					break;
				}
				default: {
					if (temStack->empty()) {
						temStack->push(sign);
					}
					else {//�ҵ����ȼ������Լ���Ϊֹ��
						while (!temStack->empty() && isSmaller(sign, temStack->top())) {
							bacQue->push(temStack->top());
							temStack->pop();
						}
						temStack->push(sign);
					}
					break;
				}
				}
			}
		}

		while (!temStack->empty()) {//����ʣ���������
			bacQue->push(temStack->top());
			temStack->pop();
		}
	}



	void FuncLoader::trans3() {
		int sign = -1, lastSign = -1, lastSign2 = -1;
		std::stack<AbsFuncBlock*>* temStack = new std::stack<AbsFuncBlock*>;
		while (!bacQue->empty()) {
			lastSign2 = lastSign;
			lastSign = sign;
			sign = bacQue->front();
			switch (sign) {
			case CON: {
				temStack->push(conQue->front());
				conQue->pop();
				break;
			}
			case VAR: {
				AbsFuncBlock* absFuncBlock = new AbsFuncBlock;
				absFuncBlock->setTag(BASBLOCK);
				temStack->push(absFuncBlock);
				break;
			}
			case UNI: {
				temStack->push(comQue->front());
				comQue->pop();
				break;
			}

			case DIV:{//TODO
				GnlFuncBlock* divFuncBlock = new GnlFuncBlock;
				divFuncBlock->setTag(DIVBLOCK); 
				if (lastSign2 == -1) {
					
				}
				else if (lastSign == ADD) {

				}
				else if (lastSign == MULT) {

				}
			}
			case PWR: {

			}
			case ADD: {

			}
			case MULT:{

			}
			default: {

			}
			}

			
		}
	}



	bool FuncLoader::isSmaller(int sign1, int sign2) {
		return sign1 / 10 <= sign2 / 10;
	}



	int FuncLoader::isSign(char c) {
		switch (c) {
		case 'C': return CON;
		case 'U': return UNI;
		case 'x': return VAR;
		case '+': return ADD;
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
		int cnt = 0, tag = DEFAULTTAG;
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

			absFuncBlock->setTag(tag);//���ø��Ͽ��ǩ��
			comQue->push(absFuncBlock);//���Ͽ����push���Ͽ顣
			str.replace(p , r - p, "U");//���滻�ĳ�����Ҫ�������š�

			p++;
			len = str.length();
		}
	}
}