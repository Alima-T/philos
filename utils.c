/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:08:34 by alima             #+#    #+#             */
/*   Updated: 2025/01/02 12:27:25 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Получение текущего времени в миллисекундах
** Использует gettimeofday для получения времени с начала эпохи
** Конвертирует секунды и микросекунды в миллисекунды */
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

void	philos_msg(int msg_code, long time, int id, pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	if (msg_code == LEFT_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", time, id);
	else if (msg_code == RIGHT_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", time, id);
	else if (msg_code == EATING)
		printf("%ld %d is eating\n", time, id);
	else if (msg_code == SLEEPING)
		printf("%ld %d is sleeping\n", time, id);
	else if (msg_code == THINKING)
		printf("%ld %d is thinking\n", time, id);
	else if (msg_code == DIED)
	{
		printf("%ld %d died\n", time, id);
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
	while ((((str[in] > 8) && (str[in] < 14)) || str[in] == 32) && \
			str[in] != '\0')
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
// void	ft_check_args(void)
// {
// 	printf(" ____________________________________________________ \n");
// 	printf("|            Please enter 4 or 5 arguments           |\n");
// 	printf("|____________________________________________________|\n");
// 	printf("|             [1][Number of philosophers]            |\n");
// 	printf("|             [2][Time to die]                       |\n");
// 	printf("|             [3][Time to eat]                       |\n");
// 	printf("|             [4][Time to sleep]                     |\n");
// 	printf("|             [5][Number of meals]                   |\n");
// 	printf("|____________________________________________________|\n");
// }