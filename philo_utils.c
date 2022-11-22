/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:23:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2022/10/20 13:31:52 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	str_to_int(char *str_n)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (str_n[i] != '\0')
	{
		n = n * 10 + (str_n[i] - '0');
		i ++;
	}
	return (n);
}

void	print_error(int a)
{
	if (a == 0)
	{
		printf("Usage: ./philo \"number_of_philosophers\" \"time_to_die\" ");
		printf("\"time_to_eat\" \"time_to_sleep\" ");
		printf("\"[number_of_times_each_philosopher_must_eat]\"\n");
	}
	else if (a == 1)
		printf("Plese use only numbers.\n");
	else if (a == 2)
		printf("number_of_philo > 0.\n");
}

int	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
	}
	return (1);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_state(t_philosophers *philo, int state)
{
	pthread_mutex_lock(&philo->msg);
	if (philo->dat->state)
	{
		if (state == 0)
			printf("%lu, philo %d, has taken a fork.\n",
				get_time() - philo->dat->start_time, philo->philo_id);
		else if (state == 1)
			printf("%lu, philo %d, is eating.\n",
				get_time() - philo->dat->start_time, philo->philo_id);
		else if (state == 2)
			printf("%lu, philo %d, is sleeping.\n",
				get_time() - philo->dat->start_time, philo->philo_id);
		else if (state == 3)
			printf("%lu, philo %d, is thinking.\n",
				get_time() - philo->dat->start_time, philo->philo_id);
	}
	if (state == 4)
		printf("%lu, philo %d, died.\n",
			get_time() - philo->dat->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->msg);
}
