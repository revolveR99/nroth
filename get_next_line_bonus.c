/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:26:38 by zabdulza          #+#    #+#             */
/*   Updated: 2023/06/04 16:31:38 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	index;
	size_t	charset_index;

	index = 0;
	while (str[index] != '\0')
	{
		charset_index = 0;
		while (charset[charset_index] != '\0')
		{
			if (str[index] == charset[charset_index])
				return (index);
			charset_index++;
		}
		index++;
	}
	return (index);
}

char	*ft_nw_crt_bfr(char *bfr)
{
	int		i;
	int		zi;
	int		ln;
	char	*result;

	i = 0;
	zi = 0;
	ln = ft_len(bfr);
	while (bfr[i] && bfr[i] != '\n')
		i++;
	if (!bfr[i])
	{
		free(bfr);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ln - i + 1));
	if (!result)
		return (NULL);
	i++;
	while (bfr[i])
		result[zi++] = bfr[i++];
	result[zi] = '\0';
	free(bfr);
	return (result);
}

char	*ft_creat_bfr(char *bfr, int bfr_sze, int fd)
{
	char	*temporary;

	temporary = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temporary)
		return (NULL);
	while ((bfr_sze != 0 && !ft_find_n(bfr)))
	{
		bfr_sze = read(fd, temporary, BUFFER_SIZE);
		if (bfr_sze == -1)
		{
			free(temporary);
			return (NULL);
		}
		temporary[bfr_sze] = '\0';
		bfr = ft_strjoin(bfr, temporary);
	}
	free(temporary);
	if (bfr && bfr[0] == '\0')
	{
		free(bfr);
		return (NULL);
	}
	return (bfr);
}

char	*get_next_line(int fd)
{
	char		*lyne;
	static char	*bfr[1024];	

	int (i) = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bfr[fd] = ft_creat_bfr(bfr[fd], 1, fd);
	if (!bfr[fd])
		return (NULL);
	i = ft_strcspn(bfr[fd], "\n");
	lyne = (char *)malloc(sizeof(char) * (i + 2));
	if (!lyne)
		return (NULL);
	ft_memcpy(lyne, bfr[fd], i);
	if (bfr[fd][i] == '\n')
	{
		lyne[i] = bfr[fd][i];
		i++;
	}
	lyne[i] = '\0';
	bfr[fd] = ft_nw_crt_bfr(bfr[fd]);
	return (lyne);
}
