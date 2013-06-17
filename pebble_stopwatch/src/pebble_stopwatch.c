#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x93, 0xEA, 0xF5, 0xD1, 0xC6, 0x2F, 0x4E, 0x56, 0x92, 0x37, 0x65, 0xBA, 0xEC, 0x6D, 0xF3, 0x5C }
PBL_APP_INFO(MY_UUID,
             "Stopwatch", "Villainous Industries",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer textLayer;
AppTimerHandle timerHandle;
ActionBarLayer action_layer;

// Modify these common button handlers

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  text_layer_set_text(&textLayer, "Up!");
}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  text_layer_set_text(&textLayer, "Down!");

}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  text_layer_set_text(&textLayer, "Select!");
  /*
   * if timerHandle == NULL {
   *   timerHandle = app_timer_send_event(appContext, 10, STOPWATCH_10MS_TIMER);
   * } else {
   *   app_timer_cancel_event(appContext, timerHandle);
   *   timerHandle = NULL;
   * }
   */
}


void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  text_layer_set_text(&textLayer, "Long select!");
}


// This usually won't need to be modified

void click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

  config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Stopwatch");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&textLayer, window.layer.frame);
  text_layer_set_text(&textLayer, "00:00.00");
  text_layer_set_font(&textLayer, fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));
  layer_add_child(&window.layer, &textLayer.layer);

  // Action layer stuff
  action_bar_layer_init(&action_layer);
  action_bar_layer_add_to_window(&action_layer, window);

  timerHandle = NULL;
  appContext = ctx;

  // Attach our desired button functionality
  action_bar_layer_set_click_config_provider(&action_layer, (ClickConfigProvider) click_config_provider);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
