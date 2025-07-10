#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *data)
{
    printf("QQ\n");
}

int main()
{
    pthread_t tid = 0;
    pthread_attr_t attr = {0};
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&tid, &attr, worker, NULL))
    {
        printf("Failed to create thread\n");
        return 0;
    }

    pthread_detach(tid);

    sleep(1);

    return 0;
}
