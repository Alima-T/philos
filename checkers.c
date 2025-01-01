/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:25:55 by alima             #+#    #+#             */
/*   Updated: 2025/01/01 23:14:53 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Функция проверяет, все ли философы поели необходимое количество раз
 * @param philos: массив структур философов
 * @return: 1 если все философы поели достаточно, 0 если нет
 */
int	check_eat(t_philo *philos)
{
	int	i;
	int	total_full; // Счетчик для кол. сытых философов

	i = 0;
	total_full = 0;
	while (i < philos[0].data->num_philos)
	{
		total_full = total_full + philos[i].is_full;// Суммируем количество сытых философов
		i++;
	}
	if (total_full >= philos[0].data->num_philos) // Если все философы сыты, возвращаем 1, иначе 0
		return (1);
	return (0);
}

/* Проверяет, не умер ли философ от голода
 * @param philos: массив структур философов
 * @param i: индекс проверяемого философа
 * @return: 1 если философ умер, 0 если жив
 */
int	check_death(t_philo *philos, int i)
{// Проверяем, прошло ли время с последнего приема пищи больше, чем время на жизнь
	if ((get_time() - philos[i].last_meal) > philos[i].data->time_to_die)
	{
		philos_msg(DIED, get_time() - philos[i].data->creation_time, \
					philos[i].id, philos[0].data->print_mutex);
		return (1); //1, если философ умер
	}
	return (0);
}

/* Основная функция мониторинга состояния философов
 * Запускается в отдельном потоке и постоянно проверяет:
 * 1. Достаточно ли поели все философы (если задано условие по приемам пищи)
 * 2. Не умер ли кто-то из философов
 */
void	*check_philo_routine(void *philos_void)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)philos_void; // Приведение типа указателя к массиву философов
	while (1) // Бесконечный цикл
	{
		if (i >= philos[0].data->num_philos) // Если индекс превышает количество философов
			i = 0; // Сбрасываем индекс на 0
		if (philos[0].data->meals_required > 0) // Если философы должны есть
		{
			if (check_eat(philos) == 1) // Проверяем, все ли философы сыты
				return (NULL); // Если да, завершаем выполнение
		}
		// Используем функцию для проверки смерти философа
		if (check_death(philos, i) == 1) // Проверяем, не умер ли текущий философ
			return ((void *) 1); // Если умер, завершаем выполнение
		i++; // Переходим к следующему философу
		usleep(100); // Задержка на 100 микросекунд
	}
	return (NULL); // Возвращаем NULL, если функция завершилась
}

/* Создает и запускает поток-наблюдатель за философами
 * @param philos: массив структур философов
 * @return: 0 при успехе, код ошибки при неудаче
 */
int	philo_checker(t_philo *philos)
{
	pthread_t	checker;

	// Создаем новый поток, который выполняет функцию check_philo_routine
	if (pthread_create(&checker, NULL, check_philo_routine, (void *)philos) != 0)
		return (error_msg(PTHREAD_ERROR)); // Обработка ошибки при создании потока
	if (pthread_join(checker, NULL) != 0)// Ожидаем завершения потока
		return (error_msg(PTHREAD_ERROR)); // Обработка ошибки при ожидании потока
	return (0);
}