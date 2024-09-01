#include "attivita.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


Attivita::Attivita(const std::string& nome, const std::string& descrizione, bool completata)
        : nome(nome), descrizione(descrizione), completata(completata) {
    if (nome.empty() || descrizione.empty()) {
        throw std::invalid_argument("Nome e descrizione non possono essere vuoti");
    }
}

std::string Attivita::getNome() const { return nome; }
std::string Attivita::getDescrizione() const { return descrizione; }
bool Attivita::isCompletata() const { return completata; }

void Attivita::setNome(const std::string& nuovoNome) {
    if (nuovoNome.empty()) {
        throw std::invalid_argument("Il nuovo nome non può essere vuoto");
    }
    nome = nuovoNome;
}

void Attivita::setDescrizione(const std::string& nuovaDescrizione) {
    if (nuovaDescrizione.empty()) {
        throw std::invalid_argument("La nuova descrizione non può essere vuota");
    }
    descrizione = nuovaDescrizione;
}

void Attivita::setCompletata(bool nuovoStato) { completata = nuovoStato; }

std::string Attivita::toCSV() const {
    return nome + "," + descrizione + "," + (completata ? "1" : "0");
}

Attivita Attivita::fromCSV(const std::string& csvLine) {
    std::istringstream ss(csvLine);
    std::string nome, descrizione, completataStr;
    std::getline(ss, nome, ',');
    std::getline(ss, descrizione, ',');
    std::getline(ss, completataStr, ',');

    if (nome.empty() || descrizione.empty() || completataStr.empty()) {
        throw std::invalid_argument("CSV line is malformed: " + csvLine);
    }

    bool completata = (completataStr == "1");
    return Attivita(nome, descrizione, completata);
}


void ListaAttivita::aggiungiAttivita(const Attivita& attivita) {
    elenco.push_back(attivita);
}

void ListaAttivita::mostraElenco() const {
    if (elenco.empty()) {
        std::cout << "Nessuna attività presente." << std::endl;
        return;
    }

    for (const auto& attivita : elenco) {
        std::cout << "Nome: " << attivita.getNome()
                  << ", Descrizione: " << attivita.getDescrizione()
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
    std::cerr << "Attività con nome '" << nome << "' non trovata." << std::endl;
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
            elenco.push_back(Attivita::fromCSV(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Errore nella lettura della linea: " << e.what() << std::endl;
        }
    }
}
