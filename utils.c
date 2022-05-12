/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:10:36 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/12 21:49:40 by mtissari         ###   ########.fr       */
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

char	*nb_to_hex(size_t num)
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
	if (ft_strlen(hex) != 2)
		hex = ft_strjoin("0\0", hex);
	return (hex);
}

char	*hex_to_str(int hex)
{
	char	*str;

	str = ft_strnew(6);
	if (hex == WHITE)
		str = "FFFFFF";
	else if (hex == BLUE)
		str = "0000FF";
	else if (hex == RED)
		str = "FF0000";
	else if (hex == YELLOW)
		str = "FFFF00";
	else if (hex == GREEN)
		str = "00FF00";
	else if (hex == CYAN)
		str = "00FFFF";
	else if (hex == MAGENTA)
		str = "FF00FF";
	return (str);
}
