# Description
C++ 파일을 빌드하고 테스트 입력 파일들을 자동으로 실행하여 정답과 실행 결과를 비교하는 스크립트

## 기본 설정
- 빌드하는 파일 : ./main.cc
- tc 경로 : ./tc
- input tc 파일 이름 : ./tc/*.in
- output tc 파일 이름 : ./tc/*.out
- 실행 파일 : ./a.out
- 실행 결과 경로 : ./output-<datetime>
- 실행 결과 diff 파일 : ./output-<datetime>/*.diff
- 실행 결과 파일은 ./output-<datetime>/*.out 으로 생성되지만, diff 가 없으면 삭제한다.
- 모든 tc 를 통과하면 ./output-<datetime> 경로에 어떤 파일도 생성되지 않는다.

# Prerequisite
input, output 파일을 처리하기 위해서 코드 상에 freopen 함수를 코드에 추가해야 함

```c++
#include <iostream>
#include <cstdio>
 
using namespace std;
 
int main() {
    //fastio
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    freopen(getenv("out"), "w", stdout);
    freopen(getenv("in"), "r", stdin);
 
    int tc;
    cin >> tc;  // read from "in"
    cout << tc << endl; //write to "out"
}
```