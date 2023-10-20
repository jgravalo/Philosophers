/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:43:29 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/12 15:43:35 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	print_state(philo, "has taken a fork");
	if (philo->fork1 == philo->fork2)
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	pthread_mutex_lock(philo->fork2);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->rules->life_check);
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->rules->assign);
	philo->times_eat++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->rules->assign);
	pthread_mutex_unlock(&philo->rules->life_check);
	do_sleep(philo->rules->to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	if (philo->rules->n_eats != -1 && \
	philo->times_eat == philo->rules->n_eats)
		return (1);
	return (0);
}

static void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->init);
	pthread_mutex_unlock(&philo->rules->init);
	if (!(philo->id % 2))
		do_sleep(philo->rules->to_eat);
	pthread_mutex_lock(&philo->rules->assign);
	while (!philo->rules->any_dead && !(philo->rules->n_eats != -1 \
		&& philo->times_eat == philo->rules->n_eats))
	{
		pthread_mutex_unlock(&philo->rules->assign);
		print_state(philo, "is thinking");
		if (routine_eating(philo))
			break ;
		print_state(philo, "is sleeping");
		do_sleep(philo->rules->to_sleep);
		pthread_mutex_lock(&philo->rules->assign);
	}
	pthread_mutex_unlock(&philo->rules->assign);
	return (NULL);
}

static void	routine_loop(t_rules *rules)
{
	int	i;
	int	t_eats;

	i = rules->n_philo - 1;
	while (!rules->any_dead && ++i)
	{
		if (i == rules->n_philo)
		{
			i = 0;
			t_eats = 0;
		}
		pthread_mutex_lock(&rules->assign);
		if (rules->philos[i].times_eat == rules->n_eats)
			t_eats++;
		pthread_mutex_unlock(&rules->assign);
		if (t_eats == rules->n_philo || !rules->n_eats)
			break ;
		pthread_mutex_lock(&rules->life_check);
		if (get_time() - rules->philos[i].last_eat >= rules->to_die)
			set_dead(&rules->philos[i], rules);
		pthread_mutex_unlock(&rules->life_check);
	}
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philos[i].ptr, NULL);
}

int	init_routine(t_rules *rules)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&rules->init);
	rules->start = get_time();
	while (++i < rules->n_philo)
	{
		if (pthread_create(&rules->philos[i].ptr, NULL, \
			(void *)routine, &rules->philos[i]))
			return (print_error(3));
	}
	pthread_mutex_unlock(&rules->init);
	i = -1;
	while (++i < rules->n_philo)
		rules->philos[i].last_eat = rules->start;
	routine_loop(rules);
	free_mutex(rules);
	return (1);
}
