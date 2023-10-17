/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:43:08 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/12 15:43:10 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_isnum(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if ((s[0] == '-' || s[0] == '+') && \
		(s[1] == '-' || s[1] == '+'))
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_size(t_lli n, t_lli len)
{
	int	size;

	size = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n /= len;
	}
	return (size);
}

static int	ft_isint(char *n)
{
	int			i;
	long long	tmp;

	i = 0;
	if (!n || !*n)
		return (0);
	if (n[i] == '-' || n[i] == '+')
		i++;
	while (n[i] && n[i] == '0')
		i++;
	if (!n[i])
		i--;
	if (ft_strlen(&n[i]) > ft_size(INT_MAX, 10))
		return (0);
	tmp = ft_atoll(n);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (0);
	return (1);
}

int	check_errors(int argc, char **argv)
{
	int	i;

	if (argc < 4 || argc > 5)
		return (print_error(1));
	i = -1;
	while (++i < argc)
		if (!ft_isint(argv[i]) || !ft_isnum(argv[i]))
			return (print_error(2));
	return (0);
}
