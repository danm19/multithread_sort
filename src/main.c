#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 3	
#define MAX_ELEMENTS 60000

pthread_mutex_t trava;

int stop = 0;
int i = 0;
int qtde_num = 0;
int num_ordenados[MAX_ELEMENTS];

void* ordena(void *argumento){ 

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
		num_ordenados[i] = num_ordenados[j];
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

	int k = 0, n_thread = 0;
	pthread_t thread[MAX_THREADS];

	while (scanf("%d ", &num_ordenados[k]) != (-1)){ 	
		k++;    
		(qtde_num)++;
			
	}  
 
	 while (stop == 0){      
	  
	      if (n_thread < MAX_THREADS){ 	
		 pthread_create(&(thread[n_thread]), NULL, ordena, (void*)num_ordenados);
		 n_thread++;
	      }	
	      else{
		for (n_thread = 0; n_thread < MAX_THREADS; n_thread++) 
		    pthread_join(thread[n_thread],NULL);
	     	n_thread = 0;
	      } 
	}

	for (k = 0; k < n_thread; k++) 
	     pthread_join(thread[k],NULL); 
	
	for (k = 0; k < qtde_num ; k++){
	     printf("%d", num_ordenados[k]); 
  
	     if (k < qtde_num-1)
		printf(" ");
	}     
	printf ("\n");
	
	return 0;

}
