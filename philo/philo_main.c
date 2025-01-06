/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:09:41 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/06 17:27:43 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data_main(char **argv, t_data_main *data_main, int argc)
{
	data_main->num_of_philo = ft_atoi(argv[1]);
	data_main->time_to_die = ft_atoi(argv[2]);
	data_main->time_to_eat = ft_atoi(argv[3]);
	data_main->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data_main->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data_main->times_each_philosopher_must_eat = -1;
}

t_data_shared	*get_data_shared(char **argv, int argc)
{
	t_data_shared	*data_shared;

	data_shared = (t_data_shared *)malloc(sizeof(t_data_shared) * 1);
	if (!data_shared)
		return (0);
	set_data_main(argv, &data_shared->data_main, argc);
	if (pthread_mutex_init(&data_shared->mutex_print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data_shared->mutex_status, NULL) != 0)
		return (0);
	data_shared->is_active_simulation = 1;
	return (data_shared);
}

t_philosopher	**get_philosophers(t_data_shared *data_shared)
{
	int				i;
	t_philosopher	**philosophers;

	philosophers = malloc(sizeof(t_philosopher *)
			* data_shared->data_main.num_of_philo);
	if (!philosophers)
		return (0);
	i = 0;
	while (i < data_shared->data_main.num_of_philo)
	{
		philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher) * 1);
		if (!philosophers[i])
			return (0);
		philosophers[i]->id = i;
		philosophers[i]->status = THINK;
		philosophers[i]->thread_id = 0;
		philosophers[i]->time_last_eat = 0;
		philosophers[i]->timestamp_last_action = 0;
		philosophers[i]->fork.available = 1;
		philosophers[i]->fork.last_user = 0;
		philosophers[i]->number_of_eat = 0;
		i++;
	}
	return (philosophers);
}

t_data_philosopher	**get_data_philosophers(t_data_shared *data_shared)
{
	int					i;
	t_data_philosopher	**data_philosopher;
	t_philosopher		**philosophers;

	philosophers = get_philosophers(data_shared);
	data_philosopher = malloc(sizeof(t_data_philosopher *)
			* data_shared->data_main.num_of_philo);
	if (!data_philosopher)
		return (0);
	i = 0;
	while (i < data_shared->data_main.num_of_philo)
	{
		data_philosopher[i] = malloc(sizeof(t_data_philosopher));
		data_philosopher[i]->philos = philosophers;
		data_philosopher[i]->data_shared = data_shared;
		data_philosopher[i]->self = philosophers[i];
		i++;
	}
	return (data_philosopher);
}

int	main(int argc, char **argv)
{
	t_data_philosopher	**data_philosopher;
	t_data_shared		*data_shared;

	if (argc < 5 || argc > 6)
		return (printf("Usage Error\n"), 1);
	data_shared = get_data_shared(argv, argc);
	if (!data_shared)
		return (1);
	data_philosopher = get_data_philosophers(data_shared);
	if (!data_philosopher)
		return (destroy_data_shared(data_shared), 1);
	manage_launch_philosopher(data_philosopher);
	destroy_all(data_philosopher);
}
