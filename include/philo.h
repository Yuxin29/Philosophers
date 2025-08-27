

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> //gettimeofday
# include <string.h> //memset
# include <unistd.h> //usleep, write
# include <stdio.h> //printf
# include <stdlib.h> //malloc. free  , gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join, 
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock. pthread_mutex_unlocK

//struct
typedef struct s_table
{
	int		nbr;
	int		to_die_time;
    int     eat_time;
    int     sleep_time;
    int     total_eating_time;
}			t_table;

//init.c
// I parse the input and put it to the t_table
void get_table(t_table *table, char **argv);

// utils.c
int	ft_atoi(char *nptr);

//philo.c
//int main(int argc, char **argv)

#endif
