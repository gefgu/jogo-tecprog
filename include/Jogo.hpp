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
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Ente.hpp"
#include "Menu.hpp" // Incluí o Menu

class Jogo
{
private:
    Gerenciador_Grafico &gerenciadorGrafico;
    ListaEntidades entidades;
    Jogador *jogador;
    Menu menu;
    sf::Texture texturaBotao;
    sf::Font fonte;
    sf::Texture texturaFundo;
    bool menuAtivo; // Flag para verificar se o menu está ativado

public:
    Jogo();
    ~Jogo();
    void adicionarEntidade(Entidade *e);
    void executar();
    void processarMenu(); // Função para processar o menu
};

#endif // JOGO_HPP
