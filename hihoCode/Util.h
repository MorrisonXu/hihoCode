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
#define DEBUG_INPUT 0

#pragma mark - 打印Vector
template <typename T>
void showVector(vector<T> &vec) {
    for (typename vector<T>::iterator iter = vec.begin(); iter != vec.end(); iter++)
        cout << *iter << " ";
    cout << endl;
}

template <typename T>
void showVector(vector<T> &vec, int l, int r) {
    for (int i = l; i <= r; i++)
        cout << vec[i] << " ";
    cout << endl;
}

#pragma mark - 交换
template <typename T>
void mySwap(T &l, T &r) {
    T tmp = l;
    l = r;
    r = tmp;
}

#endif
