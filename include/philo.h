/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:45 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/01 18:14:16 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h> 	//uint64_t
# include <sys/time.h> 	//gettimeofday
# include <string.h> 	//memset
# include <unistd.h> 	//usleep, write
# include <stdio.h> 	//printf
# include <stdlib.h> 	//malloc. free, gettimeofday
# include <pthread.h>	// pthread_create, pthread_detach, pthread_join, 
						// pthread_mutex_init, pthread_mutex_destroy, 
						// pthread_mutex_lock. pthread_mutex_unlocK
//this is not needed, here just for info
// struct timeval {
//     time_t      tv_sec;   // s
//     suseconds_t tv_usec;  // 1µs (1µs = 10^-6 s)
// };

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id; //the nbr of philos: eg -
	int				fork_l;	//eg: 0
	int				fork_r;	//eg: 1
	int				meals_eaten; // already eaten meals;
	pthread_t		thread;
	uint64_t		last_eating_time;
	t_table			*table;
}					t_philo;

//struct
typedef struct s_table
{
	int				nbr;				//nbr of philos
	int				to_die_time;		//need to eat or die
	int				eat_time;			//the time spent for each meal 
	int				sleep_time;			//the time spent for echo sleep
	int				total_eating_time;	//if all philos eated this number, ends
	int				dead;				//monitoring if anyone dead
	int				stop;				//1 for stop and
	uint64_t		starting_time;	// this is needed
	t_philo			*philos;
	pthread_mutex_t	*forks;				//same amount as philos
	pthread_mutex_t	printf_lock;		//protext printf overlapping
	pthread_mutex_t	state_lock;			//protext stop and dead
}					t_table;

//philo.c 4/5
//int main(int argc, char **argv)
int 		ft_is_stoped(t_table *table);
void		*monitor(void *arg);

// preparsing.c		4/5
int			safe_atoi(char *nptr);
int			pre_check_argv(int argc, char **argv);

// parsing.c				5/5
// I parse the input and put it to the t_table
t_table		*init_table(char **argv);

// utils.c	4/5
uint64_t	now_ms(void);
void		ft_to_sleep(t_table *table);
void		ft_to_eat(t_table *table);
void		ft_free_table(t_table *table);

//routine.c 5/5
void		*routine(void *arg); // not meaningful, redifine later

#endif
