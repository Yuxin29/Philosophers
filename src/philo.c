#include "philo.h"

// for testing, delete later
static void ft_print_table(t_table  *table)
{
    printf("%d\n", table->nbr);
    printf("%d\n", table->to_die_time);
    printf("%d\n", table->eat_time);
    printf("%d\n", table->sleep_time);
    printf("%d\n", table->total_eating_time);
}

//./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
    t_table *philo_table;
    pthread_t *tids;

    // initiate
    if (argc != 5 && argc != 6) 
        return (-1);
    philo_table = malloc(sizeof(t_table) * 1);
    if (!philo_table)
        return (-1);

    //testing print threads
    get_table(philo_table, argv);
    ft_print_table(philo_table);
    
    tids = create_threads(philo_table);
    if (!tids) //malloc inside
    {
        free(philo_table);
        return (-1);
    }
    joint_all_threads(tids, philo_table);

    //finishing
    free(philo_table);
    free(tids);
    return (0);
}