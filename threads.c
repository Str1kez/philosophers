/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:27:50 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/21 19:09:15 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_check(void *link_v)
{
	t_link		*link;

	link = (t_link *)link_v;
	while (1)
	{
		pthread_mutex_lock(&link->philo->mutex);
		if (!link->philo->is_eat && link->philo->time_limit < get_time())
		{
			output(link->philo, link->status, DEATH);
			pthread_mutex_unlock(&link->philo->mutex);
			pthread_mutex_unlock(&link->status->is_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&link->philo->mutex);
		// ? Почему от этого зависит длительность жизни???
		usleep(1000);
	}
}

static void	*coroutine(void *link_v)
{
	t_link		*link;
	pthread_t	thread;

	link = (t_link *)(link_v);
	link->philo->time_eat = get_time();
	link->philo->time_limit = link->philo->time_eat + link->status->time_to_die;
	if (pthread_create(&thread, NULL, death_check, link_v))
		return (NULL);
	pthread_detach(thread);
	while (1)
	{
		pthread_mutex_lock(&link->status->forks[link->philo->l_fork]);
		pthread_mutex_lock(&link->status->forks[link->philo->r_fork]);
		eat_action(link);
		pthread_mutex_unlock(&link->status->forks[link->philo->l_fork]);
		pthread_mutex_unlock(&link->status->forks[link->philo->r_fork]);
		output(link->philo, link->status, SLEEP);
		usleep(link->status->time_to_sleep * 1000);
		output(link->philo, link->status, THINK);
	}
}

int	threads(t_status *status, t_link *link)
{
	unsigned int	i;
	pthread_t		thread;

	i = 0;
	if (init_link(&link, status))
		return (1);
	status->time_begin = get_time();
	while (i < status->phil_count)
	{
		if (pthread_create(&thread, NULL, coroutine, (void *)(link + i)))
			return (1);
		pthread_detach(thread);
		// usleep(100);
		i++;
	}
	return (0);
}
