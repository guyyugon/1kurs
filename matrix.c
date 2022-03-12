#include <stdio.h>  
#include <stdlib.h>  
#include<time.h>

void pr(int **z,size_t n,size_t *m);//печать кривого массива
void del_string(int **, size_t *,size_t *n,  size_t k); //удаление строки с номером k
int **matrixget(size_t,size_t**);//выделение памяти под матрицу   единым куском
void del(int **a,size_t *);//освобождение памяти
void sort(int **z,size_t n,size_t *m);//сортировка строк по длине
int get_int(char *s, int *);//извлечение числа из строки, возвращает количество прочитанных байтов
int get_int(char *s, int *x){
	int pos;
	if(sscanf(s,"%d%n",x,&pos)==1)
		return pos;
	if(sscanf(s,"%s",s)==1) //ошибка 
		return -1;
	return 0;
}

void sort(int **z,size_t n,size_t *m){
        for(size_t i=0;i<n;i++)
		for(size_t j=1;j<n;j++){
			if(m[j-1]>m[j]){
				int *tmp=z[j-1],t=m[j-1];
				z[j-1]=z[j];m[j-1]=m[j];
				z[j]=tmp;m[j]=t;
			}
	}
}
int **matrixget(size_t n,size_t **m){ //возвращает матрицу (n -- количество строк, m -- массив их длин), заполненную случайными целыми
	int **a;
	size_t *b=(size_t *)malloc(n*sizeof(size_t)),k=0; //в этом массиве сохраняемдлины строк кривой матрицы
	for(size_t i=0;i<n;i++){
		b[i]=rand()%11; //сделаем длины случайными
		k+=b[i];//чтобы выделить память под хранение матрицы единым куском, нужно знать общее количесьтво чисел
	}
	a=(int **)malloc(n*sizeof(int *)+k*sizeof(int)); //запрашиваем память под размещение n указателей
	a[0]=(int *)(a+n); //разметка паияти
	for(size_t i=1;i<n;i++)
		a[i]= a[i-1]+b[i-1];

	for(size_t i=0;i<n;i++)
		for(size_t j=0;j<b[i];j++)
			a[i][j]=rand()%11;
	*m=b;
	return a;
}
void del_string(int **a, size_t *b,size_t *n, size_t k){
	for(size_t i=k;i<*n-1;i++){
		a[i]=a[i+1];
		b[i]=b[i+1];
	}
	(*n)--;
}

void pr(int **z,size_t n,size_t *m){
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<m[i];j++)
			printf("%d ",z[i][j]); 
		printf("\n");
	}
}
void del(int **a,size_t *m){
	free(a);free(m);
}
int main(void){ 
	int **matrix=NULL,x,pos;
	size_t n=4,*m=NULL;
	char buf[]="  \t  51 \n   23   -4",*str=buf;
	while(pos=get_int(str,&x),pos){
		if(pos==-1){
			puts("Err");
			break;
		}
		printf("%d ",x);
		str+=pos;
	}
	srand(time(NULL));
	matrix=matrixget(n,&m);
	puts("\nBegin");
	pr(matrix,n,m);
//        del_string(matrix,m,&n,1);
	puts("Sort");         
	sort(matrix,n,m);
	pr(matrix,n,m);
	del(matrix,m);
	return 0;
}
 