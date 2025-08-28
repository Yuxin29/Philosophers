/* ************************************************************************** */
#include "philo.h"

// for testing
// later, it should be start_routine, the eat, think and sleep routine
void *thread_fn(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_t tid = pthread_self();
    printf("Philosopher %d, thread ID = %lu\n", philo->id + 1, (unsigned long)tid);
    return (NULL);
}