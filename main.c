#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 9

pthread_t threads[NUM_THREADS];
int thread_numbers[NUM_THREADS];

void *thread_function(void *arg) {
    int thread_num = *((int *)arg);
    while (1) {
        int sleep_time = rand() % 5 + 1;
        sleep(sleep_time);
        printf("Thread %d: %d\n", thread_num, thread_num);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    // Crearea firelor de execuție
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_numbers[i]);
    }

    // Așteptarea input-ului de la tastatură și anularea firelor de execuție corespunzătoare
    while (1) {
        int input;
        printf("Introduceti cifra pentru a anula thread-ul (1-9): ");
        scanf("%d", &input);

        if (input >= 1 && input <= NUM_THREADS) {
            pthread_cancel(threads[input - 1]);
            pthread_join(threads[input - 1], NULL);
            printf("Thread-ul %d a fost anulat.\n", input);
        } else {
            printf("Introduceti o cifra valida (1-9).\n");
        }
    }

    // Așteptarea terminării tuturor firelor de execuție
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Toate firele de execuție s-au încheiat. Programul se încheie.\n");

    return 0;
}
