/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:14:33 by adantas-, r       #+#    #+#             */
/*   Updated: 2023/10/18 17:33:46 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	you_made_the_l(char *str)
{
	ft_putendl_fd(STDERR_FILENO, "Error");
	ft_putendl_fd(STDERR_FILENO, str);
	return (-1);
}
