/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:09:41 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 00:03:06 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data_main(char **argv, t_data_main *data_main, int argc)
{
	data_main->size_philo = ft_atoi(argv[1]);
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
	data_shared->sem_active_simulation = sem_open("/as", O_CREAT, 0777, 1);
	sem_unlink("/as");
	data_shared->sem_sum_eat = sem_open("/se", O_CREAT, 0777, 1);
	sem_unlink("/se");
	data_shared->sem_fork
		= sem_open("/sf", O_CREAT, 0777, data_shared->data_main.size_philo);
	sem_unlink("/sf");
	data_shared->sem_atomic_fork = sem_open("/af", O_CREAT, 0777, 1);
	if (data_shared->sem_atomic_fork == SEM_FAILED
		|| data_shared->sem_fork == SEM_FAILED
		|| data_shared->sem_sum_eat == SEM_FAILED
		|| data_shared->sem_active_simulation == SEM_FAILED)
		return (perror("semaphore init: "), NULL);
	sem_unlink("/af");
	data_shared->sum_eat = 0;
	data_shared->original_timestamp = get_current_time_in_ms();
	data_shared->is_active_simulation = 1;
	return (data_shared);
}

t_philosopher	**get_philosophers(t_data_shared *data_shared)
{
	int				i;
	t_philosopher	**philosophers;

	philosophers = malloc(sizeof(t_philosopher *)
			* data_shared->data_main.size_philo);
	if (!philosophers)
		return (0);
	i = 0;
	while (i < data_shared->data_main.size_philo)
	{
		philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher) * 1);
		philosophers[i]->id = i;
		philosophers[i]->status = THINK;
		philosophers[i]->thread_id_action = 0;
		philosophers[i]->time_last_eat = 0;
		philosophers[i]->timestamp_last_action = 0;
		philosophers[i]->number_of_eat = 0;
		i++;
	}
	return (philosophers);
}

t_data_philosopher	**get_data_philosophers(t_data_shared *data_shared)
{
	int					i;
	t_data_philosopher	**data_philos;
	t_philosopher		**philosophers;

	philosophers = get_philosophers(data_shared);
	data_philos = malloc(sizeof(t_data_philosopher *)
			* data_shared->data_main.size_philo);
	if (!data_philos)
		return (0);
	i = 0;
	while (i < data_shared->data_main.size_philo)
	{
		data_philos[i] = malloc(sizeof(t_data_philosopher));
		data_philos[i]->philos = philosophers;
		data_philos[i]->data_shared = data_shared;
		data_philos[i]->self = philosophers[i];
		if (data_philos[i]->self->id == 0)
			data_philos[i]->left
				= data_philos[i]->philos[data_shared->data_main.size_philo - 1];
		else
			data_philos[i]->left
				= data_philos[i]->philos[data_philos[i]->self->id - 1];
		i++;
	}
	return (data_philos);
}

int	main(int argc, char **argv)
{
	t_data_philosopher	**data_philosopher;
	t_data_shared		*data_shared;

	if ((argc < 5 || argc > 6) || !is_verified_input(argv + 1, argc - 1))
		return (printf("Usage Error\n"), 1);
	data_shared = get_data_shared(argv, argc);
	if (!data_shared)
		return (1);
	if (data_shared->data_main.size_philo == 0)
		return (0);
	data_philosopher = get_data_philosophers(data_shared);
	if (!data_philosopher)
		return (destroy_data_shared(data_shared), 1);
	manage_launch_philosopher(data_philosopher);
	destroy_all(data_philosopher);
	return (0);
}
