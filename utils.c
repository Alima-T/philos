/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:08:34 by alima             #+#    #+#             */
/*   Updated: 2025/01/26 21:24:03 by alima            ###   ########.fr       */
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
	u_int64_t		sec;
	u_int64_t		microsec;
	u_int64_t		millisec;

	(gettimeofday(&time, NULL));
	sec = time.tv_sec;
	microsec = time.tv_usec;
	millisec = (sec * 1000) + (microsec / 1000);
	return (millisec);
}

// int ft_usleep(u_int64_t milliseconds) //didn't use remove before eval
// {
// 	u_int64_t start;
//
// 	start = get_time();
// 	while((get_time() - start) < milliseconds)
// 		usleep(500);
// 	return (0);
// }

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


// *** for valgrind lu, for normal run llu
// void	philos_msg(int msg_code, u_int64_t time, int id,
// 		pthread_mutex_t *print_mutex)
// {
// 	pthread_mutex_lock(print_mutex);
// 	if (msg_code == LEFT_FORK_TAKEN)
// 		printf("%lu %d has taken a fork\n", time, id); // lu is for valgrind
// 	else if (msg_code == RIGHT_FORK_TAKEN)
// 		printf("%lu %d has taken a fork\n", time, id);
// 	else if (msg_code == EATING)
// 		printf("%lu %d is eating\n", time, id);
// 	else if (msg_code == SLEEPING)
// 		printf("%lu %d is sleeping\n", time, id);
// 	else if (msg_code == THINKING)
// 		printf("%lu %d is thinking\n", time, id);
// 	else if (msg_code == DIED)
// 	{
// 		printf("%lu %d died\n", time, id);
// 		return ;
// 	}
// 	pthread_mutex_unlock(print_mutex);
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

// void	ft_exit(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->num_philos)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		pthread_mutex_destroy(&data->philos[i].lock);
// 	}
// 	pthread_mutex_destroy(&data->write);
// 	pthread_mutex_destroy(&data->lock);
// 	clear_data(data);
// }