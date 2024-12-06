/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:45:41 by aokhapki          #+#    #+#             */
/*   Updated: 2024/12/06 19:20:06 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

pthread_mutex_t *chopstcks;
pthread_mutex_t print_mutex;

void think(int philo_id, int time_to_sleep)
{
	pthread_mutex_lock(&print_mutex);
	printf("philo %d is thinking\n", philo_id);
	pthread_mutex_unlock(&print_mutex);
	pthread_mutex_unlock(&print_mutex);
	usleep(time_to_sleep * 1000); // Convert milliseconds to microseconds
}

void eat(int philo_id, int time_to_eat)
{
	pthread_mutex_lock(&print_mutex);
	printf("philo %d is eating\n", philo_id);
	pthread_mutex_unlock(&print_mutex);
	pthread_mutex_unlock(&print_mutex);
	usleep(time_to_eat * 1000); // Convert milliseconds to microseconds
}
void *philos_routine(void *arg)
{
	philos_t *philo = (philos_t *) arg;
	int left = philo->id;
	int right = (philo->id + 1) % 5; // change to num of philos
	while(1)
	{
		think(philo->id, philo->time_to_sleep);
		pthread_mutex_lock(&chopstcks[left]);
		pthread_mutex_lock(&chopstcks[right]);
		eat(philo->id, philo->time_to_eat);
		pthread_mutex_unlock(&chopstcks[left]);
		pthread_mutex_unlock(&chopstcks[right]);
	}
	return(NULL);
}

int main(int ac, char **av)
{
	if(ac != 5)
	{
		write(2, "Usage: ./philo <num_philos> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms>\n", 90);
		exit(EXIT_FAILURE);
	}
	
	int num_philos = atoi(av[1]);
	int time_to_die_ms = atoi(av[2]);
	int time_to_eat_ms = atoi(av[3]);
	int time_to_sleep_ms = atoi(av[4]);
	
	if (num_philos < 2)
	{
		write(2, "Number of philosophers must be at least 2.\n", 41);
        exit(EXIT_FAILURE);
	}

	// Initialize mutexes for each chopstick and print synchronization
	chopstcks = (pthread_mutex_t *)malloc(num_philos * sizeof(pthread_mutex_t));
	pthread_mutex_init(&print_mutex, NULL);
	// Initialize mutexes for each chopstick and print synchronization
	int i = 0;
	while(i < num_philos)
	{
		pthread_mutex_init(&chopstcks[i], NULL);
		i++;
	}

	pthread_t *philos = (pthread_t *)malloc(num_philos * sizeof(pthread_t));
	philos_t *philo_data = (philos_t *)malloc(num_philos * sizeof(philos_t));
	
	int j = 0;
	while(j < num_philos)
	{
		philo_data[j].id = j;
		philo_data[j].time_to_die = time_to_die_ms;
		philo_data[j].time_to_eat = time_to_eat_ms;
		philo_data[j].time_to_sleep = time_to_sleep_ms;
		pthread_create(&philos[j], NULL, philos_routine, (void *)&philo_data[j]);
		pthread_detach(philos[j]);
	}
	j++;
	usleep(1000000);
	
	int k = 0;
	while(k < num_philos)
		pthread_mutex_destroy(&chopstcks[k]);
	k++;
	pthread_mutex_destroy(&print_mutex);
	free(chopstcks);
	free(philos);
	free(philo_data);
	return(0);
}
