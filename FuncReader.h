#pragma once
#include "BasFuncBlock.h"
#include<vector>
#include<queue>
#include<stack>
namespace FuncReader {
	using namespace BasFuncBlock;
	/// <summary>
	/// 通用函数读写器，支持将一个字符串翻译成函数。
	/// 有幂函数，指数函数，对数函数，三角函数，反三角函数。
	/// 支持复合函数阅读。
	/// 
	/// 复合函数的tag支持掩码。
	/// </summary>
	class GnlFuncReader {
#define LINC 30
#define RINC 31
#define COMB 13
#define NORM -1
	public:

			/// <summary>
			/// 粗略翻译，将函数包装成块变成单元块。
			/// 依旧是中缀表达式。
			/// 但是内部调用了两个翻译头。
			/// 第一个将中缀表达式转成后缀表达式。
			/// 第二个将后缀表达式翻译成总函数块。
			/// </summary>
			/// <param name="s">传入表达式</param>
			void load(std::string s) {
			ecde.clear();
			this->end = s.length();
			//连续左括号最左边的下标
			int seqLincs = 0;
			int p, q, r, t, isSpecFunc;
			p = q = 0;
			r = -1;
			t = -1;
			//当前读到的符号下标
			int Signtag = 0;
			int INCNT = 0;
			//这里可以加入sin和log判断
			//连续右括号不能跳
			while (q < end) {
				while ((isSign(s[q]) == NORM || isSign(s[q]) == LINC)&& q != end) {
					Signtag = isSign(s[q]);
					//括号累加器操作
					if (Signtag == LINC) {
						INCNT--;
					}
					else if (Signtag == RINC) {
						INCNT++;
					}

					//非左括号标识
					if (Signtag != LINC) {
						seqLincs = q;
					}

					//如果是读到连续左括号，停下来判断是否为复合函数。
					if (r >= 0 && Signtag == NORM) {
						if (isSign(s[r]) == LINC) {
							break;
						}
					}

					q++;
					r++;
				}

				//TODO 连续右括号的复合函数先不考虑。
				//不允许空括号的存在
				while (isSign(s[p]) == LINC) {
					INCNT++;
					ecde.push_back(LINC);
					p++;
				}

				//TODO 复合函数读取
				//如果q跳过了连续左括号，那么根据非左括号标识判断该连续括号，并借助括号累加器得到完整的复合函数。
				//如果该函数是复合函数，中缀存储器的括号元素将不会更新。
				//附带幂函数的负指数判断。
				isSpecFunc = isSpeFunc(s, seqLincs);
				if ((isSign(s[r]) ==LINC && isSpecFunc != -1) ||(isSpecFunc != -1 && isSign(s[q]) == MINU)) {
					if (isSpecFunc == PWR) {
						while (INCNT < 0) {
							Signtag = isSign(s[q]);
							if (Signtag == RINC) {
								INCNT++;
							}
							q++;
						}
						UnitFuncBlock* ufb = new UnitFuncBlock;
						ufb->load(s.substr(p, q - p));
						que.push(ufb);
						ecde.push_back(NORM);
						if (q != end) {
							ecde.push_back(isSign(s[q]));
						}
						p = q;
					}
					else {

					}
					continue;
				}

				while (isSign(s[p]) == RINC) {
					ecde.push_back(RINC);
					p++;
				}
				//防止连续括号出现运算符。
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
			trans2();
		}

			/// <summary>
			/// 获取生成的总函数块
			/// </summary>
			/// <returns>总函数块</returns>
			AbsFuncBlock* getAfb() {
				return this->Afb;
			}
	private:
		int end;
		/// <summary>
		/// 用于存中缀表达式的简化式，相当于把函数块挖成空格。
		/// </summary>
		std::vector<int> ecde;
		/// <summary>
		/// que:    用于存中缀表达式顺序的函数单元块。
		/// bacQue: 用于存放后缀表达式
		/// </summary>
		std::queue<AbsFuncBlock*> que, bacQue;
		//总函数块。
		AbsFuncBlock* Afb = NULL;
		/// <summary>
		/// 针对字符判断是否是运算符
		/// </summary>
		/// <param name="c">:传入字符</param>
		/// <returns>true:是运算符</returns>
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
		/// 判断符号优先级大小
		/// </summary>
		/// <param name="x">运算符</param>
		/// <param name="y">运算符</param>
		/// <returns>true: x的优先级小于y</returns>
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
				if (s[p] == '^') {
					return PWR;
				}
			}
			return -1;
		}
		/// <summary>
		/// 将中缀表达式转变为后缀表达式
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
				}
			}
			while (!temsta.empty()) {
				AbsFuncBlock* afb = new NoneFuncBlock;
				afb->setTag(temsta.top());
				bacQue.push(afb);
				temsta.pop();
			}
		}

		/// <summary>
		/// 根据后缀表达式生成函数单元
		/// </summary>
		void trans2() {
			std::stack<AbsFuncBlock*> afbStack;
			AbsFuncBlock* afb1, * afb2, *afb3;
			while (!bacQue.empty()) {
				afb1 = bacQue.front();
				bacQue.pop();

				int tag = afb1->getTag();
				switch (tag) {
				case ADD: case MINU:case DIV: case MULT: {
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
		 /// <summary>
		 /// 函数块生成器
		 /// </summary>
		 /// <param name="tag">标识符</param>
		 /// <param name="afb1">函数子块1</param>
		 /// <param name="afb2">函数子块2</param>
		 /// <returns>组合函数块</returns>
		 AbsFuncBlock* BlockGenr(int tag, AbsFuncBlock* afb1, AbsFuncBlock* afb2) {
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

			}
			case DIV: {

			}
			default:return NULL;
			}
			return NULL;
		}
	};
}