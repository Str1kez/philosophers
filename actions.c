/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:00:35 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/19 19:02:51 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_action(t_link *link)
{
	pthread_mutex_lock(&link->philo->mutex);
	link->philo->is_eat = 1;
	link->philo->time_eat = get_time();
	link->philo->time_limit = link->philo->time_eat + link->status->time_to_die;
	output(link->philo, link->status, EAT);
	sleep(link->status->time_to_eat * 1000);
	link->philo->is_eat = 0;
	pthread_mutex_unlock(&link->philo->eat);
	pthread_mutex_unlock(&link->philo->mutex);
}
