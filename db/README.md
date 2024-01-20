# DB

mysql과 유사한 DB 구조를 가진 DataBase 구현

- 파일 시스템을 사용하여 이전의 데이터 유지

## 처리 순서

1. DB 로그인
2. DB Control
3. 종료

### 실행방법

mysql과 동일하게 프로그램 시작 시 argument 입력으로 로그인 기능 구현

- ex: main root 1234

## compile

g++ main.cpp server.cpp client.cpp -o main

- gcc version : mac os Apple clang version 14.0.3 (clang-1403.0.22.14.1)

## 사용 가능한 명령어

1. SHOW

- show users
- show databases

2. CREATE

- create user [id] [pw]
- create database [name]
- create table [name] [columnsInfo] (columnInfo standard : name,type,size ) (divide ' ') use [database] 이후 사용가능

3. DROP

- drop user [id] [pw]
- drop database [name]
- drop table [name] use [database] 이후 사용가능

4. USE

- use database [name]

5. DESC
   use [database] 이후 사용가능

- desc table [name]

# issue

### strtok issue

상황 : 입력 받은 문자열 strtok 시 마지막 문자열 인식 불가

- strtok_r로 해결하려 했으나 잘 안됨
- strtok_r은 multi-thread 사용 시 위치 save 불가할 시 사용
- 문제 파악 : strtok을 하면 구분자로 사용하고자 했던 문자가 위치한 부분에 '\0'이 들어감
- 다른 함수에서 사용하려고 하면 '\0' 때문에 문자열 인식 오류 발생
- 문제 해결: 함수 내에서 strtok을 사용하기 전 문자열 clone하여 사용

### remove issue

상황 : stdio.h에 존재하는 remove함수는 폴더가 비어있어야 삭제 가능

- 폴더에 들어가면 모든 내용을 돌면서 파일이면 삭제
- 폴더가 있으면 재귀로 해당 폴더 내 파일도 전부 삭제

### 중복 참조 issue

상황 : struct.h를 각 파일에서 참조해서 이슈 발생

- ifndef로 처리
- 컴파일 전처리기에서 정의되어있지 않으면 선언하도록 처리
