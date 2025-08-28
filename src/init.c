/* ************************************************************************** */
#include "philo.h"

static void init_table_ints(char **argv, t_table *table)
{
    table->nbr = safe_atoi(argv[1]);
    table->to_die_time = safe_atoi(argv[2]);
    table->eat_time = safe_atoi(argv[3]);
    table->sleep_time = safe_atoi(argv[4]);
    if (argv[5])
        table->total_eating_time = safe_atoi(argv[5]);
    else
        table->total_eating_time = -1;
}

static void init_philos(int   nbr, t_table *table)
{
    int i;

    i = 0;
    while(i < nbr - 1)
    {
        table->philos[i].id = i;
        table->philos[i].fork_l = i;
        table->philos[i].fork_r = i + 1;
        table->philos[i].meals_eaten = 0;
        i++;
    }
    table->philos[i].id = i;
    table->philos[i].fork_l = i;
    table->philos[i].fork_r = 0;
    table->philos[i].meals_eaten = 0;
}

// argv prechecked
// no defined minimal eating time, ends if one of the philo dies out of hunger
t_table *init_table(char **argv)
{    
    t_table *table;
    
    table = malloc(sizeof(t_table) * 1);
    if (!table)
    {
        printf("%s\n", "malloc table failed");
        return (NULL);
    }
    init_table_ints(argv, table);
    table->philos = malloc(sizeof(t_philo) * table->nbr);
    if (!table->philos)
    {
        free(table);
        printf("%s\n", "malloc inside table failed");
        return (NULL);
    }
    init_philos(table->nbr, table);
    return (table);
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