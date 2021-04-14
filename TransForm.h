#pragma once
//转接头，字符转double
#include<string>
class TransForm
{
public:

	static double str2d(std::string s);

	static std::string d2str(double x);
	
private:
	//除去多余的末尾0，用于高精
	static std::string ridz(std::string s);
};

