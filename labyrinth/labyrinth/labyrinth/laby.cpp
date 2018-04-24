#include"laby.h"

int main() {
	labyrinth new_laby(25);
	new_laby.labyrinth_print_original();
	new_laby.labyrinth_search();
	new_laby.labyrinth_print_after_search();
	system("pause");
	return 0;
}