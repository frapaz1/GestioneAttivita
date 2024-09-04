#include "attivita.h"
#include <sstream>
#include <stdexcept>

Attivita::Attivita(const std::string& nome, const std::string& descrizione, std::basic_string<char> data, bool completata)
        : nome(nome), descrizione(descrizione), data(data), completata(completata) {
    if (nome.empty() || descrizione.empty() || data.empty()) {
        throw std::invalid_argument("Nome, descrizione e data non possono essere vuoti");
    }
}

std::string Attivita::getNome() const { return nome; }
std::string Attivita::getDescrizione() const { return descrizione; }
std::string Attivita::getData() const { return data; }
bool Attivita::isCompletata() const { return completata; }

void Attivita::setNome(const std::string& nuovoNome) {
    if (nuovoNome.empty()) {
        throw std::invalid_argument("Il nuovo nome non puo essere vuoto");
    }
    nome = nuovoNome;
}

void Attivita::setDescrizione(const std::string& nuovaDescrizione) {
    if (nuovaDescrizione.empty()) {
        throw std::invalid_argument("La nuova descrizione non puo essere vuota");
    }
    descrizione = nuovaDescrizione;
}

void Attivita::setData(const std::string& nuovaData) {
    if (nuovaData.empty()) {
        throw std::invalid_argument("La nuova data non puo essere vuota");
    }
    data = nuovaData;
}

void Attivita::setCompletata(bool nuovoStato) { completata = nuovoStato; }

std::string Attivita::toCSV() const {
    return nome + "," + descrizione + "," + data + "," + (completata ? "1" : "0");
}

Attivita::Attivita(const std::string& csvLine) {
    std::istringstream ss(csvLine);
    std::string completataStr;

    std::getline(ss, nome, ',');
    std::getline(ss, descrizione, ',');
    std::getline(ss, data, ',');
    std::getline(ss, completataStr, ',');

    if (nome.empty() || descrizione.empty() || data.empty() || completataStr.empty()) {
        throw std::invalid_argument("Linea CSV non corretta: " + csvLine);
    }

    completata = (completataStr == "1");
}
