//
//  Microsorft.h
//  hihoCode
//
//  Created by 徐佳俊 on 16/4/6.
//  Copyright (c) 2016年 morrison. All rights reserved.
//

#ifndef hihoCode_Microsorft_h
#define hihoCode_Microsorft_h
#include "Util.h"
#include <string.h>
#include <bitset>

#pragma mark - Q1
int q1_Top(int a, int b) {
    double tmp = a / (double)b;
    if (tmp - (int)tmp > 0)
        return tmp + 1;
    else
        return tmp;
}

int q1_MaxFontSize(int N, int W, int H, int P, vector<int> &A) {
    int fontSize = 0;
    int limit = min(W, H);
    while ((++fontSize) <= limit) {
        int charPerLine = W / fontSize;
        int linePerPage = H / fontSize;
        int sumLines = 0;
        for (vector<int>::iterator iter = A.begin(); iter != A.end(); iter++)
            sumLines += q1_Top(*iter, charPerLine);
        if (q1_Top(sumLines, linePerPage) > P)
            break;
    }
//    cout << fontSize << endl;
    return fontSize - 1;
}

void ms_Q1() {
    int count;
    
    int n, w, h, p;
    
    vector<int> N;
    vector<int> W;
    vector<int> H;
    vector<int> P;
    vector<vector<int>> A;
    
    cin >> count;
    for (int i = 0; i < count; i++) {
        cin >> n >> p >> w >> h;
        N.push_back(n);
        W.push_back(w);
        H.push_back(h);
        P.push_back(p);
        vector<int> Ai(n, 0);
        for (int j = 0; j < n; j++) {
            cin >> Ai[j];
        }
        A.push_back(Ai);
    }
    for (int i = 0; i < count; i++) {
        cout << q1_MaxFontSize(N[i], W[i], H[i], P[i], A[i]) << endl;
    }
}

#pragma mark - Q2
string q2_IP2Binary(string IPCode) {
    string binaryCode = "";
    string tmp = IPCode;
    for (int i = 0; i < 3; i++) {
        int sep = (int)tmp.find(".");
        string num = tmp.substr(0, sep);
        tmp = tmp.substr(sep + 1, tmp.length() - sep);
        bitset<8> x(stoi(num));
        binaryCode += x.to_string();
    }
    bitset<8> x(stoi(tmp));
    binaryCode += x.to_string();
    return binaryCode;
}

string q2_GenPrefix(string IP) {
    string res = "";
    
    int slashPos = (int)IP.find("/");
    string IPCode = (slashPos == string::npos) ? IP : IP.substr(0, slashPos);
    string tmp = IPCode;
    res += q2_IP2Binary(IPCode);
//    cout << res << endl;
    if (slashPos != string::npos) {
        string mask = IP.substr(slashPos + 1, IP.length() - slashPos);
        int maskNum = stoi(mask);
        res = res.substr(0, maskNum);
    }
    return res;
}

void ms_Q2() {
    int N, M;
//    vector<string> rules;
//    vector<string> reqs;
    string s;
    
//    cin >> N >> M;
//    cin.ignore();
//    for (int i = 0; i < N; i++) {
//        getline(cin, s);
//        rules.push_back(s);
//    }
//    for (int i = 0; i < M; i++) {
//        getline(cin, s);
//        reqs.push_back(s);
//    }
    
    N = 5;
    M = 5;
    vector<string> rules = {"allow 1.2.3.4/30", "deny 1.1.1.1", "allow 127.0.0.1", "allow 123.234.12.23/3", "deny 0.0.0.0/0"};
    vector<string> reqs = {"1.2.3.4", "1.2.3.5", "1.1.1.1", "100.100.100.100", "219.142.53.100"};
    
    vector<bool> operations;
    vector<string> forbiddenSubstr;
    for (int i = 0; i < N; i++) {
        string rule = rules[i];
        int spacePos = (int)rule.find(" ");
        string operation = rule.substr(0, spacePos);
        operations.push_back("allow" == operation);
        string forbiddenIP = rule.substr(spacePos + 1, rule.length() - spacePos);
//        cout << q2_GenPrefix(forbiddenIP) << "\t" << operation << endl;
        forbiddenSubstr.push_back(q2_GenPrefix(forbiddenIP));
    }
    
    for (int i = 0; i < M; i++) {
        string req = reqs[i];
        string binaryCode = q2_IP2Binary(req);
//        cout << binaryCode << endl;
        
        bool res = true;
        for (int j = 0; j < N; j++) {
            if (binaryCode.substr(0, forbiddenSubstr[j].length()) == forbiddenSubstr[j]) {
                res = operations[j];
                break;
            }
        }
        if (res)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

#pragma mark - Q3
int q3_Walk(vector<string> maze, int n) {
    int x = 0;
    int y = 0;
    int offsetX = 0;
    int offsetY = 1;
    int obstacleTime = 0;
    
    int width = (int)maze[0].length();
    int height = (int)maze.size();
    int sum = width + height - 1;
    for (int i = 0; i < sum; i++) {
        cout << x << y << endl;
        if (x == width - 1 && y == height - 1)
            return obstacleTime;
        if (x == width - 1) {
            offsetX = 1;
            offsetY = 0;
        }
        if (y == height - 1) {
            offsetX = 0;
            offsetY = 1;
        }
        if (maze[x][y] == 'b') {
            if ((--n) < 0) {
                if (x < width - 1)
                    offsetX = 1 - offsetX;
                if (y < height - 1)
                    offsetY = 1 - offsetY;
                obstacleTime++;
            }
        }
        x += offsetX;
        y += offsetY;
    }
    return obstacleTime;
    
//    for (; maze[x][y] == '.' && x < maze.size() && y < maze[0].length(); x += offsetX, y += offsetY);
//    if (maze[x][y] == 'b') {
//        obstacleTime++;
//        if (obstacleTime > n)
//            return;
//    }
}

void ms_Q3() {
    int N, M;
    string s;
//    vector<string> maze;
//    cin >> N >> M;
//    cin.ignore();
//    for (int i = 0; i < N; i++) {
//        getline(cin, s);
//        maze.push_back(s);
//    }
    N = 4;
    M = 8;
    vector<string> maze = {"....bb..", "........", ".....b..", "...bb..."};
    for (int i = 0; i < N * M; i++) {
        cout << "Round " << i << endl;
        if (q3_Walk(maze, i) == 0) {
            cout << "Obs " << i << endl;
            break;
        }
    }
}

#endif
