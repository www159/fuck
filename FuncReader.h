#pragma once
#include "BasFuncBlock.h"
#include<vector>
#include<queue>
#include<stack>
namespace FuncReader {
	using namespace BasFuncBlock;
	/// <summary>
	/// ͨ�ú�����д����֧�ֽ�һ���ַ�������ɺ�����
	/// ���ݺ�����ָ���������������������Ǻ����������Ǻ�����
	/// ֧�ָ��Ϻ����Ķ���
	/// 
	/// ���Ϻ�����tag֧�����롣
	/// </summary>
	class GnlFuncReader {
#define LINC 30
#define RINC 31
#define COMB 13
#define NORM -1
	public:
			/// <summary>
			/// ���Է��룬��������װ�ɿ��ɵ�Ԫ�顣
			/// ��������׺���ʽ��
			/// �����ڲ���������������ͷ��
			/// ��һ������׺���ʽת�ɺ�׺���ʽ��
			/// �ڶ�������׺���ʽ������ܺ����顣
			/// </summary>
			/// <param name="s">������ʽ</param>
		void load(std::string s);

		AbsFuncBlock* getAfb();
	private:
		int end;
		/// <summary>
		/// ���ڴ���׺���ʽ�ļ�ʽ���൱�ڰѺ������ڳɿո�
		/// </summary>
		std::vector<int> ecde;
		/// <summary>
		/// que:    ���ڴ���׺���ʽ˳��ĺ�����Ԫ�顣
		/// bacQue: ���ڴ�ź�׺���ʽ
		/// </summary>
		std::queue<AbsFuncBlock*> que, bacQue;
		//�ܺ����顣
		AbsFuncBlock* Afb = NULL;
		/// <summary>
		/// ����ַ��ж��Ƿ��������
		/// </summary>
		/// <param name="c">:�����ַ�</param>
		/// <returns>true:�������</returns>
		/// 
		int isSign(char c);
		/// <summary>
		/// �жϷ������ȼ���С
		/// </summary>
		/// <param name="x">�����</param>
		/// <param name="y">�����</param>
		/// <returns>true: x�����ȼ�С��y</returns>
		bool isSmaller(int x, int y);
		/// <summary>
		/// �жϸÿ��ɺ������Ƿ��Ǹ��Ϻ���
		/// </summary>
		/// <param name="s">�����ַ���</param>
		/// <param name="p">����λ��</param>
		/// <returns>true �Ǹ��Ϻ���������ݵ�pwr</returns>
		int isSpeFunc(std::string s, int p);
		/// <summary>
		/// ����׺���ʽת��Ϊ��׺���ʽ
		/// </summary>
		void trans1();
		/// <summary>
		/// ���ݺ�׺���ʽ���ɺ�����Ԫ
		/// </summary>
		void trans2();
		/// <summary>
		 /// ������������
		 /// </summary>
		 /// <param name="tag">��ʶ��</param>
		 /// <param name="afb1">�����ӿ�1</param>
		 /// <param name="afb2">�����ӿ�2</param>
		 /// <returns>��Ϻ�����</returns>
		AbsFuncBlock* BlockGenr(int tag, AbsFuncBlock* afb1, AbsFuncBlock* afb2);
	};
}