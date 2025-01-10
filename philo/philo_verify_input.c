/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_verify_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:58:54 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 21:07:29 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_strncmp(const char *s1, const char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	is_integer(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-')
	{
		i++;
		if (s[i] == '\0')
			return (0);
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[0] == '-' && ((i > 11)
			|| (i == 11 && ft_strncmp(s, "-2147483648", 11) > 0)))
		return (0);
	else if (s[0] != '-' && ((i > 10)
			|| (i == 10 && ft_strncmp(s, "2147483647", 10) > 0)))
		return (0);
	return (1);
}

int	is_integers(char **s, int size)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	j = 0;
	while (j < size)
	{
		if (s[j][0] == '-')
			return (0);
		if (!is_integer(s[j]))
			return (0);
		j++;
	}
	return (1);
}

int	is_verified_input(char **s, int size)
{
	if (!s)
		return (0);
	if (!is_integers(s, size))
		return (0);
	return (1);
}
