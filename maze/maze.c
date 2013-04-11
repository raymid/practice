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

void DFS(int fug_x, int fug_y, int dest_x, int dest_y, int cha_x, int cha_y) { // 현재 주인공, 추격자, 탈출구 위치를 인자로 받아서 시뮬레이션 하면서 최단경로를 찾는 함수
	
	if(fug_x == cha_x && fug_y == cha_y) {
		return;	
	}

//	printf("(%d, %d) / (%d, %d) / %d\n", fug_x, fug_y, cha_x, cha_y, tmp_length);

	tmp_length++;
	visited[fug_x][fug_y] = tmp_length;

	if(fug_x==dest_x && fug_y==dest_y) {
		if (shortest_length > tmp_length) {
			//printf("shortest!\n");
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
		if(cangoLeft(fug_x,fug_y) == 1 && visited[fug_x][fug_y-1]==0){
			int tmp_cha_x = cha_x, tmp_cha_y = cha_y;
			chasing(fug_x, fug_y-1, &tmp_cha_x, &tmp_cha_y);
			DFS(fug_x, fug_y-1, dest_x, dest_y, tmp_cha_x, tmp_cha_y);
		}
		if(cangoRight(fug_x,fug_y) == 1 && visited[fug_x][fug_y+1]==0){
			int tmp_cha_x = cha_x, tmp_cha_y = cha_y;
			chasing(fug_x, fug_y+1, &tmp_cha_x, &tmp_cha_y);
			DFS(fug_x, fug_y+1, dest_x, dest_y, tmp_cha_x, tmp_cha_y);
		}
		if(cangoDown(fug_x,fug_y) == 1 && visited[fug_x+1][fug_y]==0){
			int tmp_cha_x = cha_x, tmp_cha_y = cha_y;
			chasing(fug_x+1, fug_y, &tmp_cha_x, &tmp_cha_y);
			DFS(fug_x+1, fug_y, dest_x, dest_y, tmp_cha_x, tmp_cha_y);
		}
		if(cangoUp(fug_x,fug_y) == 1 && visited[fug_x-1][fug_y]==0){
			int tmp_cha_x = cha_x, tmp_cha_y = cha_y;
			chasing(fug_x-1, fug_y, &tmp_cha_x, &tmp_cha_y);
			DFS(fug_x-1, fug_y, dest_x, dest_y, tmp_cha_x, tmp_cha_y);
		}
	}
	visited[fug_x][fug_y] = 0;
	tmp_length--;
}

void getShortestPath(int start_x, int start_y, int dest_x, int dest_y, int cha_x, int cha_y){
	int i, j;
	shortest_length = 1000000;
	for (i=0;i<=room_size;i++){
		for (j=0;j<=room_size;j++){
			shortest_visited[i][j] = 0;
		}
	}
	DFS(start_x, start_y, dest_x, dest_y, cha_x, cha_y);
}

int chasing (int fug_x, int fug_y, int *cha_x, int *cha_y) { // 주인공 한턴 움직인 후(시뮬레이션)의 위치쌍과 추격자의 현재 위치쌍을 받아서, 추격자가 이동해야할 실제 좌표로 변경해주는 함수
	int k;
	int is_ing=0;
	for (k=0; k<2; k++) {

		// 추격자와 도망자의 세로축이 다른 경우...
		if(*cha_y > fug_y) {
			if(cangoLeft(*cha_x, *cha_y)) {
				*cha_y = *cha_y - 1;
			}
		}
		else if (*cha_y < fug_y) {
			if(cangoRight(*cha_x, *cha_y)) {
				*cha_y = *cha_y + 1;
			}
		}
		// 추격자와 도망자의 세로축이 같고, 세로좌표가 다른 경우..
		else { 
			if(*cha_x > fug_x) {
				if(cangoUp(*cha_x, *cha_y)) {
					*cha_x = *cha_x - 1;
				}

			}
			else if (*cha_x < fug_x) {
				if(cangoDown(*cha_x, *cha_y)) {
					*cha_x = *cha_x + 1;
				}
			}

		}

		prev_cha_x = *cha_x;
		prev_cha_y = *cha_y;
		if((prev_cha_x == fug_x && prev_fug_y == *cha_y) || (*cha_x == fug_x && *cha_y == fug_y))
			is_ing = 2;
	}


	if((fug_x == ex_x && fug_y == ex_y) && (is_ing == 0)) {
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
		/if (breakvar) break;
	}
	return result;
}*/
/*
void print_path2() {
	int k;
	int i, j, cur_fug_x = -1, cur_fug_y = -1;

	int cur_cha_x = 

	for(i = 1; i<=room_size; i++) {
		for(j = 1; j<=room_size; j++) {
			if(shortest_visited[i][j] == 1) {
				cur_fug_x = i;
				cur_fug_y = j;
			}
			if (cur_fug_x != -1 || cur_fug_y != -1) break;
		}
		if (cur_fug_x != -1 || cur_fug_y != -1) break;
	}

	for (k = 1; k<=shortest_length; k++) {
		printf("(%d, %d), (%d,%d)\n", cur_fug_x, cur_fug_y, cur_cha_x, cur_cha_y);
		if(shortest_visited[cur_fug_x+1][cur_fug_y] == k+1) {
			cur_fug_x = cur_fug_x+1;
			chasing(cur_fug_x, cur_fug_y, );
		}
		else if(shortest_visited[cur_fug_x-1][cur_fug_y] == k+1) {
			cur_fug_x = cur_fug_x-1;
		}
		else if(shortest_visited[cur_fug_x][cur_fug_y+1] == k+1) {
			cur_fug_y = cur_fug_y+1;
		}
		else if(shortest_visited[cur_fug_x][cur_fug_y-1] == k+1) {
			cur_fug_y = cur_fug_y-1;
		}
	}
}

*/

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


	getShortestPath(fug_x, fug_y, ex_x, ex_y, cha_x, cha_y);
	printf("Shortest Path Length : %d\n\n", (shortest_length-1));
/*	for (i=1;i<=room_size;i++){
		for (j=1;j<=room_size;j++){
			printf("%d ", shortest_visited[i][j]);
		}
		puts("");
	}
	puts(""); */


	
	int k;
	int q, w, cur_fug_x = -1, cur_fug_y = -1;

	for(q = 1; q<=room_size; q++) {
		for(w = 1; w<=room_size; w++) {
			if(shortest_visited[q][w] == 1) {
				cur_fug_x = q;
				cur_fug_y = w;
			}
			if (cur_fug_x != -1 || cur_fug_y != -1) break;
		}
		if (cur_fug_x != -1 || cur_fug_y != -1) break;
	}

	printf("Path : \n");
	for (k = 1; k<=shortest_length; k++) {
		printf("(%d,%d) / (%d,%d)\n", cur_fug_x, cur_fug_y, cha_x, cha_y);
		if(shortest_visited[cur_fug_x+1][cur_fug_y] == k+1) {
			cur_fug_x = cur_fug_x+1;
			chasing(cur_fug_x, cur_fug_y, &cha_x, &cha_y);
		}
		else if(shortest_visited[cur_fug_x-1][cur_fug_y] == k+1) {
			cur_fug_x = cur_fug_x-1;
			chasing(cur_fug_x, cur_fug_y, &cha_x, &cha_y);
		}
		else if(shortest_visited[cur_fug_x][cur_fug_y+1] == k+1) {
			cur_fug_y = cur_fug_y+1;
			chasing(cur_fug_x, cur_fug_y, &cha_x, &cha_y);
		}
		else if(shortest_visited[cur_fug_x][cur_fug_y-1] == k+1) {
			cur_fug_y = cur_fug_y-1;
			chasing(cur_fug_x, cur_fug_y, &cha_x, &cha_y);
		}
	}

/*	while (1){
		printf("fug : (%d,%d) // cha : (%d,%d)\n", cur_fug_x, cur_fug_y, cur_cha_x, cur_cha_y);
		int result = chasing (&cur_fug_x, &cur_fug_y, &cur_cha_x, &cur_cha_y);
		if (result == 1){
			printf("succ\n");
			break;
		} else if (result == 2){
			printf("fail\n");
			break;
		}
	} */

	return 0;
}
