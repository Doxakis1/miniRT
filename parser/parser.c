/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:21 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/26 10:16:49 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	skip_chars(const char *skippable, int index, const char *str)
{
	int	i;
	int	j;
	int	found;
	int	comma_found;

	i = index - 1;
	comma_found = 0;
	while (str[++i])
	{
		j = 0;
		found = 0;
		if (str[i] == ',')
			comma_found++;
		while (skippable[j])
		{
			if (str[i] == skippable[j])
				found = 1;
			j++;
		}
		if (!found || comma_found > 1)
			break ;
	}
	if (comma_found > 1 || (!comma_found && skippable[1] == ','))
		i = ft_strlen(str);
	return (i);
}

static int	constractor_loop(t_scene *scene, char *str)
{
	int	catcher;

	catcher = 0;
	if (ft_strlen_int(str) == 1)
	{
		catcher = !(str[0] == '\n');
		free(str);
		return (catcher);
	}
	catcher = get_object_identifier(str);
	if (catcher == LIGHT_SOURCE)
		catcher = get_light_source(scene, str);
	else if (catcher == AMBIENT_LIGHT)
		catcher = get_ambient_light(scene, str);
	else if (catcher == CAMERA)
		catcher = get_camera(scene, str);
	else if (catcher == VALID_OBJECT)
		catcher = get_new_object(scene->objects, str);
	free(str);
	return (catcher);
}

static int	check_required(t_scene *scene)
{
	if (!scene->check_once.ambient_light || !scene->check_once.light_source
		|| !scene->check_once.camera)
	{
		scene->error_catcher = MISSING_KEY_ELEMENTS;
		return (MISSING_KEY_ELEMENTS);
	}
	return (EXIT_SUCCESS);
}

static int	get_output_name(const char *file, t_scene *main_scene)
{
	int	size;
	int	index;

	size  = ft_strlen(file);
	if (62 < size)
		return (ERROR_BIG_FILE_NAME);
	index = 0;
	while (index < size - 2)
	{
		main_scene->file_name[index] = file[index];
		index++;
	}
	main_scene->file_name[index++] = 'p';
	main_scene->file_name[index++] = 'p';
	main_scene->file_name[index++] = 'm';
	main_scene->file_name[index++] = '\0';
	return (EXIT_SUCCESS);
}

t_scene	scene_constractor(const char *file)
{
	static t_scene	main_scene;
	int				fd;
	static char		*new_line = NULL;

	ft_bzero(&main_scene, sizeof(t_scene));
	main_scene.error_catcher = get_output_name(file, &main_scene);
	if (main_scene.error_catcher)
		return (main_scene);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		main_scene.error_catcher = OPEN_FAIL;
	main_scene.objects = (t_object *)malloc(sizeof(t_object));
	ft_bzero(main_scene.objects, sizeof(t_object));
	if (!main_scene.objects)
		main_scene.error_catcher = MALLOC_FAILED;
	main_scene.objects->next = NULL;
	while (!main_scene.error_catcher)
	{
		new_line = get_next_line(fd);
		if (ft_strlen_int(new_line) <= 0 && !close(fd))
			break ;
		main_scene.error_catcher = constractor_loop(&main_scene, new_line);
	}
	if (main_scene.error_catcher || check_required(&main_scene))
	{
		free_all_objects(main_scene.objects, -1);
		main_scene.objects = NULL;
	}
	return (main_scene);
}
