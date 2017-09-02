#ifndef PETRI_HPP
#define PETRI_HPP

#include <list>

namespace pn
{
  class Token;
  class Place;
  class Trans;
  class PTArc;
  class TPArc;
  class PetriNet;

  class PetriNet {
  public:
    PetriNet() {};
    virtual ~PetriNet() {};

    std::list<Place*> places;
    std::list<Trans*> transs;

    void run();
  };

  class Token {
  public:
    Token(){};
    virtual ~Token(){};
  };

  class Place {
  public:
    Place( PetriNet &ptn ) { ptn.places.push_back( this ); ; id=ptn.places.size();};
    virtual ~Place() {};

    std::list<TPArc*> in;
    std::list<PTArc*> out;

    std::list<Token*> tokens;

    int id;
  };

  class Trans {
  public:
    Trans( PetriNet &ptn ) { ptn.transs.push_back( this ); id=ptn.transs.size(); };
    virtual ~Trans() {};

    std::list<PTArc*> in;
    std::list<TPArc*> out;

    int id;

    bool isReady();
    void fire();
  };

  class PTArc {
  public:
    PTArc( Place &p, Trans &t ) : from(p), to(t) { p.out.push_back(this); t.in.push_back(this); };
    virtual ~PTArc() {};

    Place &from;
    Trans &to;

    bool isReady();
    void fire();
  };

  class TPArc {
  public:
    TPArc( Trans &t, Place &p ) : from(t), to(p) { t.out.push_back(this); p.in.push_back(this); };
    virtual ~TPArc() {};

    Trans &from;
    Place &to;

    void fire();
  };

};
#endif