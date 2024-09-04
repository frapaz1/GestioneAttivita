#include "attivita.h"
#include "lista_attivita.h"
#include <iostream>
#include <stdexcept>

int main() {
    ListaAttivita lista;
    std::string nome, descrizione, data;

    std::cout << "Inserisci le attivita (digita 'fine' per terminare):" << std::endl;

    while (true) {
        std::cout << "Nome dell'attivita: ";
        std::getline(std::cin, nome);
        if (nome == "fine") break;

        std::cout << "Descrizione dell'attivita: ";
        std::getline(std::cin, descrizione);
        if (descrizione == "fine") break;

        std::cout << "Data dell'attivita (formato YYYY-MM-DD): ";
        std::getline(std::cin, data);
        if (data == "fine") break;

        try {
            lista.aggiungiAttivita(Attivita(nome, descrizione, data));
        } catch (const std::invalid_argument& e) {
            std::cout << "Errore: " << e.what() << std::endl;
        }
    }

    std::string nomeFile = "attivita.csv";

    try {
        lista.salvaSuDisco(nomeFile);
    } catch (const std::ios_base::failure& e) {
        std::cout << "Errore durante il salvataggio del file: " << e.what() << std::endl;
        return 1;
    }

    ListaAttivita nuovaLista;
    try {
        nuovaLista.caricaDaDisco(nomeFile);
    } catch (const std::ios_base::failure& e) {
        std::cout << "Errore durante il caricamento del file: " << e.what() << std::endl;
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

    std::cout << "Vuoi cercare un'attivita per nome? (digita 'fine' per terminare):" << std::endl;
    while (true) {
        std::cout << "Nome dell'attivita da cercare: ";
        std::getline(std::cin, nome);
        if (nome == "fine") break;

        Attivita* attivita = nuovaLista.cercaAttivita(nome);
        if (attivita) {
            std::cout << "Attivita trovata: " << attivita->getNome()
                      << ", Descrizione: " << attivita->getDescrizione()
                      << ", Data: " << attivita->getData()
                      << ", Completata: " << (attivita->isCompletata() ? "Si" : "No") << std::endl;
        } else {
            std::cout << "Attivita con nome '" << nome << "' non trovata." << std::endl;
        }
    }

    nuovaLista.mostraElenco();

    return 0;
}
