/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:32:09 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/25 13:24:31 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	ft_gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long sleep)
{
	long	start_time;

	start_time = ft_gettime();
	while (ft_gettime() <= (start_time + sleep))
		usleep(500);
}

int	ft_init_info(char **tab, t_info *info, int ac)
{
	info->nb_ph = 0;
	info->tm_die = 0;
	info->tm_eat = 0;
	info->tm_sleep = 0;
	info->nb_tm_ph = 0;
	info->nb_ph = ft_atoi(tab[0]);
	info->tm_die = ft_atoi(tab[1]);
	info->tm_eat = ft_atoi(tab[2]);
	info->tm_sleep = ft_atoi(tab[3]);
	info->ck_eat_ph = 0;
	if (ac == 6)
	{
		info->ac = 6;
		info->nb_tm_ph = ft_atoi(tab[4]);
		if (info->nb_tm_ph == 0)
			return (1);
	}
	return (0);
}

t_philo	*ft_init_philo(t_info *info, t_philo *my_lst)
{
	t_philo	*philo;
	t_philo	*p;
	int		id;

	p = NULL;
	id = 1;
	while (id <= info->nb_ph)
	{
		philo = malloc(sizeof(t_philo));
		philo->id = id;
		philo->p_info = info;
		if (p == NULL)
		{
			p = philo;
			my_lst = p;
		}
		else
		{
			p->next = philo;
			p = philo;
		}
		id++;
	}
	philo->next = my_lst;
	return (my_lst);
}

t_philo	*ft_init_mutex(t_philo	*philo)
{
	int	i;

	i = 1;
	while (philo && i <= philo->p_info->nb_ph)
	{
		if (pthread_mutex_init(&philo->fork, NULL))
			return (NULL);
		if (pthread_mutex_init(&philo->last_e, NULL))
			return (NULL);
		if (pthread_mutex_init(&philo->nbr_e, NULL))
			return (NULL);
		philo->eat_check = false;
		philo->nb_eat = 0;
		philo->last_eat = 0;
		philo = philo->next;
		i++;
	}
	if (pthread_mutex_init(&philo->p_info->print, NULL))
		return (NULL);
	return (philo);
}
