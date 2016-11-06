#include <pebble.h>
#include "graph_window.h"

#define DELTA 1
#define TARGET 230
static int s_index = 0;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_condensed_21;
static GFont s_res_gothic_14;
static GFont s_res_gothic_18;
static GFont s_res_gothic_24;

static Layer *s_canvas_layer;
static GDrawCommandSequence *s_command_seq;

static TextLayer *s_ratio_layer_lbl;
static TextLayer *s_ratio_layer;

static GPath *s_my_path_ptr = NULL;

//GRAPH
static void next_frame_handler(void *context) {
  // Draw the next frame
  layer_mark_dirty(s_canvas_layer);

  // Continue the sequence
  if (s_index < (TARGET - 20)) {
	  app_timer_register(DELTA, next_frame_handler, NULL);

  } else if (s_index < TARGET) {
	  app_timer_register(DELTA + 5, next_frame_handler, NULL);
  }
}

static void update_proc(Layer *layer, GContext *ctx) {
//  // Get the next frame
//  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(s_command_seq, s_index);
//
//  // If another frame was found, draw it
//  if (frame) {
//    gdraw_command_frame_draw(ctx, s_command_seq, frame, GPoint(0, 30));
//  }
//
//  // Advance to the next frame, wrapping if neccessary
//  int num_frames = gdraw_command_sequence_get_num_frames(s_command_seq);
//  s_index++;
//  if (s_index == num_frames) {
//    s_index = 0;
//  }

	int32_t angle_start = DEG_TO_TRIGANGLE(0);
	int32_t angle_end = DEG_TO_TRIGANGLE(s_index);

	Layer *window_layer = window_get_root_layer(s_window);
	GRect window_bounds = layer_get_bounds(window_layer);
		GRect rect_bounds = GRect(30, 20, 80, 80);

	// Draw an arc
//	graphics_draw_arc(ctx, rect_bounds, GOvalScaleModeFitCircle, angle_start,
//	                                                                    angle_end);
		uint16_t inset_thickness = 200; //rect_bounds.size.w / 2;

		graphics_context_set_fill_color(ctx, GColorLightGray);
		graphics_context_set_stroke_width(ctx, 0);
		// Fill a radial section of a circle
		graphics_fill_radial(ctx, rect_bounds, GOvalScaleModeFitCircle, inset_thickness,  angle_start, angle_end);

		graphics_context_set_fill_color(ctx, GColorWhite);
		graphics_context_set_stroke_color(ctx, GColorDarkGray);
		graphics_context_set_stroke_width(ctx, 1);

		uint16_t x = rect_bounds.origin.x + (rect_bounds.size.w / 2);
		uint16_t y = rect_bounds.origin.y + (rect_bounds.size.h / 2);
		graphics_draw_circle(ctx, GPoint(x, y), rect_bounds.size.w/2);

		graphics_fill_circle(ctx, GPoint(x, y), rect_bounds.size.w/3);

		graphics_context_set_fill_color(ctx, GColorWhite);
		graphics_context_set_stroke_color(ctx, GColorBlack);
		graphics_context_set_stroke_width(ctx, 1);

		uint16_t padding = 20;
		uint16_t w = window_bounds.size.w - (padding * 2);
		uint16_t h = 30;
		x = padding;
		y = window_bounds.size.h - padding - h;
		graphics_draw_round_rect(ctx, GRect(x, y, w, h), 10);

		const GPathInfo separator_path_info = {
		  .num_points = 2,
		  .points = (GPoint []) {{x + 5, y + (h/2)}, {x+w -5, y + (h/2)}}
		};
		s_my_path_ptr = gpath_create(&separator_path_info);
		gpath_draw_outline_open(ctx, s_my_path_ptr);

		if (s_index < (TARGET - 20)) {
			s_index+=4;
		} else if (s_index < TARGET) {
			s_index+=2;
		}
}

static void initialise_ui(void) {
	s_window = window_create();
	window_set_background_color(s_window, GColorBlack);
	#ifndef PBL_SDK_3
	window_set_fullscreen(s_window, true);
	#endif

	s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
	s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
	s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
	s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);

	window_set_background_color(s_window, GColorWhite);

	// graph
	s_command_seq = gdraw_command_sequence_create_with_resource(RESOURCE_ID_GRAPH_SEQUENCE);

	// Get Window information
	Layer *window_layer = window_get_root_layer(s_window);
	GRect bounds = layer_get_bounds(window_layer);

	// Create the canvas Layer
	s_canvas_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));

	// Set the LayerUpdateProc
	layer_set_update_proc(s_canvas_layer, update_proc);

	// Add to parent Window
	layer_add_child(window_layer, s_canvas_layer);

	app_timer_register(DELTA, next_frame_handler, NULL);

	// text k/d
	s_ratio_layer_lbl = text_layer_create(GRect(30, 40, 80, 18));
	text_layer_set_text_color(s_ratio_layer_lbl, GColorBlack);
	text_layer_set_background_color(s_ratio_layer_lbl, GColorClear);
	text_layer_set_text_alignment(s_ratio_layer_lbl, GTextAlignmentCenter);
	text_layer_set_font(s_ratio_layer_lbl, s_res_gothic_18);
	text_layer_set_text(s_ratio_layer_lbl, "K/D");
	layer_add_child(window_layer, (Layer*)s_ratio_layer_lbl);

	// text k/d
	s_ratio_layer = text_layer_create(GRect(30, 54, 80, 24));
	text_layer_set_text_color(s_ratio_layer, GColorBlack);
	text_layer_set_background_color(s_ratio_layer, GColorClear);
	text_layer_set_text_alignment(s_ratio_layer, GTextAlignmentCenter);
	text_layer_set_font(s_ratio_layer, s_res_gothic_18);
	text_layer_set_text(s_ratio_layer, "0.5231");
	layer_add_child(window_layer, (Layer*)s_ratio_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  layer_destroy(s_canvas_layer);
  gdraw_command_sequence_destroy(s_command_seq);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_graph_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_graph_window(void) {
  window_stack_remove(s_window, true);
}


