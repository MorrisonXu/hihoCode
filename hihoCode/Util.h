//
//  Util.h
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/5.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#ifndef hihoCode_Util_h
#define hihoCode_Util_h
#include <iostream>
#include <vector>
using namespace std;

#define DEBUG_MSG   0
#define DEBUG_INPUT 1

#pragma mark - 打印Vector
template <typename T>
void showVector(vector<T> &vec, int l, int r, string seperator) {
    for (int i = l; i <= r; i++)
        cout << vec[i] << seperator;
    cout << endl;
}

template <typename T>
void showVector(vector<T> &vec, string seperator) {
    showVector(vec, 0, (int)vec.size() - 1, seperator);
}

template <typename T>
void showVector(vector<T> &vec) {
    showVector(vec, 0, vec.size() - 1, " ");
}

#pragma mark - 交换
template <typename T>
void mySwap(T &l, T &r) {
    T tmp = l;
    l = r;
    r = tmp;
}

#endif
