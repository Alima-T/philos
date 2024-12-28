/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:43 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/28 17:25:40 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philos.h"

static int	ft_check_valid(int ac, char **av)
{
	size_t	i;

	if (ac < 5 || ac > 6)
	{
		ft_check_args();
		return (1);
	}
	i = 1;
	while (av[i])
	{
		if (!ft_is_digit(av[i]) || (!ft_atoi(av[i])))
		{
			printf("Invalid argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	av_processing(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error_msg(WRONG_COUNT_OF_ARGS));
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = 0;
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1 \
		|| data->time_to_sleep < 1)
		return (error_msg(WRONG_ARG));
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required < 1)
			return (error_msg(WRONG_ARG));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (error_msg(MALLOC_ERROR));
	if (argv_processing(data, argc, argv) != 0)
	{
		free(data);
		return (1);
	}
	if (philosophers(data) != 0)
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}