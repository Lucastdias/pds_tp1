#ifndef _DIA_
#define _DIA_

#include "compromisso.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

// Define an appointment node in a linked list
struct NodoDia {
    struct Compromisso compromisso;
    struct NodoDia *proximo;
};

// Define a linked list for appointments
struct Dia {
    struct NodoDia *inicio;
    struct NodoDia *fim;
    int tamanho;
};

// Functions provided for an appointment list
void inicializarDia(struct Dia &dia);
void liberarDia(struct Dia &dia);
void inserirCompromisso(struct Dia &dia, struct Compromisso &compromisso);
bool removerCompromisso(struct Dia &dia, int hora, int minuto);
void displayDia(struct Dia &dia);
void displayDiaPorHorario(struct Dia &dia, int hora, int minuto);

#endif
