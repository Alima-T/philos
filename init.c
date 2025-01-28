/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/28 14:43:23 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* init data from input
 * @param av[5] - option - num of requirmeal, by default = 0
 * @return:  0 success
 */
int	init_av_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error_msg(WRONG_COUNT_OF_ARGS));
	data->num_philos = ft_atoi_pos(av[1]);
	data->time_to_die = ft_atoi_pos(av[2]);
	data->time_to_eat = ft_atoi_pos(av[3]);
	data->time_to_sleep = ft_atoi_pos(av[4]);
	data->meals_required = 0;
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (error_msg(WRONG_ARG));
	if (data->num_philos > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (error_msg(WRONG_ARG_LIMITS));
	if (ac == 6)
	{
		data->meals_required = ft_atoi_pos(av[5]);
		if (data->meals_required < 1)
			return (error_msg(WRONG_ARG));
	}
	return (0);
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
		philos[i].data = data;
		if (data->meals_required > 0)
		{
			philos[i].meals_eaten = 0;
			philos[i].is_full = 0;
		}
		i++;
	}
}

/* destroy mutexes for data_output and left_fork */ 
void	destroy_mutex(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->print_mutex);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		// ***** checked with this to avoid leaks, didn't help
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}

/* fix start_time, allocate mem for array of philo's threads,
 * @param creates thread for each philo 
 * @return:  1 - error, 0 - success
 */
int	run_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	*philo_ths;

	data->creation_time = get_time();
	philo_ths = malloc(sizeof(pthread_t) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_ths[i], NULL, philo_routine,
				(void *)&philos[i]) != 0)
			return (error_msg(PTHREAD_ERROR));
		i++;
	}
	if (philo_checker(philos) != 0)
		return (1);
	// Detaches each philosopher thread to allow resources to be freed automatically when the thread exits;
	i = 0;
	while (i < data->num_philos)
	{
		// printf("Before detjoin\n");
		// if (pthread_join(philo_ths[i], NULL) != 0) //infinity loop
		if (pthread_detach(philo_ths[i]) != 0) // looks working, check leaks
			return (error_msg(PTHREAD_ERROR));
		// pthread_join(philo_ths[i], NULL); //stops and does not join
		// printf("After detjoin\n");
		i++;
	}
	destroy_mutex(philos, data);
	free(philo_ths);
	return (0);
}


/** v2 */
// int	run_threads(t_philo *philos, t_data *data)
// {
// 	int			i;
// 	pthread_t	*philo_ths;

// 	philo_ths = malloc(sizeof(pthread_t) * data->num_philos);
// 	if (!philo_ths)
// 		return (error_msg(MALLOC_ERROR));
// 	data->creation_time = get_time();

// 	i = 0;
// 	while (i < data->num_philos)
// 	{
// 		if (pthread_create(&philo_ths[i], NULL, philo_routine,(void *)&philos[i]) != 0)
// 		{
// 			while (--i >= 0) // Join already-created threads
// 				pthread_join(philo_ths[i], NULL);
// 			free(philo_ths);
// 			return (error_msg(PTHREAD_ERROR));
// 		}
// 		i++;
// 	}
// 	if (philo_checker(philos) != 0)
// 	{
// 		i = 0;
// 		while (i < data->num_philos)
// 		{
// 			printf("Before join\n");
// 			pthread_join(philo_ths[i], NULL);
// 			printf("After join\n");
// 			i++;
// 		}
// 		free(philo_ths);
// 		printf("after free1\n");
// 		return (1);
// 	}

// 	// Join threads after successful execution
// 	i = 0;
// 	while (i < data->num_philos)
// 	{
// 		printf("Before detjoin\n");
// 		// pthread_join(philo_ths[i], NULL);
// 		if (pthread_detach(philo_ths[i]) != 0)
// 			return (error_msg(PTHREAD_ERROR));
// 		printf("After detjoin\n");
// 		i++;
// 	}
// 	printf("After loop with join\n");
// 	destroy_mutex(philos, data);
// 	printf("after destroy\n");
// 	free(philo_ths);
// 	printf("after free2\n");
// 	return (0);
// }


/* allocate mem for philos, forks and mutex_for_data_output
 * @param creates thread for each philo 
 * @return:  1 - error, 0 - success
 */
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
