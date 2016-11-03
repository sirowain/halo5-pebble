#include <pebble.h>
#include "totals_window.h"
#include "effect_layer/effect_layer.h"

static EffectLayer *s_effect_layer;
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_condensed_21;
static GFont s_res_gothic_14;
static GFont s_res_gothic_18;
static BitmapLayer *s_bitmaplayer_background;
static TextLayer *s_textlayer_kd;
static TextLayer *s_textlayer_kills_l;
static TextLayer *s_textlayer_deaths_l;
static TextLayer *s_textlayer_kd_l;
static TextLayer *s_textlayer_deaths;
static TextLayer *s_textlayer_kills;
static TextLayer *SRWN;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // s_bitmaplayer_background
  s_bitmaplayer_background = bitmap_layer_create(GRect(81, 38, 64, 128));
  bitmap_layer_set_background_color(s_bitmaplayer_background, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_background);
  
  // s_textlayer_kd
  s_textlayer_kd = text_layer_create(GRect(5, 135, 70, 23));
  text_layer_set_background_color(s_textlayer_kd, GColorClear);
  text_layer_set_text_color(s_textlayer_kd, GColorWhite);
  text_layer_set_text(s_textlayer_kd, "-");
  text_layer_set_text_alignment(s_textlayer_kd, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_kd, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_kd);
  
  // s_textlayer_kills_l
  s_textlayer_kills_l = text_layer_create(GRect(5, 46, 72, 14));
  text_layer_set_background_color(s_textlayer_kills_l, GColorClear);
  text_layer_set_text_color(s_textlayer_kills_l, GColorWhite);
  text_layer_set_text(s_textlayer_kills_l, "kills");
  text_layer_set_font(s_textlayer_kills_l, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_kills_l);
  
  // s_textlayer_deaths_l
  s_textlayer_deaths_l = text_layer_create(GRect(5, 84, 72, 14));
  text_layer_set_background_color(s_textlayer_deaths_l, GColorClear);
  text_layer_set_text_color(s_textlayer_deaths_l, GColorWhite);
  text_layer_set_text(s_textlayer_deaths_l, "deaths");
  text_layer_set_font(s_textlayer_deaths_l, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_deaths_l);
  
  // s_textlayer_kd_l
  s_textlayer_kd_l = text_layer_create(GRect(5, 122, 72, 14));
  text_layer_set_background_color(s_textlayer_kd_l, GColorClear);
  text_layer_set_text_color(s_textlayer_kd_l, GColorWhite);
  text_layer_set_text(s_textlayer_kd_l, "k/d");
  text_layer_set_font(s_textlayer_kd_l, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_kd_l);
  
  // s_textlayer_deaths
  s_textlayer_deaths = text_layer_create(GRect(5, 97, 70, 23));
  text_layer_set_background_color(s_textlayer_deaths, GColorClear);
  text_layer_set_text_color(s_textlayer_deaths, GColorWhite);
  text_layer_set_text(s_textlayer_deaths, "-");
  text_layer_set_text_alignment(s_textlayer_deaths, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_deaths, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_deaths);
  
  // s_textlayer_kills
  s_textlayer_kills = text_layer_create(GRect(5, 58, 70, 23));
  text_layer_set_background_color(s_textlayer_kills, GColorClear);
  text_layer_set_text_color(s_textlayer_kills, GColorWhite);
  text_layer_set_text(s_textlayer_kills, "-");
  text_layer_set_text_alignment(s_textlayer_kills, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_kills, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_kills);
  
  // SRWN
  SRWN = text_layer_create(GRect(5, 5, 135, 19));
  text_layer_set_text(SRWN, "s1r0w41n");
  text_layer_set_text_alignment(SRWN, GTextAlignmentCenter);
  text_layer_set_font(SRWN, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)SRWN);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(5, 24, 135, 14));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "Totals");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_background);
  text_layer_destroy(s_textlayer_kd);
  text_layer_destroy(s_textlayer_kills_l);
  text_layer_destroy(s_textlayer_deaths_l);
  text_layer_destroy(s_textlayer_kd_l);
  text_layer_destroy(s_textlayer_deaths);
  text_layer_destroy(s_textlayer_kills);
  text_layer_destroy(SRWN);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_totals_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_totals_window(void) {
  window_stack_remove(s_window, true);
}

void totals_window_set_background(GBitmap *bitmap) {
  bitmap_layer_set_bitmap(s_bitmaplayer_background, bitmap);
  
  if (s_effect_layer) {
    effect_layer_destroy(s_effect_layer);
  }
  
  if (SRWN) {
    layer_remove_from_parent((Layer*)SRWN);
  }
  Layer *bitmap_l = bitmap_layer_get_layer(s_bitmaplayer_background);
  GRect bitmap_r = layer_get_frame(bitmap_l);
  s_effect_layer = effect_layer_create(bitmap_r);
  effect_layer_add_effect(s_effect_layer, effect_invert, NULL);
  layer_add_child(window_get_root_layer(s_window), effect_layer_get_layer(s_effect_layer));
  layer_add_child(window_get_root_layer(s_window), (Layer *)SRWN);
  text_layer_set_text(s_textlayer_kd, "ratio");
}

void totals_window_set_kills(char* kills) {
  text_layer_set_text(s_textlayer_kills, kills);
}
void totals_window_set_deaths(char* deaths) {
  text_layer_set_text(s_textlayer_deaths, deaths);
}
void totals_window_set_ratio(char* ratio) {
  text_layer_set_text(s_textlayer_kd, ratio);
}
