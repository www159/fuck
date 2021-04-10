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
		virtual ~AbsFuncBlock() {};

		virtual void dt() = 0;

		virtual std::string rtStr() = 0;
		/// <summary>
		/// ���ƺ���
		/// </summary>
		/// <returns>�ú�����ĸ��ƶ���</returns>
		virtual AbsFuncBlock* copy() = 0;

		void setTag(int t);
		/// <summary>
		/// ��ʼ��������ϵ��Ϊ1
		/// </summary>
		/// <param name="afb0">������</param>
		/// <param name="afb1">�Һ�����</param>
		virtual void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1);

		int getTag();
		/// <summary>
		/// �Ƿ�Ϊ��Ԫ
		/// </summary>
		/// <returns>true �ǵ�Ԫ</returns>
		bool isUnit();

		bool isNorm();

		bool isZero();

		bool isMult();

		double getLparam();

		void setLparam(double s);

		AbsFuncBlock* setMult(AbsFuncBlock* mfb);
		/// <summary>
		/// �ж��Ƿ�Ϊ�պ�����0������
		/// �����0������ת��Ϊ�պ���
		/// </summary>
		/// <param name="afb">���жϺ���</param>
		/// <returns>true: �ú���Ϊ�պ���</returns>
		static bool isExist(AbsFuncBlock* afb);

	protected:
		/// <summary>
		/// ͨ����ʶ����������
		/// </summary>
		int tag;

		bool isNor = false;

		bool isZer = false;

		bool isMul = false;

		AbsFuncBlock* afb[2] = {NULL};

		double lparam;

		/// <summary>
		/// ���ڽ��˷�������Ϊ�ӷ��顣
		/// </summary>
		/// <param name="mfb">�˷���</param>
		/// <returns>�������͵ĳ˷���</returns>
	};
	/**************************************************************************/
	/// <summary>
	/// �ӷ�������ͼ���������ϲ�
	/// </summary>
	class AddFuncBlock :public AbsFuncBlock {
	public:
		~AddFuncBlock();
		/// <summary>
		/// �ӷ�����Ҫ�����ϲ�
		/// </summary>
		/// <param name="afb0"></param>
		/// <param name="afb1"></param>
		void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1);

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

		MultFuncBlock();

		~MultFuncBlock();
		/// <summary>
		/// �˷���Ԫ�󵼣���Ҫ�ⲿ�����ͳɼӷ���Ԫ
		/// ���������ӵ�Ԫ
		/// </summary>
		void dt();

		std::string rtStr();

		AbsFuncBlock* copy();
		//TODO ���Ӷ�0�ж�

};
	/**************************************************************************/

	/// <summary>
	/// ��ָ�����飬ʷ����ĺ��������ˡ�
	/// </summary>
	class PwrFuncBlock :public AbsFuncBlock {
	public:
		~PwrFuncBlock();

		void dt();

		std::string rtStr();

		void load(std::string s);

		AbsFuncBlock* copy();
	};
	/**************************************************************************/
	/// <summary>
	/// ��Ԫ��
	/// �������뺯��Ԫ�Ľ����ӿ�
	/// </summary>
	class UnitFuncBlock : public AbsFuncBlock {


#define PWR 1
#define IND 2
#define ARI 3
#define TRI 4

#define ART 5


	public:

		~UnitFuncBlock();

		void dt();

		std::string rtStr();
		/// <summary>
		/// ��дͷ��֤����ĺ���Ϊ���ε���������Ⱥ�����
		/// </summary>
		/// <param name="s">�����ַ���</param>
		void load(std::string s);

		AbsFuncBlock* copy();

	private:

		double str2d(std::string s);
		std::string ridz(std::string s);
		std::string d2str(double x);
		bool isNum(std::string s);
	};
	/**************************************************************************/
	/// <summary>
	/// ûɶ���õ��ֻ࣬����������дͷ��������ŵġ�
	/// </summary>
	class NoneFuncBlock :public AbsFuncBlock {
	public:

		~NoneFuncBlock();

		void dt();

		std::string rtStr();

		void load(std::string);

		AbsFuncBlock* copy();

	};
}
