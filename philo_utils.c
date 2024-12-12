/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:13:55 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 00:14:15 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL); // Get the current time
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // Convert to milliseconds
}