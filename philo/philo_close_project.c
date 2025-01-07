/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_close_project.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:25:02 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/07 17:50:16 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data_shared(t_data_shared *data_shared)
{
	pthread_mutex_destroy(&data_shared->mutex_print);
	free(data_shared);
}

void	destroy_philosophers(t_philosopher **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&philos[i]->fork.mutex_fork);
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

	size = data_philos[0]->data_shared->data_main.num_of_philo;
	destroy_data_shared(data_philos[0]->data_shared);
	destroy_philosophers(data_philos[0]->philos, size);
	destroy_data_philosopher(data_philos, size);
}
