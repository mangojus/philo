/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:32:04 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 17:38:24 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_config(t_cfg *cfg, int argc, char **argv)
{
	long	param[5];
	int			i;

	i = 0;
	memset(param, -1, sizeof(long) * 5);
	while (i <= argc - 2)
	{
		param[i] = atol(argv[i + 1]);
		if (param[i] > INT_MAX || param[i] < 0)
			return (false);
		++i;
	}
	cfg->start_t = -1;
	cfg->nb_philos = param[0];
	cfg->die_t = param[1];
	cfg->eat_t = param[2];
	cfg->sleep_t = param[3];
	cfg->max_meals = param[4];
	cfg->forks = malloc(cfg->nb_philos * sizeof(t_fork));
	if (!cfg->forks)
		return (false);
	memset(cfg->forks, 0, sizeof(t_fork) * cfg->nb_philos);
	return (true);
}

static bool	init_philos(t_env *env)
{
	t_fork	*lfork;
	t_fork	*rfork;
	int		i;

	env->philos = malloc(env->cfg.nb_philos * sizeof(t_phi));
	if (!env->philos)
		return (false);
	memset(env->philos, 0, sizeof(t_phi) * env->cfg.nb_philos);
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		env->philos[i].id = i + 1;
		env->philos[i].cfg = &env->cfg;
		lfork = &env->cfg.forks[i];
		rfork = &env->cfg.forks[(i + 1) % env->cfg.nb_philos];
		env->philos[i].f[(i + 1) % 2] = rfork;
		env->philos[i].f[(i + 2) % 2] = lfork;
		++i;
	}
	return (true);
}

static bool	init_mutexes(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->cfg.nb_mutexes)
	{
		if (pthread_mutex_init(&env->mutexes[i], NULL))
		{
			clean_mutexes(env->mutexes, i);
			return (false);
		}
		++i;
	}
	env->cfg.cfg_mtx = &env->mutexes[0];
	env->cfg.print_mtx = &env->mutexes[1];
	env->cfg.full_mtx = &env->mutexes[2];
	env->cfg.death_mtx = &env->mutexes[3];
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		env->philos[i].meal.mtx = &env->mutexes[4 + i * 2];
		env->cfg.forks[i].mtx = &env->mutexes[4 + (i * 2) + 1];
		++i;
	}
	return (true);
}

t_err	init_env(t_env *env, int argc, char **argv)
{
	memset(env, 0, sizeof(t_env));
	if (!init_config(&env->cfg, argc, argv))
		return (ERR_MALLOC);
	if (!init_philos(env))
	{
		free(env->cfg.forks);
		return (ERR_MALLOC);
	}
	env->cfg.nb_mutexes = 4 + env->cfg.nb_philos * 2;
	env->mutexes = malloc(env->cfg.nb_mutexes * sizeof(t_mtx));
	if (!env->mutexes)
	{
		free(env->philos);
		free(env->cfg.forks);
		return (ERR_MALLOC);
	}
	if (!init_mutexes(env))
	{
		free(env->philos);
		free(env->cfg.forks);
		return (ERR_MUTEX);
	}
 	return (ERR_OK);
}
