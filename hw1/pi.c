#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
long long toss_per_thread ;                         // the number of toss in each thread
long long ttl_in_num = 0 ;                          // total toss in the circle
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

void* thread_fnc(){
    long long part_sum = 0 ;
    double x , y ;
    double dist_sqr ;

    unsigned int seed = rand();
    for ( long long i = 0 ; i < toss_per_thread ; i++ ){
        x = rand_r(&seed) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        y = rand_r(&seed) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        if ( x*x + y*y <= 1 )
            part_sum += 1 ;
    }

    pthread_mutex_lock(&mutex);
    ttl_in_num += part_sum ;
    pthread_mutex_unlock(&mutex);

    return NULL ;
}

int main(int argc, char** argv){
    srand(time(NULL)) ;

    if ( argc != 3 ){
        fprintf(stderr, "Usage: ./pi <core #> <tosses #>\n") ;
        exit(1);
    }

    int ttl_thread_num = atoi(argv[ 1 ]) ;          // total thread number
    long long ttl_toss_num = atoll(argv[ 2 ]) ;     // total toss number
    toss_per_thread = ttl_toss_num / ttl_thread_num ;   

    pthread_t* tid = malloc(ttl_thread_num * sizeof(pthread_t)) ;;

    for ( int i = 0 ; i < ttl_thread_num ; i++ )
        pthread_create(&tid[ i ], NULL, thread_fnc, NULL) ;


    for ( int i = 0 ; i < ttl_thread_num ; i++ )
        pthread_join(tid[ i ], NULL) ;

    double pi_est = 4 * ttl_in_num / ((double)ttl_toss_num) ;
    printf("%f\n", pi_est) ;


    pthread_mutex_destroy(&mutex) ;
    free(tid) ;

    return 0 ;
}

