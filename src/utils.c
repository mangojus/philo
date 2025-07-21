/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:42:06 by rshin             #+#    #+#             */
/*   Updated: 2025/07/21 11:20:57 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

void	print_output(t_data *data)
{
	(void)data;
	printf("philo died\n");
}

long	atol(const char *nptr)
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

