#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct arg_struct {
    int a;
    int b;
    int sum;
};

void *addition(void *arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
    args->sum = args->a + args->b;
    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    
    struct arg_struct *args = malloc(sizeof(struct arg_struct));
    if (args == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    args->a = 10;
    args->b = 5;

    pthread_create(&t, NULL, addition, (void *)args);
    
    pthread_join(t, NULL);

    printf("%d + %d = %d\n", args->a, args->b, args->sum);

    free(args);

    return 0;
}
