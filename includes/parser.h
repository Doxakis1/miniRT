/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:26 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/26 09:54:43 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include "../libft/includes/get_next_line.h"
# define INVALID_INPUT 4
# define OPEN_FAIL 1
# define INVALID_OBJECTS 2
# define MISSING_KEY_ELEMENTS 3
# define INVALID_INPUT 4
# define MALLOC_FAILED 5
# define EXCESS_ELEMENTS 6
# define INSIDE_OBJECT 7
# define ERROR_BIG_FILE_NAME 8
# define LIGHT_SOURCE 0
# define AMBIENT_LIGHT 1
# define CAMERA 2
# define VALID_OBJECT 3
# define OBJECT_SPHERE 4
# define OBJECT_PLANE 5
# define OBJECT_CYLINDER 6

typedef unsigned int	t_color;
typedef short			t_degrees;
typedef short			t_object_type;

typedef struct s_check_once
{
	int				light_source;
	int				camera;
	int				ambient_light;
}	t_check_once;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}	t_vec3;

typedef struct s_vec4
{
	float			alpha;
	float			r;
	float			g;
	float			b;
}	t_vec4;

typedef struct s_object
{
	int				id;
	void			*data;
	struct s_object	*next;
	t_object_type	type;
}	t_object;

typedef struct s_cyl_hit
{
	t_vec3		pos;
	t_vec3		my_normal;
}	t_cyl_hit;

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		axis_vector;
	float		diameter;
	float		height;
	t_color		color;
	t_cyl_hit	my_hit;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal_vector;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_vec3		pos;
	float		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_light_source
{
	t_vec3			pos;
	float			ratio;
	t_color			color;
}	t_light_source;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		forward_dir;
	t_vec3		up_dir;
	t_vec3		right_dir;
	t_vec3		norm_vector;
	t_vec3		not_normalized_norm_vector;
	t_degrees	fov;
}	t_camera;

typedef struct s_ambient_light
{
	float			ratio;
	t_color			color;
}	t_ambient_light;

typedef struct s_hit
{
	int		hit;
	t_vec3	pos;
}	t_hit;

typedef struct s_float_vec3
{
	float	dist;
	t_vec3	light;
}	t_float_vec3;

typedef struct s_hit_data
{
	int		closest_id;
	int		is_in_shadow;
	float	distance;
	float	brightness;
	float	specular;
	t_vec3	normal;
	t_vec4	color;
}	t_hit_data;

typedef struct s_scene
{
	char			file_name[64];
	int				output_fd;
	int				width;
	int				height;
	t_light_source	light_sources;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_object		*objects;
	t_hit_data		hit_data;
	t_check_once	check_once;
	short			error_catcher;
}	t_scene;

//parser.c
int			skip_chars(const char *skippable, int index, const char *str);
t_scene		scene_constractor(const char *file);

//ft_print_error.c
int			ft_print_error(const char *str);
int			return_parser_error(short error);

//get_object_identifier.c
short		get_object_identifier(const char *str);
int			check_valid_object(const char *str);

//ft_atoX.c
float		ft_atof(const char *str, int *index);
int			is_digit_mod(int a, short allow_neg, short allow_plus);
uint8_t		ft_atouint8(const char *str, int *index);
int			ft_atoi_mod(const char *str, int *index);

//parser_utils.c
int			get_float(float *dst, const char *str, int *index);
int			get_vec3(t_vec3 *coordinate,
				const char *str, int *index);
int			get_color(t_color *color, const char *str, int *index);
int			get_degrees(t_degrees *dst, const char *str, int *index);
int			get_3d_normal_vector(t_vec3 *coordinate, const char *str, \
				int *index);
int			check_index_error(const char *str, int *index);

//get_light_source.c
short		get_light_source(t_scene *scene, const char *str);

//get_ambient_light.c
short		get_ambient_light(t_scene *scene, const char *str);

//get_camera.c
short		get_camera(t_scene *scene, const char *str);

//get_new_object.c
short		get_new_object(t_object *scene_object, const char *str);
void		free_all_objects(t_object *head, int instruction);

#endif
