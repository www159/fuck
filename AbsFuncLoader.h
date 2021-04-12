#pragma once
#include"AbsFuncBlock.h";
#include"AbsFuncReducer.h";
#include<queue>
#include<string>
namespace FuncDre {
	/*
	*	抽线函数加载器。
	*	函数加载器作用在字符串转成函数块的过程。
	*
	*	输入的字符串应当满足以下规则：
	*	1.	严格满足乘号完全性。
	*	2.	高优先级中出现低优先级严格加括号。
	*
	*	实现的功能：
	*	1.	加载完之后返回一个总函数块。
	*	2.	化简功能独立。拥有加载和加载-化简功能
	*		(方便测试)。
	*	3.	对于浮点数的读取，正则化处理一切。
	* 
	*	因为不需要反复new，队列空间管理交给栈处
	*	理。
	* 
	*	复合块的处理：
	*	1.	非幂指型，递归Loader
	*	2.	幂指型，直接刚
	* 
	*/
	class AbsFuncLoader
	{

	public:

		//获得最终函数块。
		AbsFuncBlock*  getFinalFunc();

		//预处理。从字符串加载，化为中缀表达式和存字符的栈。
		void load(std::string str);

	private:

		AbsFuncBlock* finalAbsFuncBlock;//最终总函数块。

		std::queue<AbsFuncBlock*> conQue;//存顺序浮点数的queue。

		std::queue<AbsFuncBlock*> comQue;//存复合块的queue。

		std::queue<AbsFuncBlock*> bacQue;//存后缀表达式的queue。

		std::queue<int> signQue;//存顺序符号的queue。

		//第一次转化，利用正则表达式得到顺序常数队列。
		std::string trans1(const std::string str);

		//第二次转化，将预处理得到的浅层抽象化为后缀表达式。
		void trans2();

		//第三次转化，将后缀表达式转化为块。亿点点细节。
		void trans3();

		//返回该字符对应的符号
		int isSign(char c);

	};
}

