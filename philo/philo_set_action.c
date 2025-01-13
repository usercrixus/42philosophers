/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:11 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 05:30:59 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_active_simulation));
	if (philosopher->data_shared->is_active_simulation)
		printf("%lu %d %s\n", philosopher->self->timestamp_last_action
			- philosopher->data_shared->original_timestamp,
			philosopher->self->id + 1, str);
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_active_simulation));
}

void	set_die(t_data_philosopher *philosopher, long timestamp)
{
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->status = DEAD;
	pthread_mutex_lock(&(philosopher->data_shared->mutex_active_simulation));
	if (philosopher->data_shared->is_active_simulation)
		printf("%lu %d %s\n", philosopher->self->timestamp_last_action
			- philosopher->data_shared->original_timestamp,
			philosopher->self->id + 1, "died");
	philosopher->data_shared->is_active_simulation = 0;
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_active_simulation));
}

void	set_think(t_data_philosopher *philosopher, long timestamp)
{
	philosopher->self->status = THINK;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is thinking");
}

void	set_eat(t_data_philosopher *philosopher, long timestamp)
{
	lock_fork(philosopher, philosopher->left);
	if (philosopher->self->fork.available == 0
		|| philosopher->left->fork.available == 0)
		return (unlock_fork(philosopher, philosopher->left));
	philosopher->self->fork.available = 0;
	philosopher->left->fork.available = 0;
	unlock_fork(philosopher, philosopher->left);
	philosopher->self->status = EAT;
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->time_last_eat = timestamp;
	philosopher->self->fork.last_user = philosopher->self;
	philosopher->left->fork.last_user = philosopher->self;
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "is eating");
	usleep(980 * ft_max(1,
			ft_min(philosopher->data_shared->data_main.time_to_eat,
				philosopher->data_shared->data_main.time_to_die
				- (timestamp - philosopher->self->time_last_eat))));
}

void	set_sleep(t_data_philosopher *philosopher, long timestamp)
{
	philosopher->self->number_of_eat++;
	set_eat_times(philosopher);
	philosopher->self->fork.available = 1;
	philosopher->left->fork.available = 1;
	philosopher->self->status = SLEEP;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is sleeping");
	usleep(980 * ft_max(1,
			ft_min(philosopher->data_shared->data_main.time_to_sleep,
				philosopher->data_shared->data_main.time_to_die
				- (timestamp - philosopher->self->time_last_eat))));
}
