#include <stdio.h>  
#include <stdlib.h>  
#include<time.h>

//разлтчные способы хранения 2-мерного массива
#define N 4

void pri(int [N][N],size_t n,size_t m); //печать матрицы, заданной как массив массивов, количество столбцов нельзя опустить
void pr(int **z,size_t n,size_t m);//печать матриц, которые хранятся как массив указателей (адресов  целочисленных массивов)
void del_string(int **, size_t *n,  size_t k); //удаление строки с номером k
int **matrixget(size_t,size_t);//кусочно-динамическое выделение памяти под матрицу
void del(int **a, size_t n);//освобождение памяти

void del_string(int **a, size_t *n, size_t k){
	free(a[k]);
	for(size_t i=k;i<*n-1;i++)
		a[i]=a[i+1];
	(*n)--;
}

void pri(int z[][N],size_t n,size_t m){
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<m;j++)
			printf("%d ",z[i][j]); // z[i][j] <---> *(*(z+i)+j)
		printf("\n");
	}
}

void pr(int **z,size_t n,size_t m){
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<m;j++)
			printf("%d ",z[i][j]); //  *(*(z+i)+j)
		printf("\n");
	}
}
int **matrixget(size_t n,size_t m){ //возвращает матрицу (n строк, m столбцов), заполненную случайными целыми
	int **a;
	a=(int **)malloc(n*sizeof(int *)); //запрашиваем память под размещение n указателей
	for(size_t i=0;i<n;i++)
		a[i]=(int *)malloc(m*sizeof(int));//запрашиваем память под каждую строку (из m целых)
	for(size_t i=0;i<n;i++)
		for(size_t j=0;j<m;j++)
			a[i][j]=rand()%11;
	return a;
}
void del(int **a, size_t n){
	for(size_t i=0;i<n;i++)
		free(a[i]);
	free(a);
}
int main(void){ 
	int b[][N]={{1,2,3},{4,5,6}};  // 1 способ хранения 2-мерного массива (массив из2элементов, каждый элемент является массивом из N int
	int a1[]={1,2,3},a2[]={3,4,5},*a[]={a1,a2};//2 способ - как массив указателей на int
	int **matrix;
	size_t n=3,m=4;
	puts("First");
	pri(b,2,3);//если размеры матрицы ограничены можно использовать часть большой матрицы, выделив место статически   
	puts("Second");
	pr(a,2,3);
	srand(time(NULL));
	matrix=matrixget(n,m);// массив указателей на int + память выделяем динамически
	puts("Begin");
	pr(matrix,n,m);
        del_string(matrix,&n,1);
	puts("Del String");
	pr(matrix,n,m);
	del(matrix,n);
	return 0;
}
 