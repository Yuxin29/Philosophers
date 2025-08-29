/* ************************************************************************** */
#include "philo.h"

void ft_free_table(t_table *table)
{
    int i;

    i = 0;
    if (!table)
        return ;
    if (table->philos)
        free(table->philos); 
    while (i < table->nbr)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }    
    if (table->forks)
        free(table->forks);
    pthread_mutex_destroy(&table->printf_lock);
    free (table);
    return ;
}

int err_return_int(char *str, int i)
{
    if (str)
        printf("%s\n", str); //should I print stderr??
    return (i);
}