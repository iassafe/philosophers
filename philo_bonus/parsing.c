/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:47:19 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/24 14:20:08 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_error(void)
{
	ft_putstr("Error\n");
	exit(1);
}

void	ft_check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		ft_error();
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			ft_error();
	}
}

void	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (!ft_isdigit(str[i + 1]))
				ft_error();
		}
		if (ft_isdigit(str[i])
			&& str[i + 1] != '\0' && str[i + 1] != ' '
			&& !ft_isdigit(str[i + 1]))
			ft_error();
		i++;
	}
}

void	ft_number(char *str)
{
	int		i;
	long	n;

	if (str[0] == '\0')
		ft_error();
	i = 0;
	while (str[i])
	{
		n = ft_atoi(&str[i]);
		if (n < INT_MIN || n > INT_MAX)
			ft_error();
		if (!ft_isdigit(str[i])
			&& str[i] != '+' && str[i] != '-' && str[i] != ' ')
			ft_error();
		i++;
	}
}
