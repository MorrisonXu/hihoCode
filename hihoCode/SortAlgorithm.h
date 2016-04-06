//
//  SortAlgorithm.h
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/6.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#ifndef hihoCode_SortAlgorithm_h
#define hihoCode_SortAlgorithm_h
#include "Util.h"

// 均为顺序结果
#pragma mark - 选择 / 插入 / 冒泡
template <typename T>
void sa_SelectionSort(vector<T> &vec) {
    int ptrSmall;
    for (int i = 0; i < vec.size() - 1; i++) {
        ptrSmall = i;
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[ptrSmall])
                ptrSmall = j;
        }
        mySwap(vec[ptrSmall], vec[i]);
    }
}

template <typename T>
void sa_InsertSort(vector<T> &vec) {
    for (int i = 1; i < vec.size(); i++) {
        int j = 0;
        for (; j < i && vec[j] <= vec[i]; j++);
        if (j < i) {
            int k = i;
            T tmp = vec[i];
            while (k-- >= j)
                vec[k + 1] = vec[k];
            vec[j] = tmp;
        }
    }
}

template <typename T>
void sa_BubbleSort(vector<T> &vec) {
    for (int i = 1; i < vec.size(); i++) {
        int k = i;
        while (k-- >= 0) {
            if (vec[k] > vec[k + 1])
                mySwap(vec[k], vec[k + 1]);
        }
    }
}

#pragma mark - 堆排序(Heap Sort)
// 方便分析，下标从1开始，代码中做转换
#define HEAP_INDEX_TO_VEC(a)   ((a) - 1)

template <typename T>
void heap_Heapify(vector<T> &vec, unsigned long index, unsigned long heapSize) {
    unsigned long l = index * 2;
    unsigned long r = l + 1;
    if (l > heapSize)
        return;
    if (r <= heapSize) {
        unsigned long maxIndex = index;
        maxIndex = (vec[HEAP_INDEX_TO_VEC(l)] > vec[HEAP_INDEX_TO_VEC(maxIndex)]) ? l : maxIndex;
        maxIndex = (vec[HEAP_INDEX_TO_VEC(r)] > vec[HEAP_INDEX_TO_VEC(maxIndex)]) ? r : maxIndex;
        if (maxIndex != index) {
            mySwap(vec[HEAP_INDEX_TO_VEC(maxIndex)], vec[HEAP_INDEX_TO_VEC(index)]);
            heap_Heapify(vec, maxIndex, heapSize);
        }
    } else if (l <= heapSize) {
        if (vec[HEAP_INDEX_TO_VEC(l)] > vec[HEAP_INDEX_TO_VEC(index)]) {
            mySwap(vec[HEAP_INDEX_TO_VEC(index)], vec[HEAP_INDEX_TO_VEC(l)]);
            heap_Heapify(vec, l, heapSize);
        }
    }
}

// 顺序建立最大堆，反之最小堆
template <typename T>
void heap_BuildMaxHeap(vector<T> &vec) {
    for (unsigned long i = vec.size() / 2; i > 1; i--)
        heap_Heapify(vec, i, vec.size());
}


template <typename T>
void heap_HeapSort(vector<T> &vec) {
    for (unsigned long i = vec.size(); i > 1; i--) {
        mySwap(vec[HEAP_INDEX_TO_VEC(i)], vec[HEAP_INDEX_TO_VEC(1)]);
        heap_Heapify(vec, 1, i - 1);
    }
}

template <typename T>
void sa_HeapSort(vector<T> &vec) {
    heap_BuildMaxHeap(vec);
    heap_HeapSort(vec);
}

#pragma mark - 希尔排序(Shell Sort)
template <typename T>
void sa_ShellSort(vector<T> &vec) {
    int gap = vec.size() / 2;
    while (gap >= 1) {
        if (DEBUG_MSG)
            cout << gap << endl;
        for (int loopNum = 0; loopNum < gap; loopNum++) {
            for (int i = loopNum + gap; i < vec.size(); i += gap) {
                int j = loopNum;
                for (; j < i && vec[j] <= vec[i]; j += gap);
                if (j < i) {
                    int k = i;
                    T tmp = vec[i];
                    while ((k -= gap) >= j)
                        vec[k + gap] = vec[k];
                    vec[j] = tmp;
                }
            }
            
            if (DEBUG_MSG) {
                cout << loopNum << ": ";
                showVector(vec);
            }
        }
        
        if (DEBUG_MSG)
            showVector(vec);
        gap /= 2;
    }
}

