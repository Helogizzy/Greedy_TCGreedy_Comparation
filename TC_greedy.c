#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int arr1[], int arr2[], int left, int right) {
    if (left < right) {
        int pivotIndex = left + (right - left) / 2;
        int pivotValue = arr1[pivotIndex];
        int i = left, j = right;

        while (i <= j) {
            while (arr1[i] < pivotValue || (arr1[i] == pivotValue && arr2[i] < arr2[pivotIndex]))
                i++;
            while (arr1[j] > pivotValue || (arr1[j] == pivotValue && arr2[j] > arr2[pivotIndex]))
                j--;

            if (i <= j) {
                trocar(&arr1[i], &arr1[j]);
                trocar(&arr2[i], &arr2[j]);
                i++;
                j--;
            }
        }

        quick_sort(arr1, arr2, left, j);
        quick_sort(arr1, arr2, i, right);
    }
}

void greedy_class_distribution(int start_times[], int end_times[], int n, int* num_salas) {
    int* salas_ocupadas = malloc(n * sizeof(int));
    *num_salas = 0; // Contador de salas

    for (int i = 0; i < n; i++) {
        int sala_disponivel = -1;

        // Procura por sala disponível
        for (int j = 0; j < *num_salas; j++) {
            if (salas_ocupadas[j] <= start_times[i]) {
                sala_disponivel = j;
                break;
            }
        }

        // Se não houver sala disponível, cria uma nova sala
        if (sala_disponivel == -1) {
            salas_ocupadas[(*num_salas)++] = end_times[i];
            sala_disponivel = *num_salas - 1; // Índice da nova sala
        } else {
            salas_ocupadas[sala_disponivel] = end_times[i];
        }
    }

    free(salas_ocupadas);
}

void ler_e_salvar_vetores(const char* nome_arquivo, int** start_times, int** end_times, int* n) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }

    *n = 0;
    int* combined_array = malloc(sizeof(int));  // Combined array to store both vectors

    // Read each element from the file
    while (fscanf(file, "%d", &combined_array[*n]) == 1) {
        (*n)++;
        combined_array = realloc(combined_array, (*n + 1) * sizeof(int));
    }

    fclose(file);

    // Split the combined array into two separate arrays
    *start_times = malloc((*n / 2) * sizeof(int));
    *end_times = malloc((*n / 2) * sizeof(int));

    for (int i = 0; i < *n / 2; i++) {
        (*start_times)[i] = combined_array[i];
        (*end_times)[i] = combined_array[i + (*n / 2)];
    }

    free(combined_array);
}

void executar_greedy_e_medir_tempo(const char* nome_arquivo, int execucao) {
    int* start_times = NULL;
    int* end_times = NULL;
    int n = 0;

    ler_e_salvar_vetores(nome_arquivo, &start_times, &end_times, &n);

    clock_t inicio_total = clock();

    // Measure time for sorting
    clock_t inicio_ordenacao = clock();
    quick_sort(start_times, end_times, 0, n / 2 - 1); // Divide by 2 since it's split into two vectors
    clock_t fim_ordenacao = clock();

    // Measure time for greedy function
    clock_t inicio_greedy = clock();
    int num_salas;
    greedy_class_distribution(start_times, end_times, n / 2, &num_salas); // Divide by 2 since it's split into two vectors
    clock_t fim_greedy = clock();

    clock_t fim_total = clock();

    double tempo_ordenacao = ((double)(fim_ordenacao - inicio_ordenacao)) / CLOCKS_PER_SEC;
    double tempo_greedy = ((double)(fim_greedy - inicio_greedy)) / CLOCKS_PER_SEC;
    double tempo_total = ((double)(fim_total - inicio_total)) / CLOCKS_PER_SEC;

    printf("Execução %d do arquivo %s\n", execucao, nome_arquivo);
    printf("Tempo de ordenação: %f segundos\n", tempo_ordenacao);
    printf("Tempo de greedy: %f segundos\n", tempo_greedy);
    printf("Número de salas criadas: %d\n", num_salas);
    printf("Tempo total: %f segundos\n\n", tempo_total);

    free(start_times);
    free(end_times);
}

int main() {
    const char* arquivos[] = {"Aula10.txt", "Aula25.txt", "Aula50.txt", "Aula100.txt", "Aula200.txt", "Aula300.txt", "Aula500.txt", "Aula750.txt", "Aula1000.txt", "Aula1500.txt", "Aula2000.txt", "Aula2500.txt", "Aula5000.txt",
          "Aula7500.txt", "Aula10000.txt","Aula15000.txt", "Aula20000.txt", "Aula30000.txt", "Aula50000.txt","Aula75000.txt", "Aula100000.txt", "Aula150000.txt", "Aula250000.txt", 
          "Aula350000.txt", "Aula500000.txt","Aula750000.txt", "Aula1000000.txt"};

    for (int i = 0; i < sizeof(arquivos) / sizeof(arquivos[0]); i++) {
        for (int j = 1; j <= 5; j++) {
            executar_greedy_e_medir_tempo(arquivos[i], j);
        }
    }

    return 0;
}
