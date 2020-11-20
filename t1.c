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

void printVec (int *vec, int n){ 
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
    srand ( time(NULL) ); 
    for (int i = n-1; i > 0; i--){ 
        int j = rand() % (i+1); 
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

void print_tabela(double *matrix){
    for(int i=0;i<7;i++){
        for(int j=0;j<5;j++){
            printf("%fs\t", *((matrix+i*5) + j));
        }
        printf("\n");
    }
}

int main (void){
    int casos[7]={1000,10000,100000,200000,300000,400000,500000};
    double time_cresc[7][5]={0}, time_dec[7][5]={0}, time_aleat[7][5]={0};
    
    for(int i=0;i<7;i++){
        printf("%d\n",*(casos+i));
        int *vec,*aux;
        clock_t t=0;
        vec=(int *)malloc(sizeof(int) * (*(casos+i)));
        aux=(int *)malloc(sizeof(int) * (*(casos+i)));

        aloca_vetor_cresc(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));
        
        t=clock();
        bubble(aux,*(casos+i));
        t=clock()-t;
        time_cresc[i][0]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        insertion(aux,*(casos+i));
        t=clock()-t;
        time_cresc[i][1]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        selection(aux,*(casos+i));
        t=clock()-t;
        time_cresc[i][2]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        mergesort(aux,0,*(casos+i));
        t=clock()-t;
        time_cresc[i][3]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        quicksort(aux,0,*(casos+i)-1);
        t=clock()-t;
        time_cresc[i][4]=((double)t)/CLOCKS_PER_SEC;
        
        printf("%fs %fs %fs %fs %fs \n", time_cresc[i][0], time_cresc[i][1], time_cresc[i][2], time_cresc[i][3], time_cresc[i][4]);

        ///printf("=================================================\n");
        
        aloca_vetor_decresc(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));

        t=clock();
        bubble(aux,*(casos+i));
        t=clock()-t;
        time_dec[i][0]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        insertion(aux,*(casos+i));
        t=clock()-t;
        time_dec[i][1]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        selection(aux,*(casos+i));
        t=clock()-t;
        time_dec[i][2]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        mergesort(aux,0,*(casos+i));
        t=clock()-t;
        time_dec[i][3]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        quicksort(aux,0,*(casos+i)-1);
        t=clock()-t;
        time_dec[i][4]=((double)t)/CLOCKS_PER_SEC;
        
        printf("%fs %fs %fs %fs %fs \n", time_dec[i][0], time_dec[i][1], time_dec[i][2], time_dec[i][3], time_dec[i][4]);

        ///printf("=================================================\n");
        
        randomize(vec,*(casos+i));
        copy_vec(vec,aux,*(casos+i));

        t=clock();
        bubble(aux,*(casos+i));
        t=clock()-t;
        time_aleat[i][0]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        insertion(aux,*(casos+i));
        t=clock()-t;
        time_aleat[i][1]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        selection(aux,*(casos+i));
        t=clock()-t;
        time_aleat[i][2]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        mergesort(aux,0,*(casos+i));
        t=clock()-t;
        time_aleat[i][3]=((double)t)/CLOCKS_PER_SEC;
        
        copy_vec(vec,aux,*(casos+i));
        t=clock();
        quicksort(aux,0,*(casos+i)-1);
        t=clock()-t;
        time_aleat[i][4]=((double)t)/CLOCKS_PER_SEC;
        
        printf("%fs %fs %fs %fs %fs \n", time_aleat[i][0], time_aleat[i][1], time_aleat[i][2], time_aleat[i][3], time_aleat[i][4]);
        printf("=================================================\n");
    
        free(vec);
        free(aux);
        ///break;
    }
    ///print_tabela(time_cresc);
    /*print_tabela(time_dec);
    print_tabela(time_aleat);*/
    
    return 0;
}