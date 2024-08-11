#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entidades/Entidade.hpp"
#include "Entidades/Personagens/Personagem.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Personagens/Inimigo.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Listas/ListaEntidades.hpp"
// #include "Mapa.hpp"

class Jogo
{
private:
    sf::RenderWindow window;
    // Mapa mapa;
    ListaEntidades entidades;
    Jogador *jogador;

public:
    Jogo();
    ~Jogo();
    void adicionarEntidade(Entidade *e);
    void executar();
};

#endif // JOGO_HPP
