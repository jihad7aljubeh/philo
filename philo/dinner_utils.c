/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:49:44 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 16:00:58 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *var, bool value)
{
	mtx_handle(mtx, LOCK);
	*var = value;
	mtx_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *var)
{
	bool	value;

	mtx_handle(mtx, LOCK);
	value = *var;
	mtx_handle(mtx, UNLOCK);
	return (value);
}

void	set_long(t_mtx *mtx, long *var, long value)
{
	mtx_handle(mtx, LOCK);
	*var = value;
	mtx_handle(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *var)
{
	long	value;

	mtx_handle(mtx, LOCK);
	value = *var;
	mtx_handle(mtx, UNLOCK);
	return (value);
}

bool	sim_done(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_sim));
}
