/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:54:07 by zlayine           #+#    #+#             */
/*   Updated: 2020/10/31 09:27:15 by zlayine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define FD_SIZE 8192

size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
void			ft_bzero(void *b, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *src);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
	size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);

int				ft_tolower(int c);
int				ft_toupper(int c);
char			hex_digit(unsigned long long v, int maj);
int				ft_pow(int nb, int power);
int				ft_nblen(long long n);
int				ft_nblen_un(unsigned long long n);
void			ft_putnbr(long long d);
void			ft_putnbr_un(unsigned long long d);
void			ft_putstr(char *s);
void			ft_putchar(char c);
void			ft_del(void *data);
int				get_newln_len(char *str);
void			*new_str(void *str, void *data);
int				get_next_line(int fd, char **line);
char			**ft_arrdup(char **arr);
int     		ft_arr_len(char **arr);

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *));

#endif
