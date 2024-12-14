/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:13:55 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/14 18:59:03 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL); // Get the current time
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // Convert to milliseconds
}

int	insert(t_data_philosopher *data)
{
	t_priority_qeue	*inserted;

	inserted = (t_priority_qeue *)malloc(sizeof(t_priority_qeue) * 1);
	if (!inserted)
		return (0);
	inserted->next = data->qeue;
	data->qeue = inserted;
}

int	remove(t_priority_qeue	*head, t_philosopher *philosopher)
{
	t_priority_qeue	*buffer;
	t_priority_qeue	*current;
	t_priority_qeue	*previous;

	if (philosopher == head->philosopher)
	{
		buffer = head;
		head = head->next;
		return (free(buffer), 1);
	}
	previous = head;
	current = head->next;
	while(philosopher != current->philosopher)
	{
		current = current->next;
		previous = previous->next;
	}
	if (philosopher == current->philosopher)
	{
		buffer = current;
		previous->next = current->next;
		return(free(buffer), 1);
	}
	return (0);
}