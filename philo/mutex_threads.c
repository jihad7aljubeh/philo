/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:56:23 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 01:24:48 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_code code)
{
	if (status != 0)
	{
		if (EINVAL == status && (code == LOCK || code == UNLOCK))
			exit_it("mutex is not initialized or destroyed");
		else if (EINVAL == status && (code == INIT || code == DESTROY))
			exit_it("mutex attribute is invalid");
		else if (EDEADLK == status && code == LOCK)
			exit_it("deadlock detected");
		else if (EPERM == status && code == UNLOCK)
			exit_it("current thread does not own the mutex");
		else
			exit_it("unknown mutex error");
	}
	else
		return ;
}

void	mtx_handle(t_mtx *mtx, t_code code)
{
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mtx), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mtx), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mtx, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mtx), code);
	else
		exit_it("wrong mutex code");
}

static void	handle_thread_error(int status, t_code code)
{
	if (status != 0)
	{
		if (EAGAIN == status)
			exit_it("No resources available to create another thread");
		else if (EPERM == status)
			exit_it("the caller does not have appropriate permission");
		else if (EINVAL == status && code == CREAT)
			exit_it("the values specified in attr are invalid");
		else if (EINVAL == status && (code == JOIN))
			exit_it("thread is not a joinable thread");
		else if (EINVAL == status && code == DETACH)
			exit_it("thread is not a joinable thread");
		else if (ESRCH == status)
			exit_it("no thread could be found");
		else if (EDEADLK == status)
			exit_it("deadlock detected");
		else
			exit_it("unknown thread error");
	}
	else
		return ;
}

void	thread_handle(pthread_t *thread, void *(fun)(void *), void *data,
		t_code code)
{
	if (code == CREAT)
		handle_thread_error(pthread_create(thread, NULL, fun, data), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else
		exit_it("wrong thread code");
}
