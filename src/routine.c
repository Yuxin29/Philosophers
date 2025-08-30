/* ************************************************************************** */
#include "philo.h"


// 123     2           has taken a fork
// 123     2           is eating
// 456     2           is sleeping
// 789     2           is thinking
// 999     2           died
// time    philoid     action

// eating steps of a philo
// pick up 2 forks(lock them)
// eat
// update meal numbers
// put down forks(unlock then)
static void routine_eat(t_philo *philo)
{
    int l;
    int r;
    uint64_t    timestamp;

    l = philo->fork_l;
    r = philo->fork_r;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->forks[l]);
        pthread_mutex_lock(&philo->table->forks[r]);
    }
    else
    {
        pthread_mutex_lock(&philo->table->forks[r]);
        pthread_mutex_lock(&philo->table->forks[l]);
    }

    timestamp = ft_to_eat(philo->table, philo); 

    //printing
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("%lu, %d is eating\n", timestamp, philo->id + 1);
    pthread_mutex_unlock(&philo->table->printf_lock);

    pthread_mutex_unlock(&philo->table->forks[l]);
    pthread_mutex_unlock(&philo->table->forks[r]);
    philo->meals_eaten += 1;
}

static void routine_sleep(t_philo *philo)
{
    uint64_t    timestamp;
    
    timestamp = ft_to_sleep(philo->table, philo); 

    //printing
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("%lu, %d is sleeping\n", timestamp, philo->id + 1);
    pthread_mutex_unlock(&philo->table->printf_lock);
}

// in pholosopher, there is not given time for sleep, it does not uslepp. just print a msg
static void routine_think(t_philo *philo)
{
    uint64_t    timestamp;

    timestamp = now_ms() - philo->table->starting_time_ms;

    pthread_mutex_lock(&philo->table->printf_lock);
    printf("%lu, %d is thinking\n", timestamp, philo->id + 1);
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

    philo = (t_philo *)arg;

    while (philo->meals_eaten < 3)
    //later, this should be checking if it is dead
    {
        routine_eat(philo);
        routine_sleep(philo);
        routine_think(philo);
        printf("The philospher %d is done for this round\n\n", philo->id + 1);
    }
    printf("%s\n\n", "All philosophers are done with everythings");

    return (NULL);
}
