/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/21 16:45:09 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* data from input */
int	init_av_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error_msg(WRONG_COUNT_OF_ARGS)); 
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = 0; 
	// (av[5] - option - count of required meal, by default = 0 // check if all arguments more than 0
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (error_msg(WRONG_ARG));
	// send and check (av[5])6th arg (required meal) optionally
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required < 1) 
			return (error_msg(WRONG_ARG)); 
	}
	return (0); // success
}

/* init struct of philos */
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
			// Указатели на вилки (циклически)
		philos[i].data = data;                                   
			// Привязываем философа к общим данным
		if (data->meals_required > 0)                            
			// if 6th arg count eaten meal and not_hungry
		{
			philos[i].meals_eaten = 0;
			philos[i].is_full = 0;
		}
		i++;
	}
}
// destroy mutexes for data_output and left_fork 
void	destroy_mutex(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->print_mutex);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		i++;
	}
}
//fix start_time, allocate mem for array of philo's threads, create thread for each philo 1 - error, 0 - success	
int	run_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	*philo_threads;

	data->creation_time = get_time();
	philo_threads = malloc(sizeof(pthread_t) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_threads[i], NULL, philo_routine,
				(void *)&philos[i]) != 0)
				return (error_msg(PTHREAD_ERROR));
		i++;
	}
	// Detaches each philosopher thread to allow resources to be freed automatically when the thread exits; 
	i = 0; // doesn't change anythig with or without this code
	while (i < data->num_philos)
	{
		if (pthread_detach(philo_threads[i]) != 0)
			return (error_msg(PTHREAD_ERROR));
		i++;
	}
	if (philo_checker(philos) != 0)
		return (1);
	destroy_mutex(philos, data);
	free(philo_threads);
	//****/ with this code we free all allocations but gives more errors in valgrind and with normal run. Without this code frees always 7 allocations and 2 errors
	// i = 0; 
	// while (i < data->num_philos)
	// {
	// 	free(&philos[i]);
	// 	i++;
	// }
	//****/
	return (0);
}

// allocate mem for philos, forks and mutex_for_data_output, 1 - error, 0 - success	
int	start_sim(t_data *data)
{
	t_philo			*philos;
	pthread_mutex_t	*fork;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos || !fork || !data->print_mutex)
		return (error_msg(MALLOC_ERROR));
	pthread_mutex_init(data->print_mutex, NULL);
	init_philos(philos, data, fork);
	if (run_threads(philos, data) != 0)
		return (1);
	free(fork);
	free(data->print_mutex);
	free(philos);
	return (0);
}
