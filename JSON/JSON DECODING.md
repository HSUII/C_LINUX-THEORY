# JSON 프로젝트 

- 과제 주제

    Kakao 지도 REST API 사용 및 JSON 결과 Decoding

 

- 진행 방법

    1. Kakao Developers에서 REST API Key 발급

    2. 'eluon'  키워드로 장소 검색 (개발 가이드 | Kakao Developers 문서)

    3. 첨부된 구조체에 JSON 문자열 Decoding (Jansson 라이브러리 사용)

    4. Decoding된 구조체 출력

 
## 결과

키워드로 장소 검색후 JSON 데이터 출력    

1)응답메세지에서 JSON데이터만 저장

![image](https://user-images.githubusercontent.com/87008955/134867140-00b19d6d-b565-467b-a2e8-8028f890920c.png)

2)받아온 JSON데이터를 JANSSON라이브러리를 사용해서 KEY,VALUE 값으로 정렬 

![image](https://user-images.githubusercontent.com/87008955/134867271-b988a3d0-04ec-49ee-9653-9499ec68b243.png)

3)JSON 데이터를 구조체에 저장후 원하는 정보만 출력

![image](https://user-images.githubusercontent.com/87008955/135420447-a8408fb7-8fbf-46f2-b254-d2025e7cf774.png)

4)헤더 분리



### 소스코딩
https://github.com/HSUII/C_LINUX-SOURCE_CODING/tree/master/JSON
