/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:25:55 by alima             #+#    #+#             */
/*   Updated: 2025/01/01 19:31:15 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/* TODO  Чекер, все ли философы поели необходимое количество раз
 */
int	eat_checker(t_philo *philos)
{
	return (0);
}

/* TODO Чекер, не умер ли философ от голода
 */
int	death_checker(t_philo *philos, int i)
{
	return (0);
}

/* Основная функция мониторинга состояния философов
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
			if (eat_checker(philos) == 1) // Проверяем, все ли философы сыты
				return (NULL); // Если да, завершаем выполнение
		}
		// Используем функцию для проверки смерти философа
		if (death_checker(philos, i) == 1) // Проверяем, не умер ли текущий философ
			return ((void *) 1); // Если умер, завершаем выполнение
		i++; 
		usleep(100); // Задержка на 100 микросекунд
	}
	return (NULL); 
}

/* TODO Создает и запускает поток-наблюдатель за философами
 */
int	philo_checker(t_philo *philos)
{
	return (0);
}