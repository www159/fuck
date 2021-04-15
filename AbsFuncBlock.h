#pragma once

#include<list>
#include"Hashable.h"
#include"TransForm.h"
namespace FuncDre {
#define DEFAULTTAG     -1			//默认标签，用于初始化
#define CONBLOCK        0			//常数，无复合运算
#define BASBLOCK        1			//代表x的函数块，无复合运算
#define ADDBLOCK        2			//加法块，需要引入一个函数容器，无减法块。
#define MULTBLOCK       4			//乘法块
#define DIVBLOCK        5			//除法块
#define CONPWRBLOCK     6			//幂函数块
#define BASPWRBLOCK     7			//指数函数块
#define GNLPWRBLOCK     8			//幂指函数块
#define LOGBLOCK        9			//对数函数块
#define TRIBLOCK        10			//三角函数块
#define SIN				11			//三角函数求导法则
#define COS				12			//余弦
#define TAN				13			//正切
#define ARCBLOCK        14			//反三角函数块，暂不加入，后续细分

	/*
	*抽象函数块。
	*没多大作用，只是存容器方便。
	*可以囊括常数块和基本块
	*/
	class AbsFuncBlock: public Hashable
	{
	public:

		virtual ~AbsFuncBlock();

		int hashCode();

		int getTag();

		void setTag(int tag);

	protected:
		
		int tag = DEFAULTTAG;//该块的类型，是基块还是运算块

	};



	/*
	*	常数函数块，拥有自己的常数值
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
	*	通用运算函数块，只有一组作用域。
	*	数据结构是链表，支持快速删除操作
	*/
	class OperFuncBlock:public AbsFuncBlock {

	public:

		OperFuncBlock();

		~OperFuncBlock();

		int hashCode();

		//外界获得作用域。
		std::list<AbsFuncBlock*>* getContainer();

		//向作用域中增加函数。
		void addFunc(AbsFuncBlock* absFuncBlock);

	protected:

		std::list<AbsFuncBlock*>* FuncContainer;

	};



	/*
	* 一般函数块。
	* 需要保存两组作用域。囊括带参函数块。
	*/
	class GnlFuncBlock :public AbsFuncBlock {

	public:

		GnlFuncBlock();

		~GnlFuncBlock();

		int hashCode();

		std::list<AbsFuncBlock*>* getBottomContainer();

		void addBottomFunc(AbsFuncBlock* absFuncBlcok);
		
		//外界获得上作用域。
		std::list<AbsFuncBlock*>* getTopContainer();
		
		//向上作用域中增加函数。
		void addTopFunc(AbsFuncBlock* absFuncBlock);

	private:
		
		OperFuncBlock* BottomBlock;//下运算函数块

		OperFuncBlock* TopBlock;//上运算函数块

	};
}

