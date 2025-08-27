/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:36:40 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 14:22:34 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_env *env)
{
	if (env->philos)
	{
		free(env->philos);
		env->philos = NULL;
	}
	if (env->cfg.forks)
	{
		free(env->cfg.forks);
		env->cfg.forks = NULL;
	}
	clean_mutexes(env->mutexes, env->cfg.nb_mutexes);
}

void	clean_mutexes(t_mtx *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mutexes[i]);
		++i;
	}
	free(mutexes);
}
