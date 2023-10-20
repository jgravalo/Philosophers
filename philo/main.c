/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:42:26 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/20 18:07:03 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_destroy_aux(t_mutex *m1, t_mutex *m2, t_mutex *m3)
{
	pthread_mutex_destroy(m1);
	pthread_mutex_destroy(m2);
	pthread_mutex_destroy(m3);
	return (1);
}

static int	init_mutex(t_rules *rules, int n_philo)
{
	static int	i = -1;

	if (pthread_mutex_init(&rules->print, NULL))
		return (1);
	if (pthread_mutex_init(&rules->init, NULL))
	{
		pthread_mutex_destroy(&rules->print);
		return (1);
	}
	if (pthread_mutex_init(&rules->life_check, NULL))
	{
		pthread_mutex_destroy(&rules->print);
		pthread_mutex_destroy(&rules->init);
		return (1);
	}
	if (pthread_mutex_init(&rules->assign, NULL))
		return (mutex_destroy_aux(&rules->life_check,
				&rules->print, &rules->init));
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (mutex_destroy_aux(&rules->print,
					&rules->assign, &rules->life_check));
	}
	return (0);
}

static void	init_philos(t_rules *rules, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].fork1 = &rules->forks[i];
		rules->philos[i].fork2 = &rules->forks[((i + 1) % rules->n_philo)];
		rules->philos[i].rules = rules;
		rules->philos[i].times_eat = 0;
	}
}

static int	init_rules(t_rules *rules, int argc, char **argv)
{
	rules->any_dead = 0;
	rules->n_philo = ft_atoll(argv[0]);
	if (!rules->n_philo)
		return (1);
	rules->to_die = ft_atoll(argv[1]);
	rules->to_eat = ft_atoll(argv[2]);
	rules->to_sleep = ft_atoll(argv[3]);
	rules->n_eats = -1;
	if (argc == 5)
		rules->n_eats = ft_atoll(argv[4]);
	if (!rules->n_philo || !rules->n_eats || (argc == 5 && rules->n_eats < 0))
		return (1);
	rules->philos = (t_philo *)malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->philos)
		return (1);
	rules->forks = (t_mutex *)malloc(sizeof(t_mutex) * rules->n_philo);
	if (!rules->forks)
		return (free_arrs(rules->philos, NULL));
	if (init_mutex(rules, rules->n_philo))
		return (free_arrs(rules->philos, rules->forks));
	init_philos(rules, rules->n_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (check_errors(argc - 1, &argv[1]))
		return (1);
	if (init_rules(&rules, argc - 1, &argv[1]))
		return (1);
	if (init_routine(&rules) == 0)
		return (1);
	return (0);
}
