#include "estrutura.h"

int main() {
    Caixa caixas[NUM_CAIXAS];
    inicializarCaixas(caixas);

    int opcao = -1;

    while (opcao != 0) {
        system("clear");
        printf("\n--- Informe a opção que deseja ---\n");
        printf("0 - Sair do programa\n");
        printf("1 - Cadastrar um Cliente\n");
        printf("2 - Atender um Cliente\n");
        printf("3 - Abrir ou Fechar um Caixa\n");
        printf("4 - Imprimir a Lista de Clientes em Espera\n");
        printf("5 - Imprimir o Status dos Caixas\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do scanf

        switch (opcao) {
            case 1:
                cadastrarCliente(caixas);
                break;
            case 2:
                atenderCliente(caixas);
                break;
            case 3:
                abrirOuFecharCaixa(caixas);
                break;
            case 4:
                imprimirClientesEmEspera(caixas);
                break;
            case 5:
                imprimirStatusCaixas(caixas);
                break;
            case 0:
                puts("Saindo do programa...");
                break;
            default:
                puts("Opção inválida!");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}
