/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:37:17 by aruiz-mo          #+#    #+#             */
/*   Updated: 2022/12/01 16:04:52 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_dates	*create_dates(char **argv)
{
	t_dates	*dates;

	dates = (t_dates *)malloc(sizeof(t_dates));
	if (!dates)
		return (NULL);
	dates->num_philo = str_to_int(argv[1]);
	dates->time_to_die = str_to_int(argv[2]);
	dates->time_to_eat = str_to_int(argv[3]);
	dates->time_to_sleep = str_to_int(argv[4]);
	dates->start_time = get_time();
	if (argv[5] == NULL)
		dates->num_philo_eat = -1;
	else
		dates->num_philo_eat = str_to_int(argv[5]);
	dates->num_all_eat = 0;
	dates->state = 1;
	pthread_mutex_init(&dates->dead, NULL);
	return (dates);
}

void	parse(char **argv, t_philosophers *philo)
{
	int		i;
	t_dates	*dates;

	dates = create_dates(argv);
	i = -1;
	while (++i < str_to_int(argv[1]))
	{
		philo[i].philo_id = i + 1;
		philo[i].id = (pthread_t *)malloc(sizeof(pthread_t));
		philo[i].time_last_eat = get_time();
		philo[i].dat = dates;
		pthread_mutex_init(&philo[i].msg, NULL);
		pthread_mutex_init(&philo[i].fork, NULL);
	}
	i = -1;
	while (++i < str_to_int(argv[1]) - 1)
		philo[i].next_philo = &philo[i + 1];
	philo[i].next_philo = &philo[0];
	init_prog(philo);
	free_all(philo);
}

void	free_all(t_philosophers *philo)
{
	int	i;
	int	nf;

	i = -1;
	nf = philo->dat->num_philo;
	while (++i < nf)
		free (philo[i].id);
	free(philo->dat);
}

int	main(int argc, char **argv)
{	
	t_philosophers	*philo;

	philo = (t_philosophers *) NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (check_argv(argc, argv))
		{
			if (str_to_int(argv[1]) <= 0)
				print_error(2);
			else
			{
				philo = (t_philosophers *)malloc(sizeof (t_philosophers)
						* str_to_int(argv[1]));
				if (!philo)
					return (0);
				parse(argv, philo);
			}
		}
		else
			print_error(1);
	}
	else
		print_error(0);
	free (philo);
	return (0);
}
