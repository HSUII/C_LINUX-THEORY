# LINUX C언어 함수
   
 *** 
 ## standard I/O library
: c언어에서 입출력을 처리하기 위한 함수 

### fopen 
: 연결하고 싶은 파일과의 스트림을 형성하고 스트림 정보를 FILE 구조체 변수에 담아 변수의 주소값을 반환하는 함수 
=> 파일과 스트림을 형성하기 위해 쓰는 함수 
```c
#include <stdio.h>
FILE * fopen(const char * filename, const char * mode); //filename = 스트림을 형성할 파일이름 , mode = 형성할 스트림의 종류

```
ex) ```FILE *fp = fopen("data.txt","wt");```: 파일 data.txt와 스트림을 형성하되 wt 모드로 스트림을 형성해라 

### fputc, fclose
fputc: fp에 특정값을 저장하는 함수
fclose: 운영체제가 할당한 자원의 반환, 버퍼링 되었던 데이터를 출력하는 함수
```
fputc('A',fp); //문자A를 fp가 가르키는 파일에 저장해라 
fputc('B',fp); 
fclose(fp);
```
출력값: ```AB```

### fgetc,getc,getchar
:입력받아오는 함수

### fputc,putc,putchar
:출력하는 함수 

### *fgets,*gets
:스트링값 입력 받아오는 함수
### fflush
: 입력값을 받기전 입력버퍼에 남은 쓰레기 값 날리는 함수  
:출력버퍼를 비우는 함수 => 출력버퍼에 저장된 데이터를 목적지로 전송하는 함수 (입력버퍼는 x)
``` fflush(fp)```

### feof
: 함수 기반의 파일복사 프로그램 
```int feof(FILE * stream);```
ex) ```if(feof(src)!=0) puts("파일복사 성공");```

### fseek
:파일 위치 지시자의 참조 위치를 변경시키는 함수 
```int feek(FILE * stram, long offset, int wherefrom);```


