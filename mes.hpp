#include "dia.hpp"

// Define an item in an agenda item (month, size, appointment list)
struct Mes {
    int idMes;
    int dias; // Number of days in this month
    struct Dia *listaCompromissos; // Appointment lists for each day of this month
};
