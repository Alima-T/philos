/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:30 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/28 17:29:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/* Функция приема пищи философом
** 1. Блокируем левую вилку
** 2. Выводим сообщение о взятии вилки
** 3. Блокируем правую вилку
** 4. Выводим сообщение о взятии второй вилки
** 5. Обновляем время последнего приема пищи
** 6. Увеличиваем счетчик приемов пищи
** 7. Ждем time_to_eat миллисекунд
** 8. Освобождаем вилки */

void	eat_or_sleep(long time)
{
	long	start;
	long	stop;

	start = get_time();
	stop = start + time;
	while (stop > start)
	{
		usleep(50);
		start = get_time();
	}
}
void	eat(t_philo *philos)
{
	philos_msg(EATING, get_time() - philos->data->creation_time, \
				philos->id, philos->data->print_mutex);
	philos->last_meal = get_time();
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
	philos_msg(SLEEPING, get_time() - philos->data->creation_time, \
				philos->id, philos->data->print_mutex);
	eat_or_sleep(philos->data->time_to_sleep);
}
/* Функция сна и размышления философа
** 1. Выводим сообщение о начале сна
** 2. Спим time_to_sleep миллисекунд
** 3. Выводим сообщение о начале размышлений */
// void	sleep_think(t_philo *philo)
// {
// 	print_status(philo, "is sleeping");
// 	smart_sleep(philo->data->time_to_sleep);
// 	print_status(philo, "is thinking");
// }

void	take_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	philos_msg(LEFT_FORK_TAKEN, get_time() - philos->data->creation_time, \
				philos->id, philos->data->print_mutex);
	pthread_mutex_lock(philos->right_fork);
	philos_msg(RIGHT_FORK_TAKEN, get_time() - philos->data->creation_time, \
				philos->id, philos->data->print_mutex);
}
/* Основная функция потока философа
** 1. Приводим void* к t_philo*
** 2. Для четных философов добавляем задержку (предотвращение дедлока)
** 3. Пока философ жив и не съел необходимое количество раз:
**    - Едим
**    - Спим
**    - Думаем */

void	*philo_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	philos->last_meal = get_time();
	philos->meals_eaten = 0;
	if (!(philos->id % 2))
		usleep(100);
	while (1)
	{
		take_forks(philos);
		eat(philos);
		sleep_think(philos);
		philos_msg(THINKING, get_time() - philos->data->creation_time, philos->id, \
					philos->data->print_mutex);
	}
	return (NULL);
}
// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		usleep(1000);
// 	while (!check_death(philo))
// 	{
// 		if (philo->data->meals_required != -1
// 			&& philo->meals_eaten >= philo->data->meals_required)
// 			break ;
// 		eat(philo);
// 		sleep_think(philo);
// 	}
// 	return (NULL);
// }