출처:  [파일 입출력](https://blog.naver.com/ddongzzizzi/222326993828)
***

## DIRECTORY
### 디렉토리 관리 
- rename
```int rename(const char *old,const char *new);```
: old = 변경할 파일, new = 새파일명, 리턴값 : 성공:0/실패:-1 
- getcwd
```char *getcwd(char *buf, size_t size)```:현재 작업 디렉토리 위치를 size의 buf에 저장  
- chdir
```int chdir(const char *path)```:디렉토리 이동 

### 디렉토리 정보 검색 
- opendir   
```DIR *opendir(const char *dirname);``` 
   - dirname: 열려는 디렉토리명
   - 리턴값: 열린 디렉토리를 가리키는 dir 포인터 / 실패시 null 포인터 
- closedir   
```int closedir(DIR *dirp);```
   - dirp: 닫으려는 디렉토리를 가르키는 포인터
   - 리턴값: 성공하면 0/ 실패시 -1
- readdir    
```struct dirent *readdir(DIR *dirp);```
   - 리턴값: dir 포인터가 가르키는 디렉토리의 내용을 하나씩 읽어와 리턴(dirent 구조체로 리턴)/ 더이상 읽을것이 없으면 NULL 리턴
   - dirent 구조체
   - ![image](https://user-images.githubusercontent.com/87008955/127965575-a2aa8a9b-dded-49f2-9743-e53d28fe5470.png)
 
- ```long telldir(DIR *dirp)```: 현재 위치를 알려줌
- ```void seekdir(DIR *dirp, long loc)```: 디렉토리 오프셋을 loc으로 이동 
- ```void rewinddir(DIR *dirp)```: 오프셋을 0으로 초기화

출처:[파일 관련 명령어](https://blog.naver.com/gaechuni/221151125087)
***
 ## WRITE
 1)서버에 로그인하고 있는 사용자에게 간단하게 메시지 보내는 명령어 
 사용자가 시스템관리자 ROOT에게 메세지 보낼 수 있다. 
 2)글자 수 비교하고 출력하는 명령어 
 
 ```c
 int main(){
  if((write(1,"here is some data\n",18)!=18)))
   write(2,"a write error has occurred on file descriptior 1 \n",46);
 }
``` 

***

## READ 
:파일 디스크립터로 부터 값을 읽어와 count 크기의 buffer에 저장하는것
size_t read(int fd//file descriptior), void *buf, size_t count);   
ex) ``` read(0,buffer,128); // 0 = 파일 디스크립터의 스탠다드 입출력(키보드입력 등), 128 = 버터사이즈 ```    

- ```fread```
***

## SYSLOG
:로그 출력하는 함수      
![image](https://user-images.githubusercontent.com/87008955/128126547-f3031d85-7f1e-4305-af03-53c83d151ca2.png)

## MAPPING
:메모리 동적할당

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)

int main(){
    char *some_memory;
    int megabyte = A_MEGABYTE;
    int exit_code = EXIT_FAILURE;


    some_memory = (char *)malloc(megabyte);
    if (some_memory != NULL) {
        sprintf(some_memory,"HELLO WORLD\n");
        printf("%s",some_memory);
        exit_code = EXIT_SUCCESS;

    }
    exit(exit_code);

}
```
**메모리 할당시에는 꼭 ```free(memory 변수명)``` 해줘야 한다.**

- void * calloc(size_t number_of_elements, size_t element,size);
- void * realloc(void *exitsting_memory,size_t new_size);
- 
**보통은 배열을 쓰고, 배열 크기가 크고 너무 변화가 심할때만 malloc사용**

## lock
: 다른사람이 사용하지 못하고 독점적으로 사용할 수 있도록 lock 하는것

```C
const char *lock_file = "/tmp/LCK.test2";

int main(){
   int file_desc;
   int tries =10;
   
   while(tries--){
   file_dsec = open(lock_file,O_RDWR|O_CREAT|O_EXCL, 0444);
      if(file_desc == -1){
         print("%d - lock already present\n",getpid());
         sleep(3);
      }
      else{
         printf("%d - i have exclusive access\n",getpid());
         sleep(1)
         (void)close(file_desc);
         (void)unlink(lock_file);
         sleep(2)
      }
      exit(EXIT_SUCCESS);
   }
}

```
## fork
: 자식 프로세스를 생성하는 시스템 함수   
: 반환 값을 통하여 부모 프로세스의 수행코드와 자식 프로세스의 수행코드를 식별할 수 있게 한다 

```c
int pid;
pid = fork();//자식 프로세스인 pid 생성

if(pid<0) printf("fork 실패");
if(pid>0){ //자식 프로세스가 존재하면 부모 프로세스가 실행하는 코드 부분 
   printf("부모 프로세스 시작");
   printf("부모 pid: %d, ppid: %d\n",getpid(),getppid());
   printf("부모 프로세스 작업완료");
}else{//자식 프로세스 실행하는 코드
   printf("자식 프로세스 시작 ");
   printf("자식 pid : %d,ppid :%d\n",getpid(),getppid());
   printf("자식 프로세스 작업완료");
}
```
fork()를 하는 순간 자식 프로세스가 생겨난다. 
자식을 만든 프로세스는 부모 프로세스가 되고 총 프로세스가 2개가 된다. 
쓰레드같은경우 하나의프로세스에서 운영되기에 전역변수값이 공유되지만, 프로세스간의 공유가 불가능하다(IPC로가능)

- fork 리턴값: 자식-0 부모-PID

***
## IN&OUT REDIRECTION
### freopen
```FILE* freopen(const char* filename, const char* mode,FILE* stream);```   
스트림을 다른파일이나 mode로 다시 연다. 
freopen 함수는 먼저 세번째 인자로 전달된 스트림에 해당하는 파일을 닫는다. (close)    
그 후 파일이 성공적으로 닫혔든 안닫혔든 간에, freopen 함수는 첫번째 인자로 전달된 파일 이름에 해당하는 파일을 두번쨰 인자로 전달된 mode에 맞게 연다.
이 함수는 특히 이미 정의된 표준 입력(stdin) 표준출력(stdout) 표준 오류(stderr) 와 같은 스트림들을 특정한 파일에 해당하는 스트림으로 변경할 수 있다.   


- ```filename```
: 열을 파일의 이름을 포함하는 c 문자열, 특히 freopen 함수가 실행되는 환경에 따라 파일에 경로에 대한 정보도 포함할 수있다. 
(예로 윈도우에선 filename에 "C:\a.txt"를 전달하면 c 드라이브에 a.txt 파일을 열게 된다. 이때 \를 두개 붙ㅇ야하는데 c언어에서는 \하나를 탈출문자로 사용되기 떄문이다)
- ```mode```
: 파일접근 방식에 대한 정보
 ![image](https://user-images.githubusercontent.com/87008955/128281089-5cf10a17-3a5d-4920-9cb8-c74ac4d4e074.png)
- ```stream```
: 작업을 수행할 스트림의 FILE 객체에 대한 포인터
- 리턴값 : 성공->세번째 인자 스트림 포인터/실패->널포인터

```c
   
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

int main(int argc, char *argv[]){
   char *filename;
   if(argv!=2){
      fprintf(stderr,"usage: useupeer file\n");
      exit(1);
   }
   filename = argv[1];
   if(!freopen(filename,"r",stdin) {
      fprintf(stderr,"could not redirect stdin from file %s\n",filename);
      exit(2);
   }
   execl("./upper","upper",0);
   perror("could not exec ./upper");
   exit(3);
   
 }
   
```
***
## SIGNAL
: signal 발생시 처리하는 함수
```void(*siganl(int signum,void (*handler(함수))(int)))(int)```
- 헤더: <signal.h>
- 반환값: void*()(int)이전에 설정된 시그널 핸들러 
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
   
void ouch(int sig)
   {
   printf(*OUCH! -I GOT SIGANL %d\n",sig);
   (void) signal(SIGINT, SIG_DFL);
   }
int main(){
   (void) signal(SIGINT, such);
   
   while(1){
      printf("HELLO WORLD\n");
      sleep(1);
   }
}
```   
   
***
## C언어 문법
1. "->" = (포인터 변수). 멤버 
EX) p1.next -> next = (*p1.next).next
