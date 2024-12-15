/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:09:52 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 16:59:15 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data_main
{
	int	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_data_main;

typedef	struct s_data_shared
{
	t_data_main		data_main;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_status;
	int				is_active_simulation;
}	t_data_shared;

typedef enum e_philo_status
{
	SLEEP,
	THINK,
	EAT,
	DEAD
}	t_philo_status;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread_id;
	t_philo_status	status;
	long			timestamp_last_action;
	long			timestamp_last_eat;

}	t_philosopher;

typedef struct s_data_philosopher
{
	t_philosopher	**philosophers;
	t_data_shared	*data_shared;
	t_philosopher	*self;
}	t_data_philosopher;

int		ft_atoi(const char *str);
int		manage_launch_philosopher(t_data_shared *data);
int		is_eating_possible(t_data_philosopher *philosopher);
long	get_current_time_in_ms();
int		manage_action(t_data_philosopher *philosopher);

#endif