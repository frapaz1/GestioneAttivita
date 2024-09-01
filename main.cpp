#include "attivita.h"
#include <iostream>

int main() {
    ListaAttivita lista;
    std::string nome, descrizione;

    std::cout << "Inserisci le attivita (digita 'fine' per terminare):" << std::endl;

    while (true) {
        std::cout << "Nome dell'attivita: ";
        std::getline(std::cin, nome);
        if (nome == "fine") break;

        std::cout << "Descrizione dell'attivita: ";
        std::getline(std::cin, descrizione);
        if (descrizione == "fine") break;

        try {
            lista.aggiungiAttivita(Attivita(nome, descrizione));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Errore: " << e.what() << std::endl;
        }
    }

    std::string nomeFile = "attivita.csv";

    try {
        lista.salvaSuDisco(nomeFile);
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Errore durante il salvataggio del file: " << e.what() << std::endl;
        return 1;
    }

    ListaAttivita nuovaLista;
    try {
        nuovaLista.caricaDaDisco(nomeFile);
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Errore durante il caricamento del file: " << e.what() << std::endl;
        return 1;
    }

    nuovaLista.mostraElenco();

    std::cout << "Vuoi contrassegnare un'attivita come completata? (digita 'fine' per terminare):" << std::endl;
    while (true) {
        std::cout << "Nome dell'attivita completata: ";
        std::getline(std::cin, nome);
        if (nome == "fine") break;

        nuovaLista.contrassegnaComeCompletata(nome);
    }

    nuovaLista.mostraElenco();

    return 0;
}
