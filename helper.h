/**
 *  Copyright 2024 Swapnaneel Dutta

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   limitations under the License.

 */


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
char* helper_fnstr(char *path);
#endif 
