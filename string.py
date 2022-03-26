def words(s,q,word):# s -- строка, в которой выделяем слова, q -- набор разделителей, возвращает первое самое длинное слово в строке s согласно набору разделителй среди слов, длинне чем word
	stat=0   #в этой переменной сохраняется длина текущего слова
	i=0  #тндекс символа в строке
	while(True):# /цикл для перебора всех символов строки
		if(s[i] in q):# если очередной символ строки является разделителем
			if(stat>len(word)):#если s[i] -- это первый разделитель после слова, сравниваем длину предыдущего слова (длина которого накоплена в stat) с длиной слова, хранящегося в word
				word=s[i-stat:i]#если выделенное слово имеет длину, ольшую, чем word, вырезаем его из s и заменяем word на это слово
			stat=0 # дляследующего слова
		else:
			stat+=1  # если находимся внутри слова (текущий символ не является разделителем), увеличиваем длину
		i+=1 #переходим к следующему имволу строки s
		if(i==len(s)): #если символ s[i-1] был последним в строке s
			if stat>len(word): #если последнее слово имее длину, большую, чем wosd
				word=s[i-stat:i]
			break#//выходим из цикла
	return word

def search(SInputFile, q):
	f=open(SInputFile,"r")
	word=""
	for buf in f:
		word=words(buf,q,word)
	f.close()
	return word

def main():
	s="  22  yr\ny  g\t 2222222   wghghg5p5"
	print("Begin",s)
	word=words(s," \t\nw","")
	print('Resultfrom string  ',word,'len=',len(word))
	word=search("1.txt"," \t\n")
	print('Result from file',word,'len=',len(word))
	return 0

main() 