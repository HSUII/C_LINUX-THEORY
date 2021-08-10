# TCP 소켓프로그래밍 

## TCP/UDP
- TCP: 연결형 서비스로 발신지에서 목적지까지 경로를 설정해야하고 , 경로를 통해 자료를 송수신한다.
- UDP: 비연결형 서비스로 별도의 경로 설정이 필요 없으며, 단지 목적지로 자료를 전송하기만 하면 된다 .

***

## SERVER

### 연결준비단계 
: TCP/IP 통신망에 연결된 클라이언트가  서버에서 실행중인 응용 프로그램에 연결할 수 있도록 접속점(IP+PORT)이 제공된다. 클라이언트가 접속점인 프로토콜 주소로 연결을 요청하면 서버의 응용프로그램에 전달된다. 이전에 서버는 소켓을 생성하고, 접속점으로 사용할 프로토콜 주소를 결정하고, 소켓을 해당 주소에 실제로 연결한다. 그 후 클라이언트가 요청하면 요청을 받아들인다. 

1. 소켓 생성 : 네트워크 통신을 위해 소켓을 생성한다.
- 함수 
```c
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain,int type,int protocol);
```

- 반환값 : 성공: 소켓 기술자 / 실패: -1
- 인자      
  - domain(ex) PF_INET)    
  - type(ex)SOCK_STREAM)     
  - protocol(ex)0) ->프로토콜 인자를 0으로 설정하면 시스템에서 자동으로 domain 인자에 대해서는 PF_INET, type인자에 대해서는 SOCK_STREAM으로 설정하는데, 이는 TCP 프로토콜을 의미한다. 0대신 IPPROTO_TCP를 사용해도된다         
- 예시) 
```
int socket;
socket = socket(PF_INET, SOCK_STREAM,0);
```

2. 연결할 주소 준비: 클라이언트로부터 서비스 요청을 받을 서버의 주소(IP, PORT)를 결정해서 구조체 변수에 저장한다. 
```
struct sockaddr_in s_addr;

memset(&s_addr, 0 , sizeof(s_addr);
s_addr.sin_addr.s_addr = inet_addr(INADDR_ANY); 
//서버에 연결된 네트워크 인터페이스를 목적지로해서 들어오는 모든 자료를 수신할 수 있다.서버가 여러개 ip를 갖는경우에 INADDR_ANY유용하다
s_addr.sin_family = AF_INET;
s_addr.sin_port = htons(7000);

```
3. 주소에 연결(bind): 소켓을 프로토콜 주소에 연결한다.
- 함수 
```
#include <sys/socket.h>
int bind(int sock_fc,const struct sockaddr *addr,int addrlen)
```
- 반환값: 성공시:0 / 실패시: -1
- 인자
  - sock_fd:클라이언트의 연결 요청을 받아 처리할 소켓 기술자 
  - addr: 서버가 처리할 자료의 목적지 ip주소와 포트 번호를 지닌 주소 
  - addrlen: 주소의 길이 
  - ex
 ```
 int s_socket;
 struct sockaddr_in s_addr;
 bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr))
 ```
 서버가 별도의 bind함수를 호출하지 않으면, 서버는 listen함수를 호출할때 자동으로 사용가능한 포트를 선택한다. 클라이언트는 bind함수를 호출하지 않고, connect 함수를 호출할때 
 커널에서 부여하는 포트를 사용한다. 서버는 client에게 포트번호를 알리기위해 bind함수를 호출해서 특정 포트를 사용하게 해야한다.    
 
