/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/07/21 16:31:31 by rshin            ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_env	env;

	if (!args_checker(argc, argv))
	{
		printf("Invalid arguments\n");
		return (env.err_status);
	}
	if (init_env(&env, argc, argv) != ERR_OK)
		return (env.err_status);
	run_simulation(&env, env.philos);
	return (env.err_status);
}
