#include "dia.hpp"
#include "agenda.hpp"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    struct Agenda agenda;
    inicializarAgenda(agenda);

    int opcao = 0;
    bool agendaAberta = false;
    while (opcao != 7 && opcao != 6) {
        cout << "-----------------------------------------------" << endl;
        cout << "[1] Abrir agenda" << endl;
        cout << "[2] Inserir compromisso" << endl;
        cout << "[3] Remover compromisso" << endl;
        cout << "[4] Listar compromissos de um dia" << endl;
        cout << "[5] Checar compromisso (mes, dia, hora, minuto)" << endl;
        cout << "[6] Fechar agenda e sair" << endl;
        cout << "[7] Sair (alteracoes nao serao salvas)" << endl << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                if (!agendaAberta) {
                    abrirAgenda(agenda);
                    cout << "A agenda foi aberta." << endl << endl;
                    agendaAberta = true;
                } else {
                    cout << "A agenda ja esta aberta." << endl << endl;
                }
                break;
            }
            case 2: {
                if (!agendaAberta) {
                    cout << "A agenda deve ser aberta antes de qualquer operacao." << endl;
                    break;
                }
                int mes, dia;
                cout << "Digite o mes: ";
                cin >> mes;
                cout << "Digite o dia: ";
                cin >> dia;
                struct NodoAgenda *nodoMes = buscarAgenda(agenda, mes);
                if (nodoMes == nullptr) {
                    cout << "Mes invalido." << endl;
                } else if (dia < 0 || dia > nodoMes->mes.dias) {
                    cout << "Dia invalido." << endl;
                } else {
                    Compromisso compromisso;
                    cout << "Digite a hora: ";
                    cin >> compromisso.hora;
                    cout << "Digite o minuto: ";
                    cin >> compromisso.minuto;
                    cout << "Digite uma descricao: ";
                    cin.ignore(1, '\n');
                    getline(cin, compromisso.descricao);
                    if (compromisso.hora < 0 || compromisso.hora > 23 || compromisso.minuto < 0 || compromisso.minuto > 59) {
                        cout << "Hora ou minuto invalido." << endl;
                    } else {
                        inserirCompromisso(nodoMes->mes.listaCompromissos[dia], compromisso);
                    }
                }
                break;
            }
            case 3: {
                if (!agendaAberta) {
                    cout << "A agenda deve ser aberta antes de qualquer operacao." << endl;
                    break;
                }
                int mes, dia, hora, minuto;
                cout << "Digite o mes: ";
                cin >> mes;
                cout << "Digite o dia: ";
                cin >> dia;
                struct NodoAgenda *nodoMes = buscarAgenda(agenda, mes);
                if (nodoMes == nullptr) {
                    cout << "Mes invalido." << endl;
                }
                else if (dia < 0 || dia > nodoMes->mes.dias) {
                    cout << "Dia invalido." << endl;
                } else {
                    cout << "Digite a hora: ";
                    cin >> hora;
                    cout << "Digite o minuto: ";
                    cin >> minuto;
                    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
                        cout << "Hora ou minuto invalido." << endl;
                    } else {
                        bool deletado = removerCompromisso(nodoMes->mes.listaCompromissos[dia], hora, minuto);
                        if (deletado == true) {
                            cout << "Compromisso deletado com sucesso." << endl;
                        } else {
                            cout << "Nao foi possivel deletar o compromisso." << endl;
                        }
                    }
                }
                break;
            }
            case 4: {
                if (!agendaAberta) {
                    cout << "A agenda deve ser aberta antes de qualquer operacao." << endl;
                    break;
                }
                int mes, dia;
                cout << "Digite o mes: ";
                cin >> mes;
                cout << "Digite o dia: ";
                cin >> dia;
                struct NodoAgenda *nodoMes = buscarAgenda(agenda, mes);
                if (nodoMes == nullptr) {
                    cout << "Mes invalido." << endl;
                } else if (dia < 0 || dia > nodoMes->mes.dias) {
                    cout << "Dia invalido." << endl;
                } else {
                    cout << endl;
                    displayDia(nodoMes->mes.listaCompromissos[dia]);
                }
                break;
            }
            case 5: {
                if (!agendaAberta) {
                    cout << "A agenda deve ser aberta antes de qualquer operacao." << endl;
                    break;
                }
                int mes, dia, hora, minuto;
                cout << "Digite o mes: ";
                cin >> mes;
                cout << "Digite o dia: ";
                cin >> dia;
                struct NodoAgenda *nodoMes = buscarAgenda(agenda, mes);
                if (nodoMes == nullptr) {
                    cout << "Mes invalido." << endl;
                }
                else if (dia < 0 || dia > nodoMes->mes.dias) {
                    cout << "Dia invalido." << endl;
                } else {
                    cout << "Digite a hora: ";
                    cin >> hora;
                    cout << "Digite o minuto: ";
                    cin >> minuto;
                    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
                        cout << "Hora ou minuto invalido." << endl;
                    } else {
                        cout << endl;
                        displayDiaPorHorario(nodoMes->mes.listaCompromissos[dia], hora, minuto);
                    }
                }
                break;
            }
            case 6: {
                if (!agendaAberta) {
                    cout << "Saindo do programa. Nenhuma alteracao foi realizada." << endl;
                    break;
                }
                cout << "Saindo do programa. Todas as alteracoes serao salvas." << endl;
                fecharAgenda(agenda);
                break;
            }
            case 7: {
                cout << "Saindo do programa. Todas as alteracoes serao descartadas." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida." << endl << endl;
            }
        }
    }
    // Libera toda a memória alocada para a agenda
    liberarAgenda(agenda);
    return 0;
}
