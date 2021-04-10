#pragma once
#include<string>
#include"BasFunc.h"
namespace BasFuncBlock {
	using namespace BasFunc;
	/// <summary>
	/// 基本抽象函数块。函数块是一个二元组。
	/// 这与后续的复合函数块相互区别。
	/// 二元组的连接符号为加，减，乘，除。
	/// 二元组的组合可以是：函数块，函数块。
	/// 单项函数不能被二元组包括，但可以被一元组包括。
	/// 
	/// TODO：后续加入复合函数块。
	/// </summary>
	class AbsFuncBlock {
#define UNIT 8
#define MULT 21
#define ADD  10
#define DIV  20
#define MINU 11
	public:
		virtual ~AbsFuncBlock() {};

		virtual void dt() = 0;

		virtual std::string rtStr() = 0;
		/// <summary>
		/// 复制函数
		/// </summary>
		/// <returns>该函数块的复制对象</returns>
		virtual AbsFuncBlock* copy() = 0;

		void setTag(int t);
		/// <summary>
		/// 初始化函数块系数为1
		/// </summary>
		/// <param name="afb0">左函数块</param>
		/// <param name="afb1">右函数块</param>
		virtual void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1);

		int getTag();
		/// <summary>
		/// 是否为单元
		/// </summary>
		/// <returns>true 是单元</returns>
		bool isUnit();

		bool isNorm();

		bool isZero();

		bool isMult();

		double getLparam();

		void setLparam(double s);

		AbsFuncBlock* setMult(AbsFuncBlock* mfb);
		/// <summary>
		/// 判断是否为空函数或0函数。
		/// 如果是0函数则转变为空函数
		/// </summary>
		/// <param name="afb">待判断函数</param>
		/// <returns>true: 该函数为空函数</returns>
		static bool isExist(AbsFuncBlock* afb);

	protected:
		/// <summary>
		/// 通过标识符向下造型
		/// </summary>
		int tag;

		bool isNor = false;

		bool isZer = false;

		bool isMul = false;

		AbsFuncBlock* afb[2] = {NULL};

		double lparam;

		/// <summary>
		/// 用于将乘法块造型为加法块。
		/// </summary>
		/// <param name="mfb">乘法块</param>
		/// <returns>经过造型的乘法块</returns>
	};
	/**************************************************************************/
	/// <summary>
	/// 加法函数块和减法函数块合并
	/// </summary>
	class AddFuncBlock :public AbsFuncBlock {
	public:
		~AddFuncBlock();
		/// <summary>
		/// 加法不需要参数合并
		/// </summary>
		/// <param name="afb0"></param>
		/// <param name="afb1"></param>
		void load(AbsFuncBlock* afb0, AbsFuncBlock* afb1);

		void dt();

		std::string rtStr();
		/// <summary>
		/// 对块进行复制
		/// </summary>
		/// <returns>被复制的块</returns>
		AbsFuncBlock* copy();
		
	};
	/**************************************************************************/
	/// <summary>
	/// 乘法函数块，因为其求导最终转化为一般加法式，
	/// 因此需要借助外层二元组进行删改。
	/// </summary>
	class MultFuncBlock :public AbsFuncBlock {
	public:

		MultFuncBlock();

		~MultFuncBlock();
		/// <summary>
		/// 乘法单元求导，需要外部求导造型成加法单元
		/// 更新两个子单元
		/// </summary>
		void dt();

		std::string rtStr();

		AbsFuncBlock* copy();
		//TODO 增加对0判断

};
	/**************************************************************************/

	/// <summary>
	/// 幂指函数块，史上最烦的函数出现了。
	/// </summary>
	class PwrFuncBlock :public AbsFuncBlock {
	public:
		~PwrFuncBlock();

		void dt();

		std::string rtStr();

		void load(std::string s);

		AbsFuncBlock* copy();
	};
	/**************************************************************************/
	/// <summary>
	/// 单元块
	/// 函数块与函数元的交流接口
	/// </summary>
	class UnitFuncBlock : public AbsFuncBlock {


#define PWR 1
#define IND 2
#define ARI 3
#define TRI 4

#define ART 5


	public:

		~UnitFuncBlock();

		void dt();

		std::string rtStr();
		/// <summary>
		/// 读写头保证输入的函数为带参单项基本初等函数。
		/// </summary>
		/// <param name="s">读入字符串</param>
		void load(std::string s);

		AbsFuncBlock* copy();

	private:

		double str2d(std::string s);
		std::string ridz(std::string s);
		std::string d2str(double x);
		bool isNum(std::string s);
	};
	/**************************************************************************/
	/// <summary>
	/// 没啥卵用的类，只是用来给读写头用来存符号的。
	/// </summary>
	class NoneFuncBlock :public AbsFuncBlock {
	public:

		~NoneFuncBlock();

		void dt();

		std::string rtStr();

		void load(std::string);

		AbsFuncBlock* copy();

	};
}
