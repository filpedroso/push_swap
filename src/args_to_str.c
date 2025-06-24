/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:04:49 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 14:04:49 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		*ft_memcpy(void *dest, const void *src, size_t n);
static void		copy_args(char *result, int argc, char **argv);
static size_t	ft_strlen(const char *s);

char	*args_to_str(int argc, char **argv)
{
	int 	i;
	char	*result;
	size_t	total_len;

	total_len = 0;
	i = 0;
	while (++i < argc)
		total_len += ft_strlen(argv[i]) + 1;
	result = (char *)malloc(total_len);
	if (!result)
		return NULL;
	copy_args(result, argc, argv);
	return result;
}
static void	copy_args(char *result, int argc, char **argv)
{
	size_t	len;
	char	*ptr;
	int		i;

	ptr = result;
	i = 0;
	while (++i < argc)
	{
		len = ft_strlen(argv[i]);
		ft_memcpy(ptr, argv[i], len);
		ptr += len;
		if (i != argc - 1)
			*ptr++ = ' ';
	}
	*ptr = '\0';
}

static size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
	{
		ptr++;
	}
	return ((size_t)(ptr - s));
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d_ptr;
	const unsigned char	*s_ptr;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	d_ptr = (unsigned char *)dest;
	s_ptr = (const unsigned char *)src;
	while (n--)
	{
		*d_ptr = *s_ptr;
		d_ptr++;
		s_ptr++;
	}
	return (dest);
}
