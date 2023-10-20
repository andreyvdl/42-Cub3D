/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:52:35 by adantas-          #+#    #+#             */
/*   Updated: 2023/10/20 20:23:56 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

int	ft_atoi(const char *nptr)
{
	short int	signal;
	int			num;

	num = 0;
	while (ft_isspace(*nptr))
		nptr++;
	signal = (*nptr == '+' || ft_isdigit(*nptr)) - (*nptr == '-');
	nptr += (*nptr == '+' || *nptr == '-');
	while (ft_isdigit(*nptr))
		num = (num * 10) + (*nptr++ - '0');
	return (num * signal);
}
