#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <string>
#include <vector>

class Attivita {
public:
    Attivita(const std::string& nome, const std::string& descrizione, bool completata = false);

    std::string getNome() const;
    std::string getDescrizione() const;
    bool isCompletata() const;

    void setNome(const std::string& nuovoNome);
    void setDescrizione(const std::string& nuovaDescrizione);
    void setCompletata(bool nuovoStato);

    std::string toCSV() const;
    static Attivita fromCSV(const std::string& csvLine);

private:
    std::string nome;
    std::string descrizione;
    bool completata;
};

class ListaAttivita {
public:
    void aggiungiAttivita(const Attivita& attivita);
    void mostraElenco() const;
    void contrassegnaComeCompletata(const std::string& nome);
    void salvaSuDisco(const std::string& nomeFile) const;
    void caricaDaDisco(const std::string& nomeFile);

private:
    std::vector<Attivita> elenco;
};

#endif
