/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoX.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:34:18 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/19 15:35:29 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_digit_mod(int a, short allow_neg, short allow_plus)
{
	if ((a >= '0' && a <= '9'))
		return (1);
	if (allow_neg && a == '-')
		return (1);
	if (allow_plus && a == '+')
		return (1);
	return (0);
}

float	ft_atof(const char *str, int *index)
{
	float	result;
	float	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.1;
	sign = 1;
	if (str[*index] == '-')
	{
		sign = -1;
		(*index)++;
	}
	else if (str[*index] == '+')
		(*index)++;
	while (str[*index] >= '0' && str[*index] <= '9')
		result = result * 10.0 + (str[(*index)++] - '0');
	if (str[*index] == '.')
		(*index)++;
	while (str[*index] >= '0' && str[*index] <= '9')
	{
		result += (str[(*index)++] - '0') * fraction;
		fraction *= 0.1;
	}
	return (result * sign);
}

uint8_t	ft_atouint8(const char *str, int *index)
{
	int	result;

	result = 0;
	if (str[*index] == '+')
		(*index)++;
	while (str[*index] >= '0' && str[*index] <= '9')
	{
		result = result * 10 + (str[(*index)++] - '0');
		if (result > 255)
		{
			(*index)--;
			return ((uint8_t)(result));
		}
	}
	return ((uint8_t)(result));
}

int	ft_atoi_mod(const char *str, int *index)
{
	int	result;
	int	sign;
	int	prev;

	sign = 1;
	result = 0;
	prev = 0;
	if (str[*index] == '+')
		(*index)++;
	if (str[*index] == '-')
	{
		sign = -1;
		(*index)++;
	}
	while (str[*index] >= '0' && str[*index] <= '9')
	{
		result = result * 10 + (str[(*index)++] - '0');
		if (prev > result)
		{
			(*index)--;
			return (sign * result);
		}
		prev = result;
	}
	return (sign * result);
}
