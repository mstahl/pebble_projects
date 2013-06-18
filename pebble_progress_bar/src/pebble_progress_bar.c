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
InverterLayer tickmarks_layer;
Layer bars_layer;
PblTm current_time;

/*** Layer update callbacks **************************************************/

void tickmarks_layer_update(Layer *me, GContext *ctx) {
  // TODO: Decide if this should stick around in this version.
}

void bars_layer_update(Layer *me, GContext *ctx) {
  get_time(&current_time);

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, (GRect){
    .origin = {
      .x = 0,
      .y = 0
    },
    .size = {
      .w = SCREEN_WIDTH,
      .h = SCREEN_HEIGHT
    }
  }, 0, 0);

  graphics_context_set_fill_color(ctx, GColorBlack);

  int row;
  int col;
  int x;
  int y;

  for(int h = 0; h < current_time.tm_hour % HOUR_MODULUS; h += HOURS_PER_TICKMARK) {
    row = h / (HOURS_PER_TICKMARK * HOUR_TICKS_PER_ROW);
    col = h % HOUR_TICKS_PER_ROW;
    x   = col * PIXELS_PER_HOUR;
    y   = row * PIXELS_PER_ROW;

    graphics_fill_rect(ctx, (GRect){
      .origin = {
        .x = x,
        .y = y
      },
      .size = {
        .w = PIXELS_PER_HOUR - HOUR_BORDER_WIDTH,
        .h = PIXELS_PER_ROW - HOUR_BORDER_WIDTH
      }
    }, 0, 0);
  }

  for(int m = 0; m < current_time.tm_min; m += MINUTES_PER_TICKMARK) {
    row = m / (MINUTES_PER_TICKMARK * MINUTE_TICKS_PER_ROW);
    col = m % MINUTE_TICKS_PER_ROW;
    x   = col * PIXELS_PER_MINUTE;
    y   = (HOUR_MODULUS / HOUR_TICKS_PER_ROW + row) * PIXELS_PER_ROW;

    graphics_fill_rect(ctx, (GRect){
      .origin = {
        .x = x,
        .y = y
      },
      .size = {
        .w = PIXELS_PER_MINUTE - MINUTE_BORDER_WIDTH,
        .h = PIXELS_PER_ROW - MINUTE_BORDER_WIDTH
      }
    }, 0, 0);
  }
}



/*** Handlers ****************************************************************/

void handle_init(AppContextRef ctx) {
  (void)ctx;

  // Some useful globals
  myContext = ctx;

  window_init(&window, "Progress Bar");
  window_stack_push(&window, true /* Animated */);

  inverter_layer_init(&tickmarks_layer, window.layer.frame);
  layer_set_update_proc((Layer*)&tickmarks_layer, &tickmarks_layer_update);
  layer_add_child(&window.layer, (Layer*)&tickmarks_layer);

  layer_init(&bars_layer, window.layer.frame);
  bars_layer.update_proc = &bars_layer_update;
  layer_insert_below_sibling(&bars_layer, (Layer*)&tickmarks_layer);

  layer_mark_dirty((Layer*)&tickmarks_layer);
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
