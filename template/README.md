# Description
C++ 파일을 빌드하고 테스트 입력 파일들을 자동으로 실행하여 정답과 실행 결과를 비교하는 스크립트
python 파일도 지원

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

## python 실행
- 실행 파일 : ./main.py

## 옵션
- f : 빌드 혹은 python 실행 파일 이름(기본은 main.cc)
- p : tc 파일 경로(기본은 ./tc)
- c : output 삭제
- b : C++ 파일 build 만 실행. test 는 제외
- y : python 실행
- h : 도움말 출력
```c++
#include <iostream>
 
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
 
int main() {
    FASTIO
}
```