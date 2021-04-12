#pragma once
#include"AbsFuncBlock.h";
#include"AbsFuncReducer.h";
#include<queue>
#include<string>
namespace FuncDre {
	/*
	*	���ߺ�����������
	*	�����������������ַ���ת�ɺ�����Ĺ��̡�
	*
	*	������ַ���Ӧ���������¹���
	*	1.	�ϸ�����˺���ȫ�ԡ�
	*	2.	�����ȼ��г��ֵ����ȼ��ϸ�����š�
	*
	*	ʵ�ֵĹ��ܣ�
	*	1.	������֮�󷵻�һ���ܺ����顣
	*	2.	�����ܶ�����ӵ�м��غͼ���-������
	*		(�������)��
	*	3.	���ڸ������Ķ�ȡ�����򻯴���һ�С�
	* 
	*	��Ϊ����Ҫ����new�����пռ������ջ��
	*	��
	* 
	*	���Ͽ�Ĵ���
	*	1.	����ָ�ͣ��ݹ�Loader
	*	2.	��ָ�ͣ�ֱ�Ӹ�
	* 
	*/
	class AbsFuncLoader
	{

	public:

		//������պ����顣
		AbsFuncBlock*  getFinalFunc();

		//Ԥ�������ַ������أ���Ϊ��׺���ʽ�ʹ��ַ���ջ��
		void load(std::string str);

	private:

		AbsFuncBlock* finalAbsFuncBlock;//�����ܺ����顣

		std::queue<AbsFuncBlock*> conQue;//��˳�򸡵�����queue��

		std::queue<AbsFuncBlock*> comQue;//�渴�Ͽ��queue��

		std::queue<AbsFuncBlock*> bacQue;//���׺���ʽ��queue��

		std::queue<int> signQue;//��˳����ŵ�queue��

		//��һ��ת��������������ʽ�õ�˳�������С�
		std::string trans1(const std::string str);

		//�ڶ���ת������Ԥ����õ���ǳ�����Ϊ��׺���ʽ��
		void trans2();

		//������ת��������׺���ʽת��Ϊ�顣�ڵ��ϸ�ڡ�
		void trans3();

		//���ظ��ַ���Ӧ�ķ���
		int isSign(char c);

	};
}

