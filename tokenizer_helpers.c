#include "minishell.h"


char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((ft_strlen(s1) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int is_operator(char *line)
{
	if (!line)
	    return (0);
	if (line[0] == '|' && line[1] == '|')  // "||"
		return (1);
	if (line[0] == '&' && line[1] == '&')  // "&&"
		return (1);
	if (line[0] == '>' && line[1] == '>')  // ">>"
		return (1);
	//agora verifico os operadores simples
	if (line[0] == '|' || line[0] == '<' || line[0] == '>' || line[0] == ';')
		return (1);
	return (0);
}

int is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int	is_quote(char c)
{
	return(c == '\"' || c == '\'');
}
int is_single_quote(char c)
{
	return(c == '\'');
}
int	is_double_quote(char c)
{
	return(c == '\"');
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	dst_cpy = (unsigned char *) dst;
	src_cpy = (unsigned char *) src;
	if (dst == (void *) 0 && src == (void *) 0)
		return (dst);
	while (n--)
		*(dst_cpy++) = *(src_cpy++);
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}
