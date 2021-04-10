#include"FuncReader.h"
namespace FuncReader {
	using namespace BasFuncBlock;
	//void GnlFuncReader::load(std::string s) {
	//	ecde.clear();
	//	this->end = s.length();
	//	//��������������ߵ��±�
	//	int seqLincs = 0;
	//	int p, q, r, t, isSpecFunc;
	//	p = q = 0;
	//	r = -1;
	//	t = -1;
	//	//��ǰ�����ķ����±�
	//	int Signtag = 0;
	//	int INCNT = 0;
	//	//������Լ���sin��log�ж�
	//	//���������Ų�����
	//	while (q < end) {
	//		while ((isSign(s[q]) == NORM || isSign(s[q]) == LINC) && q != end) {
	//			Signtag = isSign(s[q]);
	//			//�����ۼ�������
	//			if (Signtag == LINC) {
	//				INCNT--;
	//			}
	//			else if (Signtag == RINC) {
	//				INCNT++;
	//			}

	//			//�������ű�ʶ
	//			if (Signtag != LINC) {
	//				seqLincs = q;
	//			}

	//			//����Ƕ������������ţ�ͣ�����ж��Ƿ�Ϊ���Ϻ�����
	//			if (r >= 0 && Signtag == NORM) {
	//				if (isSign(s[r]) == LINC) {
	//					break;
	//				}
	//			}

	//			q++;
	//			r++;
	//		}

	//		//TODO ���������ŵĸ��Ϻ����Ȳ����ǡ�
	//		//����������ŵĴ���
	//		while (isSign(s[p]) == LINC) {
	//			INCNT++;
	//			ecde.push_back(LINC);
	//			p++;
	//		}

	//		//TODO ���Ϻ�����ȡ
	//		//���q���������������ţ���ô���ݷ������ű�ʶ�жϸ��������ţ������������ۼ����õ������ĸ��Ϻ�����
	//		//����ú����Ǹ��Ϻ�������׺�洢��������Ԫ�ؽ�������¡�
	//		//�����ݺ����ĸ�ָ���жϡ�
	//		isSpecFunc = isSpeFunc(s, seqLincs);
	//		if ((isSign(s[r]) == LINC && isSpecFunc != -1) || (isSpecFunc != -1 && isSign(s[q]) == MINU)) {
	//			if (isSpecFunc == PWR) {
	//				while (INCNT < 0) {
	//					Signtag = isSign(s[q]);
	//					if (Signtag == RINC) {
	//						INCNT++;
	//					}
	//					q++;
	//					r++;
	//				}
	//				UnitFuncBlock* ufb = new UnitFuncBlock;
	//				ufb->load(s.substr(p, q - p));
	//				que.push(ufb);
	//				ecde.push_back(NORM);
	//				if (q != end) {
	//					ecde.push_back(isSign(s[q]));
	//				}
	//				p = q;
	//			}
	//			else {

	//			}
	//			continue;
	//		}

	//		while (isSign(s[p]) == RINC) {
	//			ecde.push_back(RINC);
	//			p++;
	//		}
	//		//��ֹ�������ų����������
	//		if (isSign(s[p]) != NORM) {
	//			ecde.push_back(isSign(s[p]));
	//			p++;
	//		}
	//		
	//		if (p >= q) {
	//			q++;
	//			r++;
	//			continue;
	//		}
	//		UnitFuncBlock* ufb = new UnitFuncBlock;
	//		ufb->load(s.substr(p, q - p));
	//		que.push(ufb);
	//		ecde.push_back(NORM);
	//		if (q != end) {
	//			ecde.push_back(isSign(s[q]));
	//		}
	//		q++;
	//		r++;
	//		p = q;
	//	}
	//	trans1();
	//	trans2();
	//}

	void GnlFuncReader::load(std::string s) {
		int p = 0, q = 0;
		end = s.length();
		while (q != end) {
			while ( isSign(s[q]) == NORM || isSign(s[q]) == LINC) {
				q++;
			}
			while (isSign(s[p]) == LINC) {
				ecde.push_back(LINC);
				p++;
			}
			if (p == q) {
				q++;
				continue;
			}
			UnitFuncBlock* ufb = new UnitFuncBlock;
			ufb->load(s.substr(p, q - p));
			que.push(ufb);
			ecde.push_back(NORM);
			while (q <= end && isSign(s[q]) == RINC && isSign(s[q+1]) != NORM) {
				ecde.push_back(isSign(s[q]));
				q++;
			}
			ecde.push_back(isSign(s[q]));
			q++;
			p = q;
		}
		trans1();
		trans2();
	}

