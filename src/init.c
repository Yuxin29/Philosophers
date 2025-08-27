#include "philo.h"

// argv check missing, over flow missing
void get_table(t_table *table, char **argv)
{
    table->nbr = ft_atoi(argv[1]);
    table->to_die_time = ft_atoi(argv[2]);
    table->eat_time = ft_atoi(argv[3]);
    table->sleep_time = ft_atoi(argv[4]);
    table->total_eating_time = ft_atoi(argv[5]);
}

// for testing
// later, it should be start_routine, the eat, think and sleep routine
static void *thread_fn(void *arg)
{
    long id = (long)arg;
    pthread_t tid = pthread_self();
    printf("Philosopher %ld, thread ID = %lu\n", id + 1, (unsigned long)tid);
    return NULL;
}

// pthread_create: create a new pthread
// SYNOPSIS  
// int pthread_create(pthread_t *thread,
//                     const pthread_attr_t *attr,
//                     void *(*start_routine)(void *),
//                     void *arg);
// param: id address, attribute, prt to a function, arg
pthread_t *create_threads(t_table *philo_table)
{
    int i;
    pthread_t *tids;

    i = 0;
    tids = malloc(sizeof(pthread_t) * philo_table->nbr);
    if (!tids)
        return (NULL);
    while (i < philo_table->nbr)
    {
        pthread_create(&tids[i], NULL, thread_fn, (void *)(long)i);
        i++;
    }
    return (tids);
}

// pthread_join: join with a terminated thread
// SYNOPSIS  
// int pthread_join(pthread_t thread, void **retval);
void joint_all_threads(pthread_t *tids, t_table *philo_table)
{
    int i;

    i = 0;
    while (i < philo_table->nbr)
    {
        pthread_join((long)tids[i], NULL);
        i++;
    }
    return ;
}