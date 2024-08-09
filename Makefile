CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC = src

all: jogo

jogo: $(SRC)/main.cpp $(SRC)/Entidade.cpp $(SRC)/Personagem.cpp $(SRC)/Inimigo.cpp $(SRC)/Obstaculo.cpp $(SRC)/Jogo.cpp $(SRC)/Mapa.cpp $(SRC)/Jogador.cpp 
	$(CXX) $(CXXFLAGS) -o jogo $(SRC)/main.cpp $(SRC)/Entidade.cpp $(SRC)/Personagem.cpp $(SRC)/Inimigo.cpp $(SRC)/Obstaculo.cpp $(SRC)/Jogo.cpp $(SRC)/Mapa.cpp $(SRC)/Jogador.cpp $(SFMLFLAGS)

clean:
	rm -f jogo
