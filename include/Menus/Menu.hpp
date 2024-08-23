#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Ente.hpp"

class Menu : public Ente
{
protected:
    sf::Sprite fundo; // Fundo do menu
    Gerenciador_Estado &gerenciadorEstado;
    vector<sf::RectangleShape> botoes;  // Botões
    vector<sf::Text> textos;            // Textos nos botões
    vector<sf::RectangleShape> fundos;  // Botões
    vector<sf::Text> textosDecorativos; // Textos nos botões
    int itemSelecionado;

    void setBotaoTexto(int index, const std::string &texto);
    void setFundoTexto(int index, const std::string &texto);
    int getSelectedItemIndex() const;
    void centralizaTextoNoBotao(sf::Text &texto, const sf::RectangleShape &botao);

public:
    Menu();
    ~Menu();
    void nextButton();
    void prevButton();

    virtual void desenhar() = 0;
    virtual void executar() = 0;
};

#endif // MENU_HPP
