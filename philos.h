/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:26:38 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/27 12:17:16 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc, free
#include <string.h>     // for memset
#include <unistd.h>     // for write, usleep
#include <sys/time.h>   // for gettimeofday
#include <pthread.h>    // for pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_philo
{
	int				id;              /* Номер философа */
	int				meals_eaten;     /* Кол-во приемов пищи */
	long long		last_meal;  	/* Время последнего приема пищи */
	t_data			*data;           /* Указатель на общие данные */
	pthread_t		thread;          /* Идентификатор потока философа */
	pthread_mutex_t	*left_fork;      /* Указатель на левую вилку */
	pthread_mutex_t	*right_fork;     /* Указатель на правую вилку */
}	t_philo;

/* Функции инициализации (init.c) */
int			init_data(t_data *data, int ac, char **av);
int			init_mutexes(t_data *data);
int			init_philos(t_philo **philos, t_data *data);

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
