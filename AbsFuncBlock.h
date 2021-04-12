#pragma once

#include<list>
namespace FuncDre {
#define DEAFULTTAG     -1			//Ĭ�ϱ�ǩ�����ڳ�ʼ��
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
#define SIN				11			//���Ǻ����󵼷���
#define COS				12			//����
#define TAN				13			//����
#define ARCBLOCK        14			//�����Ǻ����飬�ݲ����룬����ϸ��

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

		void setTag(int tag);

	protected:
		//�ÿ�����ͣ��ǻ��黹�������
		int tag = DEAFULTTAG;
		/**
		*	������������һ������������
		*	������ϣ���ô����Ǻ����������ڵ��ӿ顣
		*	�������ָ����������Ҫ���࣬����Ҫ�̳С�
		*/
	};



	/*
	*	���������飬ӵ���Լ��ĳ���ֵ
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
	*	ͨ�����㺯���飬ֻ��һ��������
	*	���ݽṹ������֧�ֿ���ɾ������
	*/
	class OperFuncBlock:public AbsFuncBlock {

	public:

		OperFuncBlock();

		~OperFuncBlock();
		
		std::list<AbsFuncBlock*>* getContainer();//�����������
		
		void addFunc(AbsFuncBlock* absFuncBlock);//�������������Ӻ�����

	protected:

		std::list<AbsFuncBlock*>* FuncContainer;

	};



	/*
	* һ�㺯���顣
	* ��Ҫ���������������������κ����顣
	*/
	class GnlFuncBlock :public AbsFuncBlock {

	public:

		GnlFuncBlock();

		~GnlFuncBlock();

		std::list<AbsFuncBlock*>* getBottomContainer();

		void addBottomFunc(AbsFuncBlock* absFuncBlcok);
		
		std::list<AbsFuncBlock*>* getTopContainer();//�������������
		
		void addTopFunc(AbsFuncBlock* absFuncBlock);//���������������Ӻ�����

	private:
		
		OperFuncBlock* BottomBlock;//�����㺯����

		OperFuncBlock* TopBlock;//�����㺯����

	};
}

