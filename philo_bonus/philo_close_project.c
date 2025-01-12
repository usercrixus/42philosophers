/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_close_project.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:25:02 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/11 21:56:46 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data_shared(t_data_shared *data_shared)
{
	sem_close(data_shared->sem_active_simulation);
	sem_close(data_shared->sem_sum_eat);
	sem_close(data_shared->sem_fork);
	sem_close(data_shared->sem_atomic_fork);
	free(data_shared);
}

void	destroy_philosophers(t_philosopher **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	destroy_data_philosopher(t_data_philosopher **data_philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(data_philos[i]);
		i++;
	}
	free(data_philos);
}

void	destroy_all(t_data_philosopher **data_philos)
{
	int	size;

	size = data_philos[0]->data_shared->data_main.size_philo;
	destroy_data_shared(data_philos[0]->data_shared);
	destroy_philosophers(data_philos[0]->philos, size);
	destroy_data_philosopher(data_philos, size);
}
