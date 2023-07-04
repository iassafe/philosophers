/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:46:48 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/04 12:45:57 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check_death(t_philo *philo)
{
	long	current;

	while (1)
	{
		current = (ft_gettime() - philo->p_info->time);
		sem_wait(philo->last_e);
		if ((current - philo->last_eat) >= philo->p_info->tm_die)
		{
			sem_wait(philo->p_info->print);
			printf("%ld\t%d\t%s\n", current, philo->id, "died");
			sem_post(philo->last_e);
			exit(0);
		}
		sem_post(philo->last_e);
	}
}

void	ft_create_philo(t_philo *philo)
{
	int			k;
	pthread_t	thread;

	k = 1;
	thread = NULL;
	philo->p_info->time = ft_gettime();
	while (k <= philo->p_info->nb_ph)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			pthread_create(&philo->thread, NULL, (void *)ft_check_death, philo);
			ft_routine(philo);
		}
		else if (philo->pid < 0)
			exit(1);
		k++;
		usleep(200);
		philo = philo->next;
	}
	if (philo->p_info->ac == 6)
		pthread_create(&thread, NULL, ft_check_eating, philo);
}

void	ft_philo(t_info *info, t_philo *philo, char *join, int ac)
{
	long	nbr;
	char	**tab;

	tab = ft_split(join, ' ');
	free(join);
	nbr = ft_atoi(tab[0]);
	if (nbr == 0)
		exit(0);
	ft_init_info(tab, info, ac);
	free_tab(tab);
	philo = ft_init_philo(info, philo);
	philo = ft_init_simaphore(philo);
	ft_create_philo(philo);
	waitpid(-1, 0, 0);
	close_simaphore(philo);
	kill(0, SIGINT);
	exit(0);
}

int	main(int ac, char **av)
{
	int		i;
	long	nbr;
	char	*join;
	t_info	info;
	t_philo	*philo;

	philo = NULL;
	join = NULL;
	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (av[++i])
		{
			nbr = ft_atoi(av[i]);
			if (nbr < 0)
				ft_error();
			ft_check_empty(av[i]);
			ft_check(av[i]);
			ft_number(av[i]);
			join = ft_strjoin_space(join, av[i], ' ');
		}
		ft_philo(&info, philo, join, ac);
	}
	else
		ft_error();
}
