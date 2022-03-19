#include <stdio.h>  
#include <stdlib.h>  
#include<time.h>
#include<string.h>
#define N 11         // максимальное количество строк в файле
#define L 2          // минимально возможное значение отведенной памяти для работы fgets

int **matrixget(size_t *n,size_t **m,FILE *in);
void pr(int **z,size_t n,size_t *m);//печать кривого массива
void del_string(int **, size_t *,size_t *n,  size_t k); //удаление строки с номером k
void del(int **a,size_t *);//освобождение памяти
void sort(int **z,size_t n,size_t *m);//сортировка строк по длине
int get_int(char *s, int *);//извлечение числа из строки, возвращает количество прочитанных байтов
char * mygets(char *,size_t *, FILE *); //кусочное извлечение из файла строки неограниченной длины, адаптировано для извлечения всех строк с выделением и очисткой памяти внутри этой функции

char * mygets(char *s,size_t *Len, FILE *in){ //s -- строка, в которую надо прочитать, *Len -- размер ранее выделенной под s памяти 
	size_t begin=0; //позиция в s, с которой будет введена часть строки файла
	if(s==NULL){  //если память еще не выделялась, выделим L байт
		s=(char *)malloc(L);
		*Len=L;
	}	
	while(fgets(s+begin,*Len-begin,in)){//пытаемся прочитать максимально возможное (в смысле выделенного ресурса) количество байт из файла в строку s, начиная с позиции begin
		begin= *Len-1;//сместились по строке на ту позицию, с которой нужно запиывать кусок строки из файла на следующей итерации
		if(strchr(s,'\n')) //ищем, нет ли конца строки файла ('\n') в s, эту операции можно оптимизировать, просматривая строку не от начала, а только от (неизмененного) begin
			break;//если очередная строка файла полностью прочитана, выходим из цикла
		(*Len)*=2;//иначе  выделим  память под хранение следующего куска текущей строки
		s=(char *)realloc(s,*Len);
	}
	if(begin==0){ //это условие будет выполнено, только если из файла прочитано 0 байт, т.е. достигнут конец файла
		free(s);
		return NULL;
	}
	return s;
}
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
int **matrixget(size_t *n,size_t **m,FILE *in){ //возвращает матрицу, прочитанную из файла, (*n -- количество строк, m -- массив их длин), количество строк ограничено числом N, длины строк не ограничены
	int **a;
	size_t *b=(size_t *)malloc(N*sizeof(size_t)),k=0,len;
	char *buf=NULL,*str;
        int pos,x;
	a=(int **)malloc(N*sizeof(int *)); 
	while(buf=mygets(buf,&len,in),buf!=NULL){
		b[k]=0;
		a[k]=(int *)malloc(sizeof(int)*strlen(buf));
		str=buf;
		while(pos=get_int(str,&x),pos){
			if(pos==-1){
				puts("Err");
				break;
			}
			a[k][b[k]]=x;
			str+=pos;
			b[k]++;
		}
		k++;
	}
	*n=k;
	*m=b;
	return a;
}

void del_string(int **a, size_t *b,size_t *n, size_t k){ //здесь исправить утечку памяти
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
void del(int **a,size_t *m){ //необходимо исправить, т.к. матрица хранится неединым куском
	free(a);free(m);
}
int main(void){ 
	int **matrix=NULL;
	size_t n,*m=NULL;
	FILE *in=fopen("1.txt","r");
	matrix=matrixget(&n,&m,in);
	puts("\nBegin");
	pr(matrix,n,m);
//        del_string(matrix,m,&n,1);
	puts("Sort");         
	sort(matrix,n,m);
	pr(matrix,n,m);
	for(size_t i=0;i<n;i++) //перенести этуоперацию в del
		free(matrix[i]);
	del(matrix,m);
	fclose(in);
	return 0;
}
 