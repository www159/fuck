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
			/// </summary>
			/// <param name="s">传入表达式</param>
			void load(std::string s) {
			ecde.clear();
			this->end = s.length();
			//连续左括号最左边的下标
			int seqLincs = 0;
			int p, q, r;
			p = q = 0;
			r = -1;
			//当前读到的符号下标
			int Signtag = 0;
			//这里可以加入sin和log判断
			//连续右括号不能跳
			while (q < end) {
				while ((isSign(s[q]) == NORM || isSign(s[q]) == LINC)&& q != end) {
					Signtag = isSign(s[q]);
					if (Signtag != LINC) {
						seqLincs = p;
					}
					q++;
					r++;
				}

				//TODO 复合函数读取
				if (Signtag ==LINC && isSpeFunc(s, seqLincs) != -1) {
					continue;
				}
				//TODO 连续右括号的复合函数先不考虑。
				while (isSign(s[p]) == LINC) {
					ecde.push_back(LINC);
					p++;
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