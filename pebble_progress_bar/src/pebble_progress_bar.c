#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "pebble_progress_bar.h"



/*** Setup *******************************************************************/

#define MY_UUID { 0x7B, 0x81, 0x70, 0x7F, 0xF7, 0xFB, 0x41, 0x35, 0xA5, 0x81, 0xD0, 0x36, 0xA9, 0x39, 0xEB, 0x17 }
PBL_APP_INFO(MY_UUID,
             "Progress Bar", "Villainous Industries",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
AppContextRef myContext;
Layer tickmarks_layer;
Layer bars_layer;



/*** Layer update callbacks **************************************************/

void tickmarks_layer_update(Layer *me, GContext *ctx) {
  // Draw hour ticks
  graphics_context_set_compositing_mode(ctx, GCompOpAssign);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  for(unsigned short h = 0; h <= 12; ++h) {
    unsigned short x = HOURS_MIN_WIDTH + h * (HOURS_WIDTH / 12);
    graphics_draw_line(ctx, (GPoint){.x = x, .y = 0}, (GPoint){.x = x, .y = 71});
  }
  // Draw minute ticks
  for(unsigned short m = 0; m <= 60; ++m) {
    unsigned short x = MINUTES_MIN_WIDTH + m * (MINUTES_WIDTH / 60);
    graphics_draw_line(ctx, (GPoint){.x = x, .y = 0}, (GPoint){.x = x, .y = 71});
  }
}

void bars_layer_update() {
}



/*** Handlers ****************************************************************/

void handle_init(AppContextRef ctx) {
  (void)ctx;

  // Some useful globals
  myContext = ctx;

  window_init(&window, "Progress Bar");
  window_stack_push(&window, true /* Animated */);

  layer_init(&tickmarks_layer, window.layer.frame);
  tickmarks_layer.update_proc = &tickmarks_layer_update;
  layer_add_child(&window.layer, &tickmarks_layer);

  layer_init(&bars_layer, window.layer.frame);
  bars_layer.update_proc = &bars_layer_update;
  layer_add_child(&window.layer, &bars_layer);

  layer_mark_dirty(&tickmarks_layer);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *event) {
  (void)ctx;
  (void)event;

  layer_mark_dirty(&bars_layer);
}



/*** The main method *********************************************************/

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
