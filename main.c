#include <stdio.h>
#include "dead_fish.h"

int main()
{
	char cmd_buff[64] = {0,};

	// init indexes
	init_donut(&donut);

	// info - user example
	printf("Type help for getting list of commands.\r\n");
	printf("try the follow:\r\n");
	printf("  1: info\r\n");
	printf("  2: help\r\n");
	printf("  3: test -t 88\r\n");
	printf("  4: example -h\r\n");
	printf("  4: clear\r\n");
	
    while (1) {
    	// receiving character
    	donut_receive_key(getchar()); 

    	// process the commands till there are some in the donut-buff
    	//   note: new command will be processed after \n is received and stored!
    	while (donut_pull_cmd(cmd_buff)) {
        	// printing the accumulated command
        	printf(GRN "%s" EOC "\r\n", cmd_buff);
        	// brake command line in elements and execute (handle)
        	cmd_handler(cmd_break_string(cmd_buff));
        }
    }

	return 0;
}