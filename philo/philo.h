/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:45:57 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/27 10:25:57 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_info
{
	int				nb_ph;
	int				tm_eat;
	int				tm_die;
	int				tm_sleep;
	int				nb_tm_ph;
	long			time;
	int				ac;
	int				ck_eat_ph;
	pthread_mutex_t	print;
}			t_info;

typedef struct s_philo
{
	int					id;
	long				last_eat;
	int					nb_eat;
	struct s_philo		*next;
	t_info				*p_info;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		last_e;
	pthread_mutex_t		nbr_e;
	bool				eat_check;	
}						t_philo;

int		ft_check_eating(t_philo	*philo);
void	*ft_routine(void *arg);
t_philo	*ft_init_mutex(t_philo	*philo);
int		ft_check_death(t_philo *philo);
void	ft_usleep(long sleep);
long	ft_gettime(void);
void	free_tab(char **tab);
void	ft_putstr(char *str);
int		ft_number(char *str);
int		ft_check(char *str);
int		ft_check_empty(char *str);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		ft_init_info(char **tab, t_info *info, int ac);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_space(char *left_str, char *buff, char s);
t_philo	*ft_init_philo(t_info *info, t_philo *my_lst);
#endif