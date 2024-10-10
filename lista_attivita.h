#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H

#include "attivita.h"
#include <vector>
#include <string>

class ListaAttivita {
public:
    ListaAttivita(const std::string& nomeLista);

    void aggiungiAttivita(const Attivita& attivita);
    void mostraElenco() const;
    void contrassegnaComeCompletataAvanzata(const std::string& nome = "",
                                            const std::string& descrizione = "",
                                            const std::string& data = "");
    void eliminaAttivita(const std::string& nome);
    void salvaSuDisco(const std::string& nomeFile) const;
    void caricaDaDisco(const std::string& nomeFile);

    int getAttivitaNonCompletate() const;
    int getTotaleAttivita() const;
    std::vector<Attivita> getAttivita() const;
    std::string getNomeLista() const;

    std::vector<Attivita> cercaAttivitaAvanzata(const std::string& nome = "",
                                                const std::string& descrizione = "",
                                                const std::string& data = "",
                                                bool completata = false,
                                                bool filtraPerStato = false) const;

private:
    std::string nomeLista;
    std::vector<Attivita> elenco;
};

#endif
