#pragma once

class Configuracoes
{
private:
  bool doisJogadores;
  Configuracoes();  // Singleton
  ~Configuracoes(); // Singleton

  // Delete copy constructor and assignment operator to prevent copying
  Configuracoes(const Configuracoes &) = delete;
  Configuracoes &operator=(const Configuracoes &) = delete;

public:
  static Configuracoes &getInstance()
  {
    static Configuracoes instance;
    return instance;
  }
  void setDoisJogadores(bool dois);
  bool getDoisJogadores();
};