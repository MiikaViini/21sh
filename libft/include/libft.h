/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:13:57 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/14 20:30:56 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../ft_printf/ft_printf.h"
# define CAPITAL 32

# define BUFF_SIZE 32
# define MAX_FD 4096

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memalloc(size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t n);
void	ft_memdel(void **ap);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_bzero(void *s, size_t n);
void	ft_strclr(char *s);
void	ft_strdel(char **as);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s);
char	*ft_strnew(size_t size);
char	**ft_strsplit(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *s1, const char *s2, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strrev(char *str);
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(t_list*elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void	ft_lstaddlast(t_list **alst, t_list *new);
void	ft_lstrev(t_list **alst);
int		ft_isspace(int c);
void	ft_swap(int *a, int *b);
char	*ft_strndup(const char *s, size_t size);
size_t	ft_abs(int num);
double	ft_pow(double num, double pow);
int		bintodec(signed long long bin);
char	*ft_dectobin(long long num);
size_t	ft_intlen(long long n);
char	*ft_itoabase(unsigned long long int num, int base, int flag);
char	*ft_ftoa(long double num, int afterpoint);
char	*ft_ltoa(long long int n);
char	*ft_utoa(unsigned long long n);
size_t	ft_putstrlen(char const *s);
int		get_next_line(const int fd, char **line);
char	**ft_strsplitws(char const *s);
char	**ft_strarrndup(char **dest, char **strarr, size_t size);
char	**ft_strarrcpy(char **dest, char **strarr);
size_t	ft_linecount(char **arr);
size_t	ft_wordcount_ws(const char *s);
int 	ft_only_digits(char *str);

#endif
