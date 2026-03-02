/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:19:53 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 18:15:16 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (sum > (LONG_MAX - (str[i] - '0')) / 10)
			exit_it("numeric overflow detected");
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		exit_it("non-numeric characters in argument");
	return (sum * sign);
}

void	*malloc_handle(size_t b)
{
	void	*tmp;

	tmp = malloc(b);
	if (tmp == NULL)
		exit_it("error in the malloc");
	return (tmp);
}

long	get_time(t_time code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		exit_it("error in gettimeofday");
	if (code == S)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (code == MS)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (code == US)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		exit_it("invalid time code");
	return (1337);
}

void	usleep_set(long us, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(US);
	while ((get_time(US) - start) < us)
	{
		if (sim_done(table))
			break ;
		elapsed = get_time(US) - start;
		remaining = us - elapsed;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
		{
			while (get_time(US) - start < us)
				;
		}
	}
}
