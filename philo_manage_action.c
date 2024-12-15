/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 06:19:18 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
	printf("%ld %d %s\n", philosopher->self->timestamp_last_action, philosopher->self->id + 1, str);
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
}

int	is_eating_possible(t_data_philosopher *philosopher)
{
	if (philosopher->self->id == 0)
	{
		if (philosopher->philosophers[philosopher->data_shared->data_main.number_of_philosophers - 1]->status != EAT
			&& philosopher->philosophers[philosopher->self->id + 1]->status != EAT )
			return (1);
	}
	else if (philosopher->self->id == philosopher->data_shared->data_main.number_of_philosophers - 1)
	{
		if (philosopher->philosophers[philosopher->self->id - 1]->status != EAT
			&& philosopher->philosophers[0]->status != EAT)
			return (1);;
	}
	else
	{
		if (philosopher->philosophers[philosopher->self->id - 1]->status != EAT
			&& philosopher->philosophers[philosopher->self->id + 1]->status != EAT)
			return (1);
	}
	return (0);
}

int	add_priotity_queue(t_data_philosopher *philosopher)
{
	t_priority_qeue *priority_qeue;

	priority_qeue = &philosopher->data_shared->priority_qeue;
	if (!priority_qeue->philosopher)
	{
		priority_qeue->philosopher = philosopher;
	}
	else
	{
		while (priority_qeue->next)
			priority_qeue = priority_qeue->next,
		priority_qeue->next = malloc(sizeof(struct s_priority_queue) * 1);
		if (!priority_qeue->next)
			return (0);
		priority_qeue->next->philosopher = philosopher;
	}
	return (1);
}

int	try_to_eat(t_data_philosopher *philosopher)
{
	t_priority_qeue *priority_qeue;
	long	timestamp;

	priority_qeue = &philosopher->data_shared->priority_qeue;
	if (!priority_qeue->philosopher)
		return (0);
	if (priority_qeue->philosopher->self->status == THINK && is_eating_possible(philosopher))
	{
		priority_qeue->philosopher->self->status = EAT;
		priority_qeue->philosopher->self->timestamp_last_action = timestamp;
		priority_qeue->philosopher->self->timestamp_last_eat = timestamp;
		print_action(priority_qeue->philosopher, "has taken a fork");
		print_action(priority_qeue->philosopher, "has taken a fork");
		print_action(priority_qeue->philosopher, "is eating");
		manage_action(priority_qeue->philosopher);
	}
}

int	manage_action(t_data_philosopher *philosopher)
{
	long	timestamp;

	pthread_mutex_lock(&(philosopher->data_shared->mutex_status));
	if (!philosopher->data_shared->is_active_simulation)
		return (1);
	timestamp = get_current_time_in_ms();
	if (philosopher->self->status != EAT && timestamp - philosopher->self->timestamp_last_eat > philosopher->data_shared->data_main.time_to_die)
	{
		philosopher->self->timestamp_last_action = timestamp;
		philosopher->self->status = DEAD;
		print_action(philosopher, "died");
		philosopher->data_shared->is_active_simulation = 0;
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
	}
	else if (philosopher->self->status == SLEEP && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_sleep)
	{
		philosopher->self->status = THINK;
		philosopher->self->timestamp_last_action = timestamp;
		print_action(philosopher, "is thinking");
		add_priotity_queue(philosopher);
		try_to_eat(philosopher);
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
	}
	else if (philosopher->self->status == EAT && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_eat)
	{
		philosopher->self->status = SLEEP;
		philosopher->self->timestamp_last_action = timestamp;
		print_action(philosopher, "is sleeping");
		try_to_eat(philosopher);
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
		usleep(philosopher->data_shared->data_main.time_to_sleep * 1000);
		manage_action(philosopher);
	}
	else
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));

	return (1);
}