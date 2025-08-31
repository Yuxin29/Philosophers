/* ************************************************************************** */
#include "philo.h"

// precheck stop 
static int	precheck_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->table->state_lock);
	stop = philo->table->stop;
	pthread_mutex_unlock(&philo->table->state_lock);
	return (stop);
}

// eating steps of a philo
// pick up 2 forks(lock them)
// eat
// update meal numbers
// put down forks(unlock then)
static void	routine_eat(t_philo *philo)
{
	uint64_t	timestamp;

	if (precheck_stop(philo))
		return;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork_l]);
		pthread_mutex_lock(&philo->table->forks[philo->fork_r]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork_r]);
		pthread_mutex_lock(&philo->table->forks[philo->fork_l]);
	}
	pthread_mutex_lock(&philo->table->state_lock);
	philo->last_eating_time = now_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->state_lock);
	timestamp = now_ms() - philo->table->starting_time_ms;
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%lu, %d is eating\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->printf_lock);
	ft_to_eat(philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_l]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_r]);
}

static void	routine_sleep(t_philo *philo)
{
	uint64_t	timestamp;

	if (precheck_stop(philo))
        return;
    timestamp = now_ms() - philo->table->starting_time_ms;
	pthread_mutex_lock(&philo->table->printf_lock);
	printf("%lu, %d is sleeping\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->printf_lock);
	ft_to_sleep(philo->table);
}

// in pholosopher, there is not given time for sleep
// it does not uslepp. just print a msg
static void	routine_think(t_philo *philo)
{
	uint64_t	timestamp;

	if (precheck_stop(philo))
        return;
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
void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (precheck_stop(philo))
            break;
		routine_eat(philo);
		if (precheck_stop(philo))
            break;
		routine_sleep(philo);
        if (precheck_stop(philo))
            break;
		routine_think(philo);
	}
	return (NULL);
}
