/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:03:03 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/17 13:03:07 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef long long int	t_lli;

typedef struct s_rules	t_rules;

typedef struct s_philo	t_philo;

struct s_rules {
	t_mutex		print;
	t_mutex		init;
	t_mutex		life_check;
	t_mutex		*forks;
	t_philo		*philos;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			any_dead;
	int			n_eats;
	int			n_philo;
	long long	start;
};

struct s_philo
{
	pthread_t	ptr;
	int			id;
	int			times_eat;
	t_mutex		*fork1;
	t_mutex		*fork2;
	long long	last_eat;
	t_rules		*rules;
};

int				init_routine(t_rules *rules);

void			print_state(t_philo *philo, char *state);

void			do_sleep(long long time);

void			*set_dead(t_philo *philo, t_rules *rules);

long long int	get_time(void);

void			free_mutex(t_rules *rules);

int				check_errors(int argc, char **argv);

t_lli			ft_atoll(char *str);

int				free_arrs(void *f1, void *f2);

int				print_error(int type);

int				ft_strlen(char *str);

#endif
