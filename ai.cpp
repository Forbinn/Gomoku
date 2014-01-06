#include <QTime>
#include <QString>
#include <time.h>

#include "ai.h"

AI::AI(const QString &name, const QString &imgPath, const QString &imgPathEnlighten, Map &map, const Arbiter *arbiter) :
    Player(name, imgPath, imgPathEnlighten),
    _thread(new QThread(this)),
    _arbiter(arbiter),
    _map(map),
    _run(false)
{
  this->_isAlone = 0;
  this->valeur = 0;
  this->sx = -1;
  this->sy = -1;
  this->born = 10;
  this->borne = 0;
  this->nb = 0;
  this->test = 0;

}

AI::~AI()
{
    _thread->quit();
    _thread->wait();
}

void AI::start()
{
    this->moveToThread(_thread);
    _thread->start();
    QMetaObject::invokeMethod(this, "run", Qt::QueuedConnection);

    _run = true;
}

void AI::stop()
{
    _thread->terminate();

    _run = false;
}

int AI::isEnnemy(int x, int y)
{
  const Player *curr = _map.get(x, y).owner(); 
  const QString tmp = "AI";

  if (x >= 0 && x < _map.width() && y >= 0 && y < _map.height())
    {   
     if (curr != NULL && curr->name() != tmp)
       return (1);
    }
  return (0);
}

void AI::isAlone(int x, int y)
{
  if (isEnnemy(x - 1, y - 1) > 0)
    this->_isAlone = 1;
  if (isEnnemy(x, y - 1) > 0)
    this->_isAlone = 1;
  if (isEnnemy(x + 1, y - 1) > 0)
    this->_isAlone = 1;

  if (isEnnemy(x - 1, y) > 0)
    this->_isAlone = 1;
  if (isEnnemy(x + 1, y) > 0)
    this->_isAlone = 1;

  if (isEnnemy(x - 1, y + 1) > 0)
    this->_isAlone = 1;
  if (isEnnemy(x, y + 1) > 0)
    this->_isAlone = 1;
  if (isEnnemy(x + 1, y + 1) > 0)
    this->_isAlone = 1;
}

bool AI::isOpp(int x, int y)
{
  const Player *curr = _map.get(x, y).owner();
  const QString ai = "AI";

  if (curr != NULL)
    if (curr->name() != ai)
      return true;
  return false;
}

bool AI::isAI(int x, int y)
{
  const Player *curr = _map.get(x, y).owner();
  const QString ai = "AI";

  if (curr != NULL)
    if (curr->name() == ai)
      return true;
  return false;
}

int AI::checkDouble(int x, int y, int dx, int dy)
{
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isAI(x + dx * 3, y + dy * 3) == false)
	return 3;
    }
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isAI(x + dx * 3, y + dy * 3) == true)
	return 4;
    }
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x - dx, y - dy) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x - dx, y - dy) == true && isAI(x + dx * 2, y + dy * 2) == false)
	return 2;
    }
  return 1;
}

int AI::checkTriple(int x, int y, int dx, int dy)
{
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isOpp(x + dx * 3, y + dy * 3) == true) /*&& isAI(x + dx * 4, y + dy * 4) == false)*/
	  return 6;
    }
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true  && Map::isValid(x + dx * 3, y + dy * 3) == true && Map::isValid(x + dx * 4, y + dy * 4) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isOpp(x + dx * 3, y + dy * 3) == true && isAI(x + dx * 4, y + dy * 4) == true)
	return 6;
    }
  return 1;
}

int AI::checkQuad(int x, int y, int dx, int dy)
{
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true && Map::isValid(x + dx * 4, y + dy * 4) == true && Map::isValid(x + dx * 5, y + dy * 5) == true)
    {
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isOpp(x + dx * 3, y + dy * 3) == true && isOpp(x + dx * 4, y + dy * 4) == true && isOpp(x + dx * 5, y + dy * 5) == true)
	return 8;
      if (isOpp(x + dx, y + dy) == true && isOpp(x + dx * 2, y + dy * 2) == true && isOpp(x + dx * 3, y + dy * 3) == true && isOpp(x + dx * 4, y + dy * 4) == true && isOpp(x + dx * 5, y + dy * 5) == false)
	return 9;
    }
  return 1;
}

int AI::checkWin(int x, int y, int dx, int dy)
{
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true && Map::isValid(x + dx * 4, y + dy * 4) == true)
    {
      if (isAI(x + dx, y + dy) == true && isAI(x + dx * 2, y + dy * 2) == true && isAI(x + dx * 3, y + dy * 3) == true && isAI(x + dx * 4, y + dy * 4) == true)
	return 10;
    }
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x + dx * 3, y + dy * 3) == true && Map::isValid(x - dx, y - dy) == true)
    {
      if (isAI(x + dx, y + dy) == true && isAI(x + dx * 2, y + dy * 2) == true && isAI(x + dx * 3, y + dy * 3) == true && isAI(x - dx, y - dy) == true)
	return 10;
    }
  if (Map::isValid(x + dx, y + dy) == true && Map::isValid(x + dx * 2, y + dy * 2) == true && Map::isValid(x - dx, y - dy) == true  && Map::isValid(x - dx * 2, y - dy * 2) == true)
    {
      if (isAI(x + dx, y + dy) == true && isAI(x + dx * 2, y + dy * 2) == true && isAI(x - dx, y - dy) == true && isAI(x - dx * 2, y - dy * 2) == true)
	return 10;
    }
  return 1;
}

