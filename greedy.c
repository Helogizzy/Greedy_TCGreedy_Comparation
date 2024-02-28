#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void greedy_class_distribution(int start_times[], int end_times[], int n, int* num_salas) {
    clock_t start_time = clock();

    int* salas_ocupadas = malloc(n * sizeof(int));
    *num_salas = 0; // Contador de salas

    while (n > 0) {
        int min_start = __INT_MAX__;
        int min_index = -1;

        for (int j = 0; j < n; j++) {
            if (start_times[j] < min_start) {
                min_start = start_times[j];
                min_index = j;
            }
        }

        int sala_sequencial = -1;
        for (int j = 0; j < *num_salas; j++) {
            if (salas_ocupadas[j] <= start_times[min_index]) {
                sala_sequencial = j;
                break;
            }
        }

        if (sala_sequencial == -1) {
            salas_ocupadas[(*num_salas)++] = end_times[min_index];
            sala_sequencial = *num_salas - 1;
        } else {
            salas_ocupadas[sala_sequencial] = end_times[min_index];
        }

        for (int i = min_index; i < n - 1; i++) {
            start_times[i] = start_times[i + 1];
            end_times[i] = end_times[i + 1];
        }

        n--;
    }

    free(salas_ocupadas);

    clock_t end_time = clock();
    double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

void ler_e_salvar_vetores(const char* nome_arquivo, int** start_times, int** end_times, int* n) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }

    *n = 0;
    int* combined_array = malloc(sizeof(int));

    while (fscanf(file, "%d", &combined_array[*n]) == 1) {
        (*n)++;
        combined_array = realloc(combined_array, (*n + 1) * sizeof(int));
    }

    fclose(file);

    *start_times = malloc((*n / 2) * sizeof(int));
    *end_times = malloc((*n / 2) * sizeof(int));

    for (int i = 0; i < *n / 2; i++) {
        (*start_times)[i] = combined_array[i];
        (*end_times)[i] = combined_array[i + (*n / 2)];
    }

    free(combined_array);
}


int main() {
   const char* nome_arquivo[] = {"Aula1000000.txt"};
    int* start_times;
    int* end_times;
    int n;

    for (int arquivo_idx = 0; arquivo_idx < sizeof(nome_arquivo) / sizeof(nome_arquivo[0]); arquivo_idx++) {
        printf("**************************ARQUIVO %s****************************\n", nome_arquivo[arquivo_idx]);
        
        for (int execucao = 1; execucao <= 5; execucao++) {
            ler_e_salvar_vetores(nome_arquivo[arquivo_idx], &start_times, &end_times, &n);

            printf("\nExecução %d - Alocação de salas:\n", execucao);

            int num_salas;
            greedy_class_distribution(start_times, end_times, n / 2, &num_salas);

            printf("Número de salas alocadas: %d\n", num_salas);

            free(start_times);
            free(end_times);
        }
    }

    return 0;
}
