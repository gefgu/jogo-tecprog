#pragma once

class Subject;

class Observer
{
public:
  Observer();
  virtual ~Observer();
  virtual void Update(const char *teclaPressionada) = 0;
};