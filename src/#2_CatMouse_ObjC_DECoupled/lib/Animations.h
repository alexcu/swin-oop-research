/*
* Generated by SGWrapperGen - DO NOT EDIT!
*
* SwinGame wrapper for C - Animations
*
* Wrapping sgAnimations.pas
*/

#ifndef sgAnimations
#define sgAnimations

#include <stdint.h>

#ifndef __cplusplus
  #include <stdbool.h>
#endif

#include "Types.h"

int32_t animation_current_cell(animation anim);
vector animation_current_vector(animation anim);
bool animation_ended(animation anim);
bool animation_entered_frame(animation anim);
float animation_frame_time(animation anim);
int32_t animation_index(animation_script temp, const char *name);
void animation_name(animation_script temp, int32_t idx, char *result);
void animation_script_name(animation_script script, char *result);
animation_script animation_script_named(const char *name);
void assign_animation_named(animation anim, const char *name, animation_script script);
void assign_animation(animation anim, int32_t idx, animation_script script);
void assign_animation_named_with_sound(animation anim, const char *name, animation_script script, bool withSound);
void assign_animation_with_sound(animation anim, int32_t idx, animation_script script, bool withSound);
animation create_animation_with_sound(int32_t identifier, animation_script script);
animation create_animation_named(const char *identifier, animation_script script);
animation create_animation(int32_t identifier, animation_script script, bool withSound);
animation create_animation_named_with_sound(const char *identifier, animation_script script, bool withSound);
void draw_animation_at_point(animation ani, bitmap bmp, const point2d *pt);
void draw_animation_at_point_byval(animation ani, bitmap bmp, const point2d pt);
void draw_animation(animation ani, bitmap bmp, int32_t x, int32_t y);
void draw_animation_onto_dest_at_pt(bitmap dest, animation ani, bitmap bmp, const point2d *pt);
void draw_animation_onto_dest_at_pt_byval(bitmap dest, animation ani, bitmap bmp, const point2d pt);
void draw_animation_onto_dest(bitmap dest, animation ani, bitmap bmp, int32_t x, int32_t y);
void draw_animation_on_screen_at_pt(animation ani, bitmap bmp, const point2d *pt);
void draw_animation_on_screen_at_pt_byval(animation ani, bitmap bmp, const point2d pt);
void draw_animation_on_screen(animation ani, bitmap bmp, int32_t x, int32_t y);
void free_animation(animation *ani);
void free_animation_script(animation_script *scriptToFree);
bool has_animation_script(const char *name);
animation_script load_animation_script(const char *filename);
animation_script load_animation_script_named(const char *name, const char *filename);
void release_all_animation_scripts();
void release_animation_script(const char *name);
void restart_animation(animation anim);
void reset_animation_with_sound(animation anim, bool withSound);
void update_animation(animation anim);
void update_animation_pct(animation anim, float pct);
void update_animation_pct_and_sound(animation anim, float pct, bool withSound);

#ifdef __cplusplus
// C++ overloaded functions
void assign_animation(animation anim, const char *name, animation_script script);
void assign_animation(animation anim, const char *name, animation_script script, bool withSound);
void assign_animation(animation anim, int32_t idx, animation_script script, bool withSound);
animation create_animation(int32_t identifier, animation_script script);
animation create_animation(const char *identifier, animation_script script);
animation create_animation(const char *identifier, animation_script script, bool withSound);
void draw_animation(animation ani, bitmap bmp, const point2d &pt);
void draw_animation(bitmap dest, animation ani, bitmap bmp, const point2d &pt);
void draw_animation(bitmap dest, animation ani, bitmap bmp, int32_t x, int32_t y);
void draw_animation_on_screen(animation ani, bitmap bmp, const point2d &pt);
void free_animation(animation &ani);
void free_animation_script(animation_script &scriptToFree);
void restart_animation(animation anim, bool withSound);
void update_animation(animation anim, float pct);
void update_animation(animation anim, float pct, bool withSound);

#endif

#endif

