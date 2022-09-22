/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:40:54 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 11:44:19 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_strlen_del(const char *s, char del)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != del && s[i] != '\0')
			i++;
	}
	return (i);
}

/* Adapted with the read of only one char into a two char array.*/
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join;
	size_t	join_len;
	size_t	i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	join_len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *) ft_calloc ((join_len + 1), sizeof (char));
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = s2[0];
	free(s1);
	return (join);
}

/* Deals with newlines instead of endlines and handles the case that s1 could */
/* be NULL as a valid input. Also stores the line in a parameter struct.*/
void	ft_strjoin_so_long(t_var *var, char const *s1, char const *s2)
{
	var->i = 0;
	var->j = 0;
	if (!s2)
		error_handler(MAP_READ_ERR, var);
	var->str_len = ft_strlen_del(s1, '\n') + ft_strlen_del(s2, '\n');
	var->map.line = (char *) ft_calloc ((var->str_len + 1), sizeof (char));
	if (var->map.line == NULL)
		error_handler(4, var);
	if (!s1)
		var->map.line = ft_strdup(s2);
	while (s1[var->i] != '\n' || s1[var->i] != '\0')
	{
		var->map.line[var->i] = s1[var->i];
		var->i++;
	}
	while (s2[var->i] != '\n' || s2[var->j] != '\0')
	{
		var->map.line[var->i + var->j] = s2[var->j];
		var->j++;
	}
}
