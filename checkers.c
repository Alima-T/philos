/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:25:55 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/29 09:24:02 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* проверяет, все ли философы поели необходимое количество раз
 * @param total_full: sum of not_hungly philos
 * @return: 1 - if all philos are full, 0 - if not
 */
int	check_eat(t_philo *philos)
{
	int	i;
	int	total_full;

	i = 0;
	total_full = 0;
	while (i < philos[0].data->num_philos)
	{
		total_full = total_full + philos[i].is_full;
		i++;
	}
	if (total_full >= philos[0].data->num_philos)
		return (1);
	return (0);
}

/*
 * @param philos: массив структур философов
 * @param i: индекс проверяемого философа
 * @return: 1 если философ умер, 0 если жив
 */
int	check_death(t_philo *philos, int i)
{
	// check if time from last meal is more than time to live
	if ((get_time()
			- philos[i].time_last_ate) >= ((philos[i].data->time_to_die)))
	{
		philos_msg(DIED, philos);
		return (1); // 1 if dead
	}
	return (0);
}

/* In own thread always checks philo_routine
 * (t_philo *)philos_void; - cast type to t_philo
 * check if all ate
 * @return:// NULL, if func is finished/ 1 return ((void *)1)
	- if dead return dead
 */
void	*check_philo_routine(void *philos_void)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)philos_void;
	while (1)
	{
		if (i >= philos[0].data->num_philos)
			i = 0;
		if (philos[0].data->meals_required > 0)
		{
			if (check_eat(philos) == 1)
				return (NULL);
		}
		if (check_death(philos, i) == 1)
		{
			return ((void *)1);
			break ;
		}
		i++;
		usleep(100);
	}
	return (NULL);
}

/* new thread for check_philo_routine
 * waits for the checker thread, if join fails,
	prevents further execution with an errmsg
 * @return: 0 success, err_code - if error
 */
int	philo_checker(t_philo *philos)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, check_philo_routine,
			(void *)philos) != 0)
		return (error_msg(PTHREAD_ERROR));
	if (pthread_join(checker, NULL) != 0)
		return (error_msg(PTHREAD_ERROR));
	return (0);
}
