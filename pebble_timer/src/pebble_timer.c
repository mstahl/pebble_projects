/*
 * Pebble Timer
 *
 * (c) 2013 max thom stahl
 */

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

void enter_set_state();
void enter_run_state();
#define TIMER_1S_INTERVAL 0xBEEF

#define MY_UUID { 0xE5, 0x26, 0x66, 0xEE, 0xA2, 0x71, 0x4F, 0x35, 0x8D, 0x9F, 0x00, 0xFF, 0x7B, 0x24, 0xB0, 0x6B }
PBL_APP_INFO_SIMPLE(MY_UUID, "Timer", "Villainous Industries", 1 /* App version */);

// App stuff
AppTaskContextRef myContext;
#define SET_STATE      0xAA
#define RUN_STATE      0xBB
#define FINISHED_STATE 0xCC
int state;

// UI stuff
Window window;
TextLayer textLayer;

// Timer stuff
AppTimerHandle myTimer;
int timer_time;
char display_text_buffer[16];

/*** UI methods **************************************************************/

void displayTime() {
  int minutes = timer_time / 60;
  int seconds = timer_time % 60;

  PblTm tmptime = {
    .tm_min  = minutes,
    .tm_sec  = seconds
  };

  string_format_time(display_text_buffer, 16, "%M:%S", &tmptime);

  text_layer_set_text(&textLayer, display_text_buffer);
}

/*** RUN state ***************************************************************/

void run_state_timer_reset_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  enter_set_state(); // Reset
}

void run_state_click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_UP]->click.handler            = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_UP]->long_click.handler       = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler            = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_DOWN]->long_click.handler       = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_SELECT]->click.handler            = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_SELECT]->long_click.handler       = (ClickHandler) run_state_timer_reset_click_handler;
  config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 100;
}

void enter_run_state() {
  window_set_click_config_provider(&window, (ClickConfigProvider) run_state_click_config_provider);
  state = RUN_STATE;
}

/*** SET state ***************************************************************/

void set_state_up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  timer_time += 60;

  displayTime();
}

void set_state_up_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  timer_time += 300;

  displayTime();
}

void set_state_down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  timer_time -= 60;
  if(timer_time < 0) {
    timer_time = 0;
  }

  displayTime();
}

void set_state_down_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  timer_time -= 300;
  if(timer_time < 0) {
    timer_time = 0;
  }

  displayTime();
}

void set_state_select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  enter_run_state();
}

void set_state_select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  enter_set_state(); // Reset (idempotent if already in SET state)
}

void set_state_click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_UP]->click.handler            = (ClickHandler) set_state_up_single_click_handler;
  config[BUTTON_ID_UP]->long_click.handler       = (ClickHandler) set_state_up_long_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler            = (ClickHandler) set_state_down_single_click_handler;
  config[BUTTON_ID_DOWN]->long_click.handler       = (ClickHandler) set_state_down_long_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_SELECT]->click.handler            = (ClickHandler) set_state_select_single_click_handler;
  config[BUTTON_ID_SELECT]->long_click.handler       = (ClickHandler) set_state_select_long_click_handler;
  config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 100;
}

void enter_set_state() {
  state = SET_STATE;
  timer_time = 10;
  window_set_click_config_provider(&window, (ClickConfigProvider) set_state_click_config_provider);
  displayTime();
}

/*** FINISHED state **********************************************************/

void finished_state_timer_reset_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  enter_set_state(); // Reset
}

void finished_state_click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_UP]->click.handler            = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_UP]->long_click.handler       = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler            = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_DOWN]->long_click.handler       = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_SELECT]->click.handler            = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_SELECT]->long_click.handler       = (ClickHandler) finished_state_timer_reset_click_handler;
  config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 100;
}

void enter_finished_state() {
  state = FINISHED_STATE;
  window_set_click_config_provider(&window, (ClickConfigProvider) finished_state_click_config_provider);
  text_layer_set_text(&textLayer, "Time's Up!");
}

/*** Standard app initialisation *********************************************/

void handle_init(AppContextRef ctx) {
  (void)ctx;

  myContext = ctx;

  window_init(&window, "Timer");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&textLayer, window.layer.frame);
  text_layer_set_font(&textLayer, fonts_get_system_font(FONT_KEY_GOTHAM_42_BOLD));
  text_layer_set_text_alignment(&textLayer, GTextAlignmentCenter);
  layer_add_child(&window.layer, &textLayer.layer);

  // Start in the SET state
  enter_set_state();
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *event) {
  if(state == RUN_STATE) {
    // Decrement time
    timer_time -= 1;

    // Finish timer if time is zero
    if(timer_time <= 0) {
      enter_finished_state();
    }

    // Update display
    displayTime();
  }
  else if(state == FINISHED_STATE) {
    vibes_double_pulse();
    text_layer_set_text(&textLayer, "Time's Up!");
  }
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units   = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
