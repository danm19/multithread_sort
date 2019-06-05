#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 3
#define MAX_ELEMENTS 100000000

pthread_mutex_t trava;

int stop = 0;
int i = 0;
int qtde_num = 0;
int primo = 0;
int num_ordenados[MAX_ELEMENTS];

void* ordena(void *argumento){ // Função que verifica se um determinado número é primo ou não.

	int *v = (int *)argumento, x = 0, j = 0, pivo = 0, aux = 0;
	
	if ((qtde_num == 0 || qtde_num == 1)){
	   stop = 1;
	   return NULL;
	}
	
	j = qtde_num - 1;
	
	pthread_mutex_lock(&trava); 	
	while (num_ordenados[i] <= num_ordenados[j] && i != j)
		j--; 
	   if (num_ordenados[i] > num_ordenados[j]){
		aux = num_ordenados[i];
		num_ordenados[i] = num_ordenados[j]; //printf("teste j %d\n", j); 
		num_ordenados[j] = aux;

	   }
	   else 
		i++;
		
	if (i == qtde_num-1)
	   stop = 1;

	pthread_mutex_unlock(&trava); 

 	return NULL;

}

int main (){

	int pos = 0, k = 0, contador_aux, indice = 0, c;
	pthread_t thread[MAX_THREADS];

	indice = 0;

	while (scanf("%c ", &c) != (-1)){ 
		if ((c-'0') != (-4)){
		   num_ordenados[pos] = (c-'0');
		//printf("Valor: %d\n", num_ordenados[pos]);	
		pos++;    
		(qtde_num)++;
		}	
	}  
 
  
 
	 while (stop == 0){      
	  
	      if (indice < MAX_THREADS){ 	
		 pthread_create(&(thread[indice]), NULL, ordena, (void*)num_ordenados);
		 indice++;
	      }	
	      else{
		for (indice = 0; indice < MAX_THREADS; indice++) 
		    pthread_join(thread[indice],NULL);
	     	indice = 0;
	      } 
	}

	for (k = 0; k < indice; k++) 
	     pthread_join(thread[k],NULL); 
	
	for (k = 0; k < qtde_num ; k++){
	     printf("%d", num_ordenados[k]); 
  
	     if (k < qtde_num-1)
		printf(" ");
	}     
	printf ("\n");

	return 0;

}
