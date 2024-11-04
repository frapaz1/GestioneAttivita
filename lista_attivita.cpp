#include "lista_attivita.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

ListaAttivita::ListaAttivita(const std::string& nomeLista) : nomeLista(nomeLista) {}

void ListaAttivita::aggiungiAttivita(const Attivita& attivita) {
    auto it = std::find_if(elenco.begin(), elenco.end(), [&](const Attivita& a) {
        return a.getNome() == attivita.getNome();
    });
    if (it != elenco.end()) {
        std::cerr << "Errore: esiste già un'attivita con il nome '" << attivita.getNome() << "'" << std::endl;
        return;
    }
    elenco.push_back(attivita);
}

std::string ListaAttivita::toString() const {
    std::ostringstream oss;

    if (elenco.empty()) {
        oss << "Nessuna attivita presente nella lista '" << nomeLista << "'.";
    } else {
        oss << "Attivita nella lista '" << nomeLista << "':\n";
        for (const auto& attivita : elenco) {
            oss << "Nome: " << attivita.getNome()
                << ", Descrizione: " << attivita.getDescrizione()
                << ", Data: " << attivita.getData()
                << ", Completata: " << (attivita.isCompletata() ? "Si" : "No") << '\n';
        }
    }
    return oss.str();
}

void ListaAttivita::contrassegnaComeCompletata(const std::string& nome,
                                               const std::string& descrizione,
                                               const std::string& data) {
    bool trovato = false;

    if (!nome.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getNome() == nome) {
                attivita.setCompletata(true);
                std::cerr << "Attivita '" << attivita.getNome() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato && !descrizione.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getDescrizione() == descrizione) {
                attivita.setCompletata(true);
                std::cerr << "Attivita con descrizione '" << attivita.getDescrizione() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato && !data.empty()) {
        for (auto& attivita : elenco) {
            if (attivita.getData() == data) {
                attivita.setCompletata(true);
                std::cerr << "Attivita con data '" << attivita.getData() << "' contrassegnata come completata." << std::endl;
                trovato = true;
                return;
            }
        }
    }

    if (!trovato) {
        std::cerr << "Nessuna attivita corrispondente trovata." << std::endl;
    }
}

void ListaAttivita::eliminaAttivita(const std::string& nome) {
    auto it = std::remove_if(elenco.begin(), elenco.end(), [&](const Attivita& a) {
        return a.getNome() == nome;
    });
    if (it != elenco.end()) {
        elenco.erase(it, elenco.end());
        std::cerr << "Attivita con nome '" << nome << "' eliminata." << std::endl;
    } else {
        std::cerr << "Attivita con nome '" << nome << "' non trovata." << std::endl;
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

int ListaAttivita::getNumNonCompletate() const {
    return std::count_if(elenco.begin(), elenco.end(), [](const Attivita& a) {
        return !a.isCompletata();
    });
}

int ListaAttivita::getTotaleNum() const {
    return elenco.size();
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
