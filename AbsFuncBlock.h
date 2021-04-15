#pragma once

#include<list>
#include"Hashable.h"
#include"TransForm.h"
namespace FuncDre {
#define DEFAULTTAG     -1			//Ĭ�ϱ�ǩ�����ڳ�ʼ��
#define CONBLOCK        0			//�������޸�������
#define BASBLOCK        1			//����x�ĺ����飬�޸�������
#define ADDBLOCK        2			//�ӷ��飬��Ҫ����һ�������������޼����顣
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
	class AbsFuncBlock: public Hashable
	{
	public:

		virtual ~AbsFuncBlock();

		int hashCode();

		int getTag();

		void setTag(int tag);

	protected:
		
		int tag = DEFAULTTAG;//�ÿ�����ͣ��ǻ��黹�������

	};



	/*
	*	���������飬ӵ���Լ��ĳ���ֵ
	*/
	class ConFuncBlock :public AbsFuncBlock {

	public:

		~ConFuncBlock();

		int hasCode();

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

		int hashCode();

		//�����������
		std::list<AbsFuncBlock*>* getContainer();

		//�������������Ӻ�����
		void addFunc(AbsFuncBlock* absFuncBlock);

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

		int hashCode();

		std::list<AbsFuncBlock*>* getBottomContainer();

		void addBottomFunc(AbsFuncBlock* absFuncBlcok);
		
		//�������������
		std::list<AbsFuncBlock*>* getTopContainer();
		
		//���������������Ӻ�����
		void addTopFunc(AbsFuncBlock* absFuncBlock);

	private:
		
		OperFuncBlock* BottomBlock;//�����㺯����

		OperFuncBlock* TopBlock;//�����㺯����

	};
}

