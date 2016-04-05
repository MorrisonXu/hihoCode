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
int L1015SearchPattern(string line, string pattern) {
    int ptrPattern = 0;
    int ptrPatternInLine = 0;
    int count = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == pattern[ptrPattern]) {
            ptrPatternInLine = i;
            for (int j = 0; j < pattern.length(); j++) {
                if (pattern[++ptrPattern] == line[++ptrPatternInLine] && ptrPattern == pattern.length())
                    count++;
            }
        }
    }
    return count;
}

void L1015() {
    int N = 5;
    vector<string> lines = {"HAHAHA", "BABABABABABABABABB"};
    vector<string> patterns = {"HA", "BABABB"};
    
    for (int i = 0; i < N; i++) {
        L1015SearchPattern(lines[i], patterns[i]);
    }
}

#endif
