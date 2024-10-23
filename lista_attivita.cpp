#include "lista_attivita.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

ListaAttivita::ListaAttivita(const std::string& nomeLista) : nomeLista(nomeLista) {}

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
        std::cout << "Nessuna attivita presente nella lista '" << nomeLista << "'." << std::endl;
        return;
    }

    std::cout << "Attivita nella lista '" << nomeLista << "':\n";
    for (const auto& attivita : elenco) {
        std::cout << "Nome: " << attivita.getNome()
                  << ", Descrizione: " << attivita.getDescrizione()
                  << ", Data: " << attivita.getData()
                  << ", Completata: " << (attivita.isCompletata() ? "Si" : "No") << std::endl;
    }
}

void ListaAttivita::contrassegnaComeCompletata(const std::string& nome,
                                               const std::string& descrizione,
                                               const std::string& data) {
    bool trovato = false;
    std::string descrizioneInput = descrizione;
    std::string dataInput = data;

    if (!nome.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getNome() == nome) {
                attivita.setCompletata(true);
                std::cout << "Attivita '" << attivita.getNome() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato && !descrizioneInput.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getDescrizione() == descrizioneInput) {
                attivita.setCompletata(true);
                std::cout << "Attivita con descrizione '" << attivita.getDescrizione() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato && !dataInput.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getData() == dataInput) {
                attivita.setCompletata(true);
                std::cout << "Attivita con data '" << attivita.getData() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato) {
        std::cout << "Nessuna attivita corrispondente trovata." << std::endl;
    }
}

void ListaAttivita::eliminaAttivita(const std::string& nome) {
    auto it = std::remove_if(elenco.begin(), elenco.end(), [&](const Attivita& a) {
        return a.getNome() == nome;
    });
    if (it != elenco.end()) {
        elenco.erase(it, elenco.end());
        std::cout << "Attivita con nome '" << nome << "' eliminata." << std::endl;
    } else {
        std::cout << "Attivita con nome '" << nome << "' non trovata." << std::endl;
    }
}

void ListaAttivita::salvaSuDisco(const std::string& nomeFile) const {
    std::ofstream out(nomeFile);
    if (!out) {
        throw std::ios_base::failure("Impossibile aprire il file per la scrittura.");
    }

    for (const auto& attivita : elenco) {
        out << attivita.toCSV() << std::endl;
    }
}

void ListaAttivita::caricaDaDisco(const std::string& nomeFile) {
    std::ifstream in(nomeFile);
    if (!in) {
        std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(in, linea)) {
        try {
            elenco.push_back(Attivita(linea));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Linea ignorata: " << e.what() << std::endl;
        }
    }
}

int ListaAttivita::getAttivitaNonCompletate() const {
    return std::count_if(elenco.begin(), elenco.end(), [](const Attivita& a) {
        return !a.isCompletata();
    });
}

int ListaAttivita::getTotaleAttivita() const {
    return elenco.size();
}

std::vector<Attivita> ListaAttivita::getAttivita() const {
    return elenco;
}

std::string ListaAttivita::getNomeLista() const {
    return nomeLista;
}

std::vector<Attivita> ListaAttivita::cercaAttivita(const std::string& nome,
                                                           const std::string& descrizione,
                                                           const std::string& data,
                                                           bool completata,
                                                           bool filtraPerStato) const {
    std::vector<Attivita> risultati;

    for (const auto& attivita : elenco) {
        bool corrisponde = true;

        if (!nome.empty() && attivita.getNome() != nome) {
            corrisponde = false;
        }
        if (!descrizione.empty() && attivita.getDescrizione() != descrizione) {
            corrisponde = false;
        }
        if (!data.empty() && attivita.getData() != data) {
            corrisponde = false;
        }
        if (filtraPerStato && attivita.isCompletata() != completata) {
            corrisponde = false;
        }

        if (corrisponde) {
            risultati.push_back(attivita);
        }
    }

    return risultati;
}
