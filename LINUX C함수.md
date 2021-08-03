# LINUX C언어 함수
   
 *** 
 ## standard i/o library
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
: 출력버퍼를 비우는 함수 => 출력버퍼에 저장된 데이터를 목적지로 전송하는 함수 (입력버퍼는 x)
``` fflush(fp)```

### feof
: 함수 기반의 파일복사 프로그램 
```int feof(FILE * stream);```
ex) ```if(feof(src)!=0) puts("파일복사 성공");```

### fseek
:파일 위치 지시자의 참조 위치를 변경시키는 함수 
```int feek(FILE * stram, long offset, int wherefrom);```


출처: [파일 입출력][https://blog.naver.com/ddongzzizzi/222326993828]

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
ㅇㄻ

