/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:08:07 by yuwu              #+#    #+#             */
/*   Updated: 2025/09/07 14:15:33 by yuwu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// the input has to be pos int,
// return 1 on valid and 0 on invalid
static int	ft_is_pos_int(char *nptr)
{
	char	c;

	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-')
		return (0);
	if (*nptr == '+')
		nptr++;
	if (!*nptr)
		return (0);
	while (*nptr)
	{
		c = *nptr;
		if (c < '0' || c > '9')
			return (0);
		nptr++;
	}
	return (1);
}

// firsr check positive int
// then do atoi
// return 0 as error code for overflowing
int	safe_atoi(char *nptr)
{
	int	output;

	output = 0;
	if (!ft_is_pos_int(nptr))
		return (0);
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (('0' <= *nptr) && (*nptr <= '9'))
	{
		if (output > (2147483647 - (*nptr - '0')) / 10)
			return (0);
		output = output * 10 + (*nptr - '0');
		nptr++;
	}
	return (output);
}

// input check using safe aoit
// should used stderror, fprintf(stderr, "%s\n", str); but not
// return 0 as error code, 
int	pre_check_argv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: %s\n", "wrong argument number");
		return (0);
	}
	if (!safe_atoi(argv[1]) || !safe_atoi(argv[2])
		|| !safe_atoi(argv[3]) || !safe_atoi(argv[4]))
	{
		printf("Error: %s\n", "invalid argument");
		return (0);
	}
	if (argv[5] && !safe_atoi(argv[5]))
	{
		printf("Error: %s\n", "invalid argument");
		return (0);
	}
	return (1);
}

// free the table and philos, and destroy all the mutex
void	ft_free_table(t_table *table)
{
	int	i;

	i = 1;
	if (!table)
		return ;
	if (table->philos)
		free(table->philos);
	if (table->forks)
	{
		while (i <= table->nbr)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->printf_lock);
	pthread_mutex_destroy(&table->state_lock);
	free (table);
	return ;
}
