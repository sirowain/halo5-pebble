#include <pebble.h>
#include "graph_window.h"

#define DELTA 13
static int s_index = 0;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static Layer *s_canvas_layer;
static GDrawCommandSequence *s_command_seq;

//GRAPH
static void next_frame_handler(void *context) {
  // Draw the next frame
  layer_mark_dirty(s_canvas_layer);

  // Continue the sequence
  app_timer_register(DELTA, next_frame_handler, NULL);
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
	int32_t angle_end = DEG_TO_TRIGANGLE(45);

	Layer *window_layer = window_get_root_layer(s_window);
		GRect rect_bounds = GRect(30, 30, 80, 80);

	// Draw an arc
//	graphics_draw_arc(ctx, rect_bounds, GOvalScaleModeFitCircle, angle_start,
//	                                                                    angle_end);
		uint16_t inset_thickness = 200; //rect_bounds.size.w / 2;

		graphics_context_set_fill_color(ctx, GColorPastelYellowARGB8);
		graphics_context_set_stroke_width(ctx, 0);
		// Fill a radial section of a circle
		graphics_fill_radial(ctx, rect_bounds, GOvalScaleModeFitCircle, inset_thickness,  angle_start, angle_end);

		graphics_context_set_fill_color(ctx, GColorWhite);
		graphics_context_set_stroke_color(ctx, GColorBlack);
		graphics_context_set_stroke_width(ctx, 1);

		uint16_t x = rect_bounds.origin.x + (rect_bounds.size.w / 2);
		uint16_t y = rect_bounds.origin.y + (rect_bounds.size.h / 2);
		graphics_draw_circle(ctx, GPoint(x, y), rect_bounds.size.w/2);
//		graphics_fill_circle(ctx, GPoint(rect_bounds.size.w/2, rect_bounds.size.h/2), rect_bounds.size.w/2);
}

static void initialise_ui(void) {
	s_window = window_create();
	window_set_background_color(s_window, GColorBlack);
	#ifndef PBL_SDK_3
	window_set_fullscreen(s_window, true);
	#endif

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


