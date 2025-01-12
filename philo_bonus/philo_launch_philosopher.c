/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launch_philosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:43:32 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 00:29:51 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_philosophers(void *arg)
{
	t_data_philosopher	*philosopher;

	philosopher = (t_data_philosopher *)arg;
	philosopher->self->timestamp_last_action = get_current_time_in_ms();
	philosopher->self->time_last_eat = philosopher->self->timestamp_last_action;
	print_action(philosopher, "is thinking");
	manage_action(philosopher);
	return (NULL);
}

void	*launch_set_die(void *arg)
{
	t_data_philosopher	*philosopher;
	int					i;

	philosopher = (t_data_philosopher *)arg;
	i = 0;
	while (philosopher->data_shared->is_active_simulation)
	{
		usleep(1000 * ft_max(1, (philosopher->data_shared->data_main.time_to_die
					- (get_current_time_in_ms()
						- philosopher->self->time_last_eat))));
		if (is_die(philosopher, get_current_time_in_ms()))
			set_die(philosopher, get_current_time_in_ms());
	}
	return (NULL);
}

void	manage_launch_philosopher(t_data_philosopher **data_philos)
{
	int	i;

	i = 0;
	while (i < data_philos[0]->data_shared->data_main.size_philo)
	{
		pthread_create(&(data_philos[i]->self->thread_id_action), NULL,
			launch_philosophers, data_philos[i]);
		pthread_create(&(data_philos[i]->self->thread_id_die), NULL,
			launch_set_die, data_philos[i]);
		i++;
	}
	i = 0;
	while (i < data_philos[0]->data_shared->data_main.size_philo)
	{
		pthread_join(data_philos[i]->self->thread_id_action, NULL);
		pthread_join(data_philos[i]->self->thread_id_die, NULL);
		i++;
	}
}
