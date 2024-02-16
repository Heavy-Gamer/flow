#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int size;
	int** matrics;

} Params;

void* opredel(void* arg){
	Params param = *((Params*)arg);
	int size = param.size;
	//написать циклы для решения матрицы;
	int iter = 0;
	int element = 0;
	int second = 0;
	int glav_str = 0;
	int stol = 0;
	while(iter != size){
		for(int i=1; i < size; i++){
			element = param.matrics[i][second];
			param.matrics[i][second] = param.matrics[i][second] - element * param.matrics[glav_str][stol];
			stol++;
		}
		second++;
		glav_str++;
		iter++;
	}


	int opredel = 1;
	for(int i = 0; i < size; i++){
		opredel = param.matrics[i][i] * opredel; 
	}

	printf("Определитель матрицы равен: %d\n", opredel);
	return opredel;
}



int main(int argc,char* argv[]){
	//открытие файла
	FILE* file = fopen("matriza.txt", "r");
	fseek(file, 0, SEEK_END);
	int a = ftell(file);
	fseek(file, 0, SEEK_SET);

	//массив в строке
	char* str = (char*)malloc(sizeof(char*) * a);
	fgets(str, a, file);
	//printf("str: %s\n", str);

	
	//размер матрицы
	int size = 0;
	for(int i = 0; i < a; i++){
		if(str[i] == '\t'){
			size = i;
			break;
		}
	}
	//printf("size = %d\n", size);


	//создаем матрицу
	int count = 0;
	int** matrics = malloc(sizeof(int*) * size);
	for(int i = 0; i < size; i++){
		matrics[i] = malloc(sizeof(int*) * size);
		for(int j = 0; j < size; j++){
			if(str[count] == '\t'){
				count++;
			}
				matrics[i][j] = (str[count] - 48);
				count++;
			}
		}
	//работа с потоком
	int count_thread = atoi(argv[1]);

	pthread_t* thread = (pthread_t*)malloc(count_thread*sizeof(pthread_t));
	
	for(int i = 0; i < count_thread; i++){
		Params* param = (Params*)malloc(sizeof(Params));
		param->size = size;
		param->matrics = matrics;
		pthread_create(&thread[i], NULL, opredel, param);
	}

	for(int i = 0; i < count_thread; i++){
		pthread_join(thread[i], (void*)&opredel);
	}
	return 0;
}
