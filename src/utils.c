/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:42:06 by rshin             #+#    #+#             */
/*   Updated: 2025/08/20 18:55:29 by rshin            ###   ########.fr       */
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

bool	check_full(t_phi *p)
{
	pthread_mutex_lock(&p->meal.mtx);
	p->meal.last = get_time();
	p->meal.count++;
	if (p->meal.count == p->cfg->max_meals && p->cfg->max_meals != 0)
	{
		p->cfg->full++;
		pthread_mutex_unlock(&p->meal.mtx);
		print_output(p, "full");
		return (true);
	}
	pthread_mutex_unlock(&p->meal.mtx);
	return (false);
}

bool	check_death(t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->death_mtx);
	if (cfg->death_flag == true)
	{
		pthread_mutex_unlock(&cfg->death_mtx);
		return (true);
	}
	pthread_mutex_unlock(&cfg->death_mtx);
	return (false);
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

void	print_output(t_phi *p, char *msg)
{
	long	time;

	time = get_time() - p->cfg->start;
	pthread_mutex_lock(&p->cfg->print_mtx);
	printf("%ld %d %s\n", time, p->id, msg); 
	pthread_mutex_unlock(&p->cfg->print_mtx);
}

bool	thread_barrier(t_cfg *cfg)
{
	sync_time(cfg->start);
	if (cfg->status != ERR_OK)
		return (false);
	return (true);
}