4. 개통요청(listen): 클라이언트로부터 연결 요청이 오면 받아들일 수 있도록 한다. 
- 함수
```
#include <sys/socket.h>
int listen(int sock_fd, int backlog)
```
- 반환값: 성공시: 0 / 실패시: -1
- 인자 
  - sock_fd
  - backlog: 이소켓으로 통신하려고 큐에서 대기하는 클라이언트의 수 ex)backlog=10인경우 현재 연결완료된 소켓수+연결설정 진행중인 소켓의 수 = 최대 10개
 - ex
 ```
int s_socket;
listen(s_socket,0);
```
listen 함수를 호출할 때 두번쨰 인자 backlog로 커널이 관리하는 대기큐에서 연결 요청을 기다리는 총 클라이언트의 수를 알려준다.    
이큐에서 연결 요청한 소켓이 SYN_RCVD( )나 ESTABLISHED상태로 있는다. 이 함수를 호출하면 커널은 내부적으로 해당 소켓의 상태를 CLOSED에서 LISTEN상태로 바꾼다. ㅣ
- SYN_RCVD상태:클라이언트가 connect함수로 서버에 요청한 연결을 처리하기 위해 시스템 내부에서 서버로 syn 패킷을 보내서 3hand-shaking을 진행중인 상태
- ESTABLISHED상태:클라이언트가 connect 함수로 서버에 요청한 연결을 시스템이 모두 처리한 상태. 


### 서비스 처리 단계 

1. 소켓생성: 클라이언트에서 네트워크 통신을 위해 소켓을 생성한다.
3. 연결요청(connect): 클라이언트에서 서버로 연결을 요청한다. 
4. 연결 접수(accept): 서버가 클라이언트로부터 연결 요청을 기다리다가 접수한다. 
예를들어 ip 주소가 163.1.2.3인 클라이언트에서 소켓 c를 생성하고 200번 포트를 통해 162.5.6.7이고 포트 번호 7000으로 연결 요청한다.    
이때 서버와 연결된 클라이언트 소켓은 [163.1.2.3 : 200, 162.5.6.7 : 700]으로 표현한다.
- 함수
```
#include <sys/socket.h>
int accept(int sock_fd,struct sockaddr *c_addr,int *len);
```
- 반환 값 : 성공시: 소켓기술자 / 실패시: -1
- 인자
  - sock_fd: 소켓 기술자 
  - c_addr: 클라이언트의 프로토콜 주소를 저장하는 구조체 변수 
  - len:c_addr에 저장된프로토콜 주소의 길이 
 - 예시
 ```
 int s_socket, c_socket;
 int lne;
 struct sockaddr_in c_addr;
 
 len = sizeof(c_addr);
 c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len)l
 
 ```
- 유의해야할 점은 accept 함수의 첫번째 인자로 사용한 소켓(s_socket)과 함수가 반환하는 소켓 (c_socket)이 서로 다르다는 것이다    
s_socket은 서버의 ip 주소와 포트 번호로 구성된 접속점과 연결해서 사용하는 소켓으로 클라이언트가 오청하는 접속점이다 .    
시스템은 듣기 소켓 s_socket으로 클라이언트의 연결 요청을 받으면, 내부적으로 해당 클라이언트에 대한 서비스를 전담할 새로운 소켓을 생성하고, accept함수의 반환 값으로 반환한다.
이 소켓을 연결소켓(connection socket)이라고한다. 이렇게 생성된 c_socket은 대기 큐에서 기다리고 있다가 서버의 응용프로그램이 accept함수를 호출할때마다 선택되어 응용프로그램에 제공된다. 
이 후 해당 클라이언트와 자료 송수신은 c_socket을 통해서만 이루어지고, 새로운 연결 요청이 있을땐 s_socket으로 이루어진다. 


6. 자료의 송수신(read/write): 서버와 클라이언트가 약속된 규약에 따라 자료를 송수신하는 과정     
연결소켓[163.1.2.3 : 200, 162.5.6.7 : 700]으로 클라이언트와 자료를 송수신하며 서비스를 제공한다. 
- write: 사용자 영역의 버퍼 내용을 커널의 송신 버퍼로 복사 


7. 연결 종료(close/shutdown): 클라이언트와의 연결 소켓을 종료한다.


