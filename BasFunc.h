#pragma once
#include<string>
/// </summary>
namespace BasFunc {
	class AbsBasFunc {
	public:
		/// <summary>
		/// 载入函数，并更新内部参数。
		/// </summary>
		/// <param name="s">传入函数</param>
		virtual void load(std::string s) = 0;
		/// <summary>
		/// 微分函数，将函数式变成微分形式。
		/// </summary>
		virtual void dt() = 0;
		/// <summary>
		/// 返回函数。
		/// </summary>
		/// <returns></returns>
		virtual std::string rtStr() = 0;
		virtual AbsBasFunc* copy() = 0;
		/// <summary>
		/// 传入参数，用于上层合并参数。
		/// </summary>
		/// <param name="s">参数字符串</param>
		virtual void loadLpara(double s);

		double getLpara();
		/// <summary>
		/// 后悔函数。撤销操作，只支持一步撤销
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
		/// 字符转浮点
		/// </summary>
		/// <param name="s">字符数字</param>
		/// <returns>浮点数字</returns>
		double str2d(std::string s);
		std::string d2str(double x);

		/// <summary>
		/// 擦除浮点小数多余0
		/// </summary>
		/// <param name="s">字符</param>
		/// <returns>被擦除的字符</returns>
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