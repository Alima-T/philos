/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:15:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/28 14:57:14 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
