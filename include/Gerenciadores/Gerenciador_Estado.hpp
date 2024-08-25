#pragma once

enum estadoJogo
{
  MENUINICIO = 0,
  FASE1,
  FASE2,
  GAMEOVER,
  MENUGAMEOVER,
  LEADERBOARD,
  PAUSE
};

class Gerenciador_Estado
{
private:
  estadoJogo estado;
  estadoJogo ultimoEstado;
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
  const estadoJogo getUltimoEstadoJogo() const;
  void setEstadoJogo(estadoJogo e);
};