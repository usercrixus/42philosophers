/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:09:52 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/17 03:26:53 by achaisne         ###   ########.fr       */
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
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_each_philosopher_must_eat;
}	t_data_main;

typedef struct s_data_shared
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

typedef struct s_philosopher	t_philosopher;
typedef struct s_fork
{
	int				available;
	t_philosopher	*last_user;
}	t_fork;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread_id;
	t_philo_status	status;
	long			timestamp_last_action;
	long			time_last_eat;
	t_fork			fork;
	int				number_of_eat;

}	t_philosopher;

typedef struct s_data_philosopher
{
	t_philosopher	**philos;
	t_data_shared	*data_shared;
	t_philosopher	*self;
}	t_data_philosopher;

//atoi
int					ft_atoi(const char *str);
//create philosopher
void				manage_launch_philosopher(t_data_philosopher **data_philos);
// philo utils
long				get_current_time_in_ms(void);
//manage action
int					manage_action(t_data_philosopher *data_philos);
//close project
void				destroy_all(t_data_philosopher **data_philos);
// set action
void				set_die(t_data_philosopher *data_philos);
void				set_think(t_data_philosopher *data_philos);
void				set_eat(t_data_philosopher *data_philos);
void				set_sleep(t_data_philosopher *data_philos);
// condition
int					is_die(t_data_philosopher *data_philos, long timestamp);
int					is_think(t_data_philosopher *data_philos, long timestamp);
int					is_eat(t_data_philosopher *data_philos);
int					is_sleep(t_data_philosopher *data_philos, long timestamp);

#endif