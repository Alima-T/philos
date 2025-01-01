/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/01 17:58:42 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philos.h"

/* Инициализация основных данных программы */

int	init_av_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return(1);
	data->num_philos = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->meals_required = 0;
	if (ac == 6)
	{
		data->meals_required = atoi(av[5]);
		if (data->meals_required < 1)
		return(1);
	}	
	if (data->num_philos < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	return (0);
}

/* Инициализация структур философов */
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&fork[i], NULL);
		philos[i].id = i + 1;
		philos[i].left_fork = &fork[i];
		philos[i].right_fork = &fork[(i + 1) % data->num_philos];
		philos[i].data = data;
		if (data->meals_required > 0)
		{
			philos[i].meals_eaten = 0;
			philos[i].is_full = 0;	
		}	
		i++;
	}
}