#pragma mark - 鸡尾酒排序(Shaker Sort)
template <typename T>
void shaker_BubbleSort(vector<T> &vec, int l, int r, bool l2r) {
    if (l2r) {
        for (int i = l + 1; i <= r; i++) {
            if (vec[i - 1] > vec[i])
                mySwap(vec[i - 1], vec[i]);
        }
    } else {
        for (int i = r - 1; i >= l; i--) {
            if (vec[i] > vec[i + 1])
                mySwap(vec[i], vec[i + 1]);
        }
    }
}

template <typename T>
void sa_ShakerSort(vector<T> &vec) {
    int ptrLeft = 0;
    int ptrRight = vec.size() - 1;
    while (ptrLeft <= ptrRight) {
        // left => right
        shaker_BubbleSort(vec, ptrLeft, ptrRight--, true);
        // left <= right
        shaker_BubbleSort(vec, ptrLeft++, ptrRight, false);
    }
}

#pragma mark - Quick Sort
template <typename T>
int quick_Partition(vector<T> &vec, int l, int r, int pivotIndex) {
    mySwap(vec[pivotIndex], vec[r]);
    int ptrRightStart = l;
    for (int i = l; i < r; i++) {
        if (vec[i] <= vec[r]) {
            mySwap(vec[ptrRightStart], vec[i]);
            ptrRightStart++;
        }
    }
    mySwap(vec[ptrRightStart], vec[r]);
    return ptrRightStart;
}

template <typename T>
void quick_QuickSort(vector<T> &vec, int l, int r) {
    if (DEBUG_MSG) {
        showVector(vec);
        cout << l << ", " << r << endl;
    }
    if (l >= r)
        return;
    int newPivotIndex = quick_Partition(vec, l, r, l);
    if (DEBUG_MSG)
        cout << "New Pivot: " << newPivotIndex << endl;
    quick_QuickSort(vec, l, newPivotIndex - 1);
    quick_QuickSort(vec, newPivotIndex + 1, r);
}

template <typename T>
void sa_QuickSort(vector<T> &vec) {
    quick_QuickSort(vec, 0, vec.size() - 1);
}

#pragma mark - 基数排序(Radix Sort)
#define RADIX_BASE                  10
#define RADIX_BUCKET_COUNT          10
#define RADIX_BUCKET_ID(n, radix)   (((n) / (radix)) % RADIX_BASE)

int radix_MaxDigits(vector<int> &vec) {
    int maxNum = vec[0];
    for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
        maxNum = max(maxNum, *iter);
    int count = 0;
    for (; maxNum != 0; count++, maxNum /= 10);
    return count;
}

void sa_RadixSort(vector<int> &vec) {
    int loopNum = radix_MaxDigits(vec);
    vector<int> bucketCount(RADIX_BUCKET_COUNT, 0);
    vector<int> tmp(vec.size(), 0);
    int radix = 1;
    for (int i = 0; i < loopNum; i++) {
        bucketCount.assign(RADIX_BUCKET_COUNT, 0);
        for (int j = 0; j < vec.size(); bucketCount[RADIX_BUCKET_ID(vec[j], radix)]++, j++);
        // 为了保证稳定排序: 如对于相同个位数3的(73, 53), 一轮排完仍为(73, 53)
        for (int j = 1; j < RADIX_BUCKET_COUNT; j++)
            bucketCount[j] += bucketCount[j - 1];
        // 为了保证稳定排序, 这里必须反向遍历, 将一轮结果放入tmp中
        for (int j = vec.size() - 1; j >= 0; j--)
            tmp[--bucketCount[RADIX_BUCKET_ID(vec[j], radix)]] = vec[j];
        vec = tmp;
        radix *= 10;
    }
}

#pragma mark - 合并排序(Merge Sort)
template <typename T>
void merge_MergeSortRecursive(vector<T> &vec, vector<T> &res, int l, int r) {
    if (l >= r)
        return;
    
    if (DEBUG_MSG)
        showVector(vec, l, r);
    
    int m = (l + r) / 2;
    merge_MergeSortRecursive(vec, res, l, m);
    merge_MergeSortRecursive(vec, res, m + 1, r);
    int ptrLeft = l;
    int ptrRight = m + 1;
    int ptrRes = l;
    while (ptrLeft <= m && ptrRight <= r)
        res[ptrRes++] = (vec[ptrLeft] < vec[ptrRight]) ? vec[ptrLeft++] : vec[ptrRight++];
    while (ptrLeft <= m)
        res[ptrRes++] = vec[ptrLeft++];
    while (ptrRight <= r)
        res[ptrRes++] = vec[ptrRight++];
    
    if (DEBUG_MSG)
        showVector(res, l, r);
    for (int i = l; i <= r; i++)
        vec[i] = res[i];
}

template <typename T>
void sa_MergeSort(vector<T> &vec) {
    vector<T> res(vec.size(), 0);
    merge_MergeSortRecursive(vec, res, 0, vec.size() - 1);
}

#endif
