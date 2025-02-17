#include "estrutura.h"

void inicializarCaixas(Caixa caixas[NUM_CAIXAS]) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        caixas[i].id = i + 1;
        caixas[i].aberto = true; 
        caixas[i].fila = NULL;
    }
}

Cliente* criarCliente() {
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    if (novoCliente == NULL) {
        puts("Erro ao alocar memória para o cliente");
        return NULL;
    }

    printf("Informe o nome do cliente: ");
    fgets(novoCliente->nome, 100, stdin);
    int aux = strlen(novoCliente->nome) - 1;
    if (novoCliente->nome[aux] == '\n') novoCliente->nome[aux] = '\0'; 

    printf("Informe o CPF do cliente: ");
    fgets(novoCliente->cpf, 12, stdin);
    aux = strlen(novoCliente->cpf) - 1;
    if (novoCliente->cpf[aux] == '\n') novoCliente->cpf[aux] = '\0';  

    printf("Informe a prioridade do cliente (1 = alta, 2 = média, 3 = baixa): ");
    scanf("%d", &novoCliente->prioridade);
    printf("Informe a quantidade de itens do cliente: ");
    scanf("%d", &novoCliente->itens);
    getchar(); 

    novoCliente->proximo = NULL;
    return novoCliente;
}

void inserirClienteNaFila(Caixa *caixa, Cliente *cliente) {
    if (caixa->fila == NULL) {
        caixa->fila = cliente;
    } else {
        Cliente *atual = caixa->fila;
        Cliente *anterior = NULL;
       
        while (atual != NULL && atual->prioridade <= cliente->prioridade) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL) { 
            cliente->proximo = caixa->fila;
            caixa->fila = cliente;
        } else { 
            anterior->proximo = cliente;
            cliente->proximo = atual;
        }
    }
}

void cadastrarCliente(Caixa caixas[NUM_CAIXAS]) {
    Cliente *novoCliente = criarCliente();
    if (novoCliente == NULL) return;

    int caixaEscolhido;
    do {
        printf("Informe o número do caixa (1 a %d) para adicionar o cliente: ", NUM_CAIXAS);
        scanf("%d", &caixaEscolhido);
        getchar();  // Limpa o buffer
    } while (caixaEscolhido < 1 || caixaEscolhido > NUM_CAIXAS || !caixas[caixaEscolhido - 1].aberto);

    inserirClienteNaFila(&caixas[caixaEscolhido - 1], novoCliente);
    printf("Cliente %s cadastrado com sucesso no caixa %d.\n", novoCliente->nome, caixaEscolhido);
}

void atenderCliente(Caixa caixas[NUM_CAIXAS]) {
    int caixaEscolhido;
    do {
        printf("Informe o número do caixa (1 a %d) para atendimento: ", NUM_CAIXAS);
        scanf("%d", &caixaEscolhido);
        getchar(); 
    } while (caixaEscolhido < 1 || caixaEscolhido > NUM_CAIXAS || !caixas[caixaEscolhido - 1].aberto);

    Caixa *caixa = &caixas[caixaEscolhido - 1];
    if (caixa->fila == NULL) {
        printf("Não há clientes na fila do caixa %d.\n", caixaEscolhido);
        return;
    }

    Cliente *clienteAtendido = caixa->fila;
    caixa->fila = clienteAtendido->proximo; 
    printf("Cliente %s com CPF %s foi atendido no caixa %d.\n", clienteAtendido->nome, clienteAtendido->cpf, caixaEscolhido);
    free(clienteAtendido);
}

void abrirOuFecharCaixa(Caixa caixas[NUM_CAIXAS]) {
    int caixaEscolhido;

    int caixasAbertos = 0;
    for (int i = 0; i < NUM_CAIXAS; i++) {
        if (caixas[i].aberto) {
            caixasAbertos++;
        }
    }

    do {
        printf("Informe o número do caixa (1 a %d) para abrir/fechar: ", NUM_CAIXAS);
        scanf("%d", &caixaEscolhido);
        getchar();  
    } while (caixaEscolhido < 1 || caixaEscolhido > NUM_CAIXAS);

    Caixa *caixa = &caixas[caixaEscolhido - 1];

    if (caixa->aberto && caixasAbertos == 1) {
        printf("Não é possível fechar o caixa %d, pois pelo menos um caixa deve permanecer aberto.\n", caixaEscolhido);
        return;
    }

    if (caixa->aberto) {
        printf("Fechando o caixa %d...\n", caixaEscolhido);
        caixa->aberto = false;

        Cliente *clienteAtual = caixa->fila;
        while (clienteAtual != NULL) {
            Cliente *proximoCliente = clienteAtual->proximo;

            int menorFila = -1;
            int tamanhoMenorFila = INT_MAX;

            for (int i = 0; i < NUM_CAIXAS; i++) {
                if (caixas[i].aberto) {
                    int tamanhoFila = 0;
                    Cliente *temp = caixas[i].fila;
                    while (temp != NULL) {
                        tamanhoFila++;
                        temp = temp->proximo;
                    }

                    if (tamanhoFila < tamanhoMenorFila) {
                        menorFila = i;
                        tamanhoMenorFila = tamanhoFila;
                    }
                }
            }

            if (menorFila != -1) {
                clienteAtual->proximo = NULL;
                inserirClienteNaFila(&caixas[menorFila], clienteAtual);
                printf("Realocando cliente %s para o caixa %d.\n", clienteAtual->nome, caixas[menorFila].id);
            }

            clienteAtual = proximoCliente;
        }

        caixa->fila = NULL;

    } else {
        printf("Abrindo o caixa %d...\n", caixaEscolhido);
        caixa->aberto = true;
    }
}



void imprimirClientesEmEspera(Caixa caixas[NUM_CAIXAS]) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        printf("\nClientes no Caixa %d (%s):\n", caixas[i].id, caixas[i].aberto ? "Aberto" : "Fechado");
        if (caixas[i].fila == NULL) {
            printf("Nenhum cliente em espera.\n");
        } else {
            Cliente *clienteAtual = caixas[i].fila;
            while (clienteAtual != NULL) {
                printf("Nome: %s, CPF: %s, Prioridade: %d, Itens: %d\n", 
                        clienteAtual->nome, clienteAtual->cpf, clienteAtual->prioridade, clienteAtual->itens);
                clienteAtual = clienteAtual->proximo;
            }
        }
    }
}

void imprimirStatusCaixas(Caixa caixas[NUM_CAIXAS]) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        printf("Caixa %d: %s, Clientes na fila: %d\n", caixas[i].id, 
               caixas[i].aberto ? "Aberto" : "Fechado", 
               caixas[i].fila == NULL ? 0 : 1);
    }
}
