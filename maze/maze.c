#include <stdio.h>

int ver[100][100];
int hor[100][100];

int fug_x, fug_y;
int cha_x, cha_y;
int ex_x, ex_y;
int room_size;


int cangoLeft(int x, int y) {

   if (

}


int main() {
	FILE *fp = fopen("input.txt", "r");

	int i, j;

	char tmp;


	fscanf(fp, "%d", &room_size);

	fscanf(fp, "%d%c%d", &fug_x, &tmp, &fug_y);
	fscanf(fp, "%d%c%d", &cha_x, &tmp, &cha_y);
	fscanf(fp, "%d%c%d", &ex_x, &tmp, &ex_y);

	for(i = 0; i < room_size; i++) {
		for(j=0; j < room_size-1; j++) {
			fscanf(fp, "%1d", &ver[i][j]);
		}
	}

	for(i = 0; i < room_size; i++) {
		for(j=0; j < room_size-1; j++) {
			fscanf(fp, "%1d", &hor[i][j]);
		}
	}


	for(i = 0; i < room_size; i++) {
		for(j=0; j < room_size-1; j++) {
			printf("%d", ver[i][j]);
		}
		printf("\n");
	}


	for(i = 0; i < room_size; i++) {
		for(j=0; j < room_size-1; j++) {
			printf("%d", hor[i][j]);
		}
		printf("\n");
	}

	return 0;
}
