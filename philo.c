/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/01 18:50:42 by alima            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (error_msg(MALLOC_ERROR));
	if (init_av_data(data, ac, av) != 0)
	{
		free(data);
		return (1);
	}
	if (start_sim(data) != 0)
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}