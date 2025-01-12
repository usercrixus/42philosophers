/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:11 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 00:28:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	sem_wait(philosopher->data_shared->sem_active_simulation);
	if (philosopher->data_shared->is_active_simulation)
		printf("%lu %d %s\n",
			get_current_time_in_ms()
			- philosopher->data_shared->original_timestamp,
			philosopher->self->id + 1, str);
	sem_post(philosopher->data_shared->sem_active_simulation);
}

void	set_die(t_data_philosopher *philosopher, long timestamp)
{
	sem_wait(philosopher->data_shared->sem_active_simulation);
	philosopher->self->timestamp_last_action = timestamp;
	if (philosopher->data_shared->is_active_simulation)
	{
		philosopher->data_shared->is_active_simulation = 0;
		printf("%lu %d %s\n", get_current_time_in_ms()
			- philosopher->data_shared->original_timestamp,
			philosopher->self->id + 1, "died");
	}
	sem_post(philosopher->data_shared->sem_active_simulation);
}

void	set_think(t_data_philosopher *philosopher, long timestamp)
{
	philosopher->self->status = THINK;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is thinking");
}

void	set_eat(t_data_philosopher *philosopher, long timestamp)
{
	sem_wait(philosopher->data_shared->sem_atomic_fork);
	sem_wait(philosopher->data_shared->sem_fork);
	sem_wait(philosopher->data_shared->sem_fork);
	sem_post(philosopher->data_shared->sem_atomic_fork);
	timestamp = get_current_time_in_ms();
	philosopher->self->status = EAT;
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->time_last_eat = timestamp;
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
	sem_post(philosopher->data_shared->sem_fork);
	sem_post(philosopher->data_shared->sem_fork);
	philosopher->self->number_of_eat++;
	set_eat_times(philosopher);
	philosopher->self->status = SLEEP;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is sleeping");
	usleep(980 * ft_max(1,
			ft_min(philosopher->data_shared->data_main.time_to_sleep,
				philosopher->data_shared->data_main.time_to_die
				- (timestamp - philosopher->self->time_last_eat))));
}
