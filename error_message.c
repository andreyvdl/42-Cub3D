/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:14:33 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/17 15:28:37 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int	you_made_the_l(char *str)
{
	ft_putendl_fd(1, "Error", 5);
	ft_putendl_fd(1, str, ft_strlen(str));
	return (-1);
}
