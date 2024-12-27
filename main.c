/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:43 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/27 12:15:44 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philos.h"

/* Создание потоков для каждого философа
** 1. Устанавливаем время начала симуляции
** 2. Для каждого философа:
**    - Устанавливаем время последнего приема пищи
**    - Создаем поток с функцией philo_routine
** 3. Возвращаем 0 при успехе, 1 при ошибке */
static int	create_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		philos[i].last_meal = get_time();
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}

/* Ожидание завершения всех потоков философов
** Использует pthread_join для каждого потока */
static void	join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

/* Основная функция
** 1. Проверка количества аргументов
** 2. Инициализация данных, мьютексов и философов
** 3. Создание потоков
** 4. Ожидание завершения потоков
** 5. Освобождение ресурсов */
int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, ac, av) || init_mutexes(&data)
		|| init_philos(&philos, &data))
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	if (create_threads(philos, &data))
	{
		printf("Error: thread creation failed\n");
		free_all(&data, philos);
		return (1);
	}
	join_threads(philos, &data);
	free_all(&data, philos);
	return (0);
}
