/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/20 17:56:38 by rshin            ###   ########.fr       */
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
	return (true);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!args_checker(argc, argv))
		return (print_error(ERR_INPUT));
	env.cfg.status = init_env(&env, argc, argv);
	if (env.cfg.status != ERR_OK)
		return (print_error(env.cfg.status));
	env.cfg.status = run_simulation(&env, env.philos);
	cleanup(&env);
	return (print_error(env.cfg.status));
}
