#include <stdio.h> //пример к.р.1 
#include <stdlib.h>  
#include<time.h>

void pr(double **z,size_t n,size_t m);//печать матриц, которые хранятся как массив указателей (адресов  целочисленных массивов)
void del_string(double **, size_t *n,  size_t k); //удаление строки с номером k
double **matrixget(size_t,size_t);//выделение памяти под матрицу   единым куском
void del(double **a);//освобождение памяти
double ves(double *,size_t m); //возвращает вес строки
void task(double **a,size_t ,size_t); //переставить строки так, чтобы строки максимального веса стали последними и сохранили свой взаимный порядок, при этом остальные строки также должны сохранить взаимный порядок.

double ves(double *a,size_t m){ //для примера положим вес равным сумме элементов строки.
	double s=0;
	for(size_t i=0;i<m;i++)
		s+=a[i];
	return s;
}
/*
void task(double **a,size_t *n,size_t m){ //удаление строк максимального веса
	double s=ves(a[0],m);
	for(size_t i=1;i<*n;i++)
		if(ves(a[i],m)>s)
			s=ves(a[i],m);

	for(size_t i=0;i<*n;i++)
		if(ves(a[i],m)>=s){
			del_string(a,n,i);
			i--;
		}
}
*/
void task(double **a,size_t n,size_t m){
	double s=ves(a[0],m);   //находим максимальный вес троки
	for(size_t i=1;i<n;i++)
		if(ves(a[i],m)>s)
			s=ves(a[i],m);
			            //сортировка пузырьком, решающая задачу 
	for(size_t i=0;i<n;i++)//выполняем достаточное количество аз
		for(size_t j=1;j<n;j++) //проход пузырька
		if(ves(a[j-1],m)>=s && ves(a[j],m)<s){//меняем местами только такие элементы! Это обеспечит сдвиг в конец последней строки  максимального веса при сохранении взаимного порядка остальных
			double *tmp=a[j-1];
			a[j-1]=a[j];
			a[j]=tmp;
		}
}
double **matrixget(size_t n,size_t m){ //возвращает матрицу (n строк, m столбцов), заполненную случайными целыми
	double **a;
	a=(double **)malloc(n*sizeof(double *)+n*m*sizeof(double)); //запрашиваем память под размещение n указателей
	a[0]=(double *)(a+n);
	for(size_t i=1;i<n;i++)
		a[i]= a[i-1]+m;

	for(size_t i=0;i<n;i++)
		for(size_t j=0;j<m;j++)
			a[i][j]=rand()%4/10.+1;
	return a;
}
void del_string(double **a, size_t *n, size_t k){
	for(size_t i=k;i<*n-1;i++)
		a[i]=a[i+1];
	(*n)--;
}
void pr(double **z,size_t n,size_t m){
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<m;j++)
			printf("%lf ",z[i][j]); //  *(*(z+i)+j)
		printf("  ves=%lf\n",ves(z[i],m));
	}
}
void del(double **a){
	free(a);
}
int main(void){ 
	double **matrix;
	size_t n=6,m=2;
	srand(time(NULL));
	matrix=matrixget(n,m);
	puts("Begin");
	pr(matrix,n,m);
	task(matrix,n,m);
//        del_string(matrix,&n,1);
	puts("Del String");
	pr(matrix,n,m);
	del(matrix);
	return 0;
}
 