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
		/// <summary>
		/// 后悔函数。撤销操作，只支持一步撤销
		/// </summary>
		void flhbck() {
			now = last;
			last = "";
		}
		bool isNorm() {
			return isNor;
		}
	private:

	protected:
		std::string now;
		std::string last;
		bool isNor = false;
		double str2d(std::string s) {
			int p = 0, len = 5;
			double f = 1;
			double ans = 0;
			double tai = 0;
			double eps = 1e-6;
			if (s[p] == '-') {
				f = -f;
				p++;
			}
			if (s[p] == '+') {
				p++;
			}
			while (s[p] != '.' && p != s.size()) {
				ans = ans * 10 + ((double)s[p] - '0');
				p++;
			}
			if (p == s.length()) {
				return f * ans;
			}
			p++;
			while (len-- && p != s.length()) {
				tai = tai * 10 + s[p] - '0';
				p++;
			}
			while (tai > 1) {
				tai /= 10;
			}
			ans += tai;
			return ans * f;
		}

		std::string d2str(double x) {
			return ridz(std::to_string(x));
		}
		std::string ridz(std::string s) {
			int p = s.length() - 1;
			int t = s.length() - 2;
			while (s[p] != '.' && p) {
				p--;
			}
			if (p == 0) {
				return s;
			}

			while (s[t] == '0' && s[t + 1] == '0') {
				t--;
			}
			if (s[t] == '.') {
				t--;
			}
			return s.substr(0, t + 1);
		}

	};
	class BasPwrFunc : public AbsBasFunc {
	public:
		void load(std::string s) {
			isNor = false;
			now = s;
			int p = 0;
			//左侧系数
			while (s[p] != 'x' && p != s.length()) {
				p++;
			}
			if (p == 0) {
				lpara = 1;
			}
			else {
				lpara = str2d(s.substr(0, p));
			}

			//若是常数
			if (p == s.length()) {
				isNor = true;
				return;
			}

			//幂系数
			int f = 1;
			while ((s[p] < '0' || s[p] > '9') && s[p] != '-' && p < s.length()) {
				p++;
			}
			//幂系数为空
			if (p == s.length()) {
				tpara = 1;
			}
			else if (s[p] == '-') {
				//强制规定负数做幂添括号
				tpara = str2d(s.substr(p, s.length() - p - 1));
			}
			else {
				tpara = str2d(s.substr(p, s.length() - p));
			}

		}
		void dt() {
			if (isNor) {
				last = now;
				now = "0";
				return;
			}
			last = now;
			lpara *= tpara;
			tpara -= 1;
			if (tpara == 0) {
				now = d2str(lpara);
				isNor = true;
			}
			else {
				now = d2str(lpara) + "x";
				now = now + "^";
				now = now + d2str(tpara);
			}
		}
		std::string rtStr() {
			return now;
		}

	private:
		double lpara = 0.0;
		double tpara = 0.0;
	};
}