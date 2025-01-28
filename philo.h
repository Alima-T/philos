/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:26:38 by aokhapki          #+#    #+#             */
/*   Updated: 2025/01/28 14:57:21 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // for pthreads
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc, free
# include <string.h>   // for memset
# include <sys/time.h> // for gettimeofday
# include <unistd.h>   // for write, usleep

# define RESET "\033[0m"
# define GRN "\033[32m"
# define YELLOW "\033[33m"
# define MAG "\033[35m"
# define CYAN "\x1b[36m"
# define RED "\033[31m"
# define LIGHT_YELLOW "\x1b[93m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

# define WRONG_COUNT_OF_ARGS -1
# define WRONG_ARG -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4
# define WRONG_ARG_LIMITS -5

# define LEFT_FORK_TAKEN "has taken a l_fork"
# define RIGHT_FORK_TAKEN "has taken a r_fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data
{
	int				num_philos;
	int				meals_required;
	int				dead;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		creation_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}					t_data;

typedef struct s_philo
{
	int 			id;          /* Номер философа */
	int 			meals_eaten; /* Кол-во приемов пищи */
	int 			is_full;     /* */
	int				eating;
	int 			is_dead; //
	u_int64_t 		time_last_ate;   /* Время последнего приема пищи */
	u_int64_t		time_to_die;
	t_data 			*data;       /* Указатель на общие данные */
	pthread_mutex_t	lock;
	pthread_t 		thread;            /* Идентификатор потока философа */
	pthread_mutex_t *left_fork;  /* Указатель на левую вилку */
	pthread_mutex_t *right_fork; /* Указатель на правую вилку */
}					t_philo;

/* Функции инициализации (init.c) */
int					init_av_data(t_data *data, int ac, char **av);
int					run_threads(t_philo *philos, t_data *data);
int					start_sim(t_data *data);
void				destroy_mutex(t_philo *philos, t_data *data);
void				init_philos(t_philo *philos, t_data *data,
						pthread_mutex_t *fork);

/* Вспомогательные функции (utils.c) */
int					error_msg(int err_num);
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi_pos(const char *str);
void				philos_msg(char *msg_code, t_philo *philo);
u_int64_t			get_time(void);

/* Функции действий философов (actions.c) */
void				eat_or_sleep(u_int64_t time);
void				eat(t_philo *philos);
void				sleep_think(t_philo *philo);
void				take_forks(t_philo *philos);
void				*philo_routine(void *arg);

/* checkers.c  */
int					check_eat(t_philo *philos);
int					check_death(t_philo *philos, int i);
int					philo_checker(t_philo *philos);
void				*check_philo_routine(void *philos_void);

#endif