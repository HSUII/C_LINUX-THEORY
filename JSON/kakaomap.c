#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <jansson.h>


#define BUF_LEN 128
#define h_addr h_addr_list[0]
#define PORT 80
#define MAX_CHARS (1024 * 8)

/* forward refs */
void print_json(json_t *root);
void print_json_aux(json_t *element, int indent);
void print_json_indent(int indent);
const char *json_plural(size_t count);
void print_json_object(json_t *element, int indent);
void print_json_array(json_t *element, int indent);
void print_json_string(json_t *element, int indent);
void print_json_integer(json_t *element, int indent);
void print_json_real(json_t *element, int indent);
void print_json_true(json_t *element, int indent);
void print_json_false(json_t *element, int indent);
void print_json_null(json_t *element, int indent);

void print_json(json_t *root) { print_json_aux(root, 0); }

void print_json_aux(json_t *element, int indent) {
    switch (json_typeof(element)) {
        case JSON_OBJECT:
            print_json_object(element, indent);
            break;
        case JSON_ARRAY:
            print_json_array(element, indent);
            break;
        case JSON_STRING:
            print_json_string(element, indent);
            break;
        case JSON_INTEGER:
            print_json_integer(element, indent);
            break;
        case JSON_REAL:
            print_json_real(element, indent);
            break;
        case JSON_TRUE:
            print_json_true(element, indent);
            break;
        case JSON_FALSE:
            print_json_false(element, indent);
            break;
        case JSON_NULL:
            print_json_null(element, indent);
            break;
        default:
            fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
    }
}

void print_json_indent(int indent) {
    int i;
    for (i = 0; i < indent; i++) {
        putchar(' ');
    }
}

const char *json_plural(size_t count) { return count == 1 ? "" : "s"; }

void print_json_object(json_t *element, int indent) {
    size_t size;
    const char *key;
    json_t *value;

    print_json_indent(indent);
    size = json_object_size(element);

    printf("JSON Object of %lld pair%s:\n", (long long)size, json_plural(size));
    json_object_foreach(element, key, value) {
        print_json_indent(indent + 2);
        printf("JSON Key: \"%s\"\n", key);
        print_json_aux(value, indent + 2);
    }
}

void print_json_array(json_t *element, int indent) {
    size_t i;
    size_t size = json_array_size(element);
    print_json_indent(indent);

    printf("JSON Array of %lld element%s:\n", (long long)size, json_plural(size));
    for (i = 0; i < size; i++) {
        print_json_aux(json_array_get(element, i), indent + 2);
    }
}

void print_json_string(json_t *element, int indent) {
    print_json_indent(indent);
    printf("JSON String: \"%s\"\n", json_string_value(element));
}

void print_json_integer(json_t *element, int indent) {
    print_json_indent(indent);
    printf("JSON Integer: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(element));
}

void print_json_real(json_t *element, int indent) {
    print_json_indent(indent);
    printf("JSON Real: %f\n", json_real_value(element));
}

void print_json_true(json_t *element, int indent) {
    (void)element;
    print_json_indent(indent);
    printf("JSON True\n");
}

void print_json_false(json_t *element, int indent) {
    (void)element;
    print_json_indent(indent);
    printf("JSON False\n");
}

void print_json_null(json_t *element, int indent) {
    (void)element;
    print_json_indent(indent);
    printf("JSON Null\n");
}

/*
 * Parse text into a JSON object. If text is valid JSON, returns a
 * json_t structure, otherwise prints and error and returns null.
 */
json_t *load_json(const char *text) {
    json_t *root;
    json_error_t error;

    root = json_loads(text, 0, &error);

    if (root) {
        return root;
    } else {
        fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
        return (json_t *)0;
    }
}

/*
 * Print a prompt and return (by reference) a null-terminated line of
 * text.  Returns NULL on eof or some error.
 */
char *read_line(char *line, int max_chars) {
    printf("Type some JSON > ");
    fflush(stdout);
    return fgets(line, max_chars, stdin);
}
int main(int argc,char *argv[]){

        int s,n,len_in,len_out,wn;
        struct sockaddr_in server_addr;
        char *haddr;
        char buf[BUF_LEN+1];
        int port=80;
        struct hostent *he;

  
        if ( argc < 4 )
        {
                    fprintf( stderr, "파라매터 값이 입력되지 않았습니다.\n <url> <keyword> <API key>  \n" );
                            return 1;
        }

  
    char line[MAX_CHARS];


    fprintf ( stdout, "example : [true, false, null, 1, 0.0, -0.0, \"\", {\"name\": \"barney\"}]\n\n" ) ;
    fprintf ( stdout, "Press \'q\' to exit.\n\n" ) ;

    while (read_line(line, MAX_CHARS) != (char *)NULL) {
        if ( !strncmp(line, "q", 1) )
            break ;

        /* parse text into JSON structure */
        json_t *root = load_json(line);

        if (root) {
            /* print and release the JSON structure */
            print_json(root);
            json_decref(root);
        }
    }


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

        sprintf(buf, "GET /v2/local/search/keyword.json/query=%s HTTP/1.1 Host: dapi.kakao.com Authorization: KakaoAK %s \n",argv[2],argv[3]);
        printf("%s\n",buf);
        if((wn= write(s,buf,strlen(buf)))<0) return -1;


        memset(buf,0,sizeof(buf));
        while((n=read(s,buf,BUF_LEN))>0){
                printf("%s",buf);
        /*
        char* temp = strstr(buf,"101");
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
        */

        memset(buf,0,sizeof(buf));
        }

    return 0;

        close(s);
}
