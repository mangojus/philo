/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:42:06 by rshin             #+#    #+#             */
/*   Updated: 2025/08/19 15:24:12 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

long	atol(const char *nptr) //change into strict_atol for overflow
{
    size_t	i;
    int		sign;
    long	res;

    i = 0;
    sign = 1;
    res = 0;
    while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
        i++;
    if (nptr[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (nptr[i] == '+')
        i++;
    while (nptr[i] && is_digit(nptr[i]))
    {
        res = res * 10 + (nptr[i] - '0');
        i++;
    }
    return (res * sign);
}

