/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:27:50 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/31 19:04:06 by tnessrou         ###   ########.fr       */
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
		usleep(1000);
	}
}

static void	*eat_count_check(void *link_v)
{
	t_link	*link;
	int		eat_sum;
	int		phil;

	link = (t_link *)link_v;
	eat_sum = 0;
	while (eat_sum < link->status->eat_count)
	{
		phil = 0;
		while (phil < link->status->phil_count)
			pthread_mutex_lock(&(link[phil++].philo->eat));
		eat_sum++;
	}
	output(link->philo, link->status, NOT_EAT);
	pthread_mutex_unlock(&link->status->is_dead);
	return (NULL);
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
		output(link->philo, link->status, FORK);
		pthread_mutex_lock(&link->status->forks[link->philo->r_fork]);
		output(link->philo, link->status, FORK);
		eat_action(link);
		output(link->philo, link->status, SLEEP);
		pthread_mutex_unlock(&link->status->forks[link->philo->r_fork]);
		pthread_mutex_unlock(&link->status->forks[link->philo->l_fork]);
		usleep(link->status->time_to_sleep * 1000);
		output(link->philo, link->status, THINK);
	}
}

int	threads(t_status *status, t_link *link)
{
	int			i;
	pthread_t	thread;

	i = 0;
	if (init_link(&link, status))
		return (1);
	status->time_begin = get_time();
	if (status->eat_count > 0)
	{
		if (pthread_create(&thread, NULL, eat_count_check, (void *)link))
			return (1);
		pthread_detach(thread);
	}
	while (i < status->phil_count)
	{
		if (pthread_create(&thread, NULL, coroutine, (void *)(link + i)))
			return (1);
		pthread_detach(thread);
		i++;
	}
	return (0);
}
