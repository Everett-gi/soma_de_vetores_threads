#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAM_VETOR 1000000
#define NUM_THREADS 4

// Variáveis globais
int vetor[TAM_VETOR];
long soma_total = 0;
pthread_mutex_t mutex_soma;

// Estrutura para passar dados para as threads
typedef struct {
    int inicio;
    int fim;
} DadosThread;

/******************************
 * FUNÇÃO EXECUTADA PELAS THREADS 
 ******************************/
void *soma_parcial(void *arg) {
    DadosThread *dados = (DadosThread *)arg;
    long soma_parcial = 0;
    
    // Processo: Calcula soma parcial do segmento
    for (int i = dados->inicio; i < dados->fim; i++) {
        soma_parcial += vetor[i];
    }
    
    // Seção crítica - atualiza a soma total
    pthread_mutex_lock(&mutex_soma);
    soma_total += soma_parcial;
    pthread_mutex_unlock(&mutex_soma);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    DadosThread dados[NUM_THREADS];
    int segmento = TAM_VETOR / NUM_THREADS;
    
    /******************************
     * INICIALIZAÇÃO
     ******************************/
    // 1. Inicializa o vetor com valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < TAM_VETOR; i++) {
        vetor[i] = rand() % 100;
    }
    
    // 2. Inicializa o mutex para controle da seção crítica
    pthread_mutex_init(&mutex_soma, NULL);
    
    /******************************
     * PROCESSAMENTO PARALELO
     ******************************/
    // 3. Cria as threads e divide o trabalho
    for (int i = 0; i < NUM_THREADS; i++) {
        dados[i].inicio = i * segmento;
        dados[i].fim = (i == NUM_THREADS - 1) ? TAM_VETOR : (i + 1) * segmento;
        
        pthread_create(&threads[i], NULL, soma_parcial, (void *)&dados[i]);
    }
    
    // 4. Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // 5. Libera recursos do mutex
    pthread_mutex_destroy(&mutex_soma);
    
    /******************************
     * VERIFICAÇÃO
     ******************************/
    // 6. Verificação sequencial (para validar o resultado)
    long soma_verificacao = 0;
    for (int i = 0; i < TAM_VETOR; i++) {
        soma_verificacao += vetor[i];
    }
    
    // 7. Exibe os resultados
    printf("Soma com threads: %ld\n", soma_total);
    printf("Soma verificacao: %ld\n", soma_verificacao);
    
    return 0;
}