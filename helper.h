
#ifndef HELPER_H
#define HELPER_H

// Foreground colors
#define BLACK_FG   "\x1b[30m"
#define RED_FG     "\x1b[31m"
#define GREEN_FG   "\x1b[32m"
#define YELLOW_FG  "\x1b[33m"
#define BLUE_FG    "\x1b[34m"
#define MAGENTA_FG "\x1b[35m"
#define CYAN_FG    "\x1b[36m"
#define WHITE_FG   "\x1b[37m"

// Background colors
#define RED_BG     "\x1b[41m"
#define GREEN_BG   "\x1b[42m"
#define YELLOW_BG  "\x1b[43m"
#define BLUE_BG    "\x1b[44m"
#define MAGENTA_BG "\x1b[45m"
#define CYAN_BG    "\x1b[46m"
#define WHITE_BG   "\x1b[47m"

// Reset color
#define RESET      "\x1b[0m"

void helper_ugdisplay(void);

#endif 
