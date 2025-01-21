/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:26:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/21 16:47:30 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc, free
#include <string.h>     // for memset
#include <unistd.h>     // for write, usleep
#include <sys/time.h>   // for gettimeofday
#include <pthread.h>    // for pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

# define WRONG_COUNT_OF_ARGS	-1
# define WRONG_ARG				-2
# define MALLOC_ERROR			-3
# define PTHREAD_ERROR			-4

# define LEFT_FORK_TAKEN		1
# define RIGHT_FORK_TAKEN		2
# define EATING					3
# define SLEEPING				4
# define THINKING				5
# define DIED					6

typedef struct s_data
{
	int				num_philos;
	int				meals_required;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		creation_time;
	pthread_mutex_t	*print_mutex;
}			t_data;


typedef struct s_philo
{
	int				id;              /* Номер философа */
	int				meals_eaten;     /* Кол-во приемов пищи */
	int				is_full;		/* */
	u_int64_t 		last_meal;    	/* Время последнего приема пищи */
	t_data			*data;           /* Указатель на общие данные */
	pthread_t		thread;          /* Идентификатор потока философа */
	pthread_mutex_t	*left_fork;      /* Указатель на левую вилку */
	pthread_mutex_t	*right_fork;     /* Указатель на правую вилку */
	pthread_mutex_t	philo_mutex;
}				t_philo;

/* Функции инициализации (init.c) */
int			init_av_data(t_data *data, int ac, char **av);
void		init_philos(t_philo *philos, t_data *data, pthread_mutex_t *fork);
void		destroy_mutex(t_philo *philos, t_data *data);
int			run_threads(t_philo *philos, t_data *data);
int 		start_sim(t_data *data);

/* Вспомогательные функции (utils.c) */
int			ft_usleep(u_int64_t milliseconds); //remove
u_int64_t	get_time(void);
int			error_msg(int err_num);
void		philos_msg(int msg_code, u_int64_t time, int id, pthread_mutex_t *print_mutex);
int			ft_atoi(const char *str);

/* Функции действий философов (actions.c) */
void		eat_or_sleep(u_int64_t time);
void		eat(t_philo *philos);
void		sleep_think(t_philo *philo);
void		take_forks(t_philo *philos);
void		*philo_routine(void *arg);

/* checkers.c  */

int			check_eat(t_philo *philos);
int			check_death(t_philo *philos, int i);
void		*check_philo_routine(void *philos_void);
int			philo_checker(t_philo *philos);

#endif
