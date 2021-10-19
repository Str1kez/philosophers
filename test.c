#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

struct timeval	g_time;

unsigned long	get_time(void);

void *func(void *data)
{
    while (1)
    {
        printf("Speaking from the detached thread...\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

void *func2(void *data)
{
    while (1)
    {
        printf("Speaking from the detached second thread...\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t handle;
	unsigned long	res;

	res = get_time();
	printf("%lu\n", res);
    if (!pthread_create(&handle, NULL, func, NULL))
    {
        printf("Thread create successfully !!!\n");
        if ( ! pthread_detach(handle) )
            printf("Thread detached successfully !!!\n");
    }
	if (!pthread_create(&handle, NULL, func2, NULL))
	{
		printf("Second Thread create successfully !!!\n");
        if ( ! pthread_detach(handle) )
            printf("Second Thread detached successfully !!!\n");
	}
    sleep(5);
    printf("Main thread dying...\n");
    return 0;
}
