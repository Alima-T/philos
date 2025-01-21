/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:08:34 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/21 16:40:40 by aokhapki         ###   ########.fr       */
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

u_int64_t	get_time(void)
{
	struct timeval	time;  
	u_int64_t			sec;
	u_int64_t			microsec;
	u_int64_t			millisec;

	(gettimeofday(&time, NULL));
	sec = time.tv_sec;
	microsec = time.tv_usec;
	millisec = (sec * 1000) + (microsec / 1000);
	return (millisec);
}

// int ft_usleep(u_int64_t milliseconds) //didn't use
// {
// 	u_int64_t start;
	
// 	start = get_time();
// 	while((get_time() - start) < milliseconds)
// 		usleep(500);
// 	return (0);
// }

int	error_msg(int err_num)
{
	if (err_num == WRONG_COUNT_OF_ARGS)
		printf("wrong number of arguments\n");
	else if (err_num == WRONG_ARG)
		printf("wrong argument\n");
	else if (err_num == MALLOC_ERROR)
		printf("malloc error\n");
	else if (err_num == PTHREAD_ERROR)
		printf("pthread error\n");
	return (1);
}

// void	philos_msg(int msg_code, u_int64_t time, int id,
// 		pthread_mutex_t *print_mutex)
// {
// 	pthread_mutex_lock(print_mutex);
// 	if (msg_code == LEFT_FORK_TAKEN)
// 		printf("%llu %d has taken a fork\n", time, id);
// 	else if (msg_code == RIGHT_FORK_TAKEN)
// 		printf("%llu %d has taken a fork\n", time, id);
// 	else if (msg_code == EATING)
// 		printf("%llu %d is eating\n", time, id);
// 	else if (msg_code == SLEEPING)
// 		printf("%llu %d is sleeping\n", time, id);
// 	else if (msg_code == THINKING)
// 		printf("%llu %d is thinking\n", time, id);
// 	else if (msg_code == DIED)
// 	{
// 		printf("%llu %d died\n", time, id);
// 		return ;
// 	}
// 	pthread_mutex_unlock(print_mutex);
// }

// *** for valgrind lu, for normal run llu
void	philos_msg(int msg_code, u_int64_t time, int id,
		pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	if (msg_code == LEFT_FORK_TAKEN)
		printf("%lu %d has taken a fork\n", time, id); // lu is for valgrind
	else if (msg_code == RIGHT_FORK_TAKEN)
		printf("%lu %d has taken a fork\n", time, id);
	else if (msg_code == EATING)
		printf("%lu %d is eating\n", time, id);
	else if (msg_code == SLEEPING)
		printf("%lu %d is sleeping\n", time, id);
	else if (msg_code == THINKING)
		printf("%lu %d is thinking\n", time, id);
	else if (msg_code == DIED)
	{
		printf("%lu %d died\n", time, id);
		return ;
	}
	pthread_mutex_unlock(print_mutex);
}

int	ft_atoi(const char *str)
{
	int		in;
	int		sign;
	long	num;

	in = 0;
	sign = 1;
	num = 0;
	while ((((str[in] > 8) && (str[in] < 14)) || str[in] == 32)
		&& str[in] != '\0')
		in++;
	if (str[in] == 43 || str[in] == 45)
		sign = (str[in++] & 2) - 1;
	if (str[in] < 48 || str[in] > 57)
		return (0);
	while ((str[in] > 47) && (str[in] < 58))
		num = num * 10 + (str[in++] - '0');
	num = num * sign;
	if (num > 2147483647)
		return (-1);
	if (num < -2147483648)
		return (0);
	return ((int)num);
}
