/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:46:22 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/27 12:46:11 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(long s)
{
	long	start_time;

	start_time = ft_gettime();
	while (ft_gettime() <= (start_time + s))
		usleep(500);
}

void	ft_init_info(char **tab, t_info *info, int ac)
{
	info->nb_ph = 0;
	info->tm_die = 0;
	info->tm_eat = 0;
	info->tm_sleep = 0;
	info->nb_tm_ph = 0;
	info->ck_eat_ph = 0;
	info->nb_ph = ft_atoi(tab[0]);
	info->tm_die = ft_atoi(tab[1]);
	info->tm_eat = ft_atoi(tab[2]);
	info->tm_sleep = ft_atoi(tab[3]);
	if (ac == 6)
	{
		info->ac = 6;
		info->nb_tm_ph = ft_atoi(tab[4]);
		if (info->nb_tm_ph == 0)
			exit(0);
	}
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

void	init_sem_info(t_philo *ph)
{
	sem_unlink("/fork");
	ph->p_info->fork = sem_open("/fork", O_CREAT | O_EXCL, \
	0644, ph->p_info->nb_ph);
	sem_unlink("/print");
	ph->p_info->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (ph->p_info->ac == 6)
	{
		sem_unlink("/eat");
		ph->p_info->check_eat = sem_open("/eat", O_CREAT | O_EXCL, 0644, 0);
	}
}

t_philo	*ft_init_simaphore(t_philo	*ph)
{
	int		i;
	char	*str;

	i = 1;
	while (ph && i <= ph->p_info->nb_ph)
	{
		str = ft_strjoin("/last_e", (i + 48));
		sem_unlink(str);
		ph->last_e = sem_open(str, O_CREAT | O_EXCL, 0644, 1);
		free(str);
		str = ft_strjoin("/nbr_e", (i + 48));
		sem_unlink(str);
		ph->nbr_e = sem_open(str, O_CREAT | O_EXCL, 0644, 1);
		free(str);
		ph->nb_eat = 0;
		ph->last_eat = 0;
		i++;
		ph = ph->next;
	}
	init_sem_info(ph);
	return (ph);
}
