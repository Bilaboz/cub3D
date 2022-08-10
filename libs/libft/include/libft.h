/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:09:39 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/16 20:35:48 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# ifndef GNL_FD_SIZE
#  define GNL_FD_SIZE 10
# endif

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 128
# endif

# ifndef FT_PRINTF_BUFFER_SIZE
#  define FT_PRINTF_BUFFER_SIZE 128
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_putchar(char c);
char	*get_next_line(int fd);
int		ft_iswhitespace(char c);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
void	ft_putstr(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
int		ft_power(int nb, int power);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *ptr, size_t size);
void	ft_swap(void **ptr1, void **ptr2);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *str, int c);
int		ft_printf(const char *format, ...);
char	*ft_strrchr(const char *str, int c);
void	ft_putnbr_base(int nbr, char *base);
void	*ft_calloc(size_t nmenb, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
void	*ft_memchr(const void *src, int c, size_t n);
void	*ft_memset(void *ptr, int value, size_t size);
int		ft_str_matches_charset(char *str, char *charset);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *str, const char *to_find, size_t len);

/* Bonus */

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void	*content);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
