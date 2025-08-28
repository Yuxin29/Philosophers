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
        table->philos[i].table = table;
        i++;
    }
    table->philos[i].id = i;
    table->philos[i].fork_l = i;
    table->philos[i].fork_r = 0;
    table->philos[i].meals_eaten = 0;
    table->philos[i].table = table;
}

// pthread_create: create a new pthread
// SYNOPSIS  
// int pthread_create(pthread_t *thread,
//                     const pthread_attr_t *attr,
//                     void *(*start_routine)(void *),
//                     void *arg);
// param: id address, attribute, prt to a function, arg
static void create_threads(t_table *philo_table)
{
    int i;

    i = 0;
    while (i < philo_table->nbr)
    {
        pthread_create(&philo_table->philos[i].thread, NULL, thread_fn, &philo_table->philos[i]);
        i++;
    }
    return ;
}

// pthread_join: join with a terminated thread
// SYNOPSIS  
// int pthread_join(pthread_t thread, void **retval);
static void joint_all_threads(t_table *philo_table)
{
    int i;

    i = 0;
    while (i < philo_table->nbr)
    {
        pthread_join((long)philo_table->philos[i].thread, NULL);
        i++;
    }
    return ;
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
    create_threads(table);
    joint_all_threads(table);
    return (table);
}

