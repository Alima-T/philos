/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:30 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/28 14:22:08 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Функция приема пищи философом
** 1. Блокируем левую вилку
** 2. Выводим сообщение о взятии вилки
** 3. Блокируем правую вилку
** 4. Выводим сообщение о взятии второй вилки
** 5. Обновляем время последнего приема пищи
** 6. Увеличиваем счетчик приемов пищи
** 7. Ждем time_to_eat миллисекунд
** 8. Освобождаем вилки */

void	eat_or_sleep(u_int64_t time)
{
	u_int64_t	start;
	u_int64_t	stop;

	start = get_time();
	stop = start + time;
	while (stop > start)
	{
		usleep(1000);
		start = get_time();
	}
}
void	take_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	philos_msg(LEFT_FORK_TAKEN, philos);
	pthread_mutex_lock(philos->right_fork);
	philos_msg(RIGHT_FORK_TAKEN, philos);
}

void	eat(t_philo *philos)
{
	philos_msg(EATING, philos);
	philos->time_last_ate = get_time();
	eat_or_sleep(philos->data->time_to_eat);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	if (philos->data->meals_required > 0)
	{
		philos->meals_eaten++;
		if (philos->meals_eaten >= philos->data->meals_required)
			philos->is_full = 1;
	}
}

void	sleep_think(t_philo *philos)
{
	philos_msg(SLEEPING, philos);
	eat_or_sleep(philos->data->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	philos->time_last_ate = get_time();
	philos->meals_eaten = 0;
	if (!(philos->id % 2)) // first Even-ID Philosophers (P0, P2)
		usleep(100);
	while (1)
	{
		take_forks(philos);
		eat(philos);
		sleep_think(philos);
		philos_msg(THINKING, philos);
	}
	return (NULL);
}
