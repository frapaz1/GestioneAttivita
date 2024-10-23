#include "attivita.h"
#include "lista_attivita.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

void mostraRiepilogo(const std::vector<ListaAttivita>& liste) {
    for (const auto& lista : liste) {
        int totale = lista.getTotaleAttivita();
        int nonCompletate = lista.getAttivitaNonCompletate();
        std::cout << "Riepilogo per la lista '" << lista.getNomeLista() << "':\n";
        std::cout << "Totale attivita: " << totale << "\n";
        std::cout << "Attivita non completate: " << nonCompletate << "\n";
        lista.mostraElenco();
        std::cout << std::endl;
    }
}

void Ricerca(const std::vector<ListaAttivita>& liste) {
    std::string nomeLista, nomeAttivita, descrizione, data;
    bool completata = false;
    char filtraPerStato;

    std::cout << "Nome della lista (lasciare vuoto per tutte le liste): ";
    std::getline(std::cin, nomeLista);

    std::cout << "Nome dell'attivita (lasciare vuoto per ignorare): ";
    std::getline(std::cin, nomeAttivita);
    std::cout << "Descrizione dell'attivita (lasciare vuoto per ignorare): ";
    std::getline(std::cin, descrizione);
    std::cout << "Data dell'attivita (formato YYYY-MM-DD, lasciare vuoto per ignorare): ";
    std::getline(std::cin, data);

    std::cout << "Vuoi filtrare per stato di completamento? (s/n): ";
    std::cin >> filtraPerStato;
    std::cin.ignore();

    if (filtraPerStato == 's' || filtraPerStato == 'S') {
        char stato;
        std::cout << "Completata (c) o Non Completata (n): ";
        std::cin >> stato;
        std::cin.ignore();
        completata = (stato == 'c' || stato == 'C');
    }

    for (const auto& lista : liste) {
        if (nomeLista.empty() || lista.getNomeLista() == nomeLista) {
            std::vector<Attivita> risultati = lista.cercaAttivita(nomeAttivita, descrizione, data, completata, filtraPerStato == 's');

            if (!risultati.empty()) {
                std::cout << "Risultati trovati nella lista '" << lista.getNomeLista() << "':\n";
                for (const auto& attivita : risultati) {
                    std::cout << "Nome: " << attivita.getNome()
                              << ", Descrizione: " << attivita.getDescrizione()
                              << ", Data: " << attivita.getData()
                              << ", Completata: " << (attivita.isCompletata() ? "Si" : "No") << std::endl;
                }
            } else {
                std::cout << "Nessuna attivita trovata nella lista '" << lista.getNomeLista() << "' con i criteri forniti.\n";
            }
        }
    }
}

int main() {
    std::vector<ListaAttivita> liste;
    std::string nomeLista, nomeAttivita, descrizione, data;
    int scelta;

    while (true) {
        std::cout << "\nScegli un'azione:\n";
        std::cout << "1. Crea una nuova lista di attivita\n";
        std::cout << "2. Aggiungi attivita a una lista\n";
        std::cout << "3. Mostra tutte le liste\n";
        std::cout << "4. Contrassegna attivita come completata\n";
        std::cout << "5. Elimina attivita\n";
        std::cout << "6. Cerca attivita \n";
        std::cout << "7. Salva ed esci\n";
        std::cout << "Scelta: ";
        std::cin >> scelta;
        std::cin.ignore();

        switch (scelta) {
            case 1: {
                std::cout << "Nome della nuova lista: ";
                std::getline(std::cin, nomeLista);
                liste.emplace_back(nomeLista);
                break;
            }
            case 2: {
                if (liste.empty()) {
                    std::cout << "Non ci sono liste disponibili. Crea prima una lista.\n";
                    break;
                }

                std::cout << "Nome della lista a cui aggiungere l'attivita: ";
                std::getline(std::cin, nomeLista);

                auto it = std::find_if(liste.begin(), liste.end(),
                                       [&](const ListaAttivita& l) { return l.getNomeLista() == nomeLista; });
                if (it == liste.end()) {
                    std::cout << "Lista non trovata.\n";
                    break;
                }

                std::cout << "Nome dell'attivita: ";
                std::getline(std::cin, nomeAttivita);
                std::cout << "Descrizione dell'attivita: ";
                std::getline(std::cin, descrizione);
                std::cout << "Data dell'attivita (formato YYYY-MM-DD): ";
                std::getline(std::cin, data);

                try {
                    it->aggiungiAttivita(Attivita(nomeAttivita, descrizione, data));
                } catch (const std::invalid_argument& e) {
                    std::cout << "Errore: " << e.what() << std::endl;
                }
                mostraRiepilogo(liste);
                break;
            }
            case 3:
                mostraRiepilogo(liste);
                break;
            case 4: {
                std::cout << "Nome della lista (da inserire obbligatoriamente) : ";
                std::getline(std::cin, nomeLista);
                std::cout << "Nome dell'attivita da contrassegnare come completata(lasciare vuoto per ignorare): ";
                std::getline(std::cin, nomeAttivita);

                auto it = std::find_if(liste.begin(), liste.end(),
                                       [&](const ListaAttivita& l) { return l.getNomeLista() == nomeLista; });
                if (it != liste.end()) {
                    it->contrassegnaComeCompletata(nomeAttivita);
                } else {
                    std::cout << "Lista non trovata.\n";
                }
                mostraRiepilogo(liste);
                break;
            }
            case 5: {
                std::cout << "Nome della lista: ";
                std::getline(std::cin, nomeLista);
                std::cout << "Nome dell'attivita da eliminare: ";
                std::getline(std::cin, nomeAttivita);

                auto it = std::find_if(liste.begin(), liste.end(),
                                       [&](const ListaAttivita& l) { return l.getNomeLista() == nomeLista; });
                if (it != liste.end()) {
                    it->eliminaAttivita(nomeAttivita);
                } else {
                    std::cout << "Lista non trovata.\n";
                }
                mostraRiepilogo(liste);
                break;
            }
            case 6:
                Ricerca(liste);
                break;
            case 7:
                for (const auto& lista : liste) {
                    try {
                        lista.salvaSuDisco(lista.getNomeLista() + ".csv");
                    } catch (const std::ios_base::failure& e) {
                        std::cout << "Errore durante il salvataggio del file: " << e.what() << std::endl;
                    }
                }
                mostraRiepilogo(liste);
                return 0;
            default:
                std::cout << "Scelta non valida. Riprova." << std::endl;
                break;
        }
    }
}
