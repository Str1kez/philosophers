/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:00:35 by tnessrou          #+#    #+#             */
/*   Updated: 2021/11/05 20:46:41 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_action(t_link *link)
{
	pthread_mutex_lock(&link->philo->mutex);
	link->philo->is_eat = 1;
	output(link->philo, link->status, EAT);
	usleep(link->status->time_to_eat * 1000);
	link->philo->is_eat = 0;
	link->philo->time_limit = get_time() + link->status->time_to_die;
	pthread_mutex_unlock(&link->philo->eat);
	pthread_mutex_unlock(&link->philo->mutex);
}
