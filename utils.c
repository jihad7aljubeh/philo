/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:19:53 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 00:39:00 by jalju-be         ###   ########.fr       */
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
		sum = sum * 10 + (str[i] - '0');
		i++;
	}

	return (sum * sign);
}

void    *malloc_handle(size_t b)
{
	void	*tmp;

	tmp = malloc(b);
	if(tmp = NULL)
		exit_it("error in the malloc");
	return (tmp);
}