/* ************************************************************************** */
#include "philo.h"

// for testing
// later, it should be start_routine, the eat, think and sleep routine
void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("Philosopher %d, is sleeping\n", philo->id + 1);
    pthread_mutex_unlock(&philo->table->printf_lock);
    ft_to_sleep(philo->table, philo); 

    return (NULL);
}