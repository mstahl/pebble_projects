#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "bar_graph.h"


#define MY_UUID { 0x96, 0x07, 0xA2, 0x80, 0xF2, 0xC3, 0x48, 0x7C, 0xBF, 0x7A, 0x86, 0x42, 0x54, 0xD7, 0x4E, 0xB2 }
PBL_APP_INFO(MY_UUID,
             "Bar Graph", "Villainous Industries",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
Layer bar_graph_layer;
PblTm current_time;



////// Layer update procs -----------------------------------------------------

void draw_bar_graph(Layer *me, GContext *ctx) {
  // Clear bar graph layer
  graphics_context_set_fill_color(ctx, GColorClear);
  graphics_fill_rect(ctx, me->frame, 0, 0);

  graphics_context_set_fill_color(ctx, GColorBlack);
  get_time(&current_time);

  // Draw hour bargraphs
  int hour_width, display_hour;

  if(clock_is_24h_style()) {
    hour_width = HOURS_TOTAL_WIDTH / (24 / HOURS_PER_COLUMN);
    display_hour = current_time.tm_hour;
  }
  else {
    hour_width = HOURS_TOTAL_WIDTH / (12 / HOURS_PER_COLUMN);
    display_hour = current_time.tm_hour % 12;
  }
  for(int h = 0; h < display_hour; ++h) {
    int x = hour_width * (h / HOURS_PER_COLUMN);
    int y = (SCREEN_HEIGHT / HOURS_PER_COLUMN) * (h % HOURS_PER_COLUMN);

    graphics_fill_rect(ctx, (GRect){
      .origin = {
        .x = x,
        .y = y
      },
      .size = {
        .w = hour_width - 1,
        .h = SCREEN_HEIGHT / HOURS_PER_COLUMN - 1
      }
    }, 0, 0);
  }

  // Draw minute bargraphs
  int minute_bar_height = SCREEN_HEIGHT * current_time.tm_min / 60;
  graphics_fill_rect(ctx, (GRect){
    .origin = {
      .x = HOURS_TOTAL_WIDTH + 1,
      .y = SCREEN_HEIGHT - minute_bar_height
    },
    .size = {
      .w = MINUTES_TOTAL_WIDTH - 1,
      .h = minute_bar_height
    }
  }, 0, 0);

  // Draw minute tickmarks (every 10 minutes)
  graphics_context_set_stroke_color(ctx, GColorWhite);
  int minute_tick_height = 10 * SCREEN_HEIGHT / 60;
  for(int y = SCREEN_HEIGHT; y >= 0; y -= minute_tick_height) {
    graphics_draw_line(ctx, (GPoint){
      .x = HOURS_TOTAL_WIDTH + 1,
      .y = y
    }, (GPoint){
      .x = SCREEN_WIDTH,
      .y = y
    });
  }
}



////// Handlers ---------------------------------------------------------------

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  layer_init(&bar_graph_layer, window.layer.frame);
  layer_set_update_proc(&bar_graph_layer, &draw_bar_graph);
  layer_add_child(&window.layer, &bar_graph_layer);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *event) {
  (void)ctx;
  (void)event;

  layer_mark_dirty(&bar_graph_layer);
}

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
