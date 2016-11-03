#include <pebble.h>

#include "src/c/totals_window.h"

static GBitmap *s_bitmap;

static uint8_t *s_img_data;
static int s_img_size;

static void inbox_dropped_callback(AppMessageResult result, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG , "Dropped: %d", result);
}

void set_image(uint8_t *data, int size) {
  if(s_bitmap) {
    gbitmap_destroy(s_bitmap);
  }

  // Create new GBitmap from downloaded PNG data
  s_bitmap = gbitmap_create_from_png_data(data, size);
  APP_LOG(APP_LOG_LEVEL_DEBUG , "createBitmap");

  if(s_bitmap) {
    totals_window_set_background(s_bitmap);
    APP_LOG(APP_LOG_LEVEL_DEBUG , "layerSetBitmap");
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Error creating GBitmap from PNG data!");
  }
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  // A new message has been successfully received
  Tuple *kd_tuple = dict_find(iter, MESSAGE_KEY_totals_ratio);
  if(kd_tuple) {
    char *kd_str = kd_tuple->value->cstring;
    totals_window_set_ratio(kd_str);
  }
  
  Tuple *kills_tuple = dict_find(iter, MESSAGE_KEY_totals_kills);
  if(kills_tuple) {
    int kills = kills_tuple->value->uint32;
    static char buf[] = "00000000000";
    snprintf(buf, sizeof(buf), "%d", kills);
    
    totals_window_set_kills(buf);
  }
  
  Tuple *deaths_tuple = dict_find(iter, MESSAGE_KEY_totals_deaths);
  if(deaths_tuple) {
    int deaths = deaths_tuple->value->uint32;
    static char buf[] = "00000000000";
    snprintf(buf, sizeof(buf), "%d", deaths);
    
    totals_window_set_deaths(buf);
  }
  
  Tuple *img_size_t = dict_find(iter, MESSAGE_KEY_DataLength);
  if(img_size_t) {
    s_img_size = img_size_t->value->int32;

    // Allocate buffer for image data
    s_img_data = (uint8_t*)malloc(s_img_size * sizeof(uint8_t));
  }

  // An image chunk
  Tuple *chunk_t = dict_find(iter, MESSAGE_KEY_DataChunk);
  if(chunk_t) {
    uint8_t *chunk_data = chunk_t->value->data;

    Tuple *chunk_size_t = dict_find(iter, MESSAGE_KEY_ChunkSize);
    int chunk_size = chunk_size_t->value->int32;

    Tuple *index_t = dict_find(iter, MESSAGE_KEY_Index);
    int index = index_t->value->int32;

    // Save the chunk
    memcpy(&s_img_data[index], chunk_data, chunk_size);
  }

  // Complete?
  Tuple *complete_t = dict_find(iter, MESSAGE_KEY_Complete);
  if(complete_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG , "COMPLETE!");
    // Show the image
    set_image(s_img_data, s_img_size);
  }
}

void handle_deinit(void) {
  gbitmap_destroy(s_bitmap);
}

int main(void) {
  
  // messages registration
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  const int inbox_size = 256;
  const int outbox_size = 256;
	app_message_open(inbox_size, outbox_size);
  
  show_totals_window();
  app_event_loop();
  handle_deinit();
}
