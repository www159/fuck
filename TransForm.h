#pragma once
#include<string>
/*
*	ת��ͷ������double��string֮���໥ת����
*	����ȥ��С������0�Ĺ��ܡ�
*/
class TransForm
{
public:

	static double str2d(std::string s);

	static std::string d2str(double x);
	
private:
	//��ȥ�����ĩβ0�����ڸ߾�
	static std::string ridz(std::string s);
};

