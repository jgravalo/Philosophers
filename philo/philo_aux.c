/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:43:51 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/12 15:43:53 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_state(t_philo *philo, char *state)
{
	if (philo->rules->any_dead)
		return ;
	pthread_mutex_lock(&philo->rules->print);
	if (!philo->rules->any_dead)
		printf("%lld %i %s\n", get_time() - \
				philo->rules->start, philo->id, state);
	pthread_mutex_unlock(&philo->rules->print);
}

void	do_sleep(long long time)
{
	time += get_time();
	while (get_time() <= time)
		usleep(200);
}

void	*set_dead(t_philo *philo, t_rules *rules)
{
	rules->any_dead = 1;
	pthread_mutex_lock(&rules->print);
	printf("%lld %i %s\n", get_time() - rules->start, philo->id, "died");
	pthread_mutex_unlock(&rules->print);
	return (NULL);
}

void	free_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	free_arrs(rules->philos, rules->forks);
	while (++i < rules->n_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->init);
	pthread_mutex_destroy(&rules->life_check);
}
