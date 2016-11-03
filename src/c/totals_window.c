#include <pebble.h>
#include "totals_window.h"
#include "pebble-effect-layer/effect_layer.h"

static EffectLayer s_effect_layer;
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static BitmapLayer *s_bitmaplayer_background;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_kd;
static TextLayer *SRWN;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  // s_bitmaplayer_background
  s_bitmaplayer_background = bitmap_layer_create(GRect(81, 21, 64, 128));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_background);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(-1, -1, 146, 25));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_kd
  s_textlayer_kd = text_layer_create(GRect(10, 152, 120, 14));
  text_layer_set_background_color(s_textlayer_kd, GColorClear);
  text_layer_set_text_color(s_textlayer_kd, GColorWhite);
  text_layer_set_text(s_textlayer_kd, "...");
  text_layer_set_text_alignment(s_textlayer_kd, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_kd);
  
  // SRWN
  SRWN = text_layer_create(GRect(4, 5, 134, 37));
  text_layer_set_text(SRWN, "SRWN");
  text_layer_set_text_alignment(SRWN, GTextAlignmentCenter);
  text_layer_set_font(SRWN, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)SRWN);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_background);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_kd);
  text_layer_destroy(SRWN);
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
  //bitmap_layer_set_compositing_mode(s_bitmaplayer_background, GCompOpClear);
  bitmap_layer_set_bitmap(s_bitmaplayer_background, bitmap);
  
  
}

void totals_window_set_kills(char* kills) {
  
}
void totals_window_set_deaths(char* deaths) {
  
}
void totals_window_set_ratio(char* ratio) {
  text_layer_set_text(s_textlayer_kd, ratio);
}
