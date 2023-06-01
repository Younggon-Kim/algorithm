//https://www.acmicpc.net/problem/21941
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void solve() {
    string org_str;
    int m;
    cin >> org_str >> m;

    vector<int> scores(org_str.length(), 0);

    unordered_map<char, unordered_map<string, int>> substr_map; //key : 첫 문자, value : {문자열 : 점수}
    for(int i = 0; i < m; i++) {
        string s;
        int score;
        cin >> s >> score;
        if(s.length() > score) continue; //문자열 길이보다 점수가 낮으면, 제외시킴
        substr_map[s[0]][s] = score;
    }

    for(int i = 0; i < org_str.length(); i++) {
        //현재 index 의 점수 업데이트 => 이전 index 점수+1 과 비교해서 큰 값으로
        scores[i] = max(scores[i], i == 0 ? 1 : scores[i - 1] + 1);

        char first_c = org_str[i];
        if(substr_map[first_c].empty()) continue; // 일치하는 첫번째 문자가 없다면

        for(auto &p : substr_map[first_c]) {
            int len = p.first.length();
            if(i + len - 1 > scores.size()) continue; // 부분 문자열이 너무 길면

            if(org_str.substr(i, len) != p.first) continue; // 부분 문자열이 일치하지 않으면

            int start = i;
            int end = i + len - 1;
            int prev_score = start == 0 ? 0 : scores[start - 1]; //이전 index 점수
            //3개 중 큰 값으로 => (1)현재 index 점수, (2)현재 index 점수 + 문자열 길이 - 1, (3)이전 index 점수 + 문자열 점수
            scores[end] = max(scores[end], max(scores[start] + len - 1, prev_score + p.second));
        }
    }

    printf("%d\n", scores.back());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}