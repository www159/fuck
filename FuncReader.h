#pragma once
#include "BasFuncBlock.h"
#include<vector>
#include<queue>
#include<stack>
namespace FuncReader {
	using namespace BasFuncBlock;
	/// <summary>
	/// ͨ�ú�����д����֧�ֽ�һ���ַ�������ɺ�����
	/// ���ݺ�����ָ���������������������Ǻ����������Ǻ�����
	/// ֧�ָ��Ϻ����Ķ���
	/// 
	/// ���Ϻ�����tag֧�����롣
	/// </summary>
	class GnlFuncReader {
#define LINC 30
#define RINC 31
#define COMB 13
#define NORM -1
	public:

			/// <summary>
			/// ���Է��룬��������װ�ɿ��ɵ�Ԫ�顣
			/// ��������׺���ʽ��
			/// </summary>
			/// <param name="s">������ʽ</param>
			void load(std::string s) {
			ecde.clear();
			this->end = s.length();
			//��������������ߵ��±�
			int seqLincs = 0;
			int p, q, r;
			p = q = 0;
			r = -1;
			//��ǰ�����ķ����±�
			int Signtag = 0;
			//������Լ���sin��log�ж�
			//���������Ų�����
			while (q < end) {
				while ((isSign(s[q]) == NORM || isSign(s[q]) == LINC)&& q != end) {
					Signtag = isSign(s[q]);
					if (Signtag != LINC) {
						seqLincs = p;
					}
					q++;
					r++;
				}

				//TODO ���Ϻ�����ȡ
				if (Signtag ==LINC && isSpeFunc(s, seqLincs) != -1) {
					continue;
				}
				//TODO ���������ŵĸ��Ϻ����Ȳ����ǡ�
				while (isSign(s[p]) == LINC) {
					ecde.push_back(LINC);
					p++;
				}
				while (isSign(s[p]) == RINC) {
					ecde.push_back(RINC);
					p++;
				}
				//��ֹ�������ų����������
				if (isSign(s[p]) != NORM) {
					ecde.push_back(isSign(s[p]));
					p++;
				}
				UnitFuncBlock* ufb = new UnitFuncBlock;
				ufb->load(s.substr(p, q - p));
				que.push(ufb);
				ecde.push_back(NORM);
				if (q != end) {
					ecde.push_back(isSign(s[q]));
				}
				q++;
				p = q;
			}
			trans1();
		}
	private:
		int end;
		/// <summary>
		/// ���ڴ���׺���ʽ�ļ�ʽ���൱�ڰѺ������ڳɿո�
		/// </summary>
		std::vector<int> ecde;
		/// <summary>
		/// que:    ���ڴ���׺���ʽ˳��ĺ�����Ԫ�顣
		/// bacQue: ���ڴ�ź�׺���ʽ
		/// </summary>
		std::queue<AbsFuncBlock*> que, bacQue;
		//�ܺ����顣
		AbsFuncBlock* Afb = NULL;
		/// <summary>
		/// ����ַ��ж��Ƿ��������
		/// </summary>
		/// <param name="c">:�����ַ�</param>
		/// <returns>true:�������</returns>
		inline int isSign(char c) {
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
			default: {
				return -1;
				break;
			}
			}
			return -1;
		}
		/// <summary>
		/// �жϷ������ȼ���С
		/// </summary>
		/// <param name="x">�����</param>
		/// <param name="y">�����</param>
		/// <returns>true: x�����ȼ�С��y</returns>
		inline bool isSmaller(int x, int y) {
			return (x / 10 <= y / 10 ? true : false);
		}
		int isSpeFunc(std::string s, int p) {
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
				if (s[p] == 'n') {
					return ARI;
				}
			}
			return -1;
		}
		/// <summary>
		/// ����׺���ʽת��Ϊ��׺���ʽ
		/// </summary>
		void trans1() {
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
					else if (isSmaller(temsta.top(), ecde[i])) {
						temsta.push(ecde[i]);
					}
					else {
						while (!temsta.empty()) {
							if (isSmaller(ecde[i], temsta.top())) {
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

		void trans2(){}
	};
}