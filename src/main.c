#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_AUX 5000
#define MAX_THREADS 2	
#define MAX_ELEMENTS 60000
#define divisor 3

int stop = 0;
double qtde_num = 0;
int num_ordenados[MAX_ELEMENTS];
int x = 0;

void* ordena(void *argumento){ 

	int i = *(int *)argumento, j = 0, aux = 0;

	if ((qtde_num == 0 || qtde_num == 1) || i == qtde_num-1){
	   stop = 1;
	   return NULL;
	}	
	
	j = i + (x-1);

	while (i != j){
	   while (num_ordenados[i] <= num_ordenados[j] && i != j)
              j--; 
	  
	   if (num_ordenados[i] > num_ordenados[j]){
              aux = num_ordenados[i];
              num_ordenados[i] = num_ordenados[j];
	      num_ordenados[j] = aux;
	   }
	}
	
	if (i + x >= qtde_num)
           stop = 1;

 	return NULL;
}

void intercala (){

	int i = 0, j = (qtde_num-1), aux = 0;
	
	while (i != j){
	   while (num_ordenados[i] <= num_ordenados[j] && i != j)
	      j--; 
        
	   if (num_ordenados[i] > num_ordenados[j]){
              aux = num_ordenados[i];
	      num_ordenados[i] = num_ordenados[j];
	      num_ordenados[j] = aux;
	    }
	   
	    if (i == j){
	      i++;
	      j = (qtde_num-1);
	    }			   
        }
}

int main (){

	int k = 0, n_thread = 0, indice = 0, aux[MAX_AUX];
	pthread_t thread[MAX_THREADS];

	while (scanf("%d ", &num_ordenados[k]) != (-1)){ 	
	   k++;    
	   (qtde_num)++;		
	}  

        x = (qtde_num/divisor);

	while (stop == 0){      	  
	   if (n_thread < MAX_THREADS){ 	
	      aux[indice] = (x*indice);
	      pthread_create(&(thread[n_thread]), NULL, ordena, &aux[indice]);
	      n_thread++;
	      indice++;
	   }	

	   else{
	      for (n_thread = 0; n_thread < MAX_THREADS; n_thread++) 
	         pthread_join(thread[n_thread],NULL);   
	      n_thread = 0;
	      } 
	}

	for (k = 0; k < n_thread; k++) 
	   pthread_join(thread[k],NULL); 

	intercala ();
	
	for (k = 0; k < qtde_num ; k++){
	   printf("%d", num_ordenados[k]); 
  
	   if (k < qtde_num-1)
	      printf(" ");
	}     
	
	printf ("\n");
	
	return 0;
}
