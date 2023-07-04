/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:50:06 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/24 13:11:06 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && (i < dstsize - 1))
	{
		dst[i] = src[i];
			i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;

	l = 0;
	if (!s)
		return (NULL);
	if (start <= ft_strlen(s))
		l = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		start = 0;
	if (len < l)
		l = len;
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	ft_strlcpy (str, s + start, l + 1);
	return (str);
}

static char	**free_memory(char **p)
{
	size_t	n;

	n = 0;
	while (p[n])
	{
		free(p[n]);
		n++;
	}
	free(p);
	return (NULL);
}

static size_t	nbword(char const *str, char c)
{
	int		i;
	size_t	counter;

	counter = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i + 1] == '\0' || (str[i] == c && str[i + 1] != c))
			counter++;
		i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**split;
	size_t	k;
	size_t	start;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	split = (char **)malloc((nbword(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < nbword(s, c) && s[k])
	{
		while (s[k] == c)
			k++;
		start = k;
		while (s[k] != c && s[k])
			k++;
		split[i] = ft_substr(s, start, k - start);
		if (split[i++] == NULL)
			return (free_memory(split));
	}
	split[i] = NULL;
	return (split);
}
