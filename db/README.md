# DB

최대 20명의 user가 채팅할 수 있는 채팅방을 열 수 있다.

## 처리 순서

1. DB 로그인
2. DB Control
3. 종료

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

## issue

- client의 recv 함수에서 서버가 꺼지면 length가 0으로 어떠한 문자열을 계속 수신
- 그래서 recv에서 length가 0인 msg 수신 시 프로그램 종료하게 변경
- 또한, client send에서 length가 0이면 보내지 않도록 처리 (경우의 수 : enter 치기)
