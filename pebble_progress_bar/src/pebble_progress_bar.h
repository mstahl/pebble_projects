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

#define HOURS_PER_TICKMARK    1
#define HOURS_PER_ROW         6
#define HOUR_TICKMARK_WIDTH   3
#define PIXELS_PER_HOUR       (SCREEN_WIDTH / HOURS_PER_ROW)

#define MINUTES_PER_TICKMARK  5
#define MINUTES_PER_ROW       15
#define MINUTE_TICKMARK_WIDTH 3
#define PIXELS_PER_MINUTE     (SCREEN_WIDTH / MINUTES_PER_ROW)

#define HOUR_MODULUS          12
#define PIXELS_PER_ROW        (SCREEN_HEIGHT/(HOUR_MODULUS/HOURS_PER_ROW + 60/MINUTES_PER_ROW))
