# JSON

비동기 브라우저/서버 통신(AJAX)을 위해 "속성-값","키-값"쌍으로 이루어진 
데이터 오브젝트를 전달하기 위해 인간이 읽을 수 있는 텍스트를  사용하는 개방형 표준 포맷

JSON은 문자열 형태로 존재해서 네트워크를 통해 전송할 때 유용하다. 
JSON를 데이터로 사용하기 위해선 문자열에서 객체로 변환하는 파싱(Parsing)이 필요하다. 


## 특징 

- 경량의 데이터 교환 포맷
- JAVASCRIPT의 구문 형식 준수
- 프로그래밍 언어나 플랫폼에 독립적 
- 장단점     


![image](https://user-images.githubusercontent.com/87008955/133221315-6a40b65b-f09c-4c6d-aac6-281f5aa90f23.png)

## JSON 구조 

JSON은 자바 스크립트 객체 문자열 문법을 따르는 문자열이다. 
JSON안에는 자바 스크립트와 마찬가지로 기본 데이터 타입인 문자열, 숫자, 배열, boolean, 객체가 존재한다. 

예시 
```
{
  "squadName": "Super hero squad",
  "homeTown": "Metro City",
  "formed": 2016,
  "secretBase": "Super tower",
  "active": true,
  "members": [
    {
      "name": "Molecule Man",
      "age": 29,
      "secretIdentity": "Dan Jukes",
      "powers": [
        "Radiation resistance",
        "Turning tiny",
        "Radiation blast"
      ]
    },
    {
      "name": "Madame Uppercut",
      "age": 39,
      "secretIdentity": "Jane Wilson",
      "powers": [
        "Million tonne punch",
        "Damage resistance",
        "Superhuman reflexes"
      ]
    },
   ]
  }
```

## 주의점 

- JSON은 순수한 데이터 포맷임으로 함수는 담을 수 없다
- 문자열과 속성 이름 작성시 "만사용가능하다. 


***

# REST

웹과 같은 분산 하이퍼 미디어 환경에서 자원의 존재 정보를 표준화된 HTTP 메소드로 주고받는 웹 아키텍쳐 
HTTP URI를 통해 자원을 구분 

주고받는 형식: HTTP 메소드/ POST,GET,PUT,DELETE 

SOAP과의 비교 (SOAP: HTTP,HTTPS,SMTP 등을 이용해 XML 기반의 메시지를 네트워크 상에서 교환하는 프로토콜 ) 


![image](https://user-images.githubusercontent.com/87008955/133221554-b5ee0e87-ef4d-446b-92c4-b83d5ff196d5.png)


***

## C언어 JSON 데이터 

**JANSSON**
jansson 라이브러리는 JSON데이터를 인코딩하거나 디코딩하고, 다루기 위한 c 라이브러리다. 

문자열 파싱 과정 

![image](https://user-images.githubusercontent.com/87008955/133225666-88b8cdae-2edc-4cd6-b938-185908b484d8.png)




간단한 예시 
```c
#include <stdio.h>
#include <jansson.h> //jansson 헤더를 추가

int main ( void )
{
    json_t *obj = json_object(); //오브젝트 형식의 json_t 구조체 포인터를 선언. 자바스크립트로 new Object() 
    json_object_set(obj, "hello", json_string("hello")); //hello란 키워드에 "hello" 스트링을 설정
    // { hello: "hello" } 가 된 형식.

    json_t *gobj = json_object_get(obj, "hello"); //object타입인 obj 에서 hello 키워드의 값을 가져옮
    printf("%s\n", json_string_value(gobj)); //가져온 값을 string 형으로 가져옮. 반환 형식은 const char*
        
    json_decref(obj); //생성한 json을 free해줌
}
```
예시2

```c
#include <stdio.h>
#include <jansson.h>
 
void insert_filename(json_t* pjson, char* filename)
{
    json_t* data;
 
    data = json_string(filename);
    json_array_append(pjson, data);
}
 
int main (int argc, char** argv)
{
    json_t* pjson;
    json_t* data;
    int i;
    char* result;
 
    pjson = json_array();
 
    for(i=1; i<=argc; i++)
        insert_filename(pjson, argv[i]);
 
    printf("size : %d\n", json_array_size(pjson));
    result = json_dumps(pjson, JSON_ENCODE_ANY);
    json_dump_file(pjson, "./data.json", JSON_ENCODE_ANY);
    printf("%s\n", result);
 
    json_decref(pjson);
 
    return 0;
}

```

API에서 JSON 갖고오는 예시

```c
har *data;

if ( argc < 2 )
{
    fprintf( stderr, "Must provide URL to fetch.\n" );
    return 1;
}
//data = mmpool_api( argv[1] );
data = cryptsy_api( argv[1] );

json_t *root;
json_error_t error;

root = json_loads( data, 0, &error );
if ( !root )
{
    fprintf( stderr, "error: on line %d: %s\n", error.line, error.text );
    return 1;
}
if ( !json_is_array(root) )
{
    fprintf( stderr, "error: root is not an array\n" );
    json_decref(root);
    return 1;
}

for( int i = 0; i < json_array_size(root); i++ )
{
    json_t *data, *success, *returned, *bal_avail;
    const char *balance;

    data = json_array_get( root, i );
    if ( !json_is_object(data) )
    {
        fprintf( stderr, "error: data %d is not an object\n", i + 1 );
        json_decref(root);
        return 1;
    }

    success = json_object_get( data, "success" );
    if ( !json_is_number(success))
    {
        fprintf( stderr, "error: %d: success is not a number", i+1 );
        json_decref(root);
        return 1;
    }

    returned = json_object_get(data, "return" );
    if ( !json_is_object(returned) )
    {
        fprintf( stderr, "error: %d: return is not an object", i+1  );
        json_decref(root);
        return 1;
    }

    bal_avail = json_object_get( returned, "balances_available" );
    if ( !json_is_array( bal_avail ))
    {
        fprintf( stderr, "error: %d: bal_avail is not an array", i+1 );
        json_decref(root);
    }

    balance = json_string_value(bal_avail);
    printf( "%s %.*s\n",
        json_string_value(bal_avail),
        newline_offset(balance),
        balance);
}
json_decref(root);

```


```
char *data;

if ( argc < 2 )
{
    fprintf( stderr, "Must provide URL to fetch.\n" );
    return 1;
}
//data = mmpool_api( argv[1] );
data = cryptsy_api( argv[1] );

json_t *root;
json_error_t error;

root = json_loads( data, 0, &error );
if ( !root )
{
    fprintf( stderr, "error: on line %d: %s\n", error.line, error.text );
    return 1;
}

const char *key;
json_t *value;

void *iter = json_object_iter( root );
while( iter )
{
    key = json_object_iter_key(iter);
    value = json_object_iter_value(iter);

    printf("Key: %s, Value: %f\n", key, json_real_value(value) );

    iter = json_object_iter_next(root, iter);
}

json_decref(root);
```


### 함수 

1. json_load_file: json파일의 포맷을 읽어 로드하는 함수 
```json_t *json_load_file(const char *path, size_t flags, json_error_t *error);```

2. json_dump_file: json object로 json 데이터가 들어있는 파일을 생성해준다 
```int json_dump_file(const json_t *json, const char *path, size_t flags);




