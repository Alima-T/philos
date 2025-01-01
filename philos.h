/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:26:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/01 18:00:43 by alima            ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				creation_time;
	pthread_mutex_t	*print_mutex;
}			t_data;


typedef struct s_philo
{
	int				id;              /* Номер философа */
	int				meals_eaten;     /* Кол-во приемов пищи */
	int				is_full;		/* */
	long long		last_meal;  	/* Время последнего приема пищи */
	t_data			*data;           /* Указатель на общие данные */
	pthread_t		thread;          /* Идентификатор потока философа */
	pthread_mutex_t	*left_fork;      /* Указатель на левую вилку */
	pthread_mutex_t	*right_fork;     /* Указатель на правую вилку */
}				t_philo;


/* Функции инициализации (init.c) */
int			init_av_data(t_data *data, int ac, char **av);
int			init_mutexes(t_data *data);
void		init_philos(t_philo *philos, t_data *data, pthread_mutex_t *fork);

/* Вспомогательные функции (utils.c) */
long long	get_time(void);              /* Получение текущего времени */
void		smart_sleep(long long time);  /* Умная задержка */
void		print_status(t_philo *philo, char *status); /* Печать статуса */
int			check_death(t_philo *philo);  /* Проверка смерти */
void		free_all(t_data *data, t_philo *philos); /* Освобождение памяти */

/* Функции действий философов (actions.c) */
void		*philo_routine(void *arg);    /* Основной цикл философа */
void		eat(t_philo *philo);          /* Прием пищи */
void		sleep_think(t_philo *philo);  /* Сон и размышления */

#endif
