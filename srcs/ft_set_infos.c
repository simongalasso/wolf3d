/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:41:45 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 16:48:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_set_infos(t_data *data)
{
	SDL_Rect	rect;
	SDL_Color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;

	rect.x = 10;
	rect.y = 10;
	rect.w = 150;
	rect.h = 50;

	ft_set_string(rect, "Ceci est un test", color, data);
}
