//
//  Lv1.h
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/5.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#ifndef hihoCode_Lv1_h
#define hihoCode_Lv1_h
#include "Util.h"

#pragma mark - L1000
void L1000() {
    int a, b;
    while (cin>>a>>b)
        cout << a+b << endl;
}

#pragma mark - L1039
int L1039EraseNum(string s) {
//    cout << s << ":";
    if (s.length() <= 1)
        return 0;
    if (s.length() == 2)
        return (s[0] == s[1]) ? 2 : 0;
    
    string erased = "";
    int count = 0;
    if (s[0] != s[1])
        erased += s[0];
    else
        count++;
    
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i-1] == s[i] || s[i] == s[i+1])
            count++;
        else
            erased += s[i];
    }
    if (s[s.length()-2] != s[s.length()-1])
        erased += s[s.length()-1];
    else
        count++;
    
    if (count == 0)
        return 0;
    
//    cout << count << endl;
    return count + L1039EraseNum(erased);
}

void L1039InsertABCInPos(vector<string> &vec, string s, int pos) {
    unsigned long len = s.length();
    vec.push_back(s.substr(0, pos) + "A" + s.substr(pos, len - pos));
    vec.push_back(s.substr(0, pos) + "B" + s.substr(pos, len - pos));
    vec.push_back(s.substr(0, pos) + "C" + s.substr(pos, len - pos));
    
}

vector<string> L1039GenerateCandidates(string s) {
    vector<string> res;
    for (int i=0; i<=s.length(); i++)
        L1039InsertABCInPos(res, s, i);
    return res;
}

void L1039() {
    int n;
    string s;
    vector<string> res;
    int maxScore = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        res = L1039GenerateCandidates(s);
        for (vector<string>::iterator iter = res.begin(); iter != res.end(); iter++) {
            int score = L1039EraseNum(*iter);
//            cout << *iter << ":" << score << endl;
            maxScore = max(maxScore, score);
        }
        cout << maxScore << endl;
        maxScore = 0;
    }
}

#pragma mark - L1051
int L1051FindLongestDays(vector<int> notDuty, int N, int M) {
    if (M >= N)
        return 100;
    
    int maxDays = notDuty[M] - 1;
    for (int i = M + 1; i < N; i++) {
//        cout << notDuty[i] << " - " << notDuty[i - M - 1] << endl;
        maxDays = max(maxDays, notDuty[i] - notDuty[i - M - 1] - 1);
    }
//    cout << 100 << " - " << notDuty[N - M - 1] << endl;
    maxDays = max(maxDays, 100 - notDuty[N - M - 1]);
    return maxDays;
}

void L1051() {
    int n;
    int N, M;
    vector<int> notDuty;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> N >> M;
        
        for (int j = 0; j < N; j++) {
            int tmp;
            cin >> tmp;
            notDuty.push_back(tmp);
        }
        cout << L1051FindLongestDays(notDuty, N, M) << endl;
        notDuty.clear();
    }
}

#pragma mark - L1082
string L1082ReplaceMarshtomp(string s, string marshtomp, string replaceStr, int posMarshtompBegin) {
    string left = s.substr(0, posMarshtompBegin);
    unsigned long rightBegin = posMarshtompBegin + marshtomp.length();
    string right = s.substr(rightBegin, s.length() - rightBegin);
    return left + replaceStr + right;
}

string L1082FindAndReplaceMarshtomp(string s, string marshtomp, string replaceStr) {
    int posMarshtompBegin = 0;
    int ptrMarshtomp = 0;
    string replaced = s;
    
    for (int i = 0; i < s.length(); i++) {
        if (tolower(s[i]) == marshtomp[ptrMarshtomp]) {
            if (0 == (ptrMarshtomp++))
                posMarshtompBegin = i;
        } else {
            ptrMarshtomp = 0;
            posMarshtompBegin = 0;
        }
        
        if (ptrMarshtomp == marshtomp.length() - 1) {
            replaced = L1082ReplaceMarshtomp(s, marshtomp, replaceStr, posMarshtompBegin);
            replaced = L1082FindAndReplaceMarshtomp(replaced, marshtomp, replaceStr);
            break;
        }
    }
    return replaced;
}

void L1082() {
    string s;
    string marshtomp = "marshtomp";
    string replaceStr = "fjxmlhx";
    while (getline(cin, s)) {
        cout << L1082FindAndReplaceMarshtomp(s, marshtomp, replaceStr) << endl;
    }
}

#pragma mark - L1094
vector<string> L1094RotatePosClockwise(vector<string> pos) {
    vector<string> res;
    string tmp = "";
    res.push_back(tmp + pos[2][0] + pos[1][0] + pos[0][0]);
    tmp = "";
    res.push_back(tmp + pos[2][1] + pos[1][1] + pos[0][1]);
    tmp = "";
    res.push_back(tmp + pos[2][2] + pos[1][2] + pos[0][2]);
    return res;
}

bool L1094CheckPosWithNorth(vector<string> map, vector<string> posNorth, int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (map[x-1+i][y-1+j] != posNorth[i][j])
                return false;
        }
    }
    return true;
}

bool L1094CheckPos(vector<string> map, vector<string> pos, int x, int y) {
    vector<string> posRotate1 = L1094RotatePosClockwise(pos);
    vector<string> posRotate2 = L1094RotatePosClockwise(posRotate1);
    vector<string> posRotate3 = L1094RotatePosClockwise(posRotate2);
    
    return L1094CheckPosWithNorth(map, pos, x, y) ||
    L1094CheckPosWithNorth(map, posRotate1, x, y) ||
    L1094CheckPosWithNorth(map, posRotate2, x, y) ||
    L1094CheckPosWithNorth(map, posRotate3, x, y);
}

void L1094LoopThrough(vector<string> map, vector<string> pos, int N, int M) {
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            if (map[i][j] != pos[1][1]) // 判断中心点
                continue;
            if (L1094CheckPos(map, pos, i, j))
                cout << i + 1 << " " << j + 1 << endl;
        }
    }
}

void L1094() {
//    int N = 8;
//    int M = 8;
//    vector<string> map = {
//        "...HSH..",
//        "...HSM..",
//        "...HST..",
//        "...HSPP.",
//        "PPGHSPPT",
//        "PPSSSSSS",
//        "..MMSHHH",
//        "..MMSH.."
//    };
//    vector<string> pos = {
//        "SSS",
//        "SHG",
//        "SH."
//    };
    int N, M;
    string s;
    vector<string> map;
    vector<string> pos;
    cin >> N >> M;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        getline(cin, s);
        map.push_back(s);
    }
    
    for (int i = 0; i < 3; i++) {
        getline(cin, s);
        pos.push_back(s);
    }

    L1094LoopThrough(map, pos, N, M);
}

#endif
