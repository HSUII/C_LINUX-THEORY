# THREAD

## thread
thread: 프로세스 내 에 제어 흐름으로 하나의 프로그램 안에서 여러가지 일을 동시에 수행할 수 있게해주는 기능이다. 
전역변수 공유가 가능하고 동시수행함으로써 작업속도가 향상된다.
- 단점: 동시에 같은 변수를 사용하여 작업하는 경우 어느 쓰레드가 먼저 실행될지 알 수 없다. 또한 thread를 많이 생성하게 되면 , thread의 작업속도 향상보다 thread 스케쥴링 시간이 더 길어질 수 있다.

![image](https://user-images.githubusercontent.com/87008955/128475321-5455d359-babb-4aeb-99b9-c7202de71e2d.png)

## thread 필요한 함수 


```c
#include <pthread.h>

int pthread_create(pthread_t *thread, pthread_attr_t *attr,void*(*start_routine)(void *),void *arg);
void pthread_exit(void *retval);

int pthread_join(pthread_t thread, void **thread_return);

```

## thread 프로그램
```c
#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <string.h>
#include  <pthread.h>

void *thread_function(void *arg);

char message[] = "HELLO HEESU WORLD";

int main(){
        int res;
        pthread_t a_thread;
        void *thread_result;

        res =pthread_create(&a_thread,NULL,thread_function, (void *)message);
        if(res!=0){
                perror("thread creation failed");
                exit(EXIT_FAILURE);
        }

        printf("waiting for thread to finish..\n");
        res = pthread_join(a_thread,&thread_result);
        if(res != 0 ){
                perror("thread join failed");
                exit(EXIT_FAILURE);
        }
                printf("thread joined, it returned  %s\n",(char *)thread_result);
                printf("message is now %s",message);
                exit(EXIT_SUCCESS);

}

void *thread_function(void *arg){
printf("thread_function is running. Argument was %s\n",(char*)arg);
sleep(3);
strcpy(message,"Bye!");
pthred_exit("thank u for the cpu time");
}
```

