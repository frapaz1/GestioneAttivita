#include "attivita.h"
#include "lista_attivita.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(Attivita, ConstructorTest) {
    Attivita attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false);
    EXPECT_EQ(attivita.getNome(), "Lettura");
    EXPECT_EQ(attivita.getDescrizione(), "Leggere un libro di C++");
    EXPECT_EQ(attivita.getData(), "2024-09-04");
    EXPECT_FALSE(attivita.isCompletata());
}

TEST(AttivitaTest, SetNomeTest) {
    Attivita attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false);
    attivita.setNome("Scrittura");
    EXPECT_EQ(attivita.getNome(), "Scrittura");
}

TEST(AttivitaTest, SetDescrizioneTest) {
    Attivita attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false);
    attivita.setDescrizione("Leggere un libro di Python");
    EXPECT_EQ(attivita.getDescrizione(), "Leggere un libro di Python");
}

TEST(AttivitaTest, SetDataTest) {
    Attivita attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false);
    attivita.setData("2024-12-25");
    EXPECT_EQ(attivita.getData(), "2024-12-25");
}

TEST(AttivitaTest, SetCompletataTest) {
    Attivita attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false);
    attivita.setCompletata(true);
    EXPECT_TRUE(attivita.isCompletata());
}

TEST(ListaAttivitaTest, AggiungiAttivitaTest) {
    ListaAttivita lista;
    lista.aggiungiAttivita(Attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false));
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    lista.mostraElenco();
    std::cout.rdbuf(oldCout);
    EXPECT_NE(output.str().find("Nome: Lettura"), std::string::npos);
}

TEST(ListaAttivitaTest, ContrassegnaComeCompletataTest) {
    ListaAttivita lista;
    lista.aggiungiAttivita(Attivita("Lettura", "Leggere un libro di C++", "2024-09-04", false));
    lista.contrassegnaComeCompletata("Lettura");
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    lista.mostraElenco();
    std::cout.rdbuf(oldCout);
    EXPECT_NE(output.str().find("Completata: Si"), std::string::npos);
}
