#include <stdio.h>  
#include <stdlib.h> 
#include<string.h>
#include<ctype.h>
void words(char *,const char *,char *); //поиск самого длинного слова, реализация перебором всех символов строки
void words(char *s,const char *q,char *word){//s -- строка, в которой выделяем слова, q -- набор разделителей, word -- буфер для сохранения самого длинного слова в строке
	unsigned int stat=0;//stat -- переменная, значение которой определяет статус символа в строке (находится он внутри или вне слова)
	while(1){ //цикл для перебора всех символов строки
		if(strchr(q,*s)){ //если очередной символ строки является разделителем
			if(stat>strlen(word)){//если *s -- это первый разделитель после слова, сравниваем длину предыдущего слова (длина которого накоплена в stat) с длиной слова, хранящегося в word
				strncpy(word,s-stat,stat);//если выделенное слово большей длины, копируем его в word
				word[stat]=0;//strncpy не выставляет конец строки, делаем это вручную
			}
			stat=0;//т.к. текущий символ является разделителем, обнуляем stat
		}
		else
			stat++; //т.к.  находимся внутри слова, увеличиваем количество составляющих слово букв
		if(*s==0) // если просмотр строки закончен
			break;//выходим из цикла
		s++;
	}
}
void search(const char *SInputFile, char *word); //поиск самого длинного слова в файле согласно набору разделителей  ,, .\t\n, использующий функцию words
void search(const char *SInputFile, char *word){
	FILE *in=fopen(SInputFile,"r");//открываем файл с заданным именем на чтение
	char buf[111]; //в этот буфер будем прочитывать строку файла
	word[0]=0;//начинаем со слова минимальной длины
	while(fgets(buf,111,in)!=NULL) //пока в файле остались символы, записываем очередную строку в буфер, при этом  текущее положение указателя внутри файла смещается к началу следующей строки
		words(buf,",, .\t\n",word);//режем строку по заданному набору разделителей и слово максимальной длины сохраняем в word
	fclose(in);
}
void search1(const char *SInputFile, char *word); //поиск самого длинного слова в файле согласно набору разделителей  ,, .\t\n, использующий стандартную функцию strtok
void search1(const char *SInputFile, char *word){
	FILE *in=fopen(SInputFile,"r");//открываем файл с заданным именем на чтение
	char buf[111]; //в этот буфер будем прочитывать строку файла
	word[0]=0;//начинаем со слова минимальной длины
	while(fgets(buf,111,in)!=NULL) //пока в файле остались символы, записываем очередную строку в буфер, при этом  текущее положение указателя внутри файла смещается к началу следующей строки
	for(char *begin=strtok(buf,",, .\t\n");begin;begin=strtok(NULL,",,. \t\n")) //перебираем слова строки buf
		if(strlen(begin)>strlen(word)) //если нашлось более длинное слово, чем word
			strcpy(word,begin); //обновляем word
	fclose(in);
}
void search2(const char *SInputFile, char *word);//поиск самого длинного слова файла, здесь под словом понимается участок строки между символами "
void search2(const char *SInputFile, char *word){
	FILE *in=fopen(SInputFile,"r");
	char buf[111],*begin,*end;
	memset(word,0,111);//это избавит нас от необходимости прописывать конец строки
	while(fgets(buf,111,in)!=NULL)
	for((begin=strchr(buf,'\"'),begin?end=strchr(begin+1,'\"'):NULL) //находим в строке, если это возможно, пару символов "
		;begin; //for будет работать, когда такая пара кавычек нашлась (т.е. можно выделить очередное слово в строке)
		(begin=strchr(end+1,'\"'),begin?end=strchr(begin+1,'\"'):NULL))//на следующей итерации for передвигаемся по строке и пытаемся выделить следующее слово
		if(end-begin-2>(int)strlen(word)) //если найденное слово длиннее word
			strncpy(word,begin+1,end-begin-1); //копируем его
	fclose(in);
}

int main(void){
	char word[111];
	char s[]="   yr\ny  g\t    ghghg    ";
	int k;
	for(char *begin=s;sscanf(begin,"%s%n",word,&k)==1;begin+=k) //выделение слов из строки с использованием sscanf
		puts(word);                //работает только для пробельных разделителей
        search2("1.txt",word);
	puts(word);
	return 0;
}
 