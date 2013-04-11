#include <stdio.h>

int ver[100][100];
int hor[100][100];

int visited[100][100];
int shortest_visited[100][100];

int fug_x, fug_y;
int cha_x, cha_y;
int ex_x, ex_y;
int room_size;
int shortest_length = 10000000;

int prev_cha_x, prev_cha_y;
int prev_fug_x, prev_fug_y;

int tmp_length=0;

int cangoLeft(int x, int y) {
   return (y>1 && ver[x-1][y-2]==0);
}

int cangoUp(int x, int y) {
	return (x>1 && hor[y-1][x-2]==0);
}

int cangoDown(int x, int y) {
	return (x<room_size && hor[y-1][x-1]==0);
}

int cangoRight(int x, int y) {
	return (y<room_size && ver[x-1][y-1]==0);
}

void DFS(int x, int y, int dest_x, int dest_y) {
	tmp_length++;
	visited[x][y] = tmp_length;


//	printf("(%d, %d)\n", x, y);
	if(x==dest_x && y==dest_y) {
	//	printf("Exit Complete! : %d\n", tmp_length);
		if (shortest_length > tmp_length) {
			int i, j;
			shortest_length = tmp_length;
			for(i=1; i<=room_size; i++) {
				for(j=1; j<=room_size; j++) {
					shortest_visited[i][j] = visited[i][j];
				}
			}

		}
	}
	else {
		if(cangoLeft(x,y) == 1 && visited[x][y-1]==0){
			DFS(x, y-1, dest_x, dest_y);
		}

		if(cangoRight(x,y) == 1 && visited[x][y+1]==0){
			DFS(x, y+1, dest_x, dest_y);
		}
		if(cangoDown(x,y) == 1 && visited[x+1][y]==0){
			DFS(x+1, y, dest_x, dest_y);
		}
		if(cangoUp(x,y) == 1 && visited[x-1][y]==0){
			DFS(x-1, y, dest_x, dest_y);
		}
	}
	visited[x][y] = 0;
	tmp_length--;
}

void getShortestPath(int start_x, int start_y, int dest_x, int dest_y){
	int i, j;
	shortest_length = 1000000;
	for (i=0;i<=room_size;i++){
		for (j=0;j<=room_size;j++){
			shortest_visited[i][j] = 0;
		}
	}
	DFS(start_x, start_y, dest_x, dest_y);
}

int chasing (int *fug_x, int *fug_y, int *cha_x, int *cha_y) {


	getShortestPath(*fug_x, *fug_y, ex_x, ex_y);

	prev_fug_x = *fug_x;
	prev_fug_y = *fug_y;

	if(shortest_visited[*fug_x + 1][*fug_y] == 2) {
		*fug_x = *fug_x + 1;
	}
	else if(shortest_visited[*fug_x - 1][*fug_y] == 2) {
		*fug_x = *fug_x - 1;
	}
	else if(shortest_visited[*fug_x][*fug_y + 1] == 2) {
		*fug_y = *fug_y + 1;
		}
	else if(shortest_visited[*fug_x][*fug_y - 1] == 2) {
		*fug_y = *fug_y - 1;
	}

	int k;
	int is_ing=0;
	for (k=0; k<2; k++) {

		// 추격자와 도망자의 세로축이 다른 경우...
		if(*cha_y > *fug_y) {
			if(cangoLeft(*cha_x, *cha_y)) {
				*cha_y = *cha_y - 1;
			}
		}
		else if (*cha_y < *fug_y) {
			if(cangoRight(*cha_x, *cha_y)) {
				*cha_y = *cha_y + 1;
			}
		}
		// 추격자와 도망자의 세로축이 같고, 세로좌표가 다른 경우..
		else { 
			if(*cha_x > *fug_x) {
				if(cangoUp(*cha_x, *cha_y)) {
					*cha_x = *cha_x - 1;
				}

			}
			else if (*cha_x < *fug_x) {
				if(cangoDown(*cha_x, *cha_y)) {
					*cha_x = *cha_x + 1;
				}
			}

		}

		prev_cha_x = *cha_x;
		prev_cha_y = *cha_y;
		if((prev_cha_x == *fug_x && prev_fug_y == *cha_y) || (*cha_x == *fug_x && *cha_y == *fug_y))
			is_ing = 2;
	}


	if((*fug_x == ex_x && *fug_y == ex_y) && (is_ing == 0)) {
		is_ing = 1;
	}

	return is_ing;
}

void print_path() {

	int i, j;
	//	int k = 3;
	int k;
	int x, y;

	for(k = 1; k<=shortest_length; k++) {
		for(i = 1; i<=room_size; i++) {
			for(j = 1; j<=room_size; j++) {
				if(shortest_visited[i][j] == k) {
					x = i;
					y = j;
				}
			}
		}
		printf("(%d,%d)\n", x, y);
	}
}

/*bool isEqualMatrix(int *m1[], int *m2[]){
	bool result = true;
	bool breakvar = false;
	for (int i=0;i<m1.length;i++){
		for (int j=0;j<m1.length;j++){
			if (m1[i][j] != m2[i][j]){
				result = false;
				breakvar = true;
			}
			if (breakvar) break;
		}
		if (breakvar) break;
	}
	return result;
}*/

void print_path2() {
	int k;
	int i, j, cur_x = -1, cur_y = -1;

	for(i = 1; i<=room_size; i++) {
		for(j = 1; j<=room_size; j++) {
			if(shortest_visited[i][j] == 1) {
				cur_x = i;
				cur_y = j;
			}
			if (cur_x != -1 || cur_y != -1) break;
		}
		if (cur_x != -1 || cur_y != -1) break;
	}

	for (k = 1; k<=shortest_length; k++) {
		printf("(%d, %d)\n", cur_x, cur_y);
		if(shortest_visited[cur_x+1][cur_y] == k+1) {
			cur_x = cur_x+1;
		}
		else if(shortest_visited[cur_x-1][cur_y] == k+1) {
			cur_x = cur_x-1;
		}
		else if(shortest_visited[cur_x][cur_y+1] == k+1) {
			cur_y = cur_y+1;
		}
		else if(shortest_visited[cur_x][cur_y-1] == k+1) {
			cur_y = cur_y-1;
		}
	}
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


/*	for(i = 0; i < room_size; i++) {
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

	printf("%d\n", cangoLeft(2, 2));
	printf("%d\n", cangoLeft(2, 3));
	printf("%d\n", cangoLeft(3, 2));*/

/*	getShortestPath(fug_x, fug_y, ex_x, ex_y);
	print_path2();
	getShortestPath(1, 1, 3, 4);
	print_path2();


	for (i=1;i<=room_size;i++){
		for (j=1;j<=room_size;j++){
			printf("%d ", shortest_visited[i][j]);
		}
		puts("");
	}
	puts("");
	printf("%d\n", shortest_length); */

	int cur_fug_x = fug_x;
	int cur_fug_y = fug_y;
	int cur_cha_x = cha_x;
	int cur_cha_y = cha_y;


	while (1){
		printf("fug : (%d,%d) // cha : (%d,%d)\n", cur_fug_x, cur_fug_y, cur_cha_x, cur_cha_y);
		int result = chasing (&cur_fug_x, &cur_fug_y, &cur_cha_x, &cur_cha_y);
		if (result == 1){
			printf("succ\n");
			break;
		} else if (result == 2){
			printf("fail\n");
			break;
		}
	}

	return 0;
}
