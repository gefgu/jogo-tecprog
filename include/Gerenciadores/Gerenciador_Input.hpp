#pragma once

#include "Controladores/Subject.hpp"
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <set>

class Gerenciador_Input : public Subject
{
private:
  Gerenciador_Grafico &pGG;
  map<sf::Keyboard::Key, std::string> keyMap;
  set<sf::Keyboard::Key> pressedKeys;
  Gerenciador_Input();  // Singleton
  ~Gerenciador_Input(); // Singleton

  // Delete copy constructor and assignment operator to prevent copying
  Gerenciador_Input(const Gerenciador_Input &) = delete;
  Gerenciador_Input &operator=(const Gerenciador_Input &) = delete;

public:
  static Gerenciador_Input &getInstance()
  {
    static Gerenciador_Input instance;
    return instance;
  }
  void executar();
  void Notify(const char *teclaPressionada);
  void NotifyContinuous(const char *teclaPressionada);
};