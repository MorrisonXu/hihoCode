//
//  main.cpp
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/5.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Lv1.h"
#include "Lv2.h"
#include "SortAlgorithm.h"

int main(int argc, const char * argv[]) {
    vector<int> vecToSort = {70, 80, 31, 37, 10, 1, 48, 60, 33, 80};
    sa_MergeSort(vecToSort);
    showVector(vecToSort);
    
    system("pause");
    return 0;
}