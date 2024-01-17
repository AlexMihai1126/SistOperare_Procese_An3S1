#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define NUM_THREADS 9
bool threads_running = true;

pthread_t threads[NUM_THREADS];
int thread_numbers[NUM_THREADS];

void *thread_function(void *arg) {
    int thread_num = *((int *)arg);
    while (1) {
        int sleep_time = rand() % 5 + 1;
        sleep(sleep_time);
        printf("Thread %d \n", thread_num);
    }
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_numbers[i]);
    }

    while (threads_running == true) {
        int input;
        scanf("%d", &input);
        if (input >= 1 && input <= NUM_THREADS && thread_numbers[input-1] !=0) {
            pthread_cancel(threads[input - 1]);
            pthread_join(threads[input - 1], NULL);
            printf("Thread-ul %d a fost anulat.\n", input);
            thread_numbers[input-1] = 0;
            for (int i=0;i<NUM_THREADS;i++){
                if (thread_numbers[i] != 0){
                    threads_running = true;
                    break;
                }
                else{
                    threads_running = false;
                }
            }
        } else {
            printf("Thread-ul nu exista.\n");
        }
    }
    printf("Toate firele de executie s-au încheiat. Programul se încheie.\n");
    return 0;
}
