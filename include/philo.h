

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> //gettimeofday
# include <string.h> //memset
# include <unistd.h> //usleep, write
# include <stdio.h> //printf
# include <stdlib.h> //malloc. free  , gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join, 
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock. pthread_mutex_unlocK

typedef struct s_philo
{
	int		id; //the nbr of philos: eg -
	int		fork_l;	//eg: 0
	int		fork_r;	//eg: 1
	int		meals_eaten; // already eaten meals;
}			t_philo;

//struct
typedef struct s_table
{
	int		nbr;			//nbr of philos
	int		to_die_time;	//need to eat or die
	int		eat_time;		//the time spent for each meal 
	int		sleep_time;		//the time spent for echo sleep
	int		total_eating_time;	//if all philos has eated this number, ends
	t_philo *philos;
}			t_table;

// init.c
// I parse the input and put it to the t_table
t_table *init_table(char **argv);
pthread_t	*create_threads(t_table *philo_table);
void		joint_all_threads(pthread_t *tids, t_table *philo_table);

// utils.c
int	        safe_atoi(char *nptr);

//err_msg.c
int err_return_int(char *str, int i);

//philo.c
//int main(int argc, char **argv)

#endif
