/* ************************************************************************** */
#include "philo.h"

// for testing
// later, it should be start_routine, the eat, think and sleep routine
void *routine(void *arg)
{
    t_philo     *philo;
    uint64_t    end_time;

    philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->table->printf_lock);
    printf("The starting time of the table is %lu\n", philo->table->starting_time_ms);
    printf("Philosopher %d, is sleeping\n", philo->id + 1);
    end_time = ft_to_sleep(philo->table, philo); 
    printf("after the sleep, the time is %lu\n", end_time);
    pthread_mutex_unlock(&philo->table->printf_lock);
    return (NULL);
}
