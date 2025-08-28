/* ************************************************************************** */
#include "philo.h"

//not needed yet
// static void ft_free_philos(t_philo *philo)
// {
//     ...
//     return;
// }

void ft_free_table(t_table *table)
{
    if (!table)
        return ;
    if (table->philos)
        free(table->philos); 
    return ;
}

int err_return_int(char *str, int i)
{
    if (str)
        printf("%s\n", str); //should I print stderr??
    return (i);
}