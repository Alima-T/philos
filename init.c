/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/19 20:48:40 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Инициализация основных данных программы */
int	init_av_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error_msg(WRONG_COUNT_OF_ARGS)); 
	data->num_philos = ft_atoi(av[1]);    // philos num
	data->time_to_die = ft_atoi(av[2]);   // tm to die
	data->time_to_eat = ft_atoi(av[3]);   // tm to eat
	data->time_to_sleep = ft_atoi(av[4]); // tm to sleep
	data->meals_required = 0; // option - count of required meal, by default = 0
	// check if all arguments more than 0
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (error_msg(WRONG_ARG));
	// send and check 6th arg (required meal) optionally
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);// option - count of required meal
		if (data->meals_required < 1) // check that it is more than 0
			return (error_msg(WRONG_ARG)); 
	}
	return (0); // Возвращаем 0, если все корректнo
}

/* Инициализация структур философов */
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&fork[i], NULL);                      
			// Инициализируем мьютексы для вилок
		philos[i].id = i + 1;                                    
			// Присваиваем философу ID
		philos[i].left_fork = &fork[i];                          
			// Указатели на вилки
		philos[i].right_fork = &fork[(i + 1) % data->num_philos];
			// Указатели на вилки (циклически)
		philos[i].data = data;                                   
			// Привязываем философа к общим данным
		if (data->meals_required > 0)                            
			// Если задано количество приемов пищи, инициализируем счетчики
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
	pthread_mutex_destroy(data->print_mutex); // Уничтожаем мьютекс для вывода
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

	data->creation_time = get_time();                            
		// Фиксируем время начала симуляции
	philo_threads = malloc(sizeof(pthread_t) * data->num_philos);
		// Выделяем память для массива потоков философов
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_threads[i], NULL, philo_routine,
				(void *)&philos[i]) != 0) // create thread for each philo
				return (error_msg(PTHREAD_ERROR)); // Выводим ошибку,поток не создан
		i++;
	}
	// Detaches each philosopher thread to allow resources to be freed automatically when the thread exits; 
	i = 0; // doesn't change anythig with or without this code
	while (i < data->num_philos)
	{
		if (pthread_detach(philo_threads[i]) != 0)
			return (error_msg(PTHREAD_ERROR));//returns an error message if pthread_detach fails.
		i++;
	}
	if (philo_checker(philos) != 0)
		return (1);//  1 - ошибка
	// destroy and free
	destroy_mutex(philos, data);   
	free(philo_threads);
	//****/ with this code we free all allocations but gives more of errors in valgrind. without this code frees always 7 allocations and 2 errors
	i = 0; 
	while (i < data->num_philos)
	{
		free(&philos[i]);
		i++;
	}
	//****/
	return (0); //  0 - успешно
}

int	start_sim(t_data *data)
{
	t_philo			*philos;
	pthread_mutex_t	*fork;

	// Выделяем память для философов, вилок и мьютекса вывода
	philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos || !fork || !data->print_mutex)
		return (error_msg(MALLOC_ERROR)); // ошибкa, память не выделена
	pthread_mutex_init(data->print_mutex, NULL);
	init_philos(philos, data, fork); // Иниц философов и вилки
	if (run_threads(philos, data) != 0) // Запускаем симуляцию
		return (1);// 1 - ошибка
	free(fork);
	free(data->print_mutex);
	free(philos);
	return (0); // 0 - успешно
}
