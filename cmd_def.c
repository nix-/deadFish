/*
 * cmd_def.c
 *
 *  Created on: Apr. 11, 2021
 *      Author: niks
 */

#include "cmd_def.h"

#include "stdio.h"
#include <unistd.h>
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

// Create New Command
// define function, extend structure

// format of the help command
/*
Naval Fate.

Usage:
  naval_fate ship new <name>...
  naval_fate ship <name> move <x> <y> [--speed=<kn>]
  naval_fate ship shoot <x> <y>
  naval_fate mine (set|remove) <x> <y> [--moored|--drifting]
  naval_fate -h | --help
  naval_fate --version

Options:
  -h --help     Show this screen.
  --version     Show version.
  --speed=<kn>  Speed in knots [default: 10].
  --moored      Moored (anchored) mine.
  --drifting    Drifting mine.
*/

#define COMMANDS_LIST_LENGHT  (sizeof(commands_list)/sizeof(commands_list[0]))

int cmd_template(const int argc, const char *argv[]);
// Definition of the command execution functions
int cmd_empty(const int argc, const char *argv[]);
int cmd_help(const int argc, const char *argv[]);
int cmd_info(const int argc, const char *argv[]);
int cmd_flash(const int argc, const char *argv[]);
int cmd_rtc(const int argc, const char *argv[]);
int cmd_nfc(const int argc, const char *argv[]);
int cmd_clear(const int argc, const char *argv[]);
int cmd_test(const int argc, const char *argv[]);

command_t commands_list[] = {
        {"",        "",         cmd_empty,      ""},
        {"help",    "",         cmd_help,       "Listing all of the available commands."},
        {"info",    "",         cmd_info,       "Information about terminal."},
        {"clear",   "",         cmd_clear,      "Removing accumulated data in the terminal."},
        {"test",    "",         cmd_test,       "Place holder for experimenting."},
        {"example", "",         cmd_template,   "Template for a terminal-call function."},
};


int cmd_get_list_lenght(void)
{
    return COMMANDS_LIST_LENGHT;
}


int cmd_help(const int argc, const char *argv[])
{
    int i = 0;

    // starting from 1 in order to avoid printing of the example
    for (i = 1; i < COMMANDS_LIST_LENGHT; i++) {
        printf(BOLD "%9s" EOC " - %s\r\n", commands_list[i].cmd, commands_list[i].description);
    }
    return 0;
}

// example of the command
int cmd_empty(const int argc, const char *argv[])
{
    static bool trap = true;

    if (trap) {
        printf(MAG "Execute help for getting list available commands." EOC "\r\n");
        trap = false;
    }
    return 0;
}


int cmd_clear(const int argc, const char *argv[])
{
    printf(CLEAR_SCREEN);
}


int cmd_info(const int argc, const char *argv[])
{
    int i = 0;
    printf(BLU);
    printf("Simple implementation of Command Line Interface.\r\n" BOLD);
    //printf(" \r\n");

    printf("     _                _    __ _     _     \r\n");
    printf("  __| | ___  __ _  __| |  / _(_)___| |__  \r\n");
    printf(" / _` |/ _ \\/ _` |/ _` | | |_| / __| '_ \\ \r\n");
    printf("| (_| |  __/ (_| | (_| | |  _| \\__ \\ | | |\r\n");
    printf(" \\__,_|\\___|\\__,_|\\__,_| |_| |_|___/_| |_|\r\n");
    //printf("                                          ");
    printf(EOC);

    printf("\r");
    //sleep(0.731);
    for (i=1; i<23; i+=2) {
        printf("\a%*s%s", i, "", BLU ">/"MAG"o"EOC">\r");
        //sleep((0.021*i)+100);
    }
    --i;
    printf("\a%*s%s", i, "", BLU ">/x"EOC">\r");
    //sleep(0.777);
    printf(BLU "\r\n(only dead fish goes with the flow)"EOC"\r\n");
    //sleep(0.777);
    return 0;
}


