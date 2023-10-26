/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/26 10:07:45 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "parser.h"
# include "vectors.h"
# include "../libft/includes/libft.h"

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 680
# define TINY_VALUE 0.00001
# define FLT_MAX 3.402823466e+38F

#ifndef SPECULAR
# define SPECULAR 0
#endif

typedef struct s_vec3		t_vec3;
typedef struct s_vec4		t_vec4;
typedef struct s_scene		t_scene;
typedef struct s_camera		t_camera;
typedef struct s_hit		t_hit;
typedef struct s_float_vec3	t_float_vec3;
typedef struct s_object		t_object;
typedef struct s_cylinder	t_cylinder;
typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;

int			check_camera(t_scene *scene);

//window
int			create_output_file(t_scene *img);
int			exit_button(t_scene *img);

//scene.c
int			raytrace(t_scene *img);
int			get_closest_hit(t_camera *cam, t_scene *img, \
				t_hit *hit, int *coords);
void		get_distance(t_scene *img, \
				t_hit *hit, t_hit new, int id);
void		set_id(t_scene *img);

//ray_hit.c
t_hit		get_hit(t_camera *cam, t_object *objects, float x, float y);
int			plane_hit(t_vec3 origin, t_vec3 direction, \
				t_plane plane, t_vec3 *point);
int			sphere_hit(const t_sphere *sphere, const t_vec3 ray_start, \
				const t_vec3 direction, t_vec3 *intersection1);
int			sanity_check(t_vec3 origin, t_vec3 direction, t_vec3 hit);

//normals.c
void		get_normal(t_scene *img, t_hit *hit);
void		get_plane_normal(t_object *data, t_scene *img, t_hit hit);
void		get_sphere_normal(t_object *data, t_scene *img, t_hit *hit);

//light.c
t_vec4		add_ambient_value(t_scene *img);
float		get_specular(t_scene *img, t_hit *hit);
float		get_brightness(t_scene *img, t_hit *hit);

//shadows.c
void		get_shadow(t_scene *img, t_hit *hit);
int			check_for_shadow(t_scene *img, t_hit *hit, t_object *object);
int			check_sphere_shadow(t_hit *hit, t_object *object, \
				t_vec3 shadow_direction, t_float_vec3 data);
int			check_plane_shadow(t_hit *hit, t_object *object, \
				t_vec3 shadow_direction, t_float_vec3 data);
int			check_cylinder_shadow(t_hit *hit, t_object *object, \
				t_vec3 shadow_direction, t_float_vec3 data);

//colors.c
t_vec4		get_pixel_color(t_scene *img, t_hit *hit);

//cylinder.c
t_vec3		cylinder_normal(t_vec3 center, t_vec3 hit_pos, float d, \
				t_cylinder *cylinder);
int			find_min(float *dists, int size);
void		cyl_cap_plane_initialize(t_plane *my_planes, t_cylinder *cylinder, \
				int dir);
int			infinite_cylinder_hit(t_vec3 start, t_vec3 ray_direction, \
				t_cylinder *cylinder, t_vec3 *intersection1);
int			find_best_hit(t_vec3 *intersection1, t_vec3 *intersection2, \
				t_vec3 start, t_cylinder *cylinder);
t_vec3		dist_compare(t_vec3 start, t_vec3 one, t_vec3 two);
int			check_hit(t_cylinder *cylinder, t_vec3 hitpoint);
t_vec3		closest_point_to_line(t_vec3 start, t_vec3 end, t_vec3 point, \
				t_cylinder *cylinder);
float		validate_cap_hit(t_plane cap, t_vec3 start_pos, t_vec3 hit_pos, \
				float radius);
t_plane		find_cap_hit(t_cylinder *cylinder, t_vec3 ray_direction, \
				t_vec3 start_pos, float *distance);
void		translate_t_vec3s(float *x, float *y, float aspect_ratio, \
				float fov);
t_hit		find_cylinder_hit(t_cylinder *cylinder, t_vec3 ray_direction, \
				t_vec3 start_pos);

//object_color.c
void		get_object_basecolor(t_scene *img);
void		get_sphere_color(t_object *data, t_scene *img);
void		get_cylinder_color(t_object *data, t_scene *img);
void		get_plane_color(t_object *data, t_scene *img);

#endif
