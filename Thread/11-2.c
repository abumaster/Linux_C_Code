/*
 * get Thread exit code
 * */
#include "apue.h"
#include <pthread.h>

void *thr_fn1(void *arg)
{
	printf("thread1 returning\n");
	return ((void*)1);//正常返回
}
void *thr_fn2(void *arg)
{
	printf("thread2 exiting\n");
	pthread_exit((void*)2);//调用pthread_exit()
}

int main(void)
{
	pthread_t tid1, tid2;
	int err;
	void *tret;//线程返回码

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err!=0)
		err_quit("can't create thread1: %s\n", strerror(err));

	err=pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err!=0)
		err_quit("can not create thread2: %s\n", strerror(err));

	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_quit("can't join with thread1: %s\n", strerror(err));
	printf("thread1 exit code %d\n", (int)tret);

	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_quit("can't join with thread2: %s\n", strerror(err));
	printf("thread2 exit code %d\n", (int)tret);

	exit(0);
}

