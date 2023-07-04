/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:46:47 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/04 10:59:09 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print(long time, int id, char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->p_info->print);
	printf("%ld	%d	%s\n", time, id, str);
	pthread_mutex_unlock(&ph->p_info->print);
}

void	ft_nbr_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->nbr_e);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->nbr_e);
}

void	*ft_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&ph->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "has taken a fork", ph);
		pthread_mutex_lock(&ph->next->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "has taken a fork", ph);
		print(ft_gettime() - ph->p_info->time, ph->id, "is eating", ph);
		if (ph->p_info->ac == 6)
			ft_nbr_eat(ph);
		pthread_mutex_lock(&ph->last_e);
		ph->last_eat = ft_gettime() - ph->p_info->time;
		pthread_mutex_unlock(&ph->last_e);
		ft_usleep(ph->p_info->tm_eat);
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next->fork);
		print(ft_gettime() - ph->p_info->time, ph->id, "is sleeping", ph);
		ft_usleep(ph->p_info->tm_sleep);
		print(ft_gettime() - ph->p_info->time, ph->id, "is thinking", ph);
	}
}

int	ft_check_eating(t_philo	*philo)
{
	int	k;

	k = 1;
	while (k <= philo->p_info->nb_ph)
	{
		pthread_mutex_lock(&philo->nbr_e);
		if (philo->nb_eat == philo->p_info->nb_tm_ph && !philo->eat_check)
		{
			philo->p_info->ck_eat_ph++;
			philo->eat_check = true;
		}
		pthread_mutex_unlock(&philo->nbr_e);
		if (philo->p_info->ck_eat_ph == philo->p_info->nb_ph)
			return (1);
		k++;
	}
	return (0);
}

int	ft_check_death(t_philo *ph)
{
	while (1)
	{
		if (ph->p_info->ac == 6)
		{
			if (ft_check_eating(ph))
				return (1);
		}
		pthread_mutex_lock(&ph->last_e);
		if ((ft_gettime() - ph->p_info->time - ph->last_eat) >= \
			ph->p_info->tm_die)
		{
			pthread_mutex_lock(&ph->p_info->print);
			printf("%ld	%d	%s\n", (ft_gettime() - ph->p_info->time),
				ph->id, "died");
			pthread_mutex_unlock(&ph->last_e);
			return (1);
		}
		pthread_mutex_unlock(&ph->last_e);
		ph = ph->next;
	}
	return (0);
}
