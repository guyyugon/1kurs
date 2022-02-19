#include <stdio.h>  
#include <stdlib.h>  
#include<time.h>

void pr(int **z,size_t n,size_t m);//печать матриц, которые хранятся как массив указателей (адресов  целочисленных массивов)
void del_string(int **, size_t *n,  size_t k); //удаление строки с номером k
int **matrixget(size_t,size_t);//выделение памяти под матрицу   единым куском
void del(int **a);//освобождение памяти

int **matrixget(size_t n,size_t m){ //возвращает матрицу (n строк, m столбцов), заполненную случайными целыми
	int **a;
	a=(int **)malloc(n*sizeof(int *)+n*m*sizeof(int)); //запрашиваем память под размещение n указателей
	a[0]=(int *)(a+n);
	for(size_t i=1;i<n;i++)
		a[i]= a[i-1]+m;

	for(size_t i=0;i<n;i++)
		for(size_t j=0;j<m;j++)
			a[i][j]=rand()%11;
	return a;
}
void del_string(int **a, size_t *n, size_t k){
	for(size_t i=k;i<*n-1;i++)
		a[i]=a[i+1];
	(*n)--;
}

void pr(int **z,size_t n,size_t m){
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<m;j++)
			printf("%d ",z[i][j]); //  *(*(z+i)+j)
		printf("\n");
	}
}
void del(int **a){
	free(a);
}
int main(void){ 
	int **matrix;
	size_t n=4,m=5;
	srand(time(NULL));
	matrix=matrixget(n,m);
	puts("Begin");
	pr(matrix,n,m);
        del_string(matrix,&n,1);
	puts("Del String");
	pr(matrix,n,m);
	del(matrix);
	return 0;
}
 