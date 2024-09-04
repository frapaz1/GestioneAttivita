#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H

#include "Attivita.h"
#include <vector>
#include <string>

class ListaAttivita {
public:
    void aggiungiAttivita(const Attivita& attivita);
    void mostraElenco() const;
    void contrassegnaComeCompletata(const std::string& nome);
    void salvaSuDisco(const std::string& nomeFile) const;
    void caricaDaDisco(const std::string& nomeFile);
    Attivita* cercaAttivita(const std::string& nome);

private:
    std::vector<Attivita> elenco;
};

#endif
