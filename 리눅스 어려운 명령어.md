# 리눅스 어려운 명령어 정리

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

  

 


 
