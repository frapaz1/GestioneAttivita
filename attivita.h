#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <string>
#include <stdexcept>

class Attivita {
public:
    Attivita(const std::string& nome, const std::string& descrizione, std::string data, bool completata = false);
    Attivita(const std::string& csvLine);

    std::string getNome() const;
    std::string getDescrizione() const;
    std::string getData() const;
    bool isCompletata() const;

    void setNome(const std::string& nuovoNome);
    void setDescrizione(const std::string& nuovaDescrizione);
    void setData(const std::string& nuovaData);
    void setCompletata(bool nuovoStato);

    std::string toCSV() const;

private:
    bool dataValida(const std::string& data) const;

    std::string nome;
    std::string descrizione;
    std::string data;
    bool completata;
};

#endif
