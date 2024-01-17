# DB

mysql과 유사한 DB 구조를 가진 DataBase 구현

- 파일 시스템을 사용하여 이전의 데이터 유지

## 처리 순서

1. DB 로그인
2. DB Control
3. 종료

### 로그인

mysql과 동일하게 프로그램 시작 시 argument 입력으로 로그인 기능 구현

## compile

g++ main.cpp server.cpp client.cpp -o main

- gcc version : mac os Apple clang version 14.0.3 (clang-1403.0.22.14.1)

## 서버, 클라이언트 실행 방법(예시)

- 서버
  ./main server 9090
- 클라이언트
  ./main client 9091 127.0.0.1 9090

## argument 별 설명

- argv[0] : 프로그램 명
- argv[1] : 사용할 Type (server, client)
- argv[2] : 사용할 Port
- argv[3] : 목적지 Server IP
- argv[4] : 목적지 Server Port

# issue

- client의 recv 함수에서 서버가 꺼지면 length가 0으로 어떠한 문자열을 계속 수신
- 그래서 recv에서 length가 0인 msg 수신 시 프로그램 종료하게 변경
- 또한, client send에서 length가 0이면 보내지 않도록 처리 (경우의 수 : enter 치기)

### strtok issue

상황 : 입력 받은 문자열 strtok 시 마지막 문자열 인식 불가

- strtok_r로 해결하려 했으나 잘 안됨
- strtok_r은 multi-thread 사용 시 위치 save 불가할 시 사용
- 문제 파악 : strtok을 하면 구분자로 사용하고자 했던 문자가 위치한 부분에 '\0'이 들어감
- 다른 함수에서 사용하려고 하면 '\0' 때문에 문자열 인식 오류 발생
- 문제 해결: 함수 내에서 strtok을 사용하기 전 문자열 clone하여 사용

### remove issue

상황 : stdio.h에 존재하는 remove함수는 폴더가 비어있어야 삭제 가능

- 하위 모든 내용을 돌면서 삭제할 생각
