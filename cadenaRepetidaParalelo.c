#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(){
int n=1108251,contador, cadenaMasLarga=0,numeroHilos;
char A[n];
char temp,letra;

FILE *fp;
fp = fopen("Vibrio_cholerae.txt", "r");

for(int i=0;i<n;i++){
	A[i]=(char)fgetc(fp );
}
fclose(fp);

//printf("Ingrese numeros hilos: ");
//scanf("%d", &numeroHilos);
numeroHilos=4;
omp_set_num_threads(numeroHilos);

clock_t begin = clock();
#pragma omp parallel private(contador,temp) shared(cadenaMasLarga,letra)
{
	contador=0;
	temp='0';
	int threadID=omp_get_thread_num();
	int inicio=(float)threadID*(n/numeroHilos);
	int fin=(float)(threadID+1)*(n/numeroHilos);
	while(inicio!=0&&A[inicio]==A[inicio-1]){
		inicio--;
	}
	while(fin!=n&A[fin]==A[fin-1]){
		fin--;
	}
	//printf("threadId: %d, incio: %d, fin: %d,contador: %d, temp: %c\n",threadID,inicio,fin,contador,temp);
	for(int i=inicio;i<fin;i++){
		if(A[i]==temp){
			contador++;
		}else{
			if(contador>cadenaMasLarga){
				cadenaMasLarga=contador;
				letra=temp;
			}
			temp=A[i];
			contador=0;
		}
	}
}
clock_t end = clock();

double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

printf("Tiempo Paralelo: %f\n",time_spent);
printf("Cadena mas larga, letra: %c, repeticion: %d\n",letra,cadenaMasLarga+1);
}
