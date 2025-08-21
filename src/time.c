/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/18 10:58:52 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(long duration)
{
	long	end_time;

	end_time = get_time() + duration;
	while (end_time > get_time())
		usleep(1000);
}

void	sync_time(long target_t)
{
	long	curr_t;
	long	rem_t;

	curr_t = get_time();
	rem_t = target_t - curr_t;
//	printf("remainder %ld\n", rem_t);
	if (rem_t > 0)
		usleep(rem_t * 1000);
}
