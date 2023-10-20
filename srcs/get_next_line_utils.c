/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas-, rleite-s <adantas-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:13:48 by rleite-s          #+#    #+#             */
/*   Updated: 2023/10/20 20:24:05 by adantas-, r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_node(t_text **text)
{
	t_text	*aux;

	if (!text || !*text)
		return ;
	aux = (*text)->next;
	free(*text);
	*text = aux;
}

void	free_list(t_text **text)
{
	if (!text || !*text)
		return ;
	while (*text)
		free_node(text);
}

int	insert_into_list(t_text **text, char letter)
{
	t_text	*aux;

	if (!text)
		return (-1);
	if (!*text)
	{
		*text = malloc(sizeof(t_text));
		if (!*text)
			return (-1);
		(*text)->letter = letter;
		(*text)->next = NULL;
		return (0);
	}
	aux = *text;
	while (aux->next)
		aux = aux->next;
	aux->next = malloc(sizeof(t_text));
	if (!aux->next)
		return (-1);
	aux->letter = letter;
	aux->next = NULL;
	return (0);
}
