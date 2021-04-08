#pragma once
#include<string>
#include"BasFunc.h"
namespace BasFuncBlock {
	using namespace BasFunc;
	/// <summary>
	/// 基本抽象函数块。函数块是一个二元组。
	/// 这与后续的复合函数块相互区别。
	/// 二元组的连接符号为加，减，乘，除。
	/// 二元组的组合可以是：函数块，函数块。
	/// 单项函数不能被二元组包括，但可以被一元组包括。
	/// 
	/// TODO：后续加入复合函数块。
	/// </summary>
	class AbsFuncBlock {
#define UNIT 8
#define MULT 21
#define ADD  10
#define DIV  20
#define MINU 11
	public:
		virtual void dt() = 0;
		virtual std::string rtStr() = 0;
		void setTag(int t) {
			this->tag = t;
		}
		inline int getTag() {
			return this->tag;
		}
	protected:
		/// <summary>
		/// 通过标识符向下造型
		/// </summary>
		int tag;
	};
	/// <summary>
	/// 加法函数块和减法函数块合并
	/// </summary>
	class AddFuncBlock :public AbsFuncBlock {
	public:
		void dt() {
			afb[0]->dt();
			afb[1]->dt();
		}
		std::string rtStr() {
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

		void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
			afb[0] = afb0;
			afb[1] = afb1;
		}
	private:
		AbsFuncBlock* afb[2];
	};
	/// <summary>
	/// 函数单元块，只装一个函数。
	/// </summary>
	class UnitFuncBlock : public AbsFuncBlock {
#define PWR 1
#define IND 2
#define ARI 3
#define TRI 4
#define ART 5
	public:
		void dt() {
			abf->dt();
		}
		std::string rtStr() {
			if (tag == PWR) {
				if (abf->isZero()) {
					return "";
				}
			}
			return abf->rtStr();
		}
		/// <summary>
		/// 读写头保证输入的函数为带参单项基本初等函数。
		/// </summary>
		/// <param name="s">读入字符串</param>
		void load(std::string s) {
			//单元块load需要switch
			//TODO
			if (s.find("arc") != s.npos) {

			}
			else if (s.find("ln") != s.npos) {

			}
			else if (s.find("s") != s.npos && s.find("tan") != s.npos) {

			}
			else if(s.find("^x")!=s.npos) {

			}
			else {
				abf = new BasPwrFunc;
				tag = PWR;
			}
			abf->load(s);
		}
	private:
		AbsBasFunc* abf = NULL;
	};

	/// <summary>
	/// 没啥卵用的类，知识用来存符号的。
	/// </summary>
	class NoneFuncBlock :public AbsFuncBlock {
		void dt(){}
		std::string rtStr() { return NULL; }
		void load(std::string){}
		
	};
}
