#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entidade.hpp"
#include "Personagem.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Obstaculo.hpp"
#include "Mapa.hpp"

class Jogo {
private:
    sf::RenderWindow window;
    Mapa mapa;
    std::vector<Entidade*> entidades;
    Jogador* jogador;

public:
    Jogo();
    ~Jogo();
    void adicionarEntidade(Entidade* e);
    void executar();
};

#endif // JOGO_HPP
