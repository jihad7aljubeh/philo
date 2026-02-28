/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:39:08 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:15:46 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include <errno.h>

#define DEBUG_MODE  0

typedef enum e_code
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREAT,
    JOIN,
    DETACH,
}       t_code;

typedef enum e_phstate
{
    EAT,
    SLEEP,
    THINK,
    FFORK,
    SFORK,
    DIE,
}           t_phstate;

typedef enum e_time
{
    S,
    MS,
    US,
}   t_time;

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
    t_mtx fork;
    int   fork_id;
    
}   t_fork;

typedef struct s_philo
{
    int id;
    long meals;
    bool full;
    long last_meal_time;
    t_fork  *first;
    t_fork  *second;
    pthread_t thread_id;
    t_table   *table;
    t_mtx philo_mtx;
}             t_philo;

struct s_table
{
    long    ph_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limit_meals;
    long    start_sim;
    bool    end_sim;
    bool    all_ready;
    pthread_t   monitor;
    t_mtx   table_mtx;
    t_mtx   print_mtx;
    t_fork  *forks;
    t_philo *philo;
};

void    exit_it(const char *error);
long	ft_atol(const char *str);
void    parse_table(t_table *table, char **av);
void    *malloc_handle(size_t b);
void    mtx_handle(t_mtx *mtx, t_code code);
void    thread_handle(pthread_t *thread, void *(fun)(void *), void *data, t_code code);
void    philo_init(t_table *table);
void    init_table(t_table *table);
bool sim_done(t_table *table);
long get_long(t_mtx *mtx, long *var);
void set_long(t_mtx *mtx, long *var, long value);
bool get_bool(t_mtx *mtx, bool *var);
void set_bool(t_mtx *mtx, bool *var, bool value);
long get_time(t_time code);
void usleep_set(long us, t_table *table);
void print_status(t_philo *philo, t_phstate status, bool debug);
void    start_dinner(t_table *table);
void    *sim_dinner(void *data);
void clean_table(t_table *table);
void    *monitor_routine(void *data);
void    wait_thread(t_table *table);

#endif