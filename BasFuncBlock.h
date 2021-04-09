#pragma once
#include<string>
#include"BasFunc.h"
namespace BasFuncBlock {
	using namespace BasFunc;
	/// <summary>
	/// �����������顣��������һ����Ԫ�顣
	/// ��������ĸ��Ϻ������໥����
	/// ��Ԫ������ӷ���Ϊ�ӣ������ˣ�����
	/// ��Ԫ�����Ͽ����ǣ������飬�����顣
	/// ��������ܱ���Ԫ������������Ա�һԪ�������
	/// 
	/// TODO���������븴�Ϻ����顣
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

		/// <summary>
		/// ���ƺ���
		/// </summary>
		/// <returns>�ú�����ĸ��ƶ���</returns>
		virtual AbsFuncBlock* copy() = 0;

		void setTag(int t) {
			this->tag = t;
		}

		void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1) {
			afb[0] = afb0;
			afb[1] = afb1;
		}	

		inline int getTag() {
			return tag;
		}
	protected:
		/// <summary>
		/// ͨ����ʶ����������
		/// </summary>
		int tag;
		AbsFuncBlock* afb[2] = {NULL};

		/// <summary>
		/// �Ƿ�Ϊ��Ԫ
		/// </summary>
		/// <returns>true �ǵ�Ԫ</returns>
		inline bool isUnit() {
			switch (tag)
			{
			case ADD: case MULT: case MINU:case DIV: {
				return true;
				break;
			}
			default:return false;
				break;
			}
			return false;
		}
	};


	/// <summary>
	/// �ӷ�������ͼ���������ϲ�
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
			//�жϴ��ݺ������Ƿ�Ϊ0��
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

		/// <summary>
		/// �Կ���и���
		/// </summary>
		/// <returns>�����ƵĿ�</returns>
		AbsFuncBlock* copy() {
			AbsFuncBlock* blockUnit1, * blockUnit2, *newAfb;
			newAfb = new AddFuncBlock;
			blockUnit1 = afb[0]->copy();
			blockUnit2 = afb[1]->copy();
			newAfb->load(blockUnit1, blockUnit2);
			return newAfb;
		}
	};


	/// <summary>
	/// �˷������飬��Ϊ��������ת��Ϊһ��ӷ�ʽ��
	/// �����Ҫ��������Ԫ�����ɾ�ġ�
	/// </summary>
	class MultFuncBlock :public AbsFuncBlock {
	public:
		/// <summary>
		/// �˷���Ԫ�󵼣���Ҫ�ⲿ�����ͳɼӷ���Ԫ
		/// ���������ӵ�Ԫ
		/// </summary>
		void dt() {
			AbsFuncBlock* mulUnit1, * mulUnit2, * t1, * t2;
			mulUnit1 = new MultFuncBlock;
			mulUnit2 = new MultFuncBlock;
			t1 = afb[0]->copy();
			t2 = afb[1]->copy();
			//�˷�����
			mulUnit1->load(t1, afb[1]);
			mulUnit1->setTag(MULT);
			mulUnit2->load(afb[0], t2);
			mulUnit2->setTag(MULT);
		}
		std::string rtStr() {

		}
		AbsFuncBlock* copy() {
			AbsFuncBlock* blockUnit1, * blockUnit2, * newAfb;
			newAfb = new MultFuncBlock;
			blockUnit1 = afb[0]->copy();
			blockUnit2 = afb[1]->copy();
			newAfb->load(blockUnit1, blockUnit2);
			return newAfb;
		}
};
	/// <summary>
	/// ������Ԫ�飬ֻװһ��������
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
		/// ��дͷ��֤����ĺ���Ϊ���ε���������Ⱥ�����
		/// </summary>
		/// <param name="s">�����ַ���</param>
		void load(std::string s) {
			//��Ԫ��load��Ҫswitch
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
		AbsFuncBlock* copy() {
			AbsBasFunc* newAbf;
			UnitFuncBlock* newAfb = new UnitFuncBlock;
			newAbf = abf->copy();
			newAfb->load(newAbf->rtStr());
			return newAfb;
		}
	private:
		AbsBasFunc* abf = NULL;
	};

	/// <summary>
	/// ûɶ���õ��֪࣬ʶ��������ŵġ�
	/// </summary>
	class NoneFuncBlock :public AbsFuncBlock {
		void dt(){}
		std::string rtStr() { return ""; }
		void load(std::string){}
		AbsFuncBlock* copy(){}
	};
}
