/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:14:33 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/20 20:23:51 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	you_made_the_l(char *str)
{
	ft_putendl_fd(STDERR_FILENO, "Error");
	ft_putendl_fd(STDERR_FILENO, str);
	return (-1);
}
