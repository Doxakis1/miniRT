/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:29:32 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/26 10:20:06 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

int	validate_filename(char *filename)
{
	size_t	len;
	char	*temp;
	int		f_len;

	len = ft_strlen(filename);
	f_len = (len - 3);
	temp = ft_substr(filename, f_len, 3);
	if (ft_strcmp(temp, ".rt") != 0)
	{
		free (temp);
		return (0);
	}
	free (temp);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc == 2)
	{
		if (validate_filename(argv[1]))
		{
			scene = scene_constractor(argv[1]);
			if (scene.error_catcher || check_camera(&scene))
				return_parser_error(scene.error_catcher);
			else
				raytrace(&scene);
		}
		else
			return (ft_print_error("Error\nWrong filename\n"));
	}
	else
		return (ft_print_error("Error\nOne map.rt expected as argument\n"));
	if (scene.objects != NULL)
		free_all_objects(scene.objects, 0);
	close(scene.output_fd);
	return (0);
}
