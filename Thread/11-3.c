#include "apue.h"
#include <pthread.h>

struct foo {
	int a,b,c,d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf(s);
	printf(" structure at 0x%x\n", (unsigned int)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo foo1={1,2,3,4};
	printfoo("thread1 :\n",&foo1);
	pthread_exit((void*)&foo1);
}
void *thr_fn2(void *arg)
{
	printf("thread 2 ID: %u\n", (unsigned int)pthread_self());
	pthread_exit((void*)0);
}
int main(void)
{
	int err;
	pthread_t tid1,tid2;
	struct foo *fp;

	err = pthread_create(&tid1,NULL,thr_fn1,NULL);
	if (err!=0)
		err_quit("thread 1 create error:%s\n", strerror(err));
	err = pthread_join(tid1, (void*)&fp);
	if (err!=0)
		err_quit("can't join with thread1:%s\n", strerror(err));
	sleep(1);
	printf("parent start second thread\n");
	err = pthread_create(&tid2,NULL,thr_fn2,NULL);
	if (err!=0)
		err_quit("thread2 can't create\n");
	sleep(1);
	printfoo("parent:\n",fp);
	exit(0);
}
