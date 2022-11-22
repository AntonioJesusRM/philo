/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:40:22 by aruiz-mo          #+#    #+#             */
/*   Updated: 2022/10/20 13:32:27 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_prog(t_philosophers *philo)
{
	int	i;
	int	n_philo;

	i = -1;
	n_philo = philo[0].dat->num_philo;
	while (++i < n_philo)
	{
		if (pthread_create(philo[i].id, NULL, &philo_cycle, &philo[i]))
		{
			printf("ERROR\n");
			return ;
		}
	}
	dead_check(philo, n_philo);
	i = -1;
	while (++i < n_philo)
		pthread_join(*philo[i].id, NULL);
	i = -1;
	while (++i < n_philo)
		pthread_mutex_destroy(&philo[i].fork);
}

void	*philo_cycle(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->dat->dead);
		if (philo->dat->state == 0)
		{
			pthread_mutex_unlock(&philo->dat->dead);
			break ;
		}
		pthread_mutex_unlock(&philo->dat->dead);
		if ((philo->dat->num_philo_eat != -1)
			&& philo->dat->num_all_eat
			>= (philo->dat->num_philo_eat * philo->dat->num_philo))
			return (NULL);
		philo_eat(philo);
		if (philo->dat->num_philo == 1)
			return (NULL);
	}
	return (NULL);
}

void	dead_check(t_philosophers *philo, int n_philo)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	if (philo->dat->num_philo_eat != -1)
		tmp = philo->dat->num_philo_eat;
	while (philo->dat->state)
	{
		if (i == n_philo)
			i = 0;
		pthread_mutex_lock(&philo->dat->dead);
		if (get_time() - philo[i].time_last_eat
			>= (size_t)philo[i].dat->time_to_die)
		{
			philo[i].dat->state = 0;
			if (philo[i].dat->num_all_eat < tmp * philo[0].dat->num_philo)
				print_state(philo, 4);
		}
		pthread_mutex_unlock(&philo->dat->dead);
		i++;
		usleep(100);
	}
}

void	philo_eat(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_state(philo, 0);
	if (philo->dat->num_philo == 1)
		return ;
	pthread_mutex_lock(&philo->next_philo->fork);
	print_state(philo, 0);
	print_state(philo, 1);
	philo->time_last_eat = get_time();
	wait_time(philo, (size_t)philo->dat->time_to_eat);
	if (philo->dat->num_philo_eat != -1)
		philo->dat->num_all_eat++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next_philo->fork);
	print_state(philo, 2);
	wait_time(philo, (size_t)philo->dat->time_to_sleep);
	print_state(philo, 3);
}

void	wait_time(t_philosophers *philo, size_t t)
{
	size_t	time_now;

	time_now = get_time();
	while (philo->dat->state)
	{
		if ((get_time() - time_now) >= t)
			break ;
		usleep(100);
	}
}
