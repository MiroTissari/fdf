/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:10:36 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/12 19:22:26 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(float num)
{
	int	minus;

	minus = -1;
	if (num < 0)
	{
		num = num * minus;
	}
	return (num);
}

int	hex_converter(char *hex)
{
	int	i;
	int	len;
	int	nb;
	int	total;

	len = ft_strlen(hex);
	i = 0;
	total = 0;
	while (hex[i])
	{
		if (hex[i] <= '9' && hex[i] >= '0')
			nb = hex[i] - 48;
		else if (hex[i] <= 'F' && hex[i] >= 'A')
			nb = hex[i] - 65 + 10;
		else if (hex[i] <= 'f' && hex[i] >= 'a')
			nb = hex[i] - 97 + 10;
		else
			return (0);
		total = total + nb * pow(16, (len - (i + 1)));
		i++;
	}
	return (total);
}

char	*nb_to_hex(int num)
{
	int			i;
	float		nb;
	float		remain;
	char		temp[10];
	char		*hex;

	i = 0;
	remain = num;
	while (remain >= 1 || i < 2)
	{
		remain = remain / 16;
		nb = (remain - (int)remain) * 16;
		if (nb >= 10)
			temp[i] = (nb - 10 + 65);
		else
			temp[i] = (nb + '0');
		i++;
	}
	num = 0;
	hex = ft_strnew(i);
	while (--i >= 0)
		hex[num++] = temp[i];
	//if (remain)
	//	hex[num] = '1';
	return (hex);
}
