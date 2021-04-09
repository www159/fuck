#pragma once
#include<string>
/// </summary>
namespace BasFunc {
	class AbsBasFunc {
	public:
		/// <summary>
		/// ���뺯�����������ڲ�������
		/// </summary>
		/// <param name="s">���뺯��</param>
		virtual void load(std::string s) = 0;
		/// <summary>
		/// ΢�ֺ�����������ʽ���΢����ʽ��
		/// </summary>
		virtual void dt() = 0;
		/// <summary>
		/// ���غ�����
		/// </summary>
		/// <returns></returns>
		virtual std::string rtStr() = 0;
		virtual AbsBasFunc* copy() = 0;
		/// <summary>
		/// ��������������ϲ�ϲ�������
		/// </summary>
		/// <param name="s">�����ַ���</param>
		virtual void loadLpara(double s);

		double getLpara();
		/// <summary>
		/// ��ں���������������ֻ֧��һ������
		/// </summary>
		void flhbck();
		bool isNorm();
		bool isZero();
	protected:
		std::string now = "";
		std::string last = "";
		double lpara = 0.0;
		bool isNor = false;
		/// <summary>
		/// �ַ�ת����
		/// </summary>
		/// <param name="s">�ַ�����</param>
		/// <returns>��������</returns>
		double str2d(std::string s);
		std::string d2str(double x);

		/// <summary>
		/// ��������С������0
		/// </summary>
		/// <param name="s">�ַ�</param>
		/// <returns>���������ַ�</returns>
		std::string ridz(std::string s);

	};
	class BasPwrFunc : public AbsBasFunc {
	public:
		void load(std::string s);

		void dt();

		std::string rtStr();

		AbsBasFunc* copy();
	private:
		double tpara = 0.0;
	};
}