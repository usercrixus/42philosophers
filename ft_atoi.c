/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:22:35 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/11 23:10:08 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
	{
		return (1);
	}
	return (0);
}

int	calc_int(int is_neg, const char *str, int i)
{
	int	result;

	result = 0;
	if (is_neg)
		while (str[i] && ft_isdigit(str[i]))
		{
			result *= 10;
			result -= str[i] - '0';
			i++;
		}
	else
		while (str[i] && ft_isdigit(str[i]))
		{
			result *= 10;
			result += str[i] - '0';
			i++;
		}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	is_neg = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg = 1;
		i++;
	}
	return (calc_int(is_neg, str, i));
}