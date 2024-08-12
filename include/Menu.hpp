#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>  // Para usar std::string

class Menu {
private:
    sf::Sprite fundo;  // Fundo do menu
    std::vector<sf::RectangleShape> botoes;  // Botões
    std::vector<sf::Text> textos;  // Textos nos botões
    sf::Font fonte;
    int itemSelecionado;

public:
    Menu(float largura, float altura);
    ~Menu();
    
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
    void setBotaoTexto(int index, const std::string& texto, const sf::Font& fonte);
    void setFundoTexture(const sf::Texture& texture);  // Declaração do método
    const sf::Font& getFonte() const;
};

#endif // MENU_HPP
