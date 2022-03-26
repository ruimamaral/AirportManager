# include <stdio.h>

int main(){
	while (command_listener())
}

int command_listener() {
	char command = getchar();
	getchar() /* remove whitespace chararcter */
	switch (command) {
		case 'q':
			return 0;
		case 'a':
			add_airport();
			return 1;
		case 'l':
			list_airports();
			return 1;
		case 'v':
			flights();
			return 1;
		case 'p':
			departing();
			return 1;
		case 'c':
			arriving();
			return 1;
		case 't':
			set_time();
			return 1;
	}
}
