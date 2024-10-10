#include "attivita.h"
#include <sstream>
#include <stdexcept>


bool Attivita::dataValida(const std::string& data) const {
    if (data.size() != 10 || data[4] != '-' || data[7] != '-') {
        return false;
    }

    int anno = std::stoi(data.substr(0, 4));
    int mese = std::stoi(data.substr(5, 2));
    int giorno = std::stoi(data.substr(8, 2));

    if (mese < 1 || mese > 12 || giorno < 1 || giorno > 31) {
        return false;
    }

    int giorniPerMese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) {
        giorniPerMese[1] = 29;
    }

    return giorno <= giorniPerMese[mese - 1];
}

Attivita::Attivita(const std::string& nome, const std::string& descrizione, std::string data, bool completata)
        : nome(nome), descrizione(descrizione), data(data), completata(completata) {
    if (nome.empty() || descrizione.empty() || data.empty()) {
        throw std::invalid_argument("Nome, descrizione e data non possono essere vuoti");
    }

    if (!dataValida(data)) {
        throw std::invalid_argument("Data non valida: " + data);
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

    if (!dataValida(nuovaData)) {
        throw std::invalid_argument("Data non valida: " + nuovaData);
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

    if (!dataValida(data)) {
        throw std::invalid_argument("Data non valida: " + data);
    }

    completata = (completataStr == "1");
}
