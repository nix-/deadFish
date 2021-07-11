#include "dead_fish.h"
#include "cmd_def.h"

#include "stdio.h"
#include "string.h"
#include "stdbool.h"


void init_donut(donut_buff_t* p_donut)
{
    int i = 0;
    // set shelfs to 0
    p_donut->hi = 0;
    p_donut->ti = 0;
    // set all indexes to 0
    for(i=0; i < UART_DONUT_DEEP; i++) {
        p_donut->s[i].ri = 0;
        p_donut->s[i].wi = 0;
    }
    return;
}


static void donut_add_data(char input)
{
    const unsigned int shelf_index = donut.hi;
    const unsigned int write_index = donut.s[shelf_index].wi;

    donut.s[shelf_index].d[write_index] = input;
    donut.s[shelf_index].wi = (write_index + 1) & UART_BUFF_MASK;

    if (input == '\n') {
        donut.hi = (shelf_index + 1) & UART_DONUT_MASK;
    }

    return;
}


void donut_receive_key(const char c)
{
    char symbol = c;

    // todo: this need to be reworked. 
    // no-control character
    if (isalnum(symbol)
            || (symbol == '\n')
            || (symbol == ' ')
            || (symbol == '.')
            || (symbol == '_')
            || (symbol == '-')) {

        if (symbol == '\n') {
        	// Windows New Line combination
            donut_add_data('\r');
            donut_add_data('\n');
        }
        else {
        	donut_add_data(symbol);	
        }
    }
    // handling the backspace
    else if (symbol == '\b') {
        // corner case when the buffer pointer zero
        if (donut.s[donut.hi].wi > donut.s[donut.hi].ri) {
            printf("\b \b");
            donut.s[donut.hi].wi--;
        }
    }

    return;
}


bool donut_pull_cmd(char *p_cmd)
{
    if (donut.hi != donut.ti) {
        unsigned int shelf_index = (donut.hi - 1) & UART_DONUT_MASK;
        unsigned int lenght = (donut.s[shelf_index].wi - donut.s[shelf_index].ri) & UART_BUFF_MASK;

        memccpy(p_cmd, donut.s[shelf_index].d, '\r', lenght);
        p_cmd[donut.s[shelf_index].wi] = '\0'; // set end of string
        // removing the new line symbols (\r\n)
        p_cmd[(donut.s[shelf_index].wi - 1) & UART_BUFF_MASK] = ' '; // set end of string
        p_cmd[(donut.s[shelf_index].wi - 2) & UART_BUFF_MASK] = '\0'; // set end of string

        donut.hi = shelf_index;
        donut.s[shelf_index].ri = 0;
        donut.s[shelf_index].wi = 0;

        return true;  // command found
    }
    return false;
}


static int tokenization(const char *str, char *argv[], char *delimiter)
 {
    int argc = 0;
    char *token;
    /* get the first token */
    token = strtok(str, delimiter);
    /* walk through other tokens */
    while ((token != NULL) && (argc < MAX_NUM_ATTRIBUTES)) {
        argv[argc] = token;
        token = strtok( NULL, delimiter);
        argc++;
    }
    argv[argc] = NULL;  // The next attribute mark with NULL

    return argc;
 }


command_line_t* cmd_break_string(char *str)
{
    cmd_line.argc = tokenization(str, cmd_line.argv, " ");

    if (cmd_line.argc > 0) {
        cmd_line.cmd = cmd_line.argv[0];
    }
    else {
        cmd_line.cmd = NULL;
    }

    return &cmd_line;
}


int cmd_handler(char **cmd_list)
{
    int i = 0;
    int len = cmd_get_list_lenght();
    bool status = false;
    // going trought list of commands
    if (cmd_line.cmd != NULL) {
    	for (i = 0; (i < len); i++) {
    	    if (!strncmp(cmd_line.cmd, commands_list[i].cmd, 16)) {
    	        commands_list[i].exec(cmd_line.argc, cmd_line.argv);
    	        status = true;
    	        break;
    	    }
    	}
    }
    // command prompt
    printf(BLU ">/x" EOC "> ");

    if (status) {
    	return 0; // found command
    } 
    return 1; // no command found
}