int AI::findQuad(int x, int y)
{
  int valor = 0;
  int ret = 0;

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      if (i != 0 || j != 0)
	{
	  valor = checkQuad(x, y, i, j);
	  if (valor > ret)
	    ret = valor;
	}

  return ret;
}

int AI::findWin(int x, int y)
{
  int valor = 0;
  int ret = 0;

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      if (i != 0 || j != 0)
	{
	  valor = checkWin(x, y, i, j);
	  if (valor > ret)
	    ret = valor;
	}
  return ret;
}

int AI::findTriple(int x, int y)
{
  int valor = 0;
  int ret = 0;

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      if (i != 0 || j != 0)
	{
	  valor = checkTriple(x, y, i, j);
	  if (valor > ret)
	    ret = valor;
	}
  return ret;
}

int AI::findDouble(int x, int y)
{
  int valor = 0;
  int ret = 0;

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      if (i != 0 || j != 0)
	{
	  valor = checkDouble(x, y, i, j);
	  if (valor > ret)
	    ret = valor;
	}

  return ret;
}

int AI::Tactic(int x, int y)
{
  int valor = 0;
  int ret = 0;

  ret = findDouble(x, y);
  if ((valor = findTriple(x, y)) > ret)
    ret = valor;
  if ((valor = findQuad(x, y)) > ret)
    ret = valor;
  if ((valor = findWin(x, y)) > ret)
    ret = valor;
  return ret;
}

void AI::passOver(int x, int y)
 {
   while (y < _map.height())
     {
       this->_isAlone = 0;
       ++x;
       if (x >= _map.width())
	 {
	   x = 0;
	   ++y;
	 }
       if (y < 19)
	 {
	   isAlone(x, y);
	   if (this->_isAlone == 1)
	     {
	       valeur = Tactic(x, y);
	       if (_map.get(x, y).owner() != NULL)
		 valeur = 0;
	       _map.get(x, y).setValor(valeur);
	     }
	   else
	     _map.get(x, y).setValor(0);
	 }
     }
}

void AI::findBestValor(int x, int y, Case *solution)
{
  if (x != sx && y != sy)
    {
      if (_map.get(x, y).valor() > test)
	test = _map.get(x, y).valor();
      if (_map.get(x, y).valor() >= test)
	{
	  if (_map.get(x, y).owner() != NULL)
	    _map.get(x, y).setValor(0);
	  if (test >= solution->valor() &&
	      _map.get(x, y).owner() == NULL )
	    {
	      solution->setValor(test);
	      solution->setX(x);
	      solution->setY(y);
	    }
	  else if (test >= solution->valor() && x == sx && y == sy && _map.get(x, y).owner() != NULL)
	    {
	      _map.get(x, y).setValor(0);
	      borne = _map.get(x, y).valor() - 1;
	    }
	}
    }
}

void AI::passUnder(int x, int y, Case *solution)
{
  x = 0;
  y = 0;
  srand(time(NULL));
  while ( !_arbiter->isValid(x, y, this) )
    {
      x = rand() % 19;
      y = rand() % 19;
    }
  solution->setX(x);
  solution->setY(y);
}

void AI::run()
{
    QTime _time;
    int x = 0;
    int y = 0;
    QString _AI = "AI";
    QString _name = name();

    Case *solution = new Case();
    solution->setValor(0);
    solution->setX(0);
    solution->setY(0);

     _time.start();

     passOver(x, y);
     
     while ( !_arbiter->isValid(x, y, this) )
       {
	 borne = born;
	 nb++;
	 for (x = 0, y = 0, test = 0; y < _map.height() && test != borne && nb <= 50; )
	   {
	     ++x;
	     if (x >= _map.width())
	       {
		 x = 0;
		 ++y;
	       }
	     findBestValor(x, y, solution);
	   }
	 if (nb > 50)
	   passUnder(x, y, solution);
	 x = solution->x();
	 y = solution->y();
	 sx = x;
	 sy = y;
	 if (x == sx && y == sy)
	   {
	     _map.get(x, y).setValor(0);
	     _map.get(sx, sy).setValor(0);
	   }
	 if (_map.get(x, y).owner() != NULL)
	   nb++;
	 if (x == 0 && y == 19)
	   born--;
       }
     nb = 0;
     emit finished(_time.elapsed());
     emit movePlayed(x, y);
     _thread->quit();
}
