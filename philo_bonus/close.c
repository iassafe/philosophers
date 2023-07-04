/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:03:11 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/27 12:46:25 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

char	*ft_strjoin(char *left_str, char buff)
{
	size_t	i;
	char	*result;

	i = 0;
	result = malloc(ft_strlen(left_str) + 2);
	if (result == NULL)
		return (NULL);
	while (left_str[i])
	{
		result[i] = left_str[i];
		i++;
	}
	result[i++] = buff;
	result[i] = '\0';
	return (result);
}

void	close_simaphore(t_philo *philo)
{
	int		k;
	char	*str;

	k = 1;
	while (k <= philo->p_info->nb_ph)
	{
		sem_close(philo->nbr_e);
		str = ft_strjoin("/nbr_e", (k + 48));
		sem_unlink(str);
		free(str);
		sem_close(philo->last_e);
		str = ft_strjoin("/last_e", (k + 48));
		sem_unlink(str);
		free(str);
		k++;
		philo = philo->next;
	}
	sem_close(philo->p_info->fork);
	sem_unlink("/fork");
}

void	kill_childs(t_philo *philo)
{
	int	k;

	k = 1;
	while (k <= philo->p_info->nb_ph)
	{
		kill(philo->pid, SIGINT);
		k++;
		philo = philo->next;
	}
}
