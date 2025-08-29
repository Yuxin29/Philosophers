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

uint64_t ft_to_sleep(t_table *table, t_philo *philo)
{
    (void)philo; 
    uint64_t    current_time;
    uint64_t    end_time;
    useconds_t  sleep_period;

    current_time = now_ms();
    if (!current_time)
        return (0);
    sleep_period = table->sleep_time * 1000;
    end_time = (uint64_t)sleep_period + current_time;
    usleep(sleep_period);
    return (end_time);
}

