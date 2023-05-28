#include <stdio.h>
#include <stdlib.h>
int check(int **A, int N){
	int odd_vertex = 0;
	for (int i = 0; i < N; i++){
		int count = 0;
		for (int j = 0; j < N; j++){
			if (*(*(A+i)+j) == 1 ){
				count++;
			}
		}
		if (count == 1 || count %2 != 0){
			printf("\n%d is odd vertex",i);
			odd_vertex++;
		}
	}
	if (odd_vertex == 2 ){
		printf("\nThe graph has path\n");
		return 1;
	}else if (odd_vertex == 0){
		printf("\nThe graph has circuit\n");
		return 0;
	}
}

int check_nonBridge(int **A, int N, int SV, int j) {
            if (*(*(A+SV)+j) == 1) {
                int count1 = 0;
                int count2 = 0;

                int *queue = (int *)malloc(N * sizeof(int));
                int front = 0, rear = 0;
                int *visited = (int *)malloc(N * sizeof(int));

                for (int k = 0; k < N; k++) {
                    visited[k] = 0;
                }
                visited[SV] = 1;
                queue[rear++] = SV;

                while (front != rear) {
                    int u = queue[front++];
                    for (int v = 0; v < N; v++) {
                        if (*(*(A+u)+v) == 1 && !visited[v]) {
                            visited[v] = 1;
                            count1++;
                            queue[rear++] = v;
                        }
                    }
                }

                A[SV][j] = 0;
				A[j][SV] = 0;
				
				front = 0, rear = 0;
                for (int k = 0; k < N; k++) {
                    visited[k] = 0;
                }
                visited[SV] = 1;
                queue[rear++] = SV;

                while (front != rear) {
                    int u = queue[front++];
                    for (int v = 0; v < N; v++) {
                        if (*(*(A+u)+v) == 1 && !visited[v]) {
                            visited[v] = 1;
                            count2++;
                            queue[rear++] = v;
                        }
                    }
                }
				A[SV][j] = 1;
				A[j][SV] = 1;
                free(queue);
                free(visited);

                if (count1 > count2 ) {
                    return 1;
                }else {
                	return 0;
				}
            }
    return 0;
}
void print_Fleury(int **A, int N, int SV, int **visited) {
    int bridge = 0;
    printf("%d ", SV);
    for (int j = 0; j < N; j++) {
        if (*(*(A+SV)+j) == 1 && !visited[SV][j] && !visited[j][SV]) {
            if (check_nonBridge(A, N, SV, j) == 1) {
                visited[SV][j] = 2;
                visited[j][SV] = 2;
                bridge = j;
            } else {
                visited[SV][j] = 1;
                visited[j][SV] = 1;
                print_Fleury(A, N, j, visited);
            }
        } else if (*(*(A+SV)+j) == 1 && visited[SV][j] == 2 && visited[j][SV] == 2) {
            visited[SV][j] = 1;
            visited[j][SV] = 1;
            bridge = j;
            print_Fleury(A, N, bridge, visited);
        }
    }
    if (bridge != 0) {
        visited[SV][bridge] = 1;
        visited[bridge][SV] = 1;
        print_Fleury(A, N, bridge, visited);
    }
}

void Fleury(int **A, int N) {
    int SV = 0;
    int isPath = check(A, N);

    if (isPath == 1) {
        printf("\nInput the starting odd vertex: ");
        scanf("%d", &SV);
    }
    int **visited = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++){
		*(visited+i) = (int*)malloc(N * sizeof(int));
		for(int j = 0; j < N; j++){
			visited[i][j] = 0;
		}
	}

    print_Fleury(A, N, SV, visited);
    for (int i = 0; i < N; i++) {
	    free(visited[i]);
	}
	free(visited);

}

//void Check_Hierholzer(int **A, int N, int *stack, int &top, int SV){
//	int curr = SV;
//	for (int next = 0; next < N; next++) {
//        if (A[curr][next] == 1) {
//            A[curr][next] = 0;
//            A[next][curr] = 0;
//            stack[top++] = next;
//            Check_Hierholzer(A, N, stack, top, next);
//        }
//	}
//}

void Hierholzer(int **A, int N) {
    int SV = 0;
    int *stack = (int*)malloc(N * sizeof(int));
    int top = 0;
    int *CS = (int*)malloc(N * sizeof(int));
    int topCS = 0;
    printf("\nInput vertex to start: ");
    scanf("%d", &SV);
    stack[top++] = SV;
//    Check_Hierholzer(A, N, stack, top, SV);
    
    while (top != 0) {
        int curr = stack[--top];
//        int connect = 0;
        for (int next = 0; next < N; next++) {
            if (A[curr][next] == 1) {
                A[curr][next] = 0;
                A[next][curr] = 0;
                stack[top++] = next;
//                connect = 1;
//                break;
            }else{
            	CS[topCS++] = curr;
			}
        }
//    	if(connect == 0){
//    		CS[topCS++] = curr;
//		}
    }
    while (topCS != 0){
    	int curr = CS[--topCS];
    	printf("%d ", curr);
	}
	free(stack);
	free(CS);
}

int main(){
	int N, **A;
	char input[] = "input5.txt";
	FILE *file = fopen(input, "r");
	fscanf(file, "%d", &N);
	A = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++){
		*(A+i) = (int*)malloc(N * sizeof(int));
		for(int j = 0; j < N; j++){
			fscanf(file, "%d", *(A+i)+j);
		}
	}
	fclose(file);
	printf("%d\n ", N);
	for (int i = 0; i < N; i++){
		printf(" %d", i);
	}
	for (int i = 0; i < N; i++){
		printf("\n%d ",i);
		for(int j = 0; j < N; j++){
			printf("%d ", *(*(A+i)+j));
		}
	}
	
	Fleury(A, N);
	Hierholzer(A, N);
	
	for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
}