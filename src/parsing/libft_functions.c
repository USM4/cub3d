/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 04:42:27 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/14 02:34:55 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	ft_strlen_prs(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy_prs(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	l_src;

	l_src = ft_strlen_prs(src);
	i = 0;
	if (dstsize == 0)
		return (l_src);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l_src);
}

char	*ft_strjoin_prs(char *s1, char *s2)
{
	char	*s1_s2;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = ft_strlen_prs(s1) + ft_strlen_prs(s2);
	s1_s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s1_s2)
		return (NULL);
	while (s1[i] && i < len)
	{
		s1_s2[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i] && i < (len - ft_strlen_prs(s1)))
		s1_s2[j++] = s2[i++];
	s1_s2[j] = '\0';
	free(s1);
	return (s1_s2);
}

char	*ft_strdup_prs(char *s1)
{
	int		i;
	int		len;
	char	*to_fill;

	i = 0;
	len = ft_strlen_prs(s1);
	to_fill = malloc((len + 1) * sizeof(char));
	if (!to_fill)
		return (NULL);
	while (s1[i])
	{
		to_fill[i] = s1[i];
		i++;
	}
	to_fill[i] = '\0';
	return (to_fill);
}
