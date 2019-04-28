#ifndef _AGENDA_
#define _AGENDA_

#include "dia.hpp"
#include "mes.hpp"
#include <iostream>

struct NodoAgenda {
    struct Mes mes; // Conteúdo da nodo para ficar modular (tipo: Mes)
    struct NodoAgenda *proximo;
};

struct Agenda {
    NodoAgenda *inicio;
    NodoAgenda *fim;
    int tamanho; // Número de meses (12)
};

// Funções definidas para a nossa agenda
void inicializarAgenda(struct Agenda &agenda);
void inserirAgenda(struct Agenda &agenda, struct Mes &mes);
void displayAgenda(struct Agenda &agenda);
void abrirAgenda(struct Agenda &agenda);
void fecharAgenda(struct Agenda &agenda);
void inserirAgenda(struct Agenda &agenda, Mes &mes);
void liberarAgenda(struct Agenda &agenda);
struct NodoAgenda* buscarAgenda(struct Agenda &agenda, int mes);

#endif