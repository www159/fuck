#include"BasFunc.h"
namespace BasFunc {
/*************************************************************************/

	void AbsBasFunc::setLpara(double s) {
		lpara = s;
	}
	double AbsBasFunc::getLpara() {
		return lpara;
	}

	void AbsBasFunc::flhbck() {
		now = last;
		last = "";
	}

	bool AbsBasFunc::isNorm() {
		return isNor;
	}

    bool AbsBasFunc::isZero() {
		if (now.compare("0") == 0 && isNor) {
			return true;
		}
		return false;
	}
	double AbsBasFunc::str2d(std::string s) {
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
	std::string AbsBasFunc::ridz(std::string s) {
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
	std::string AbsBasFunc::d2str(double x) {
		return ridz(std::to_string(x));
	}


/*************************************************************************/
	void BasPwrFunc::load(std::string s) {
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

	void BasPwrFunc::dt() {
		if (isNor) {
			last = now;
			now = "";
			return;
		}
		last = now;
		lpara *= tpara;
		tpara -= 1;
		if (tpara == 0) {
			now = d2str(lpara);
			isNor = true;
		}
		else if (tpara == 1) {
			now = d2str(lpara) + "x";
		}
		else if (tpara < 0) {
			now = d2str(lpara) + "x";
			now = now + "^";
			now = now + "(";
			now = now + d2str(tpara);
			now = now + ")";
		}
		else {
			now = d2str(lpara) + "x";
			now = now + "^";
			now = now + d2str(tpara);
		}
	}

	std::string BasPwrFunc::rtStr() {
		return now;
	}

	AbsBasFunc* BasPwrFunc::copy() {
		AbsBasFunc* pwAbf = new BasPwrFunc;
		pwAbf->load(now);
		return pwAbf;
	}
}

