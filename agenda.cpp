#include "agenda.hpp"
#include "dia.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

/*
Inicializa a agenda inserindo todos os 12 meses com listas de compromissos vazias
*/
void inicializarAgenda(struct Agenda &agenda) {
    agenda.inicio = agenda.fim = nullptr;
    agenda.tamanho = 0;
    int diasNoMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i = 1;
    while (i <= 12) {
        struct Mes mes;
        mes.idMes = i;
        mes.dias = diasNoMes[i];
        mes.listaCompromissos = new Dia[mes.dias + 1];
        for (int j = 0; j <= mes.dias; j++) {
            inicializarDia(mes.listaCompromissos[j]);
        }
        inserirAgenda(agenda, mes);
        i++;
    }
}

void inserirAgenda(struct Agenda &agenda, struct Mes &mes) {
    NodoAgenda *novoNodo = new NodoAgenda;
    novoNodo->mes = mes;
    novoNodo->proximo = nullptr;
    agenda.tamanho++;
    if (agenda.inicio == nullptr) { // Primeiro mês
        agenda.inicio = novoNodo;
        agenda.fim = novoNodo;
    } else {
        agenda.fim->proximo = novoNodo;
        agenda.fim = novoNodo;
    }
}

/*
Recupera o estado da agenda a partir de um arquivo
*/
void abrirAgenda(Agenda &agenda) {
    ifstream arquivo;
    arquivo.open("agenda.txt");
    string linhaAgenda = "";
    while (getline(arquivo, linhaAgenda)) {
        istringstream analizador(linhaAgenda);
        string campo;
        int contador, mes, dia, hora, minuto;
        contador = mes = dia = hora = minuto = 0;
        string descricao;
        while (getline(analizador, campo, ';')) {
            if (contador == 0) {
                istringstream(campo) >> mes;
            } else if (contador == 1) {
                istringstream(campo) >> dia;
            }
            else if (contador == 2) {
                istringstream(campo) >> hora;
            }
            else if (contador == 3) {
                istringstream(campo) >> minuto;
            } else {
                descricao = campo;
            }
            contador++;
        }
        Compromisso compromisso {.hora=hora, .minuto=minuto, .descricao=descricao};
        NodoAgenda *nodoMes = buscarAgenda(agenda, mes);
        inserirCompromisso(nodoMes->mes.listaCompromissos[dia], compromisso);
    }
    arquivo.close();
}

/*
Fecha a agenda e salva as alteracoes
*/
void fecharAgenda(Agenda &agenda) {
    ofstream arquivo;
    arquivo.open("agenda.txt");

    NodoAgenda *nodoMes = agenda.inicio;
    while (nodoMes != nullptr) {
        struct Mes mes = nodoMes->mes;
        int dias = mes.dias;

        int i = 1;
        while (i <= dias) {
            struct Dia dia = mes.listaCompromissos[i];
            struct NodoDia *nodoDia = dia.inicio;
            while (nodoDia != nullptr) {
                arquivo << mes.idMes << ";" << i << ";" << nodoDia->compromisso.hora << ";";
                arquivo << nodoDia->compromisso.minuto << ";" << nodoDia->compromisso.descricao;
                arquivo << endl;
                nodoDia = nodoDia->proximo;
            }
            i++;
        }
        nodoMes = nodoMes->proximo;
    }
    arquivo.close();
}

/*
Libera os recursos alocados para a agenda
*/
void liberarAgenda(struct Agenda &agenda) {
    NodoAgenda *curr = agenda.inicio;
    while (curr != nullptr) {
        NodoAgenda *aux = curr;
        for (int i = 0; i <= aux->mes.dias; i++) {
            liberarDia(aux->mes.listaCompromissos[i]);
        }
        curr = curr->proximo;
        delete [] aux->mes.listaCompromissos;
        delete aux;
    }
}

/*
Busca um nó na agenda (um mês, nesse caso)
*/
struct NodoAgenda* buscarAgenda(struct Agenda &agenda, int mes) {
    if (mes < 0 || mes > agenda.tamanho) return nullptr;
    NodoAgenda *curr = agenda.inicio;
    while (curr != nullptr && curr->mes.idMes != mes) 
        curr = curr->proximo;
    return curr;
}
