/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:38:59 by rshin             #+#    #+#             */
/*   Updated: 2025/07/22 15:08:10 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	bool			start;
	int				id;
	pthread_t		tid;
	bool			is_full;
	bool			has_eaten;
	bool			status;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}	t_phi;

typedef struct s_data
{
	struct s_phi	*philo;
	pthread_mutex_t	*fork;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
}	t_data;

bool	init_data(t_data *data, int argc, char **argv);
bool	run_philo(t_data *data);

int		is_digit(int c);
long	atol(const char *nptr);
void	print_output(t_data *data);

#endif
