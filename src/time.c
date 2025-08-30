/* ************************************************************************** */
#include "philo.h"

// I am going to use millisecond,  毫秒 in my philosopher
// struct timeval {
//     time_t      tv_sec;   // s
//     suseconds_t tv_usec;  // 1µs (1µs = 10^-6 s)
// };
// gettimeofday, settimeofday - get / set time
//     --> return the time on the wall in millisecond, "real-world time"
uint64_t now_ms(void)
{
    struct timeval current_time;
    uint64_t       time_ms;

    if (gettimeofday(&current_time, NULL) == -1)
        return (0);  // my error code
    time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (time_ms);
}

// returns the comparative time stamp only
uint64_t ft_to_sleep(t_table *table, t_philo *philo)
{
    (void)philo; 
    uint64_t    timestamp;
    useconds_t  sleep_period;
    
    timestamp = now_ms() - table->starting_time_ms;
    sleep_period = table->sleep_time * 1000;
    usleep(sleep_period  * 1000); //us
    return (timestamp);
}

uint64_t ft_to_eat(t_table *table, t_philo *philo)
{
    (void)philo;
    uint64_t    timestamp;
    useconds_t  eating_period;
    
    timestamp = now_ms() - table->starting_time_ms;
    eating_period = table->eat_time * 1000;
    usleep(eating_period  * 1000); //us
    return (timestamp);
}
