#include<stdlib.h>
#include<stdio.h>


typedef struct pair_{
	int x;
	int y;
} Pair;

int pair_comp(const void *a, const void *b){

	Pair *ai = (Pair*)a;
	Pair *bi = (Pair*)b;

	return ((ai->x > bi->x) - (ai->x < bi->x));
}

int main(int argc, char *argv[]){
	
	Pair ten_oh;

	Pair p[] = { { 1,3}, {2,-1}, {3,-2}, {5,-1}, {10,0}, {-5,3}, {-1,-2}, {0,0}, {1,-1}  };

	ten_oh.x = 10;
	ten_oh.y = 0;

	qsort(p,9,sizeof(Pair),pair_comp);
	
	printf("Pair [10, 0] is located at %p\n", bsearch((void*)&ten_oh,(void*)p,9,sizeof(Pair),pair_comp));
	
	return 0;
}
