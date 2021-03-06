# 리눅스 명령어 

## 프로세스 관련 명령어

### ps
 -a : 모든 사용자   
 -u : 이름, 시간    
 -x : 완료되지 않는 프로세스   
 -e : 실행환경   
 -f : 시스템의 모든 프로세스   
 -ef : 프로세스 소유자, 번호, PID, CPU 사용량 등..
 -aux | grep hslee : 특정 사용자의 프로세스 출력      
 
 ![image](https://user-images.githubusercontent.com/87008955/128140232-0aa57d2c-cac1-41d1-b928-d7b7bb3696f8.png)
 
 -프로세스 상태    
 
![image](https://user-images.githubusercontent.com/87008955/128140335-00a6bc9f-c948-455b-905e-76ae52119060.png)

 
### top
:실시간으로 프로세스 정보 확인할 수 있는 명령어 ```q```로 정지

### &
```command~[&]```   
:리눅스에서 명령어를실행할 떄 뒤에 &를 붙이면 백그라운드로 실행할 수 있게 된다.
오래걸리는 작업을 할 떄 ex) yum으로 다운로드하는경우 백그라운드로 실행하면 다운받으면서 다른 행동도 할 수 있다. 

### sleep
```# sleep 100```하면 100초동안 아무것도 할 수 없다. ctrl+z로 누르면 프로세스를 일시정지시켜 백그라운드로 넘기게된다.

### jobs
: 백그라운드 프로세스를 확인하는 명령어 

### *fg*
:백그라운드로 실행중인 프로세스를 포어그라운드로 변경하는것   
``` # fg %작업번호 ```     
### *bg*
:포어그라운드로 실행 중인 프로세스를 백그라운드로 변경하는 것
```# ctrl+z```    
stop된걸 다시 작동시키려면 kill 명령어를 수행해야한다.

### kill
```kill -19 %1 // 정지 ```   
```kill -18 %1 //재시작 ```    
```kill -9 %1 //종료 ```     

***

## touch    
:빈 파일을 생성하는 명령어, 이미 생성된 파일을 touch할 시 파일 수정시간이 현재시간으로 변경된다. 

***

## GCC
:C와 C++ 컴파일러 
- ```gcc --help```: 사용법 출력
- ```gcc --version``` : 버전 정보 출력
- ```gcc -S```: 컴파일만하고 어셈블이나 링크는 하지않는다. => 어셈블리어를 변환하지 않는다 vi편집기로보면 test.s가 어셈블리어로 이루어져있음을 알수 있음
- ```gcc -c```: 링크를 실행하지 않고 컴파일과 어셈블만 수행
- ```gcc -o```: 지정한 file로 출력 파일을 생성한다. 이 옵션을 사용하지 않으면 기본으로 a.out 실행파일 생성

![image](https://user-images.githubusercontent.com/87008955/127808565-cb3b7fa1-acbf-43e6-a899-1a97ada73e56.png)

***
## 환경변수 설정
```
$ echo PATH
$ echo $PATH
$ PATH=$PATH:./
```
이렇게 하면 ./안치고도 파일을 실행시킬수 있다. 

***
     
## ctags

### ctags?
:프로그래밍 소스코드의 태그들의 database를 생성하는 명령어
:함수 및 변수의 위치를 쉽게 인식할 수 있는 인덱스를 만드는 유틸리티
- ctags를 이용하면 소스코드 내에서 함수나 변수가 선언된 곳으로 이동할 수 있기 떄문에 특정 심벌을 찾고자 할 떄 주로 사용
- ctags의 장점 
: 소스코드를 분석하기 용이하기 때문에 큰프로젝트의 소스를 분석할때 유용

***
### ctags 설치 
```
$ctags-help //ctags설치 여부 확인 
```
```
$sudo apt-get install ctags
```
없다면 설치

***
### ctags 생성
```
$ctags-R
```
명령어로 현재 디렉토리의 모든파일과, 하위 디렉토리의 모든 파일까지 TAG 생성
***
### ctags 사용법
 - tags 파일 열기
 ```
 $vi tags
 ```
 tags 파일 오픈 
***
### vi 편집기와 연결
 -vi 편집기와 ctags를 연동해서 보던 파일내에서 ctags를 사용하게 한다. 
 ```
 $vi ~/.vimrc   
 set tags = /home/hslee/tags
 ```
 와 같이 tags 파일의 경로를 등록 
 ***
### ctags 명령어
- ctrl+] : 해당함수나 변수가 선언된 위치로 이동
- ctrl+t : 이전 태그로 이동
- 그 외 명령어 

![image](https://user-images.githubusercontent.com/87008955/126609819-0b499174-e639-4606-9de7-6879cbea9def.png)

***

## MAKE

### MAKE? 
: 소스의 일부가 변경된 경우에 변경된 부분만 다시 컴파일하고 링크하여 컴파일 시간을 단축시켜주는 명령어
: 모듈별 소스 관리 기능을 해주어 소스관리를 매우 효율적으로 하게 해준다

### MAKE 실행 방법
 - MAKE 명령어는 makefile이나 Makefile 파일에서 설정된 내용을 읽은 후 실행한다. 
 ( *Makefile*? : 스크립트 파일로써 프로그램의 컴파일 규칙을 적어 놓는다. )
 
 - 예시
   - foo1.c 파일과 foo2.c 파일이 있다고 가정, Makefile파일을 이와 같이 생성
   ![image](https://user-images.githubusercontent.com/87008955/126610620-20a9ba2c-5f9d-4544-b331-f8a636e970b1.png)
   
   ``` $make //명령어 컴파일 ```
   ``` $make foo ```
   와 같이 컴파일 시 gcc-o foo foo1.c foo2.c 와 같은 실행효과를 낸다
   
   ![image](https://user-images.githubusercontent.com/87008955/127813047-da1953da-343a-4c85-95fb-afe8ce5acb6a.png)


   - clean 구문 추가
   ```
   $ vi Makefile
   -
   -
   clean: 
   rm -rf foo foo1.o foo2.o
   ```
   clean 구문은 make clean 명령으로 실행한다

   ```
   $make clean
   rm -rf foo foo1.o foo2.o
   ```

***
   
   ## 리눅스 단축키 
   
   - [tab] 자동완성 
   - ctrl + a : 명령 라인의 처음으로 커서 이동
   - ctrl + e: 명령라인의 끝으로 커서 이동 
   - ctrl + u: 커서 앞부분 정리
   - ctrl + k : 화면졍리 (=```clear```)
   - ctrl + c : 현재 실행중인 명령을 종료 ( 포어그라운드 프로세스 종료)
   - ctrl + z : 현재 실행 중인 명령 정지
   - ctrl + d : 문서의 끝 

  

 


 
