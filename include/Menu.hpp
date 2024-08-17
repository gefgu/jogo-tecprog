#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"

class Menu
{
private:
    sf::Sprite fundo;                       // Fundo do menu
    std::vector<sf::RectangleShape> botoes; // Botões
    std::vector<sf::Text> textos;           // Textos nos botões
    sf::Font fonte;
    int itemSelecionado;
    Gerenciador_Grafico &gerenciadorGrafico;
    Gerenciador_Estado &gerenciadorEstado;

public:
    Menu(float largura, float altura);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
    void centralizaTextoNoBotao(sf::Text &texto, const sf::RectangleShape &botao);
    void setBotaoTexto(int index, const std::string &texto, const sf::Font &fonte);
    const sf::Font &getFonte() const;
    void executar();
};

#endif // MENU_HPP
