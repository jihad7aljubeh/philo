/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:39:05 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 00:17:33 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table    table;
    
    if(ac != 5 && ac != 6)
        exit_it("wrong input number\n");
    parse_table(&table, av);
    init_table(&table);
    start_dinner(&table);
    clean_table(&table);
    return (0);
}