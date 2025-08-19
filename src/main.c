/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/19 13:43:04 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

static bool	args_checker(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (false);
	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '-')
			return (false);
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j++]))
				return (false);
		}
		i++;
	}
	if (atol(argv[1]) > 200) //remove depending on correction
		return (false);
	return (true);
}

void	cleanup(t_env *env)
{
	if (env->philos)
	{
		free(env->philos);
		env->philos = NULL;
	}
	if (env->forks)
	{
		free(env->forks);
		env->forks = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!args_checker(argc, argv))
	{
		printf("Invalid arguments\n");
		return (ERR_INPUT);
	}
	env.status = init_env(&env, argc, argv);
	if (env.status != ERR_OK)
		return (env.status);
	run_simulation(&env, env.philos);
	cleanup(&env);
	return (env.status);
}
