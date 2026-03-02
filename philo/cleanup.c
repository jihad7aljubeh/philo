/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:09:21 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:07:06 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	exit_it(const char *error)
{
	write(2, "Error: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	clean_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->ph_nbr)
	{
		mtx_handle(&table->forks[i].fork, DESTROY);
		mtx_handle(&table->philo[i].philo_mtx, DESTROY);
	}
	mtx_handle(&table->print_mtx, DESTROY);
	mtx_handle(&table->table_mtx, DESTROY);
	free(table->philo);
	free(table->forks);
}
