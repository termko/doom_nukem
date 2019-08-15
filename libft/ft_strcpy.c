/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:54:20 by njacobso          #+#    #+#             */
/*   Updated: 2018/11/28 21:54:22 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = -1;
	while (*(src + ++i))
		*(dst + i) = *(src + i);
	*(dst + i) = '\0';
	return (dst);
}
