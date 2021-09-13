# HTTP2

## HTTP2란?

HTTP2는 WWW에서 쓰이는 HTTP 프로토콜 두번쨰 버전이다. 
HTTP1.1과 호환성은 유지하면서 다양한 기능을 추가해서 더 나은 HHTP 프로토콜을 구현하는 것을 목표로 하였다. 

## 목표

- HTTP 헤더 데이터 압축
- 서버 푸시 기술 
- 요청을 HTTP 파이프라인으로 처리 
- HTTP1의 HOL blocking 문제 해결 
- TCP 연결하나로 여러 요청을 다중화 처리
- 데스크탑, 모바일 브라우저, 웹 API, 웹 서버, 프록시 서버, 방화벽 등 자주 사용되는것들을 지원 

## 지원되는 브라우저 

크롬, IOS용 크롬, 파이어폭스 익스플로러11, MICROSOFT EDGE, 오페라, 사파리9 

***

## HTTP2 CHECKER 

HTTP2를 사용하기 위해선 클라이언트와 서버 양측 모두 HTTP/2를 지원해야 한다. 
지원 여부를 파악히기위해 HTTP/2 CHEKCER 프로그램을 사용해 서버에게 HTTP/2를 지원하는지를 질의하고 ,    
그에 대한 응답여부에 따라 HTTP/2로 통신해야할지, HTTP1.1으로 통신해야할지 경정해야한다

### CHECKER 방식 

RFC7540에 통신 방법이 정의되어있다. 

클라이언트가 최초 서버 접속시 Upgrade,HTTP-2 Settings 헤더를 요청 헤더에 실어 보낸다. 
HTTP2-Settings 커스텀 헤더는 각종 연결에 필요한 설정 정보를 base64url 인코딩한 값이다. 
![image](https://user-images.githubusercontent.com/87008955/132651279-8dbb2a91-2966-425e-8cf0-41018d247b1a.png)

**서버가 HTTP/2를 지원하지 않는다면, 요청에 대한 응답을 HTTP1.1버전의 200 OK로 응답한다.**     

![image](https://user-images.githubusercontent.com/87008955/132651467-bb1e810b-bc00-49de-900f-b895ba51629d.png)

**서버가 HTTP/2를 지원한다면 101 Swotoching Protocols 응답을 한다**
그리고 프로토콜이 업데이트 가능함을 Connection 헤더로 알려주고, Upgrade 헤더에 HTTP/2 지사자인 h2c로 응답한다. 

![image](https://user-images.githubusercontent.com/87008955/132651753-f599ea09-9f3f-4a8b-8f7d-0d78c2c3d0b2.png)


출처: <https://www.popit.kr/http2-rfc%EB%A5%BC-%EC%9D%91%EC%9A%A9%ED%95%9C-http2-checker%EC%9D%98-%EA%B5%AC%ED%98%84/>

## HTTP/2 CHECKER 구현 

```C
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUF_LEN 128
#define h_addr h_addr_list[0]
#define PORT 80

int main(int argc,char *argv[]){

        int s,n,len_in,len_out,wn;
        struct sockaddr_in server_addr;
        char *haddr;
        char buf[BUF_LEN+1];
        int port=80;
        struct hostent *he;

        he = gethostbyname(argv[1]);
        if(!he){
                printf("gethostname failed\n");
                return -1;
        }
        if((s=socket(PF_INET,SOCK_STREAM,0))<0){
                printf("can not create socket\n");
                return -1;
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr =*((struct in_addr *)he->h_addr);
        //server_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*he->h_addr_list));
        /*
        memcpy(haddr,he->h_addr,he->h_length);
        server_addr.sin_addr.s_addr=inet_addr(haddr)
        */
        server_addr.sin_port=htons(port);

        if(connect(s,(struct sockaddr *) &server_addr,sizeof(server_addr)) ==-1 ) {
                printf("fail\n");
                close(s);
                return -1;
        }

        sprintf(buf, "GET / HTTP/1.1\r\nHost:%s\r\nConnection: Upgrade, HTTP2-Settings\r\nUpgrade: h2c\r\nHTTP2-Settings: <base64url encoding of HTTP/2 SETTINGS payload>\r\n\r\n",argv[1]);
        printf("%s\n",buf);
        if((wn= write(s,buf,strlen(buf)))<0) return -1;


        memset(buf,0,sizeof(buf));
        while((n=read(s,buf,BUF_LEN))>0){
                printf("%s",buf);

        char* temp = strstr(buf,"Upgrade");
        if(temp){
                printf("\n");
                printf("===============================\n");
                printf("http2를 지원하는 사이트 입니다.\n");
                printf("===============================\n");
                return -1;
        }
        else {
                printf("\n");
                printf("==========================\n");
                printf("http/2를 지원하지 않습니다\n");
                printf("==========================\n");
                return -1;
        }

        memset(buf,0,sizeof(buf));
        }
        /*
        char temp[101];
        int i =0;

        for(i =0; i<100;i++){
                temp[i]=buf[i];
        }
        */

        close(s);
}

````
HTTP2 CHECKER는 기본적으로 TCP/IP 서버 CLIENT 소스코드를 기반으로 구현한다.        

<추가되는 기능>      
1. 도메인 주소를 IP로 변환시켜 서버와 TCP/IP 통신 가능     
2. 서버에게 HTTP2를 확인할 수 있는 헤더를 메세지에 담아 전송     
3. 서버가 보낸 메세지를 받아 HTTP2 지원여부 판단 가능      

이 기능 3가지를 추가하기 위해    

처음으로 도메인 주소를 IP로 변환하기 위해 매개변수로 받아온 도메인을 ```gethostbyname```함수를 이용하여 ip 주소로 변환하여 저장한다.    
이때 int형이나 char형으로 저장하면 안되고 hostent 구조체에 ip 주소를 저장해야 정상적으로 변환이 가능하다.       
ip가 저장된 hostent 구조체를 이용하여 소켓의 서버 주소 값에 저장한다.     
```server_addr.sin_addr = *((struct in addr *)he->h_addr); //server_addr=sockaddr_in, he=hostent```    

두번째 기능은 간단하게 소켓에 담겨 전송될 버퍼에 헤더를 담아 저장하면 된다 .        
```sprintf(buf, "GET / HTTP/1.1 HOST ~~ ");```      

마지막으로 서버와 연결한후 서버가 응답을 전송해주면 소켓을 버퍼에 저장한 후에          
버퍼의 내용에 정상적인 응답코드 101이 담겨있는지 비교한다 .           
비교한 후 101 코드가 들어있는 경우 지원하는 사이트라는 문장을 출력한다.    



### 출력결과     
1. 지원하는 경우      

![image](https://user-images.githubusercontent.com/87008955/133050850-94e44225-56a4-42a4-8964-e71053ffff3a.png)

2. 지원하지 않거나 http/2를 우선적으로 인식하지 않는 경우

![image](https://user-images.githubusercontent.com/87008955/133050980-58472b9e-4ed6-4394-b7fc-cc17f1c3ec33.png)




