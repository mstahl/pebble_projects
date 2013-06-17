#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "constants.h"

#define MY_UUID { 0x7B, 0x81, 0x70, 0x7F, 0xF7, 0xFB, 0x41, 0x35, 0xA5, 0x81, 0xD0, 0x36, 0xA9, 0x39, 0xEB, 0x17 }
PBL_APP_INFO(MY_UUID,
             "Progress Bar", "Villainous Industries",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
AppContextRef myContext;

void handle_init(AppContextRef ctx) {
  (void)ctx;

  // Some useful globals
  myContext = ctx;

  window_init(&window, "Progress Bar");
  window_stack_push(&window, true /* Animated */);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *event) {
  (void)ctx;
  (void)event;

  int hours = event.tm_hour;
  int minutes = event.tm_min;


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
