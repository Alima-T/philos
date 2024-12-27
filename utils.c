/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:08:34 by alima             #+#    #+#             */
/*   Updated: 2024/12/26 22:37:35 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/* Получение текущего времени в миллисекундах
** Использует gettimeofday для получения времени с начала эпохи
** Конвертирует секунды и микросекунды в миллисекунды */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Умная задержка с периодической проверкой
** Вместо простого usleep используем активное ожидание
** с периодическими короткими паузами для более точного timing */
void	smart_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

/* Безопасный вывод статуса философа
** 1. Блокируем мьютекс печати
** 2. Проверяем, жив ли философ
** 3. Выводим сообщение с временной меткой
** 4. Освобождаем мьютекс */
void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo))
		printf("%lld %d %s\n",
			get_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/* Проверка смерти философа
** 1. Блокируем мьютекс смерти
** 2. Проверяем флаг общей смерти
** 3. Проверяем время с последнего приема пищи
** 4. Если прошло больше time_to_die:
**    - Устанавливаем флаг смерти
**    - Выводим сообщение о смерти
** 5. Освобождаем мьютекс */
int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	if (get_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d died\n",
			get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

/* Освобождение всех ресурсов
** 1. Уничтожаем все мьютексы вилок
** 2. Уничтожаем мьютексы печати и смерти
** 3. Освобождаем выделенную память */
void	free_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(philos);
}
