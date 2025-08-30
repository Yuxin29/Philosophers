/* ************************************************************************** */
#include "philo.h"

// eating steps of a philo
// pick up 2 forks(lock them)
// eat
// update meal numbers
// put down forks(unlock then)
static void routine_eat(t_philo *philo)
{
    int l;
    int r;

    l = philo->fork_l;
    r = philo->fork_r;
    pthread_mutex_lock(&philo->table->printf_lock);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->forks[l]);
        pthread_mutex_lock(&philo->table->forks[r]);
    }
    printf("The philospher %d has taken 2 forks\n", philo->id);
    printf("The philospher %d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->table->forks[l]);
    pthread_mutex_unlock(&philo->table->forks[r]);
    pthread_mutex_unlock(&philo->table->printf_lock);

}

// for testing
// later, it should be start_routine, the eat, think and sleep routine
// routine of a philo
// eat
// think
// sleep
void *routine(void *arg)
{
    t_philo     *philo;
    uint64_t    end_time;

    philo = (t_philo *)arg;

    //check if it is dead

    //sleep
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("The starting time of the table is %lu\n", philo->table->starting_time_ms);
    printf("Philosopher %d, is sleeping\n", philo->id + 1);
    end_time = ft_to_sleep(philo->table, philo); 
    printf("after the sleep, the time is %lu\n", end_time);
    pthread_mutex_unlock(&philo->table->printf_lock);

    //eat
    routine_eat(philo);

    //think

    return (NULL);
}
