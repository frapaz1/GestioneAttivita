#include "attivita.h"
#include <gtest/gtest.h>

TEST(AttivitaTest, ConstructorTest) {
Attivita attivita("Lettura", "Leggere un libro di C++", false);
EXPECT_EQ(attivita.getNome(), "Lettura");
EXPECT_EQ(attivita.getDescrizione(), "Leggere un libro di C++");
EXPECT_FALSE(attivita.isCompletata());
}

TEST(AttivitaTest, SetNomeTest) {
Attivita attivita("Lettura", "Leggere un libro di C++", false);
attivita.setNome("Scrittura");
EXPECT_EQ(attivita.getNome(), "Scrittura");
}

TEST(AttivitaTest, SetDescrizioneTest) {
Attivita attivita("Lettura", "Leggere un libro di C++", false);
attivita.setDescrizione("Leggere un libro di Python");
EXPECT_EQ(attivita.getDescrizione(), "Leggere un libro di Python");
}

TEST(AttivitaTest, SetCompletataTest) {
Attivita attivita("Lettura", "Leggere un libro di C++", false);
attivita.setCompletata(true);
EXPECT_TRUE(attivita.isCompletata());
}

TEST(ListaAttivitaTest, AggiungiAttivitaTest) {
ListaAttivita lista;
lista.aggiungiAttivita(Attivita("Lettura", "Leggere un libro di C++", false));
std::ostringstream output;
std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
lista.mostraElenco();
std::cout.rdbuf(oldCout);
EXPECT_NE(output.str().find("Nome: Lettura"), std::string::npos);
}

TEST(ListaAttivitaTest, ContrassegnaComeCompletataTest) {
ListaAttivita lista;
lista.aggiungiAttivita(Attivita("Lettura", "Leggere un libro di C++", false));
lista.contrassegnaComeCompletata("Lettura");
std::ostringstream output;
std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
lista.mostraElenco();
std::cout.rdbuf(oldCout);
EXPECT_NE(output.str().find("Completata: Si"), std::string::npos);
}
