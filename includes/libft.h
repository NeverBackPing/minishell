/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:30:03 by sjossain          #+#    #+#             */
/*   Updated: 2024/04/16 14:47:56 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include "minishell.h"

//LIBC and LIBBSD
bool			empty_space(char *srcs);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isspace(char *str);
int				ft_signe(char *str);
int				ft_isdigit(char *str);
int				ft_isprint(int c);
void			ft_putstr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmp_ascii(const char *s1, int ascii);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, int n);
char			*ft_strtok(char *str, char delimiter);
char			*check_str(char *buf);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
//FUNCTION ADD
size_t			ft_array_len(char **array);
char			**ft_split_token(const char *s, char delim);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			**dest_free(char **dest);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcharjoin(char const *s1, char c);
char			*ft_strtrim(char const *s1, char const *set);
int				check_signe(char *str);
int				loop_signe(char *str, int i, int first, int second);
int				check(int first, int second, int digit, char *str);
int				check_part2(int first, int digit);
int				words(const char *str);
//BONUS
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
	struct s_list		*prev;
}	t_list;
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
#endif
