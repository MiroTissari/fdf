/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:24:58 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 21:50:29 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	ft_strdel (&hex);
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
		hex = ft_strjoin_free("0\0", hex, 0, 2);
	return (hex);
}

char	*hex_to_str(int hex)
{
	if (hex == WHITE)
		return ("FFFFFF");
	else if (hex == BLUE)
		return ("0000FF");
	else if (hex == RED)
		return ("FF0000");
	else if (hex == YELLOW)
		return ("FFFF00");
	else if (hex == GREEN)
		return ("00FF00");
	else if (hex == CYAN)
		return ("00FFFF");
	else if (hex == MAGENTA)
		return ("FF00FF");
	else if (hex == BROWN)
		return ("A52A2A");
	return ("FFFFFF");
}

int	back_to_int(t_col *col)
{
	char	*str;

	str = ft_strnew (6);
	if (col->r != 0)
		str = ft_strjoin_free(str, nb_to_hex(col->r), 2, 0);
	else
		str = ft_strjoin_free(str, "00", 2, 1);
	if (col->g != 0)
		str = ft_strjoin_free(str, nb_to_hex(col->g), 4, 0);
	else
		str = ft_strjoin_free(str, "00", 4, 1);
	if (col->b != 0)
		str = ft_strjoin_free(str, nb_to_hex(col->b), 6, 0);
	else
		str = ft_strjoin_free(str, "00", 6, 1);
	return (hex_converter(str));
}
