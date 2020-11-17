#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 500000

void troca(int *a, int *b){
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}
void printVec (int *vec, int n) 
{ 
    for (int i = 0; i < n; i++) 
        printf("%d ", *(vec+i)); 
    printf("\n"); 
}

void copy_vec(int *vec,int *aux,int size){
	for(int i=0;i<size;i++)
		*(aux+i)=*(vec+i);
}

void aloca_vetor_cresc(int *vec, int size){
    for(int i=0;i<size;i++)
        *(vec+i)=i;
}

void aloca_vetor_decresc(int *vec, int size){
    for(int i=0;i<size;i++)
        *(vec+i)=size-1-i;
}

void randomize ( int *vec, int n ) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        troca((vec+i), (vec+j)); 
    }
} 


void bubble(int *v,int n){
    int max;
    for(int i=0;i<n;i++){
        max=n-1-i;
        for(int j=0;j<max;j++){
            if(*(v+j)>*(v+j+1))
                troca((v+j),(v+j+1));
        }
    }
}

void insertion (int *v, int n){
    int j,x;
    for(int i=1;i<n;i++){ /*Tudo para trás do i já está ordenado. Por isso começa em i=1*/
        x=v[i]; /*auxiliar recebe o próximo valor*/
        for(j=i-1;j>=0 && v[j]>x;j--){ /*Verifica os valores antes da posição i. Ou seja, procura onde inserir o valor de x*/
            v[j+1]=v[j];
        }
        v[j+1]=x;
    }
}

void selection(int*v, int n){
    int maxj,max_valido;
    for (int i=0;i<n;i++){
        max_valido=n-i;
        maxj=0;
        for(int j=1;j<max_valido;j++){
            if(v[j]>v[maxj])
                maxj=j;
        }
        troca(&v[max_valido-1],&v[maxj]);
    }
}

void intercala(int *v, int comeco, int meio, int fim){
    int w[2*MAX];
    int i,j,k=0;
    i=comeco;
    j=meio;
    while(i<meio && j<fim){
        if(v[i]<v[j]){
            w[k]=v[i];
            i++;
        }else{
            w[k]=v[j];
            j++;
        }
        k++;
    }
    /*Jogar para dentro de W o que sobrou*/
    while(i<meio){
        w[k]=v[i];
        i++;
        k++;
    }
    while(j<fim){
        w[k]=v[j];
        j++;
        k++;
    }
    for(i=comeco;i<fim;i++){ /*Copia w de volta para v*/
        v[i]=w[i-comeco];
    }
}

void mergesort( int *v, int comeco,int fim){
    int meio;
    if(comeco<fim-1){
        meio=(comeco+fim)/2;
        mergesort(v,comeco,meio);
        mergesort(v,meio,fim);
        intercala(v,comeco,meio,fim);
    }
}

int separa(int *v, int comeco, int fim){
    int pivo=v[fim];
    int j=comeco,k;
    /*v[c:j-1]<=p<v[j;k]*/
    for(k=comeco;k<fim;k++){
        if(v[k]<=pivo){
            troca(&v[k],&v[j]);
            j++;
        }
    }
    troca(&v[j],&v[fim]);
    return j;
}

void quicksort(int *v,int comeco, int fim){
    int pivo;
    if(comeco<fim){
        pivo=separa(v,comeco,fim);
        quicksort(v,comeco,pivo-1);
        quicksort(v,pivo+1,fim);
    }
}

int main (void){
    int casos[7]={10,10000,100000,200000,300000,400000,500000};
    double tabela[7][5]={0};
    
    for(int i=0;i<7;i++){
        printf("%d\n",*(casos+i));
        int *vec,*aux;
        double time[5]={0};
        clock_t t=0;
        
        vec=(int *)malloc(sizeof(int) * (*(casos+i)));
        aux=(int *)malloc(sizeof(int) * (*(casos+i)));

        aloca_vetor_cresc(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));
        printVec(aux,*(casos+i));
        
        t=clock();
        bubble(aux,*(casos+i));
        t=clock()-t;
        time[0]=((double)t)/CLOCKS_PER_SEC;
        
        printVec(aux,*(casos+i));
        printf("%f\n", time[0]);

        printf("=================================================\n");
        
        aloca_vetor_decresc(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));
        printVec(aux,*(casos+i));
        bubble(aux,*(casos+i));
        printVec(aux,*(casos+i));
        
        printf("=================================================\n");
        
        randomize(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));
        printVec(aux,*(casos+i));
        bubble(aux,*(casos+i));
        printVec(aux,*(casos+i));
        
        free(vec);
        free(aux);
        break;
    }
    
    return 0;
}
