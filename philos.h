/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:26:38 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/06 19:15:53 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc, free
#include <string.h>     // for memset
#include <unistd.h>     // for write, usleep
#include <sys/time.h>   // for gettimeofday
#include <pthread.h>    // for pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct philos_s
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
} philos_t;

void think(int philo_id, int time_to_sleep);
void eat(int philo_id, int time_to_eat);
void *philos_routine(void *arg);
int main(int ac, char **av);


// int ft_strlen (char *str);
// void *print(void *buf);

// void *printint(void *buf);

// typedef struct s_philo
// {
// 	pthread_t	thread;
// 	int	id;
// 	int eating;
// 	int		meals_eaten;
// 	int			mum_of_philos;
// 	int			num_times_to_eat;
// 	int			*dead;
// 	size_t		last_meal;
// 	size_t		time_to_die;
// 	size_t		time_to_eat;
// 	size_t		time_to_sleap;
// 	size_t		start_time;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t	*dead_lock;
// 	pthread_mutex_t	*meal_lock;
// }			t_philo;