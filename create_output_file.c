/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_output_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:32:59 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 15:59:15 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"


int	create_output_file(t_scene *img)
{
	img->output_fd = open(img->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (img->output_fd == -1)
		return (EXIT_FAILURE);
	img->width = WINDOW_WIDTH;
	img->height = WINDOW_HEIGHT;
	ft_putstr_fd("P3\n", img->output_fd);
	ft_putnbr_fd(img->width, img->output_fd);
	ft_putstr_fd(" ", img->output_fd);
	ft_putnbr_fd(img->height, img->output_fd);
	ft_putstr_fd("\n", img->output_fd);
	return (EXIT_SUCCESS);
}
