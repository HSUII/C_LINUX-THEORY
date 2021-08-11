# TCP 

## CLIENT

### 연결 준비 단계 

**1. 소켓 생성 (SOCKET)**
**2. 연결할 서버 주소 준비**

### 서비스 처리 단계 

**1. 서버 연결(connect)**
**2. 자료의 송수신(read/write)**
**3. 연결종료(close/shutdown)**

***

#### 소켓 생성 

```c
int socket;
socket = socket(PF_INET,SOCK_STREAM,0);
```
#### 서버 주소 준비 

```c
struct sockaddr_in c_addr;
memset(&c_addr,0,sizeof(c_addr));
c_addr.sin_addr.s_addr = inet_addr("192.1.1.1");
c_addr.sin_family = AF_INET;
c_addr.sin_port = htons(7000)
```

#### 서버 연결
- 함수
```c
#include <sys/types.h>
#inlcude <sys/socket.h>

int connect(int sock_fd, const struct sockaddr *serv_addr,int addrlen);
```
- 반환값 성공시 : 0 / 실패시: -1
- 인자 
  - sock_fd
  - serv_addr: 연결할 서버의 프로토콜 주소(ip주소와 포트번호)를 저장하는 구조체 변수의 포인터
  - addrlen:인자 serv_addr이 가르키는 구초 변수의 크기 


#### 자료의 송수신 

 읽어야 하는 자료의 크기(byte)를 미리 알수 없고, 줄 단위로 자료를 수신하는 경우는 close()함수를 호출시 자료의 끝을 알리는 EOF가 상대방에게 전송된다. 
 
 - 예시
 ```c
int sock_sd; 
int n,r,length;
char c;
cahr buf[BUFSIZE].*ptr;

length = 0;
ptr = buf;
while((n=read(sock_sd, ptr,1))>0){
  if(*ptr =='\r' ) continue;
  if(*ptr == '\n') break;
  
  if(length == BUFSIZE) break;
  ptr++; length++;


}
buf[length] = '\0';

```
이 코드는 소켓으로부터 한바이트씩 읽어 buf에 저장한후 비교하기 떄문에 성능이 떨어질수 있다. 
보안하기 위해 사용자가 별도의 버퍼를 관리하고 여러 바이트를 한꺼번에 읽어온 후 한 바이트씩 가져다 처리하게 함으로써 성느을 향상시킬 수 있다.

```c
int sock_sd;
char  buf[BUFSIZE];
char *ptr;
int length =0;
ptr = buf;
while((n = read_line(sock_sd,ptr))>0){
  if(*ptr =='\r' ) continue;
  if(*ptr == '\n') break;
  
  if(length == BUFSIZE) break;
  ptr++; length++;


}
buf[length] = '\0';

```
소켓의 송신 버퍼로부터 사용자 버퍼로 자료를 읽어온후 1바이트 씩 반환하도록 하는 코드를 구현했다.

```c
static int r_count =0;
static char *r_ptr;
static char r_buffer[BUFSIZ];

int
read_line(int sd,char *temp){
  if(r_count <=0){
  
    if((r_count = read(sd,r_buffer, sizeof(r_buffer))<0) return -1;
    else if(r_count ==0) return 0;
    r_ptr = r_buffer;
  
  }
  r_count--;
  *temp = *r_ptr++;
  return(1);
}
