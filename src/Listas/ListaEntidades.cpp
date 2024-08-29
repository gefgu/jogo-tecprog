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
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->executar();
  }
}

void ListaEntidades::desenhar()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->desenhar();
  }
}

// Entidade *ListaEntidades::getRandom()
// {
//   Elemento<Entidade> *it;
//   for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
//   {
//     if ((rand() % 100) == 0)
//       return it->getInfo();

//     if (it->getProximo() == NULL)
//       it = LEs.getPrimeiro();
//   }
//   return LEs.getPrimeiro()->getInfo();
// }

void ListaEntidades::remover(Entidade *pE)
{
  LEs.remover(pE);
}

Json::Value ListaEntidades::toJsonArray()
{
  Json::Value jsonArray(Json::arrayValue);
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    jsonArray.append(it->getInfo()->gravar());
  }

  return jsonArray;
}

Entidade *ListaEntidades::getOneUsingNormalDistribution()
{
  // Seed the random engine with current time for variability
  static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

  // Set the parameters for the normal distribution
  // mean = center of the range, stddev = controls the spread
  double mean = LEs.size() / 2.0;   // Center the mean in the middle of the list
  double stddev = LEs.size() / 3.0; // Adjust to control the spread (experiment with this value)

  // Create a normal distribution object
  std::normal_distribution<double> distribution(mean, stddev);

  // Generate a valid index for the list
  int index;
  do
  {
    index = static_cast<int>(distribution(generator));
  } while (index < 0 || index >= LEs.size()); // Ensure index is within valid bounds

  // Return the platform at the generated index
  return LEs[index]->getInfo();
}