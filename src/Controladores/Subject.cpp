#include "Controladores/Subject.hpp"

Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::Attach(Observer *o)
{
  _observers.push_back(o);
}

void Subject::Detach(Observer *o)
{
  _observers.remove(o);
}
