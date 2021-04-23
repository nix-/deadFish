#include <stdio.h>
#include "dead_fish.h"

int main()
{
	char cmd_buff[2000] = {0,};

	init_donut(&donut);
	
    while (1) {
    	donut_receive_key(getchar()); 
    	while (donut_pull_cmd(cmd_buff)) {
        	// printing the accumulated command
        	printf(GRN "%s" EOC "\r\n", cmd_buff);
        	// brake command line in elements and execute (handle)
        	cmd_handler(cmd_break_string(cmd_buff));
        }
    }

	return 0;
}