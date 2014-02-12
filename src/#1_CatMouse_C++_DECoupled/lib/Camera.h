/*
* Generated by SGWrapperGen - DO NOT EDIT!
*
* SwinGame wrapper for C - Camera
*
* Wrapping sgCamera.pas
*/

#ifndef sgCamera
#define sgCamera

#include <stdint.h>

#ifndef __cplusplus
  #include <stdbool.h>
#endif

#include "Types.h"

point2d camera_pos();
rectangle camera_screen_rect();
float camera_x();
float camera_y();
void center_camera_on_character(character c, const vector *offset);
void center_camera_on_character_byval(character c, const vector offset);
void center_camera_on(sprite s, const vector *offset);
void center_camera_on_byval(sprite s, const vector offset);
void center_camera_on_with_xyoffset(sprite s, int32_t offsetX, int32_t offsetY);
void move_camera_by(const vector *offset);
void move_camera_by_byval(const vector offset);
void move_camera_by_xy(float dx, float dy);
void move_camera_to(const point2d *pt);
void move_camera_to_byval(const point2d pt);
void move_camera_to_xy(float x, float y);
bool point_on_screen(const point2d *pt);
bool point_on_screen_byval(const point2d pt);
bool rect_on_screen(const rectangle *rect);
bool rect_on_screen_byval(const rectangle rect);
void set_camera_pos(const point2d *pt);
void set_camera_pos_byval(const point2d pt);
void set_camera_x(float x);
void set_camera_y(float y);
point2d to_screen(const point2d *worldPoint);
point2d to_screen_byval(const point2d worldPoint);
rectangle to_screen_rect(const rectangle *rect);
rectangle to_screen_rect_byval(const rectangle rect);
int32_t to_screen_x(float worldX);
int32_t to_screen_y(float worldY);
point2d to_world(const point2d *screenPoint);
point2d to_world_byval(const point2d screenPoint);
float to_world_x(int32_t screenX);
float to_world_y(int32_t screenY);

#ifdef __cplusplus
// C++ overloaded functions
void center_camera_on(character c, const vector &offset);
void center_camera_on(sprite s, const vector &offset);
void center_camera_on(sprite s, int32_t offsetX, int32_t offsetY);
void move_camera_by(const vector &offset);
void move_camera_by(float dx, float dy);
void move_camera_to(const point2d &pt);
void move_camera_to(float x, float y);
bool point_on_screen(const point2d &pt);
bool rect_on_screen(const rectangle &rect);
void set_camera_pos(const point2d &pt);
point2d to_screen(const point2d &worldPoint);
rectangle to_screen(const rectangle &rect);
point2d to_world(const point2d &screenPoint);

#endif

#endif

