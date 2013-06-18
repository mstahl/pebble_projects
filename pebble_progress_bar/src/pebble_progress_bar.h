/*
 * pebble_progress_bar.h
 *
 * Constants and functions for the "Progress Bar" watchface.
 *
 * (c) 2013 Max Thom Stahl
 */

// Constants ------------------------------------------------------------------

#define SCREEN_WIDTH  144
#define SCREEN_HEIGHT 168


// Options --------------------------------------------------------------------

#define HOURS_PER_TICKMARK   1
#define HOUR_TICKS_PER_ROW   4
#define HOUR_BORDER_WIDTH    1
#define PIXELS_PER_HOUR      (SCREEN_WIDTH / HOUR_TICKS_PER_ROW)

#define MINUTES_PER_TICKMARK 1
#define MINUTE_TICKS_PER_ROW 20
#define MINUTE_BORDER_WIDTH  1
#define PIXELS_PER_MINUTE    ((SCREEN_WIDTH / MINUTE_TICKS_PER_ROW)+1)

#define HOUR_MODULUS         12
#define PIXELS_PER_ROW       (SCREEN_HEIGHT/(HOUR_MODULUS/HOUR_TICKS_PER_ROW + 60/MINUTE_TICKS_PER_ROW))
