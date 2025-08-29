/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:42:06 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 14:23:51 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
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
		++i;
	if (nptr[i] == '-')
	{
		sign = -1;
		++i;
	}
	else if (nptr[i] == '+')
		++i;
	while (nptr[i] && is_digit(nptr[i]))
	{
		res = res * 10 + (nptr[i] - '0');
		++i;
	}
	return (res * sign);
}

t_err	print_error(t_err error)
{
	if (error == ERR_INPUT)
		printf("philo: Invalid arguments\n");
	else if (error == ERR_MALLOC)
		printf("philo: Malloc creation failure\n");
	else if (error == ERR_THREAD)
		printf("philo: Thread creation failure\n");
	else if (error == ERR_MUTEX)
		printf("philo: Mutex creation failure\n");
	return (error);
}

bool	print_output(t_phi *p, char *msg)
{
	long	cur_t;

	if (check_death(p->cfg))
		return (false);
	pthread_mutex_lock(p->cfg->print_mtx);
	cur_t = get_time() - p->cfg->start_t;
	printf("%ld %d %s\n", cur_t, p->id, msg);
	pthread_mutex_unlock(p->cfg->print_mtx);
	return (true);
}
