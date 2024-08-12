#include "Menu.hpp"
#include <iostream>

Menu::Menu(float largura, float altura) : itemSelecionado(0) {

    sf::Texture texturaFundo;
    setFundoTexture(texturaFundo);
    if (!texturaFundo.loadFromFile("/home/padovam/jogo-tecprog/assets/images/fundo_menu.png")) {
        std::cerr << "Erro ao carregar a textura de fundo!" << std::endl;
    } else {
        std::cout << "Textura de fundo carregada com sucesso." << std::endl;
    }

        sf::Texture texturaBotao;
    if (!texturaBotao.loadFromFile("/home/padovam/jogo-tecprog/assets/images/botoes.png")) {
        std::cerr << "Erro ao carregar a textura dos botões!" << std::endl;
    }

    if (!fonte.loadFromFile("/home/padovam/jogo-tecprog/assets/fonts/BACKTO1982.TTF")) {
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
    } else {
        std::cout << "Fonte carregada com sucesso." << std::endl;
    }

    // Criar botões
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape botao(sf::Vector2f(300, 100));  // Tamanho dos botões
        botao.setPosition(sf::Vector2f((largura / 2) - 150, (altura / (5 + 1) * (i + 1))));
        botoes.push_back(botao);

        sf::Text texto;
        texto.setFont(fonte);
        texto.setFillColor(sf::Color::White);
        texto.setCharacterSize(24);
        texto.setPosition(botao.getPosition().x + 50, botao.getPosition().y + 25);
        textos.push_back(texto);
    }

    // Definir os textos dos botões
    setBotaoTexto(0, "Stage 1", fonte);
    setBotaoTexto(1, "Stage 2", fonte);
    setBotaoTexto(2, "Load Games", fonte);
    setBotaoTexto(3, "Settings", fonte);

    if (!botoes.empty()) {
        botoes[itemSelecionado].setFillColor(sf::Color::Red);  // Destacar o botão selecionado
        std::cout << "Botão " << itemSelecionado << " destacado." << std::endl;
    }
}

Menu::~Menu() {
    std::cout << "Destruindo menu." << std::endl;
}

void Menu::draw(sf::RenderWindow& window) {
    // Verifique se a textura do fundo está carregada corretamente antes de desenhar
    if (fundo.getTexture() != nullptr) {
        window.draw(fundo);
    } else {
        std::cerr << "Erro: Textura de fundo não carregada." << std::endl;
    }

    for (size_t i = 0; i < botoes.size(); i++) {
        window.draw(botoes[i]);
        window.draw(textos[i]);
    }
}

void Menu::moveUp() {
    std::cout << "Movendo para cima: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado - 1 >= 0) {
        botoes[itemSelecionado].setFillColor(sf::Color::White);
        itemSelecionado--;
        botoes[itemSelecionado].setFillColor(sf::Color::Red);
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

void Menu::moveDown() {
    std::cout << "Movendo para baixo: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado + 1 < botoes.size()) {
        botoes[itemSelecionado].setFillColor(sf::Color::White);
        itemSelecionado++;
        botoes[itemSelecionado].setFillColor(sf::Color::Red);
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

int Menu::getSelectedItemIndex() const {
    return itemSelecionado;
}

void Menu::setBotaoTexto(int index, const std::string& texto, const sf::Font& fonte) {
    if (index >= 0 && index < textos.size()) {
        textos[index].setFont(fonte);
        textos[index].setString(texto);
    }
}

void Menu::setFundoTexture(const sf::Texture& texture) {
    fundo.setTexture(texture);
    std::cout << "Textura de fundo aplicada." << std::endl;
}

const sf::Font& Menu::getFonte() const {
    return fonte;
}
