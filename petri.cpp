#include <petri.hpp>
#include <iostream>

using namespace pn;
using namespace std;

bool Trans::isReady() {
    for( auto i : in )
    {
      if( i->isReady()==false)
      return false;
    };
    return true;
}

void Trans::fire() {
    for( auto i : in )
    {
      i->fire();
    };
    for( auto o : out )
    {
      o->fire();
    };
}

void TPArc::fire()
{
  cerr << "t" << from.id << " --> p" << to.id << endl;
  to.tokens.push_back( new Token );
}

void PTArc::fire()
{
  cerr << "p" << from.id << " --> t" << to.id << endl;
  from.tokens.pop_front();
}

bool PTArc::isReady() {
    return from.tokens.size() > 0;
}

void PetriNet::run()
{
  static int runs=0;
  runs++;
  cerr << "r:" << runs << endl;

  for( auto t : transs )
  {
    if( t->isReady() )
      t->fire();
  }
}

int main( int argc, char *argv[] )
{
  PetriNet pn;
  Place pa( pn );
  Place pb( pn );
  Place p2( pn );
  Place p3( pn );

  Trans t1( pn );
  Trans t2( pn );

  PTArc pta1(pa, t1 );
  PTArc ptb1(pb, t1 );
  PTArc pt2( p2, t2 );

  TPArc tp12( t1, p2 );
  TPArc tp23( t2, p3 );

  pn.run();

  pa.tokens.push_back( new Token );
  pn.run();

  pb.tokens.push_back( new Token );
  pn.run();

  return 0;
}
