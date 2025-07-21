/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:38:59 by rshin             #+#    #+#             */
/*   Updated: 2025/07/21 14:50:29 by rshin            ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	bool			is_full;
	int				has_eaten;
	bool			status;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}	t_phi;

typedef struct s_data
{
	struct s_phi	philo[200];
	int				tab[5];
}	t_data;

int		is_digit(int c);
long	ft_strtol(const char *nptr, char **endptr);
void	print_output(t_data *data);

#endif
