/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:05:11 by rshin             #+#    #+#             */
/*   Updated: 2025/09/04 09:05:14 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}

void	smart_sleep(long duration)
{
	long	end_t;
	long	cur_t;

	end_t = get_time() + duration;
	while (true)
	{
		cur_t = get_time();
		if (cur_t >= end_t)
			break ;
		else if (end_t - cur_t > 2)
			usleep(1000);
		else
			usleep(100);
	}
}

void	sync_time(long target_t)
{
	long	rem_t;

	rem_t = target_t - get_time();
	if (rem_t > 0)
		smart_sleep(rem_t);
}