	AbsFuncBlock* GnlFuncReader::getAfb() {
		return this->Afb;
	}

	int GnlFuncReader::isSign(char c) {
		switch (c) {
		case '(': {
			return LINC;
		}
		case ')': {
			return RINC;
		}
		case '+': {
			return ADD;
		}
		case '-': {
			return MINU;
		}
		case '*': {
			return MULT;
		}
		case '/': {
			return DIV;
		}
		case '^': {
			return PWR;
		}
		default: {
			return -1;
			break;
		}
		}
		return -1;
	}


	bool GnlFuncReader::isSmaller(int x, int y) {
		return (x / 10 <= y / 10 ? true : false);
	}


	int GnlFuncReader::isSpeFunc(std::string s, int p) {
		if (p > 3) {
			if (s[p - 3] == 'c' && s[p - 4] == 'r') {
				return ART;
			}
		}
		if (p > 1) {
			if (s[p - 2] == 's' || s[p - 2] == 'c' || s[p - 2] == 't') {
				return TRI;
			}
		}
		if (p > 0) {
			//��ָ�����Ѿ�������������
			if (s[p] == 'n') {
				return ARI;
			}
		}
		return -1;
	}
	
	//TODO����ʱ����Ҫ�����鲢��̫nm���ˣ�
	void GnlFuncReader::trans1() {
		std::stack<int> temsta;
		for (int i = 0; i < ecde.size(); i++) {
			switch (ecde[i]) {
			case NORM: {
				bacQue.push(que.front());
				que.pop();
				break;
			}
			default: {
				if (temsta.empty()) {
					temsta.push(ecde[i]);
				}
				else if (ecde[i] == LINC) {
					temsta.push(ecde[i]);
				}
				else if (ecde[i] == RINC) {
					while (!temsta.empty()) {
						if (temsta.top() != LINC) {
							AbsFuncBlock* afb = new NoneFuncBlock;
							afb->setTag(temsta.top());
							bacQue.push(afb);
							temsta.pop();
							continue;
						}
						else {
							break;
						}
					}
					temsta.pop();
				}
				else if (isSmaller(temsta.top(), ecde[i])) {
					temsta.push(ecde[i]);
				}
				else {
					while (!temsta.empty()) {
						if (isSmaller(ecde[i], temsta.top()) && temsta.top() != LINC) {
							AbsFuncBlock* afb = new NoneFuncBlock;
							afb->setTag(temsta.top());
							bacQue.push(afb);
							temsta.pop();
							continue;
						}
						else {
							break;
						}
					}
						temsta.push(ecde[i]);
				}
				break;
			}
				   while (!temsta.empty()) {
					   AbsFuncBlock* afb = new NoneFuncBlock;
					   afb->setTag(temsta.top());
					   bacQue.push(afb);
					   temsta.pop();
				   }
			}
		}
	}

	
	void GnlFuncReader::trans2() {
		std::stack<AbsFuncBlock*> afbStack;
		AbsFuncBlock* afb1, * afb2, * afb3;
		while (!bacQue.empty()) {
			afb1 = bacQue.front();
			bacQue.pop();

			int tag = afb1->getTag();
			switch (tag) {
			case ADD: case MINU:case DIV: case MULT:case PWR: {
				afb2 = afbStack.top();
				afbStack.pop();
				afb3 = afbStack.top();
				afbStack.pop();
				AbsFuncBlock* afb0 = BlockGenr(tag, afb3, afb2);
				afbStack.push(afb0);
				break;
			}
			default: {
				afbStack.push(afb1);
			}
			}
		}
		afb2 = afbStack.top();
		afbStack.pop();
		this->Afb = afb2;
	}
	


	AbsFuncBlock* GnlFuncReader::BlockGenr(int tag, AbsFuncBlock* afb1, AbsFuncBlock* afb2) {
		switch (tag) {
		case ADD: {
			AddFuncBlock* adfb = new AddFuncBlock;
			adfb->setTag(ADD);
			adfb->load(afb1, afb2);
			return adfb;
		}
		case MINU: {
			AddFuncBlock* mifb = new AddFuncBlock;
			mifb->setTag(MINU);
			mifb->load(afb1, afb2);
			return mifb;
		}
		case MULT: {
			MultFuncBlock* mfb = new MultFuncBlock;
			mfb->setTag(MULT);
			mfb->load(afb1, afb2);
			return mfb;
		}
		case DIV: {

		}
		case PWR: {
			PwrFuncBlock* pfb = new PwrFuncBlock;
			pfb->setTag(PWR);
			pfb->load(afb1, afb2);
			return pfb;
		}
		default:return NULL;
		}
		return NULL;
	}
}