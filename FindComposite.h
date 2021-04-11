#pragma once
#include <iostream>
#include <regex>
#include <string>

using namespace std;

//aeg: string that splited by ' ', e.g. A(x) + B(x) -> A(x)\n B(x)
void FindComposite(string funcs) {
    string str(funcs);

    regex e(" \\+ ");

    sregex_token_iterator pos(str.cbegin(), str.cend(), e, -1); // 定义regex_token_iterator
    sregex_token_iterator end; //序列结束

    for (; pos != end; pos++) {
        cout << *pos << endl;
    }
}