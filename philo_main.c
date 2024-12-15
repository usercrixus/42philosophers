/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:09:41 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 17:35:22 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data_main(char **argv, t_data_main *data_main)
{
	data_main->num_of_philo = atoi(argv[1]);
	data_main->time_to_die = atoi(argv[2]);
	data_main->time_to_eat = atoi(argv[3]);
	data_main->time_to_sleep = atoi(argv[4]);
}

t_data_shared	*get_data_shared(char **argv)
{
	t_data_shared	*data_shared;

	data_shared = (t_data_shared *)malloc(sizeof(t_data_shared) * 1);
	if (!data_shared)
		return (0);
	set_data_main(argv, &data_shared->data_main);
	pthread_mutex_init(&data_shared->mutex_print, NULL);
	pthread_mutex_init(&data_shared->mutex_status, NULL);
	data_shared->is_active_simulation = 1;
	return (data_shared);
}

int	main(int argc, char **argv)
{
	t_data_shared	*data_shared;

	if (argc != 5)
		return (printf("Usage Error\n"), 1);
	data_shared = get_data_shared(argv);
	if (!data_shared)
		return (1);
	manage_launch_philosopher(data_shared);
}
