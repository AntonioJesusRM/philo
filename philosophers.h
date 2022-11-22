/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:29:31 by aruiz-mo          #+#    #+#             */
/*   Updated: 2022/10/20 13:29:17 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/*	STRUCTS  */

typedef struct s_dates
{
	int					num_philo;
	int					num_all_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_philo_eat;
	int					state;
	size_t				start_time;
	pthread_mutex_t		dead;
}	t_dates;

typedef struct s_philosophers
{
	int						philo_id;
	size_t					time_last_eat;
	pthread_t				*id;
	pthread_mutex_t			fork;
	pthread_mutex_t			msg;
	struct s_philosophers	*next_philo;
	t_dates					*dat;
}	t_philosophers;

/*	MAIN  */

int				main(int argc, char **argv);
void			parse(char **argv, t_philosophers *philo);
void			free_all(t_philosophers *philo);
t_dates			*create_dates(char **argv);

/*	PROGRAM  */

void			init_prog(t_philosophers *philo);
void			*philo_cycle(void *arg);
void			dead_check(t_philosophers *philo, int n_philo);
void			philo_eat(t_philosophers *philo);
void			wait_time(t_philosophers *philo, size_t t);

/*	PHILO_UTILS  */

int				str_to_int(char *str_n);
void			print_error(int a);
int				check_argv(int argc, char **argv);
void			print_state(t_philosophers *philo, int state);
size_t			get_time(void);

#endif