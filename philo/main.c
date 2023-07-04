/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:45:50 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/04 11:26:27 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_philo *philo)
{
	int	k;

	k = 1;
	while (k <= philo->p_info->nb_ph)
	{
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->nbr_e);
		pthread_mutex_destroy(&philo->last_e);
		k++;
		philo = philo->next;
	}
}

void	ft_philo(t_info *info, t_philo *philo, char *join, int ac)
{
	long	nbr;
	char	**tab;
	int		i;

	tab = ft_split(join, ' ');
	free(join);
	nbr = ft_atoi(tab[0]);
	if (nbr == 0 || ft_init_info(tab, info, ac))
		return ;
	free_tab(tab);
	info->time = ft_gettime();
	philo = ft_init_philo(info, philo);
	philo = ft_init_mutex(philo);
	i = 1;
	while (i <= info->nb_ph)
	{
		pthread_create(&philo->thread, NULL, *ft_routine, philo);
		i++;
		usleep(200);
		philo = philo->next;
	}
	if (ft_check_death(philo))
		return (ft_destroy_mutex(philo));
}

int	main(int ac, char **av)
{
	int		i;
	long	nbr;
	char	*join;
	t_info	info;
	t_philo	*philo;

	nbr = 0;
	philo = NULL;
	join = NULL;
	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (av[++i])
		{
			nbr = ft_atoi(av[i]);
			if (nbr < 0)
				return (ft_putstr("Error\n"), 0);
			if (ft_check(av[i]) || ft_number(av[i]) || ft_check_empty(av[i]))
				return (0);
			join = ft_strjoin_space(join, av[i], ' ');
		}
		ft_philo(&info, philo, join, ac);
	}
	else
		return (ft_putstr("Error\n"), 0);
}
