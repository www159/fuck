#pragma once

#include<vector>
namespace FuncDre {
#define CONBLOCK        0			//�������޸�������
#define BASBLOCK        1			//����x�ĺ����飬�޸�������
#define ADDBLOCK        2			//�ӷ��飬��Ҫ����һ����������
#define MINBLOCK        3			//������
#define MULTBLOCK       4			//�˷���
#define DIVBLOCK        5			//������
#define CONPWRBLOCK     6			//�ݺ�����
#define BASPWRBLOCK     7			//ָ��������
#define GNLPWRBLOCK     8			//��ָ������
#define LOGBLOCK        9			//����������
#define TRIBLOCK        10			//���Ǻ�����
#define ARCBLOCK        11			//�����Ǻ�����

	/*
	*�������顣
	*û������ã�ֻ�Ǵ��������㡣
	*��������������ͻ�����
	*/
	class AbsFuncBlock
	{
	public:

		virtual ~AbsFuncBlock();

		int getTag();

		void setTag();

	protected:
		//�ÿ�����ͣ��ǻ��黹�������
		int tag = -1;
		/**
		* ������������һ������������
		* ������ϣ���ô����Ǻ����������ڵ��ӿ顣
		* �������ָ����������Ҫ���࣬����Ҫ�̳С�
		*/
	};



	/*
	* ���������飬ӵ���Լ��ĳ���ֵ
	*/
	class ConFuncBlock :public AbsFuncBlock {

	public:

		~ConFuncBlock();

		double getNum();

		void setNum(double num);

	private:
		double num;
	};



	/*
	* ͨ�����㺯���飬ֻ��һ��������
	*/
	class OperFuncBlock:public AbsFuncBlock {

	public:
		~OperFuncBlock();
		
		std::vector<AbsFuncBlock*> getContainer();//�����������
		
		void addFunc();//�������������Ӻ�����

	protected:

		std::vector<AbsFuncBlock*> FuncContainer;
	};



	/*
	* һ�㺯���顣
	* ��Ҫ���������������������κ����顣
	*/
	class GnlFuncBlock :public AbsFuncBlock {

	public:

		~GnlFuncBlock();

		std::vector<AbsFuncBlock> getContainer();

		void addFunc();
		
		std::vector<AbsFuncBlock*> getUpContainer();//�������������
		
		void addUpFunc();//���������������Ӻ�����

	private:
		
		OperFuncBlock* BottomBlock;//�����㺯����

		OperFuncBlock* TopBlock;//�����㺯����

	};
}

