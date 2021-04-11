// fuck.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include "FuncReader.h"
#include "FIndComposite.h"
using namespace FuncReader;
int main() {
    FindComposite("x - A(x) + ln(x) + (x+y)*100*(x/y)^100");
}