static void progres_bar(unsigned int value, unsigned int max_value, const char* color)
{
    unsigned int proc = (value * 10) / max_value;
    unsigned int proc_p = ((value * 100) / max_value);
    int i = 0;

    if (proc_p > 100) {
        proc = 100;
        proc_p = 100;
    }

    printf("[%s" , color);

    for (i = 0; i < 10; i++) {
        if (i < proc) {
            printf("##");
        }
        else if(i == proc) {
            printf(COLOUR_RESET);
            printf("--");
        }
        else {
            printf("--");
        }
    }

    printf(COLOUR_RESET "] %3lu%c", proc_p, 0x25);

    return; 
}


int cmd_template(const int argc, const char *argv[])
{
    int option = 0;

    optind = 0; // initialize opt index for parsing terminal input
    while ((option = getopt(argc, argv, "ht:")) != -1) {
        switch (option) {
        case 'h':
            printf(
                "Naval Fate.\r\n"
                "\r\n"
                "Usage:\r\n"
                "  naval_fate ship new <name>...\r\n"
                "  naval_fate ship <name> move <x> <y> [--speed=<kn>]\r\n"
                "  naval_fate ship shoot <x> <y>\r\n"
                "  naval_fate mine (set|remove) <x> <y> [--moored|--drifting]\r\n"
                "  naval_fate -h | --help\r\n"
                "  naval_fate --version\r\n"
                "\r\n"
                "Options:\r\n"
                "  -h --help     Show this screen.\r\n"
                "  --version     Show version.\r\n"
                "  --speed=<kn>  Speed in knots [default: 10].\r\n"
                "  --moored      Moored (anchored) mine.\r\n"
                "  --drifting    Drifting mine.\r\n"
                );
            break;
        case 't':
            printf("-t input: %s\r\n", optarg);
            break;
        case ':':
            printf("option needs a value\r\n");
           break;
        case '?': //used for some unknown options
            printf("unknown option: %c\r\n", optopt);
           break;
        default:
            printf("Usage.\r\n");
            return -1;
        }
    }

    return 0;
}


int cmd_test(const int argc, const char *argv[])
{
    int option = 0;

    int area = -1;
    int perimeter = -1;
    int breadth = -1;
    int line =-1;

    optind = 0; // initialize opt index for parsing terminal input
    //Specifying the expected options
    //The two options l and b expect numbers as argument
    while ((option = getopt(argc, argv,"apm::l:b:t:")) != -1) {
        switch (option) {
        case 'a' : area = 0;
            printf("area\r\n");
            break;
        case 'p' : perimeter = 0;
            printf("perimeter\r\n");
            break;
        case 'm': {
            char* arg1 = NULL;
            unsigned int arg2 = 0;
            arg1 = argv[optind];
            ++optind; // shift to the next argument
            arg2 = strtol(argv[optind], NULL, 16);
            printf("Handling multiple arguments example (%.16s; 0x%08x)\r\n", arg1, arg2);
            break;
        }
        case 'l' :
            line = atoi(optarg);
            printf("\033[%dA", line);
            break;
        case 'b' : breadth = atoi(optarg);
            printf("breadth\r\n");
            break;
        case 't': {
            int i = atoi(optarg);
            for (; i<=100; i++) {

                printf("Simulation of progress ");
                progres_bar(i, 100, BLU);

                printf("\r\nSimulation of progress ");
                progres_bar(100-i, 100, RED);

                printf("\r\nSimulation of progress ");
                progres_bar(i, 200, GRN);

                printf("\r\nSimulation of progress ");
                progres_bar(100-i, 200, YEL);

                printf("\r\nSimulation of progress ");
                progres_bar(100-i, 100, MAG);

                printf("\r\nSimulation of progress ");
                progres_bar(i, 100, CYN);

                printf("\033[5A\r");

                sleep(1);
            }
            printf("\033[5B");
            printf("\r\nProgress Done.\r\n");
            break;
        }
        default:
            printf("usage.\r\n");
            return -1;
        }
    }

    return 0;
}
