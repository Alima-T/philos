/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:30 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/27 12:15:31 by aokhapki         ###   ########.fr       */
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
void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	smart_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/* Функция сна и размышления философа
** 1. Выводим сообщение о начале сна
** 2. Спим time_to_sleep миллисекунд
** 3. Выводим сообщение о начале размышлений */
void	sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death(philo))
	{
		if (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}
