/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:26:10 by zabdulza          #+#    #+#             */
/*   Updated: 2023/06/04 16:30:57 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (bfr[0] == 0)
	{
		free(bfr);
		return (NULL);
	}
	return (bfr);
}

char	*get_next_line(int fd)
{
	char		*lyne;
	static char	*bfr;	

	int (i) = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bfr = ft_creat_bfr(bfr, 1, fd);
	if (!bfr)
		return (NULL);
	i = ft_strcspn(bfr, "\n");
	lyne = (char *)malloc(sizeof(char) * (i + 2));
	if (!lyne)
		return (NULL);
	ft_memcpy(lyne, bfr, i);
	if (bfr[i] == '\n')
	{
		lyne[i] = bfr[i];
		i++;
	}
	lyne[i] = '\0';
	bfr = ft_nw_crt_bfr(bfr);
	return (lyne);
}
