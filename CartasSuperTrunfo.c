#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar uma carta de cidade
typedef struct {
    char codigo[5];          // Código da carta (Ex: A01)
    char nome[50];           // Nome da cidade
    char estado[2];          // Estado (A-H)
    long long populacao;     // População da cidade
    double area;             // Área da cidade
    long long pib;           // PIB da cidade
    int pontosTuristicos;    // Número de pontos turísticos

    // Propriedades calculadas (Nível Aventureiro)
    double densidadePopulacional;
    double pibPerCapita;

    // Propriedade para comparação (Nível Mestre)
    double superPoder;
} Carta;

// Protótipos de funções
void cadastrarCarta(Carta *carta);
void calcularPropriedades(Carta *carta);
void exibirCarta(Carta carta);
void compararCartas(Carta carta1, Carta carta2);

int main() {
    setlocale(LC_ALL, "Portuguese");

    int numCartas;
    printf("Quantas cartas você deseja cadastrar? ");
    scanf("%d", &numCartas);
    getchar(); // Limpa buffer do teclado

    // Aloca dinamicamente array de cartas
    Carta *cartas = malloc(numCartas * sizeof(Carta));

    // Cadastro de cartas
    for (int i = 0; i < numCartas; i++) {
        printf("\n--- Cadastro da Carta %d ---\n", i+1);
        sprintf(cartas[i].codigo, "%c%02d", 'A' + (i/4), (i%4) + 1);
        strcpy(cartas[i].estado, cartas[i].codigo);
        cadastrarCarta(&cartas[i]);
        calcularPropriedades(&cartas[i]);
    }

    // Exibição das cartas
    printf("\n--- Cartas Cadastradas ---\n");
    for (int i = 0; i < numCartas; i++) {
        exibirCarta(cartas[i]);
    }

    // Comparação de cartas (Nível Mestre)
    if (numCartas >= 2) {
        printf("\n--- Comparação de Cartas ---\n");
        compararCartas(cartas[0], cartas[1]);
    }

    // Libera memória alocada
    free(cartas);

    return 0;
}

// Função para cadastrar uma carta
void cadastrarCarta(Carta *carta) {
    printf("Nome da cidade: ");
    fgets(carta->nome, sizeof(carta->nome), stdin);
    carta->nome[strcspn(carta->nome, "\n")] = 0; // Remove newline

    printf("População: ");
    scanf("%lld", &carta->populacao);

    printf("Área (km²): ");
    scanf("%lf", &carta->area);

    printf("PIB: ");
    scanf("%lld", &carta->pib);

    printf("Pontos Turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
    getchar(); // Limpa buffer do teclado
}

// Calcula propriedades derivadas
void calcularPropriedades(Carta *carta) {
    // Densidade populacional
    carta->densidadePopulacional = carta->populacao / carta->area;

    // PIB per capita
    carta->pibPerCapita = (double)carta->pib / carta->populacao;

    // Super poder (soma de todas as propriedades)
    carta->superPoder = carta->populacao + carta->area + 
                        carta->pib + carta->pontosTuristicos;
}

// Exibe detalhes de uma carta
void exibirCarta(Carta carta) {
    printf("\nCódigo: %s\n", carta.codigo);
    printf("Cidade: %s\n", carta.nome);
    printf("Estado: %s\n", carta.estado);
    printf("População: %lld\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: R$ %lld\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontosTuristicos);
    
    // Propriedades calculadas
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidadePopulacional);
    printf("PIB per Capita: R$ %.2f\n", carta.pibPerCapita);
    printf("Super Poder: %.2f\n", carta.superPoder);
}

// Compara duas cartas
void compararCartas(Carta carta1, Carta carta2) {
    printf("Comparação entre %s e %s:\n", carta1.nome, carta2.nome);

    // Comparações com base em diferentes propriedades
    printf("População: %s (%lld) x %s (%lld) - Vencedor: %s\n", 
           carta1.nome, carta1.populacao, 
           carta2.nome, carta2.populacao,
           carta1.populacao > carta2.populacao ? carta1.nome : carta2.nome);

    printf("Área: %s (%.2f km²) x %s (%.2f km²) - Vencedor: %s\n", 
           carta1.nome, carta1.area, 
           carta2.nome, carta2.area,
           carta1.area > carta2.area ? carta1.nome : carta2.nome);

    printf("Densidade Populacional: %s (%.2f hab/km²) x %s (%.2f hab/km²) - Vencedor: %s\n", 
           carta1.nome, carta1.densidadePopulacional, 
           carta2.nome, carta2.densidadePopulacional,
           carta1.densidadePopulacional < carta2.densidadePopulacional ? carta1.nome : carta2.nome);
}