#pragma once

enum estadoJogo
{
  MENU = 0,
  FASE1,
  FASE2,
  GAMEOVER
};

class Gerenciador_Estado
{
private:
  estadoJogo estado;
  Gerenciador_Estado();  // Singleton
  ~Gerenciador_Estado(); // Singleton

  // Delete copy constructor and assignment operator to prevent copying
  Gerenciador_Estado(const Gerenciador_Estado &) = delete;
  Gerenciador_Estado &operator=(const Gerenciador_Estado &) = delete;

public:
  static Gerenciador_Estado &getInstance()
  {
    static Gerenciador_Estado instance;
    return instance;
  }

  const estadoJogo getEstadoJogo() const;
  void setEstadoJogo(estadoJogo e);
};