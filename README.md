# Greedy_TCGreedy_Comparation
>Colaboradoras: [Eduarda Elger](https://github.com/EduardaElger), [Ellen Bonafin](https://github.com/EllenBonafin) e [Heloisa Alves](https://github.com/Helogizzy)

## Sobre
Trabalho de Projeto e Análise de Algortimos com a finalidade de resolver o problema de alocação de salas usando duas estratégias distintas: Greddy e TC Greedy, e avaliar o comportamento e impacto computacional dos métodos perante conjuntos de testes com diferentes tamanhos. Durante a execução dos testes o critério de análise será a compexidade do algoritmo e o tempo cronológico gasto para a execução dos métodos.

### Greedy
um algoritmo guloso para alocar salas de aula para a realização de aulas, utilizando os tempos de início e término das mesmas como critério. Entretanto, é importante destacar que este algoritmo não segue uma ordenação específica. Na busca pela próxima aula a ser alocada, ele seleciona aquela com o menor tempo de início, sem considerar a ordem das aulas no array.

### TC Greedy
O código implementa o QuickSort para ordenar os tempos de início e término das aulas, proporcionando uma base organizada para a distribuição subsequente. Ele é aplicado como uma etapa preliminar, considerando tanto os tempos de início quanto os de término, evitando conflitos em casos de horários de início iguais. Posteriormente, o algoritmo guloso aloca as aulas nas salas de aula de maneira a minimizar o número total de salas utilizadas, garantindo assim uma distribuição otimizada dos horários disponíveis.

## Testes
A fim de avaliar o impacto no tempo de processamento dos algoritmos, foi feita a leitura dos vetores de entrada, cada um deles recebeu testes com vetores de tamanhos: 10, 25, 50, 100, 200, 300, 500, 750, 1000, 1500, 2000, 2500, 5000, 7500, 10000, 15000, 20000, 30000, 50000, 75000, 100000, 150000, 250000, 350000, 500000, 750000 e 1000000.
