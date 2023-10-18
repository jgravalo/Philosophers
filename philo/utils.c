/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:44:31 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/12 15:44:35 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(char *str)
{
	long long	neg;
	long long	res;

	neg = 1;
	res = 0;
	if (!str || !*str)
		return (0);
	while (*str && (*str == '\t' || *str == ' ' || *str == '\n'))
		str++;
	if (*str && *str == '-')
		neg = -1;
	if (*str && (*str == '+' || *str == '-'))
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = (*str - '0') + (res * 10);
		str++;
	}
	return (res * neg);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	free_arrs(void *f1, void *f2)
{
	free(f1);
	free(f2);
	return (1);
}

int	print_error(int type)
{
	char	*msg;

	msg = NULL;
	if (type == 1)
		msg = "\'Invalid number of arguments\'";
	else if (type == 2)
		msg = "\'Arguments must be an integers\'";
	else if (type == 3)
		msg = "\'Thread error\'";
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}
