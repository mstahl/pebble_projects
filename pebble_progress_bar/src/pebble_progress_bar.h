/*
 * pebble_progress_bar.h
 *
 * Constants and functions for the "Progress Bar" watchface.
 *
 * (c) 2013 Max Thom Stahl
 */

// Constants ------------------------------------------------------------------

#define SCREEN_WIDTH  168
#define SCREEN_HEIGHT 144


// Options --------------------------------------------------------------------

#define HOURS_MIN_WIDTH   10
#define HOURS_MAX_WIDTH   SCREEN_WIDTH
#define HOURS_WIDTH       (HOURS_MAX_WIDTH - HOURS_MIN_WIDTH)
#define MINUTES_MIN_WIDTH 10
#define MINUTES_MAX_WIDTH SCREEN_WIDTH
#define MINUTES_WIDTH     (MINUTES_MAX_WIDTH - MINUTES_MIN_WIDTH)
