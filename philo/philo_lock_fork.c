/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lock_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:01:32 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/07 18:02:01 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_data_philosopher *philosopher, int left)
{
	if (philosopher->self->id < left)
	{
		pthread_mutex_lock(&(philosopher->self->fork.mutex_fork));
		pthread_mutex_lock(&(philosopher->philos[left]->fork.mutex_fork));
	}
	else
	{
		pthread_mutex_lock(&(philosopher->philos[left]->fork.mutex_fork));
		pthread_mutex_lock(&(philosopher->self->fork.mutex_fork));
	}
}

void	unlock_fork(t_data_philosopher *philosopher, int left)
{
	if (philosopher->self->id < left)
	{
		pthread_mutex_unlock(&(philosopher->philos[left]->fork.mutex_fork));
		pthread_mutex_unlock(&(philosopher->self->fork.mutex_fork));
	}
	else
	{
		pthread_mutex_unlock(&(philosopher->self->fork.mutex_fork));
		pthread_mutex_unlock(&(philosopher->philos[left]->fork.mutex_fork));
	}
}
