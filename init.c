/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/27 12:15:39 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philos.h"

/* Инициализация основных данных программы */
int	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = atoi(av[5]);
	if (data->num_philos < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	return (0);
}
/*
pthread_mutex_init() - это функция инициализации мьютекса (mutex = mutual exclusion, взаимное исключение).
Параметры функции:
Первый параметр &data->print_mutex - указатель на мьютекс, который мы хотим инициализировать
Второй параметр NULL - атрибуты мьютекса (NULL означает использование атрибутов по умолчанию)
Возвращаемое значение:
0 - если инициализация прошла успешно
ненулевое значение - если произошла ошибка
Поэтому конструкция 
if (pthread_mutex_init(&data->forks[i], NULL))
		return (1);
означает: "Если инициализация мьютекса не удалась (вернула не 0), вернуть 1 (код ошибки)"
В нашей программе этот мьютекс (print_mutex) используется для:
Защиты вывода сообщений в консоль
Предотвращения смешивания сообщений от разных философов
*/

/* Инициализация мьютексов */
int	init_mutexes(t_data *data)
{
	int	i;
/* Инициализация мьютекса для вывода */
	if (pthread_mutex_init(&data->forks[i], NULL))
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

/* Инициализация структур философов */
int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].left_fork = get_time();
		(*philos)[i].data = data;
		(*philos)[i].left_fork = &data->forks[i];
		if (i == data->num_philos - 1)
			(*philos)[i].right_fork = &data->forks[0];
		else
			(*philos)[i].right_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}
