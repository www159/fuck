#pragma once
#include"AbsFuncBlock.h";
#include"AbsFuncReducer.h";
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
	*/
	class AbsFuncLoader
	{

	pirvate:

		AbsFuncBlock* finalAbsFuncBlock;
	};
}

