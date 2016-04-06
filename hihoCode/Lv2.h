//
//  Lv2.h
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/5.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#ifndef hihoCode_Lv2_h
#define hihoCode_Lv2_h
#include <iostream>
#include <vector>
#include "Util.h"
using namespace std;

#pragma mark - L1014
class L1014TrieNode {
public:
    char letter;
    int count;
    vector<L1014TrieNode *> children;
    
    L1014TrieNode(char c) : letter(c), count(1) {}
    L1014TrieNode(char c, int count) : letter(c), count(count) {}
    L1014TrieNode * containChild(char c);
    
    void show();
};

L1014TrieNode * L1014TrieNode::containChild(char c) {
    for (vector<L1014TrieNode *>::iterator iter = children.begin(); iter != children.end(); iter++)
        if ((*iter)->letter == c)
            return *iter;
    return NULL;
}

void L1014TrieNode::show() {
    cout << letter;
    for (vector<L1014TrieNode *>::iterator iter = children.begin(); iter != children.end(); iter++) {
        if ((*iter)->children.size() == 0)
            cout << endl;
        (*iter)->show();
    }
}

L1014TrieNode * L1014BuildTrie(vector<string> words) {
    L1014TrieNode *root = new L1014TrieNode(0, 0);
    L1014TrieNode *ptrVisitRoot;
    L1014TrieNode *ptr;
    for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
        string word = *iter;
        ptrVisitRoot = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word[i];
            ptr = ptrVisitRoot->containChild(c);
            if (ptr == NULL) {
                L1014TrieNode *newNode = new L1014TrieNode(c);
                (ptrVisitRoot->children).push_back(newNode);
                ptrVisitRoot = newNode;
            } else {
                ptr->count++;
                ptrVisitRoot = ptr;
            }
        }
    }
    return root;
}

int L1014CountPrefix(L1014TrieNode *root, string prefix) {
    L1014TrieNode *ptrVisitRoot = root;
    L1014TrieNode *ptr;
    for (int i = 0; i < prefix.length(); i++) {
        char c = prefix[i];
        ptr = ptrVisitRoot->containChild(c);
        if (ptr == NULL) {
            ptrVisitRoot = root;
            break;
        } else {
            ptrVisitRoot = ptr;
        }
    }
    return ptrVisitRoot->count;
}

void L1014SearchPrefixes(L1014TrieNode *root, vector<string> prefixes) {
    for (vector<string>::iterator iter = prefixes.begin(); iter != prefixes.end(); iter++) {
        string s = *iter;
        cout << L1014CountPrefix(root, s) << endl;
    }
}

void L1014() {
    int wordCount, prefixCount;
    string s;
    vector<string> words;
    vector<string> prefixes;
    
    cin >> wordCount;
    cin.ignore();
    for (int i = 0; i < wordCount; i++) {
        getline(cin, s);
        words.push_back(s);
    }
    
    cin >> prefixCount;
    cin.ignore();
    for (int i = 0; i < wordCount; i++) {
        getline(cin, s);
        prefixes.push_back(s);
    }
    
    L1014SearchPrefixes(L1014BuildTrie(words), prefixes);
}

#pragma mark - L1015
// Time Limit Exceeded
int L1015SearchPattern(string line, string pattern) {
    int count = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == pattern[0]) {
            int ptr = 0;
            while (++ptr < pattern.length()) {
                if (pattern[ptr] != line[i + ptr])
                    break;
            }
            if (ptr == pattern.length())
                count++;
        }
    }
    return count;
}

// Time Limit Exceeded
int L1015SearchPatternPlus(string line, string pattern) {
    int count = 0;
    int ptrNext;
    int i = 0;
    while (i < line.length()) {
        cout << i;
        ptrNext = i;
        int ptr = 0;
        do {
            if (ptr > 0 && ptrNext == i && line[i + ptr] == pattern[0])
                ptrNext = i + ptr - 1;
            if (line[i + ptr] != pattern[ptr])
                break;
        } while (++ptr < pattern.length());
        if (ptr == pattern.length())
            count++;
        i = ptrNext + 1;
    }
    cout << endl;
    return count;
}

// KMP Algorithm:
// Introduction: http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
// Generate Next[]: http://blog.csdn.net/yearn520/article/details/6729426 (Give a clue, but not the best!)
// Summary code: http://kenby.iteye.com/blog/1025599

// indexPattern:_ 0 1 2 3 4 5 6 7 8
// pattern:     _ a g c t a g c a g
// i:           0 1 2 3 4 5 6 7 8 9
// next:        0 0 0 0 0 1 2 3 1 2
// So we can use next(indexPattern) to trace back to the correct position in pattern
// For example: if we find difference at indexPattern = 8, then we should trace back to the next value of indexPattern = 7
//              the next value of indexPattern = 7 is next[indexPattern], so we trace back to next[indexPattern], and keep compare from indexPattern
vector<int> L1015GenerateNext(string pattern) {
    vector<int> next(pattern.length() + 1, 0);
    next[0] = next[1] = 0;
    int k = 0; // k = next[i-1] at first, the next value of last char, the find sub-symmetry string recursively
    for (int i = 2; i < next.size(); i++) {
        // Transformation of index, make the code more readable
        // next[i] is the next value of pattern[indexPattern]
        int indexPattern = i - 1;
        for (; k != 0 && pattern[indexPattern] != pattern[k]; k = next[k]); // k = 0 means no sub-symmetry string
        // k = 0: compare to first char, if pattern[indexPattern] == pattern[k] is true, next value becomes 1
        // k > 0: pattern[indexPattern] == pattern[k] must be true(because the end condition in for loop);
        //        So the sub-symmetry string length add 1, [0, (pattern[k]-1)] => [0, pattern[k]]
        // So, we can combine 2 conditions in 1 line
        if (pattern[indexPattern] == pattern[k]) k++;
        next[i] = k;
    }
    return next;
}

int L1015SearchPatternKMP(string line, string pattern) {
    vector<int> next = L1015GenerateNext(pattern);
    if (DEBUG_MSG)
        showVector(next);
    int count = 0;
    int ptrPattern = 0;
    int ptrLine = 0;
    while (ptrLine < line.length()) {
        // Keep searching the same char until:
        // 1. All match
        // 2. Find the difference at [ptrLine, ptrPattern]
        for (ptrPattern = next[ptrPattern]; ptrPattern < pattern.length() && line[ptrLine] == pattern[ptrPattern]; ptrLine++, ptrPattern++);
        if (ptrPattern == 0) ptrLine++;
        if (ptrPattern == pattern.length()) count++;
    }
    
    return count;
}

void L1015() {
    int N;
    string s;
    vector<string> lines;
    vector<string> patterns;
    
    if (DEBUG_INPUT) {
        N = 5;
        lines = {"HAHAHA", "WQN", "ADADADA", "BABABABABABABABABB", "ADDAADAADDAAADAAD"};
        patterns = {"HA", "WQN", "ADA", "BABABB", "DAD"};
    } else {
        cin >> N;
        cin.ignore();
        for (int i = 0; i < N; i++) {
            getline(cin, s);
            patterns.push_back(s);
            getline(cin, s);
            lines.push_back(s);
        }
    }
    
    for (int i = 0; i < N; i++) {
        cout << L1015SearchPatternKMP(lines[i], patterns[i]) << endl;
    }
}

#endif
