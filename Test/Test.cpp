#include "attivita.h"
#include "lista_attivita.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

class AttivitaTest : public ::testing::Test {
protected:
    Attivita* attivita;

    void SetUp() override {
        attivita = new Attivita("Test Attività", "Descrizione di prova", "2024-10-03");
    }

    void TearDown() override {
        delete attivita;
    }
};

TEST_F(AttivitaTest, TestCostruttoreValido) {
EXPECT_NO_THROW(Attivita("Nome", "Descrizione", "2024-10-03"));
}

TEST_F(AttivitaTest, TestCostruttoreDataNonValida) {
EXPECT_THROW(Attivita("Nome", "Descrizione", "2024-13-01"), std::invalid_argument);
}

TEST_F(AttivitaTest, TestGetters) {
EXPECT_EQ(attivita->getNome(), "Test Attività");
EXPECT_EQ(attivita->getDescrizione(), "Descrizione di prova");
EXPECT_EQ(attivita->getData(), "2024-10-03");
EXPECT_FALSE(attivita->isCompletata());
}

TEST_F(AttivitaTest, TestSetters) {
attivita->setNome("Nuovo Nome");
attivita->setDescrizione("Nuova Descrizione");
attivita->setData("2024-11-01");
attivita->setCompletata(true);

EXPECT_EQ(attivita->getNome(), "Nuovo Nome");
EXPECT_EQ(attivita->getDescrizione(), "Nuova Descrizione");
EXPECT_EQ(attivita->getData(), "2024-11-01");
EXPECT_TRUE(attivita->isCompletata());
}

TEST_F(AttivitaTest, TestToCSV) {
EXPECT_EQ(attivita->toCSV(), "Test Attività,Descrizione di prova,2024-10-03,0");
}

TEST(ListaAttivita, TestAggiungiAttivita) {
ListaAttivita lista("Lista di Prova");
Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");

EXPECT_NO_THROW(lista.aggiungiAttivita(attivita));
EXPECT_EQ(lista.getTotaleAttivita(), 1);
}

TEST(ListaAttivitaTest, TestEliminaAttivita) {
ListaAttivita lista("Lista di Prova");
Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
lista.aggiungiAttivita(attivita);

lista.eliminaAttivita("Test Attività");
EXPECT_EQ(lista.getTotaleAttivita(), 0);
}

TEST(ListaAttivitaTest, TestEliminaAttivitaNonEsistente) {
ListaAttivita lista("Lista di Prova");
EXPECT_NO_THROW(lista.eliminaAttivita("Attività Inesistente"));
}

TEST(ListaAttivitaTest, TestCercaAttivitaAvanzata) {
ListaAttivita lista("Lista di Prova");
Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
lista.aggiungiAttivita(attivita);

auto risultati = lista.cercaAttivitaAvanzata("Test Attività", "", "", false, false);
EXPECT_EQ(risultati.size(), 1);
EXPECT_EQ(risultati[0].getNome(), "Test Attività");
}
