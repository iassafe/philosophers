/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:04:46 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/14 08:35:45 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return ;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	ft_check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (ft_putstr("Error\n"), 1);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			return (ft_putstr("Error\n"), 1);
	}
	return (0);
}

int	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (!ft_isdigit(str[i + 1]))
				return (ft_putstr("Error\n"), 1);
		}
		if (ft_isdigit(str[i])
			&& str[i + 1] != '\0' && str[i + 1] != ' '
			&& !ft_isdigit(str[i + 1]))
			return (ft_putstr("Error\n"), 1);
		i++;
	}
	return (0);
}

int	ft_number(char *str)
{
	int		i;
	long	n;

	if (str[0] == '\0')
		return (ft_putstr("Error\n"), 1);
	i = 0;
	while (str[i])
	{
		n = ft_atoi(&str[i]);
		if (n < INT_MIN || n > INT_MAX)
			return (ft_putstr("Error\n"), 1);
		if (!ft_isdigit(str[i])
			&& str[i] != '+' && str[i] != '-' && str[i] != ' ')
			return (ft_putstr("Error\n"), 1);
		i++;
	}
	return (0);
}
