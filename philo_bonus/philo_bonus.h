/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:49:23 by iassafe           #+#    #+#             */
/*   Updated: 2023/06/27 10:34:11 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
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
	sem_t			*print;
	sem_t			*fork;
	sem_t			*check_eat;
}			t_info;

typedef struct s_philo
{
	int					id;
	int					nb_eat;
	pthread_t			thread;
	struct s_philo		*next;
	t_info				*p_info;
	pid_t				pid;
	long				last_eat;
	sem_t				*last_e;
	sem_t				*nbr_e;
}						t_philo;

void	kill_childs(t_philo *philo);
void	close_simaphore(t_philo *philo);
void	*ft_check_eating(void *arg);
void	ft_routine(t_philo	*ph);
void	ft_error(void);
void	ft_usleep(long sleep);
long	ft_gettime(void);
void	free_tab(char **tab);
void	ft_putstr(char *str);
void	ft_number(char *str);
void	ft_check(char *str);
void	ft_check_empty(char *str);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
t_philo	*ft_init_simaphore(t_philo	*philo);
char	*ft_strjoin(char *left_str, char buff);
void	ft_init_info(char **tab, t_info *info, int ac);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_space(char *left_str, char *buff, char s);
t_philo	*ft_init_philo(t_info *info, t_philo *my_lst);
void	ft_check_death(t_philo *philo);
#endif
