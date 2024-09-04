#include "lista_attivita.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

void ListaAttivita::aggiungiAttivita(const Attivita& attivita) {
    auto it = std::find_if(elenco.begin(), elenco.end(), [&](const Attivita& a) {
        return a.getNome() == attivita.getNome();
    });
    if (it != elenco.end()) {
        std::cout << "Errore: esiste gia un'attivita con il nome '" << attivita.getNome() << "'" << std::endl;
        return;
    }
    elenco.push_back(attivita);
}

void ListaAttivita::mostraElenco() const {
    if (elenco.empty()) {
        std::cout << "Nessuna attivita presente." << std::endl;
        return;
    }

    for (const auto& attivita : elenco) {
        std::cout << "Nome: " << attivita.getNome()
                  << ", Descrizione: " << attivita.getDescrizione()
                  << ", Data: " << attivita.getData()
                  << ", Completata: " << (attivita.isCompletata() ? "Si" : "No") << std::endl;
    }
}

void ListaAttivita::contrassegnaComeCompletata(const std::string& nome) {
    for (auto& attivita : elenco) {
        if (attivita.getNome() == nome) {
            attivita.setCompletata(true);
            return;
        }
    }
    std::cout << "Attivita con nome '" << nome << "' non trovata." << std::endl;
}

Attivita* ListaAttivita::cercaAttivita(const std::string& nome) {
    for (auto& attivita : elenco) {
        if (attivita.getNome() == nome) {
            return &attivita;
        }
    }
    return nullptr;
}

void ListaAttivita::salvaSuDisco(const std::string& nomeFile) const {
    std::ofstream out(nomeFile);
    if (!out) {
        throw std::ios_base::failure("Errore nell'apertura del file per la scrittura: " + nomeFile);
    }

    for (const auto& attivita : elenco) {
        out << attivita.toCSV() << std::endl;
    }
}

void ListaAttivita::caricaDaDisco(const std::string& nomeFile) {
    std::ifstream in(nomeFile);
    if (!in) {
        throw std::ios_base::failure("Errore nell'apertura del file per la lettura: " + nomeFile);
    }

    elenco.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        try {
            elenco.push_back(Attivita(line));
        } catch (const std::invalid_argument& e) {
            std::cout << "Errore nella lettura della linea: " << e.what() << std::endl;
        }
    }
}
