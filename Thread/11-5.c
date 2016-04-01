#include "apue.h"
#include <stdlib.h>
#include <pthread.h>
//使用互斥量来保护数据结构

pthread_t ntid;

struct foo {
	int f_count;//counts of foo
	pthread_mutex_t f_clock;//互斥量
	//others
	int m_m;
};

struct foo*
foo_alloc(void)//aloct the object
{
	struct foo *fp;
	if ((fp=malloc(sizeof(struct foo)))!=NULL) {
		fp->f_count=1;
		fp->m_m=5;
		if (pthread_mutex_init(&fp->f_clock, NULL)!=0) {
			free(fp);
			return (NULL);
		}
	}
	return fp;
}
void
foo_hold(struct foo *fp)
{
	/*add a reference to the object*/
	pthread_mutex_lock(&fp->f_clock);
	fp->f_count++;
	fp->m_m++;
	pthread_mutex_unlock(&fp->f_clock);
}
void 
foo_rele(struct foo *fp)
{
	/*release a reference to the object */
	
	pthread_mutex_lock(&fp->f_clock);
	fp->m_m--;
//	fp->f_count--;
	if (--fp->f_count == 0)// the last one
	{
		pthread_mutex_unlock(&fp->f_clock);
		pthread_mutex_destroy(&fp->f_clock);
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_clock);
	}

}

void Print(struct foo *fp)
{
	printf("  fp->f_count = %d; m_m = %d\n", fp->f_count,fp->m_m);
}
void *
thr1_fn(void *arg)
{
//线程1 add fp->m_m
	struct foo *ftemp=(struct foo *)arg;
	while (ftemp && (ftemp->f_count)<10) {
	//sleep(1);
	foo_hold(ftemp);
	pthread_t tid;
	tid=pthread_self();
	//sleep(1);
	printf("thread1: %u : ",(unsigned int)tid);
	Print(ftemp);
	sleep(1);}
	return ((void *)0);

}
void * 
thr2_fn(void *arg)
{
//线程2 减少m_m
	struct foo *ftemp=(struct foo*)arg;
	while(ftemp /*&& (ftemp->f_count)>0*/) {
	//sleep(1);
	//if ((ftemp->f_count)>0) {
//	if ((ftemp->f_count)<0) continue;
	foo_rele(ftemp);
	pthread_t tid;
	tid=pthread_self();
	//sleep(1);
	printf("thread2: %u : ", (unsigned int)tid);
	Print(ftemp);//}
	sleep(2);}
	return ((void*)0);
}	

int main(void)
{
	int err;
	struct foo *sfm;
	sfm=foo_alloc();
	Print(sfm);	
	err = pthread_create(&ntid,NULL,thr1_fn,(void*)sfm);
	if (err!=0)
		err_quit("can't create thread: %s\n",strerror(err));
	err = pthread_create(&ntid, NULL, thr2_fn, (void*)sfm);
	if (err!=0)
		err_quit("can't create thread: %s\n", strerror(err));
	
	sleep(20);
	exit(0);
}
