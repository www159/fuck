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

		void setTag(int t);

		void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1);

		int getTag();
		/// <summary>
		/// �Ƿ�Ϊ��Ԫ
		/// </summary>
		/// <returns>true �ǵ�Ԫ</returns>
		bool isUnit();

		bool isNorm();

	protected:
		/// <summary>
		/// ͨ����ʶ����������
		/// </summary>
		int tag;

		bool isNor = false;

		bool isZer = false;

		AbsFuncBlock* afb[2] = {NULL};


	};
	/**************************************************************************/
	/// <summary>
	/// �ӷ�������ͼ���������ϲ�
	/// </summary>
	class AddFuncBlock :public AbsFuncBlock {
	public:

		void dt();

		std::string rtStr();
		/// <summary>
		/// �Կ���и���
		/// </summary>
		/// <returns>�����ƵĿ�</returns>
		AbsFuncBlock* copy();
		
	};
	/**************************************************************************/
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
		void dt();

		std::string rtStr();

		AbsFuncBlock* copy();
		//TODO ���Ӷ�0�ж�
		void setLpara();

};
	/**************************************************************************/
	/// <summary>
	/// ��Ԫ��
	/// �������뺯��Ԫ�Ľ����ӿ�
	/// </summary>
	/// <param name="s"></param>
	class UnitFuncBlock : public AbsFuncBlock {


#define PWR 1
#define IND 2
#define ARI 3
#define TRI 4

#define ART 5


	public:

		void dt();

		std::string rtStr();
		/// <summary>
		/// ��дͷ��֤����ĺ���Ϊ���ε���������Ⱥ�����
		/// </summary>
		/// <param name="s">�����ַ���</param>
		void load(std::string s);

		AbsFuncBlock* copy();

		void setLpara(double s);

		double getLpara();

	private:

		AbsBasFunc* abf = NULL;


	};
	/**************************************************************************/
	/// <summary>
	/// ûɶ���õ��ֻ࣬����������дͷ��������ŵġ�
	/// </summary>
	class NoneFuncBlock :public AbsFuncBlock {
	public:
		void dt();

		std::string rtStr();

		void load(std::string);

		AbsFuncBlock* copy();

	};
}
