/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:28:04 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/04 12:46:01 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

long	ft_gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_nbr_eat(t_philo *philo)
{
	philo->nb_eat++;
	if (philo->nb_eat == philo->p_info->nb_tm_ph)
		sem_post(philo->p_info->check_eat);
}

void	print(long time, int id, char *str, t_philo *ph)
{
	sem_wait(ph->p_info->print);
	printf("%ld\t%d\t%s\n", time, id, str);
	sem_post(ph->p_info->print);
}

void	ft_routine(t_philo	*ph)
{
	while (1)
	{
		sem_wait(ph->p_info->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "has taken a fork", ph);
		sem_wait(ph->p_info->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "has taken a fork", ph);
		print(ft_gettime() - ph->p_info->time, ph->id, "is eating", ph);
		sem_wait(ph->last_e);
		ph->last_eat = ft_gettime() - ph->p_info->time;
		sem_post(ph->last_e);
		sem_wait(ph->nbr_e);
		if (ph->p_info->ac == 6 && ph->nb_eat < ph->p_info->nb_tm_ph)
			ft_nbr_eat(ph);
		sem_post(ph->nbr_e);
		ft_usleep(ph->p_info->tm_eat);
		sem_post(ph->p_info->fork);
		sem_post(ph->p_info->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "is sleeping", ph);
		ft_usleep(ph->p_info->tm_sleep);
		print(ft_gettime() - ph->p_info->time, ph->id, "is thinking", ph);
	}
}

void	*ft_check_eating(void *arg)
{
	t_philo	*philo;
	int		k;

	philo = arg;
	k = 1;
	while (k <= philo->p_info->nb_ph)
	{
		sem_wait(philo->p_info->check_eat);
		k++;
	}
	sem_wait(philo->p_info->print);
	close_simaphore(philo);
	kill_childs(philo);
	exit(0);
}
