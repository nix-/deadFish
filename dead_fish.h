#ifndef DEADFISH_DEAD_FISH_H_
#define DEADFISH_DEAD_FISH_H_

#include "stdio.h"

// TERMINAL CONSOLE COMMANDS
#define BLC             "\e[30m"
#define RED             "\e[31m"
#define GRN             "\e[32m"
#define YEL             "\e[33m"
#define BLU             "\e[34m"
#define MAG             "\e[35m"
#define CYN             "\e[36m"
#define WHT             "\e[37m"

#define H_RED           "\e[91m"
#define H_GRN           "\e[92m"
#define H_YEL           "\e[93m"
#define H_BLU           "\e[94m"
#define H_MAG           "\e[95m"
#define H_CYN           "\e[96m"
#define H_WHT           "\e[97m"

#define B_RED           "\e[41m"
#define B_GRN           "\e[42m"
#define B_YEL           "\e[43m"
#define B_BLU           "\e[44m"
#define B_MAG           "\e[45m"
#define B_CYN           "\e[46m"
#define B_WHT           "\e[47m"
#define B_RESET         "\e[40m"
#define BOLD            "\e[1m"
#define BOLD_RESET      "\e[0m"
#define UNDERLINE       "\e[4m"
#define UNDERLINE_RESET "\e[0m"
#define COLOUR_RESET    "\e[0m\e[39m\e[49m"
#define EOC             "\e[0m"

#define CLEAR_SCREEN    "\033c"

#define UART_BUFF_SIZE      64
#define UART_BUFF_MASK      (UART_BUFF_SIZE-1)
#define UART_DONUT_DEEP     4
#define UART_DONUT_MASK     (UART_DONUT_DEEP-1)

#define MAX_NUM_ATTRIBUTES  16

typedef volatile struct {
    unsigned int wi;                    // write index
    unsigned int ri;                    // read index
    char d[UART_BUFF_SIZE];      // data
} ring_buff_t;


typedef volatile struct {
    unsigned int hi;                    // head
    unsigned int ti;                    // tail
    ring_buff_t s[UART_DONUT_DEEP]; // shelf
} donut_buff_t;


typedef struct {
    const char* cmd;
    const char* format;
    int (*exec)(const int, const char**);
    const char* description;
} command_t;


typedef struct {
    char* cmd;
    int argc;
    char* argv[MAX_NUM_ATTRIBUTES];
} command_line_t;

// storage for the commands
donut_buff_t donut;
command_line_t cmd_line;

void init_donut(donut_buff_t* p_donut);
void donut_receive_key(const char c);

#endif /* DEADFISH_DEAD_FISH_H_ */
