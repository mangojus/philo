/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/07/22 15:07:43 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	*monitor(void *arg)
{
	t_param	*param;
	int		i;

	param = (t_param *)arg;
	while (true)
	{
		i = 0;
		while (i < param->nb_philos)
		{
			if (param->philo[i].status == DEAD)
			{
				printf("%d is dead, end of simulation\n", i);
				param->end = true;
				return (NULL);
			}
			i++;
		}
	}
}

void	*loop(void *arg)
{
	t_phi	*p;

	p = (t_phi *)arg;
	while (!p->param->start)
		usleep(1000);
	while (true)
	{
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->l_fork->mutex);
			pthread_mutex_lock(&p->r_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&p->r_fork->mutex);
			pthread_mutex_lock(&p->l_fork->mutex);
		}
	}
}

void	assign_forks(void)
{
	
}

bool	run_simulation(t_param *param, t_phi *philo)
{
	int		i;

	if (pthread_create(&param.monitor, NULL, &monitor, &param))
		return (false);
	i = 0;
	while (i < param->nb_philos)
	{
		if (pthread_create((&param->philo[i]), NULL, &loop, param->philo[i]))
			return (false)
		i++;
	}
	param->start = get_time();
	return (true);
}
