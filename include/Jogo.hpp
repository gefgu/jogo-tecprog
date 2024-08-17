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
#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Gerenciadores/Gerenciador_Threads.hpp"
#include "Ente.hpp"
#include "PerformanceMonitor.hpp"
#include "Menu.hpp" 
#include "Fases/Fase_Primeira.hpp"

class Jogo
{
private:
    Gerenciador_Grafico &gerenciadorGrafico;
    Gerenciador_Colisoes gerenciadorColisoes;
    Gerenciador_Threads gerenciadorThreads;
    PerformanceMonitor performanceMonitor; 

    Menu menu;
    sf::Font fonte;
    bool menuAtivo; // Flag para verificar se o menu está ativado
    bool fase_primeira_ativa;
    Fase_Primeira fase1;

public:
    Jogo();
    ~Jogo();
    void adicionarEntidade(Entidade *e);
    void executar();
    void processarMenu(); // Função para processar o menu
};

#endif // JOGO_HPP
