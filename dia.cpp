#include "dia.hpp"
#include "compromisso.hpp"
#include <iomanip>

/*
Inicializa a lista de compromissos
*/
void inicializarDia(struct Dia &dia) {
    dia.inicio = dia.fim = nullptr;
    dia.tamanho = 0;
}

/*
Libera a memória utilizada pela lista
*/
void liberarDia(struct Dia &dia) {
    NodoDia *curr = dia.inicio;
    while (curr != nullptr) {
        NodoDia *aux = curr;
        curr = curr->proximo;
        delete aux;
    }
}

/* 
Insere um compromisso na lista
*/
void inserirCompromisso(struct Dia &dia, struct Compromisso &compromisso) {
    NodoDia *novoNodo = new NodoDia;
    novoNodo->proximo = nullptr;
    novoNodo->compromisso = compromisso;
    dia.tamanho++;
    if (dia.inicio == nullptr) { // A lista está inicialmente vazia
        dia.inicio = dia.fim = novoNodo;
    } else {
        dia.fim->proximo = novoNodo;
        dia.fim = novoNodo;
    }
}

/*
Remove um compromisso da lista
*/
bool removerCompromisso(struct Dia &dia, int hora, int minuto) {
    NodoDia *curr = dia.inicio;
    NodoDia *prev = dia.inicio;
    bool nodoDeletado = false;
    while (curr != nullptr && !nodoDeletado) { // Percorre a lista enquanto não encontrar o nó
        if (curr->compromisso.minuto == minuto && curr->compromisso.hora == hora) {
            if (curr == dia.inicio) {
                dia.inicio = curr->proximo;
            } else {
                prev->proximo = curr->proximo;
            }
            dia.tamanho--;
            delete curr;
            nodoDeletado = true;
        }
        prev = curr;
        curr = curr->proximo;
    }
    return nodoDeletado;
}

/*
Mostra todos os compromissos de um dia
*/
void displayDia(struct Dia &dia) {
    NodoDia *curr = dia.inicio;
    while (curr != nullptr) { // Percorre toda a lista
        cout << curr->compromisso.hora << "h" << curr->compromisso.minuto << "min - ";
        cout << curr->compromisso.descricao << endl;
        curr = curr->proximo;
    }
}

/*
Mostra os compromissos de um dia em um determinado horário (hora, minuto)
*/
void displayDiaPorHorario(struct Dia &dia, int hora, int minuto) {
    NodoDia *curr = dia.inicio;
    int contador = 0;
    while (curr != nullptr) { // Percorre toda a lista
        if (curr->compromisso.minuto == minuto && curr->compromisso.hora == hora) {
            cout << curr->compromisso.hora << "h" << curr->compromisso.minuto << "min - ";
            cout << curr->compromisso.descricao << std::endl;
            contador++;
        }
        curr = curr->proximo;
    }
    if (contador == 0) {
        cout << "Nenhum compromisso para a data/horario especificado." << endl;
    }
}
