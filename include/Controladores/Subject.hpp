#pragma once

#include <list>
#include "Controladores/Observer.hpp"

using namespace std;

class Subject
{
public:
  virtual ~Subject();
  virtual void Attach(Observer *o);
  virtual void Detach(Observer *o);
  virtual void Notify(const char *teclaPressionada) = 0;

protected:
  Subject();
  list<Observer *> _observers;
};