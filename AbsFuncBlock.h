#pragma once

#include<vector>
namespace FuncDre {
#define CONBLOCK        0			//常数，无复合运算
#define BASBLOCK        1			//代表x的函数块，无复合运算
#define ADDBLOCK        2			//加法块，需要引入一个函数容器
#define MINBLOCK        3			//减法块
#define MULTBLOCK       4			//乘法块
#define DIVBLOCK        5			//除法块
#define CONPWRBLOCK     6			//幂函数块
#define BASPWRBLOCK     7			//指数函数块
#define GNLPWRBLOCK     8			//幂指函数块
#define LOGBLOCK        9			//对数函数块
#define TRIBLOCK        10			//三角函数块
#define ARCBLOCK        11			//反三角函数块

	/*
	*抽象函数块。
	*没多大作用，只是存容器方便。
	*可以囊括常数块和基本块
	*/
	class AbsFuncBlock
	{
	public:

		virtual ~AbsFuncBlock();

		int getTag();

		void setTag();

	protected:
		//该块的类型，是基块还是运算块
		int tag = -1;
		/**
		* 函数容器，是一个线性容器。
		* 如果复合，那么存的是函数作用域内的子块。
		* 如果是幂指函数，还需要分类，还需要继承。
		*/
	};



	/*
	* 常数函数块，拥有自己的常数值
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
	* 通用运算函数块，只有一组作用域。
	*/
	class OperFuncBlock:public AbsFuncBlock {

	public:
		~OperFuncBlock();
		
		std::vector<AbsFuncBlock*> getContainer();//外界获得作用域。
		
		void addFunc();//向作用域中增加函数。

	protected:

		std::vector<AbsFuncBlock*> FuncContainer;
	};



	/*
	* 一般函数块。
	* 需要保存两组作用域。囊括带参函数块。
	*/
	class GnlFuncBlock :public AbsFuncBlock {

	public:

		~GnlFuncBlock();

		std::vector<AbsFuncBlock> getContainer();

		void addFunc();
		
		std::vector<AbsFuncBlock*> getUpContainer();//外界获得上作用域。
		
		void addUpFunc();//向上作用域中增加函数。

	private:
		
		OperFuncBlock* BottomBlock;//下运算函数块

		OperFuncBlock* TopBlock;//上运算函数块

	};
}

