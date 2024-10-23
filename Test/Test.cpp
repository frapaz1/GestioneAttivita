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


class ListaAttivitaTest : public ::testing::Test {
protected:
    ListaAttivita* lista;

    void SetUp() override {
        lista = new ListaAttivita("Lista di Prova");
    }

    void TearDown() override {
        delete lista;
    }
};

TEST(ListaAttivitaTest, TestAggiungiAttivita) {
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

TEST(ListaAttivitaTest, TestCercaAttivitaPerNome) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
    lista.aggiungiAttivita(attivita);

    auto risultati = lista.cercaAttivita("Test Attività", "", "", false, false);
    EXPECT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati[0].getNome(), "Test Attività");
}

TEST(ListaAttivitaTest, TestCercaAttivitaPerDescrizione) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
    lista.aggiungiAttivita(attivita);

    auto risultati = lista.cercaAttivita("", "Descrizione di prova", "", false, false);
    EXPECT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati[0].getDescrizione(), "Descrizione di prova");
}

TEST(ListaAttivitaTest, TestCercaAttivitaPerData) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
    lista.aggiungiAttivita(attivita);

    auto risultati = lista.cercaAttivita("", "", "2024-10-03", false, false);
    EXPECT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati[0].getData(), "2024-10-03");
}

TEST(ListaAttivitaTest, TestContrassegnaComeCompletata) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita("Test Attività", "Descrizione di prova", "2024-10-03");
    lista.aggiungiAttivita(attivita);

    lista.contrassegnaComeCompletata("Test Attività");
    auto risultati = lista.cercaAttivita("Test Attività", "", "", true, true);
    EXPECT_EQ(risultati.size(), 1);
    EXPECT_TRUE(risultati[0].isCompletata());
}

TEST(ListaAttivitaTest, TestGetAttivitaNonCompletate) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita1("Test Attività 1", "Descrizione 1", "2024-10-03");
    Attivita attivita2("Test Attività 2", "Descrizione 2", "2024-10-04");
    lista.aggiungiAttivita(attivita1);
    lista.aggiungiAttivita(attivita2);

    EXPECT_EQ(lista.getAttivitaNonCompletate(), 2);

    lista.contrassegnaComeCompletata("Test Attività 1");
    EXPECT_EQ(lista.getAttivitaNonCompletate(), 1);
}

TEST(ListaAttivitaTest, TestCercaAttivitaConFiltroCompletata) {
    ListaAttivita lista("Lista di Prova");
    Attivita attivita1("Test Attività 1", "Descrizione 1", "2024-10-03");
    Attivita attivita2("Test Attività 2", "Descrizione 2", "2024-10-04");
    lista.aggiungiAttivita(attivita1);
    lista.aggiungiAttivita(attivita2);

    lista.contrassegnaComeCompletata("Test Attività 1");

    auto risultatiCompletate = lista.cercaAttivita("", "", "", true, true);
    EXPECT_EQ(risultatiCompletate.size(), 1);
    EXPECT_EQ(risultatiCompletate[0].getNome(), "Test Attività 1");

    auto risultatiNonCompletate = lista.cercaAttivita("", "", "", false, true);
    EXPECT_EQ(risultatiNonCompletate.size(), 1);
    EXPECT_EQ(risultatiNonCompletate[0].getNome(), "Test Attività 2");
}
