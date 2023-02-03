#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int det = 0;
int sign = 1;

void freeMat(int n, int** mat){
    for(int i = 0; i < n; i ++){
        free(mat[i]);
    }
    free(mat);
}

void printMat(int** mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//function to construct the submatrix of matrix with the (0,j)-th col-row removed
void cofactor(int n, int** matrix, int** ijElim, int col){
    int x = 0;
    int y = 0;
    for(int i = 0; i < n; i ++) {
        if(i!=0){
            for(int j = 0; j < n; j++) {
                if(j!=col) {
                    ijElim[x][y] = matrix[i][j];
                    y++;
                }
            }
            x++;
            y=0;
        }
    }
}



int determinant(int n, int** matrix){
    int i,j, sign = 1, det = 0; int**ijElim;
    if(n==1){
        return matrix[0][0];
    } else if (n==2){
        return (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);
    } else {
        for(i = 0; i < n; i++){
            ijElim = malloc((n-1)*sizeof(int*));
            for(j = 0; j < n-1; j++){
                ijElim[j] = malloc((n-1)*sizeof(int));
            }
            cofactor(n,matrix,ijElim,i);
            det+= sign*matrix[0][i]*determinant(n-1,ijElim);
            sign*=-1;
            freeMat(n-1,ijElim);
        }
    }
    return det;
}

int main(int argc, char* argv[argc+1]){

    //declare file and variables
    FILE* fPointer;
    fPointer = fopen(argv[1],"r");
    int n;
    fscanf(fPointer, "%d", &n);
    int entry;

    //delcare array
    int** matrix;
    matrix = malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(n*sizeof(int));
    }

    //initialize the values in the array
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(fPointer, "%d", &entry);
            matrix[i][j] = entry;
        }
    }

    //run and print method
    int num = determinant(n, matrix);
    printf("%d\n",num);

    //free memory allocated by matrix
    freeMat(n, matrix);
    
}
