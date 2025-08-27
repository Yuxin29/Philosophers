#include "philo.h"

void get_table(t_table *table, char **argv)
{
    table->nbr = ft_atoi(argv[1]);
    table->to_die_time = ft_atoi(argv[2]);
    table->eat_time = ft_atoi(argv[3]);
    table->sleep_time = ft_atoi(argv[4]);
    table->total_eating_time = ft_atoi(argv[5]);
}