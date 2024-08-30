#include <random> // Include for normal distribution
#include <ctime>  // Include for seeding
#include "Listas/ListaEntidades.hpp"
#include "Entidades/Personagens/Personagem.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Projetil.hpp"

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidade *pE)
{
  LEs.incluir(pE);
}

void ListaEntidades::executar()
{
  typename Lista<Entidade>::Elemento *it; // Correctly qualified nested class
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->executar();
  }
}

void ListaEntidades::desenhar()
{
  typename Lista<Entidade>::Elemento *it; // Correctly qualified nested class
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->desenhar();
  }
}

void ListaEntidades::remover(Entidade *pE)
{
  LEs.remover(pE);
}

Json::Value ListaEntidades::toJsonArray()
{
  Json::Value jsonArray(Json::arrayValue);
  typename Lista<Entidade>::Elemento *it; // Correctly qualified nested class
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    jsonArray.append(it->getInfo()->gravar());
  }
  return jsonArray;
}

Entidade *ListaEntidades::getOneUsingNormalDistribution()
{
  static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

  double mean = LEs.size() / 2.0;
  double stddev = LEs.size() / 3.0;

  std::normal_distribution<double> distribution(mean, stddev);

  int index;
  do
  {
    index = static_cast<int>(distribution(generator));
  } while (index < 0 || index >= LEs.size());

  return LEs[index]->getInfo();
}
