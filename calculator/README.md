# calculator

calculator는 문자열을 입력받아 사칙연산과 괄호 연산을 처리할 수 있다.

## 처리 순서

1. 문자열 입력받기
2. 후위 연산식으로 변경
3. 계산

## compile

g++ calculator.cpp operator.cpp valuce.cpp -o calculator

- gcc version : mac os Apple clang version 14.0.3 (clang-1403.0.22.14.1)

## call by referance issue

- 해당 gcc version에선 call by referance가 안되는 현상 발생
- 그래서 call by value로 처리함
