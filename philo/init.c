/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:41:45 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:07:52 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo, t_fork *forks, int i)
{
	int	ph_nbr;

	ph_nbr = philo->table->ph_nbr;
	philo->first = &forks[(i + 1) % ph_nbr];
	philo->second = &forks[i];
	if (i % 2 == 0)
	{
		philo->first = &forks[i];
		philo->second = &forks[(i + 1) % ph_nbr];
	}
}

void	wait_thread(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_ready))
		usleep(100);
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->ph_nbr)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->meals = 0;
		philo->full = false;
		philo->table = table;
		mtx_handle(&philo->philo_mtx, INIT);
		set_forks(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_ready = false;
	table->philo = malloc_handle(sizeof(t_philo) * table->ph_nbr);
	mtx_handle(&table->table_mtx, INIT);
	mtx_handle(&table->print_mtx, INIT);
	table->forks = malloc_handle(sizeof(t_fork) * table->ph_nbr);
	while (++i < table->ph_nbr)
	{
		mtx_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
