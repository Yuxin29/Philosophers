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

    philo->last_eating_time = now_ms();

    timestamp = now_ms() - philo->table->starting_time_ms;
    //printing
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("%lu, %d is eating\n", timestamp, philo->id + 1);
    pthread_mutex_unlock(&philo->table->printf_lock);
    
    
    ft_to_eat(philo->table);
    philo->meals_eaten += 1;

    pthread_mutex_unlock(&philo->table->forks[l]);
    pthread_mutex_unlock(&philo->table->forks[r]);
}

static void routine_sleep(t_philo *philo)
{
    uint64_t    timestamp;
    
    timestamp = now_ms() - philo->table->starting_time_ms;; 
    //printing
    pthread_mutex_lock(&philo->table->printf_lock);
    printf("%lu, %d is sleeping\n", timestamp, philo->id + 1);
    pthread_mutex_unlock(&philo->table->printf_lock);

    ft_to_sleep(philo->table);
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


static int check_all_philo_done(t_table *table)
{
    int i;

    i = 0;
    if (table->total_eating_time == -1)
        return (0); // no limitation, not done
    while (i < table->nbr)
    {
        if (table->philos[i].meals_eaten < table->total_eating_time)
            return (0);
        i++;
    }
    return (1); //done
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
    int         done;

    philo = (t_philo *)arg;

    while (1)
    {
        if (now_ms() - philo->last_eating_time >= (uint64_t)philo->table->to_die_time)
        {
            // death msg
            break ;
        }
        pthread_mutex_lock(&philo->table->printf_lock);
        done = check_all_philo_done(philo->table);
        pthread_mutex_unlock(&philo->table->printf_lock);
        if (done)
        {
            // all philos has eater wnough
            break ;
        }
        routine_eat(philo);
        routine_sleep(philo);
        routine_think(philo);
    }

    return (NULL);
}
