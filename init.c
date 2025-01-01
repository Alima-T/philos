/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/01 23:14:57 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Инициализация основных данных программы */

int	init_av_data(t_data *data, int ac, char **av)
{
	// Проверяем количество аргументов (должно быть 5 или 6)
	if (ac < 5 || ac > 6)
		return (error_msg(WRONG_COUNT_OF_ARGS)); // Выводим ошибку, если аргументов недостаточно или слишком много

	// Считываем данные из аргументов командной строки
	data->num_philos = ft_atoi(av[1]);   // Количество философов
	data->time_to_die = ft_atoi(av[2]);     // Время до смерти без еды
	data->time_to_eat = ft_atoi(av[3]);     // Время на прием пищи
	data->time_to_sleep = ft_atoi(av[4]);   // Время на сон
	data->meals_required = 0;           // Изначально количество обязательных приемов пищи равно 0

	// Проверяем, что все значения положительные
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (error_msg(WRONG_ARG)); // Выводим ошибку, если значения некорректны

	// Если передан шестой аргумент (количество приемов пищи), обрабатываем его
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]); // Количество обязательных приемов пищи
		if (data->meals_required < 1)           // Проверяем, что значение корректно
			return (error_msg(WRONG_ARG));   // Выводим ошибку, если значение некорректно
	}
	return (0); // Возвращаем 0, если все данные корректны
}

/* Инициализация структур философов */
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&fork[i], NULL);// Инициализируем мьютексы для вилок
		philos[i].id = i + 1;// Присваиваем философу ID
		philos[i].left_fork = &fork[i];                         // Указатели на вилки
		philos[i].right_fork = &fork[(i + 1) % data->num_philos];  // Указатели на вилки (циклически)
		philos[i].data = data;// Привязываем философа к общим данным
		if (data->meals_required > 0)// Если задано количество приемов пищи, инициализируем счетчики
		{
			philos[i].meals_eaten = 0; // Счетчик съеденных приемов пищи
			philos[i].is_full = 0;     // Индикатор сытости
		}
		i++;
	}
}

void	destroy_mutex(t_philo *philos, t_data *data)
{
	int	i;
	
	i = 0;
	pthread_mutex_destroy(data->print_mutex);// Уничтожаем мьютекс для вывода
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(philos[i].left_fork); // Уничтожаем мьютекс вилки
		i++;
	}
}

int	run_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	*philo_threads;

	data->creation_time = get_time();	// Фиксируем время начала симуляции
	philo_threads = malloc(sizeof(pthread_t) * data->num_philos);// Выделяем память для массива потоков философов
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_threads[i], NULL, philo_routine, (void *)&philos[i]) != 0)// Создаем поток для каждого философа
			return (error_msg(PTHREAD_ERROR)); // Выводим ошибку, если поток не создан
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_detach(philo_threads[i]) != 0)// Отсоединяем поток, чтобы он завершался сам
			return (error_msg(PTHREAD_ERROR)); // Выводим ошибку, если отсоединение не удалось
		i++;
	}
	if (philo_checker(philos) != 0)// Проверяем состояние философов (функция philo_checker)
		return (1); // Возвращаем 1, если обнаружена ошибка
	destroy_mutex(philos, data);// Уничтожаем мьютексы и освобождаем память для потоков
	free(philo_threads);
	return (0); // Возвращаем 0, если все прошло успешно
}

int start_sim(t_data *data)
{
	t_philo			*philos;
	pthread_mutex_t	*fork;
	// Выделяем память для философов, вилок и мьютекса вывода
	philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos || !fork || !data->print_mutex)
		return (error_msg(MALLOC_ERROR)); // Выводим ошибку, если память не выделена
	pthread_mutex_init(data->print_mutex, NULL);// Инициализируем мьютекс для вывода
	init_philos(philos, data, fork);// Инициализируем философов и вилки
	if (run_threads(philos, data) != 0)// Запускаем симуляцию
		return (1); // Выходим, если произошла ошибка
	free(fork);
	free(data->print_mutex);
	free(philos);
	return (0); // Возвращаем 0, если симуляция завершилась успешно
}
