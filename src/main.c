#include <stdio.h>
#include "../lib/add.h"

int main(){
	int a=5, b=10;
	printf( "%i + %i = %i\n",a,b,add(a,b) );
	return 0;
}
