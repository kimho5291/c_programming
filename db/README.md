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

- 첫 strtok시 strtok_r로 저장 위치 초기화
- 이후 부터 strtok 사용으로 처리
- strtok_r은 multi-thread 사용 시 위치 save 불가할 시 사용하는 것으로 알고있었으나 해당 문제도 해결 가능
