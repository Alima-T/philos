/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:08:34 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/28 14:55:37 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * [1][Number of philosophers]);
 * [2][Time to die];
 * [3][Time to eat];
 * [4][Time to sleep];
 * [5][Number of meals].
 * 1 second = 1000 ms = 1,000,000 microsec
 * get current time in  ms
 * gettimeofday get time since the Unix epoch (January 1, 1970)
 */


u_int64_t get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	error_msg(int err_num)
{
	if (err_num == WRONG_COUNT_OF_ARGS)
		printf(RED "Wrong number of arguments\n");
	else if (err_num == WRONG_ARG)
		printf(MAG "Wrong argument\n");
	else if (err_num == MALLOC_ERROR)
		printf(YELLOW "Error: malloc error\n");
	else if (err_num == PTHREAD_ERROR)
		printf(CYAN "Error: pthread error\n");
	else if (err_num == WRONG_ARG_LIMITS)
		printf(GRN "Limits error! Allowed: philos <= 200, time >= 60 ms.\n");
	return (1);
}

void	philos_msg(char *msg, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(philo->data->print_mutex);
	time = get_time() - philo->data->creation_time;
	if (ft_strcmp(DIED, msg) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, msg);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->data->print_mutex);
}

// *** for valgrind lu, for normal run llu
// void	philos_msg(char *msg, t_philo *philo)
// {
// 	u_int64_t	time;

// 	pthread_mutex_lock(philo->data->print_mutex);
// 	time = get_time() - philo->data->creation_time;
// 	if (ft_strcmp(DIED, msg) == 0 && philo->data->dead == 0)
// 	{
// 		printf("%lu %d %s\n", time, philo->id, msg);
// 		philo->data->dead = 1;
// 	}
// 	if (!philo->data->dead)
// 		printf("%lu %d %s\n", time, philo->id, msg);
// 	pthread_mutex_unlock(philo->data->print_mutex);
// }


int	ft_atoi_pos(const char *str)
{
	int		in;
	long	num;

	in = 0;
	num = 0;
	while (str[in] == ' ' || (str[in] >= 9 && str[in] <= 13))
		in++;
	while (str[in] >= '0' && str[in] <= '9')
	{
		num = num * 10 + (str[in] - '0');
		if (num > 2147483647)
			return (0);
		in++;
	}
	if (str[in] != '\0')
		return (0);
	return ((int)num);
}

// int	ft_atoi(const char *str)
// {
// 	int		in;
// 	// int		sign;
// 	long	num;

// 	in = 0;
// 	// sign = 1;
// 	num = 0;
// 	while(str[in] != '\0')
// 	{
// 		if (str[in] < 48 || str[in] > 57)
// 			return (0);
// 		in++;
// 	}
// 	in = 0;
// 	while ((((str[in] > 8) && (str[in] < 14)) || str[in] == 32)
// 		&& str[in] != '\0')
// 		in++;
// 	// if (str[in] == 43 || str[in] == 45)
// 	// 	sign = (str[in++] & 2) - 1;
// 	while ((str[in] > 47) && (str[in] < 58))
// 		num = num * 10 + (str[in++] - '0');
// 	// num = num * sign;
// 	if (num > 2147483647 || num < 0)
// 		return (0);
// 	return ((int)num);
// }
