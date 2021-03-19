// A index_appender_view osztály template első
// template paramétere egy 0-tól indexelhető STL-es konténer, a második, hogy
// ez  milyen adatokat tárol. A view-hoz az első template paraméterrel
// megegyező típusú konténert lehet adni (add), de a konténer kívülről
// változhat. Az egymás után add-olt konténerek folytonosan lesznek indexelve
// at/operator[] segítségével. Működjön vector<bool>-lal, valamint ne
// kelljen megadni a második template paramétert.

#include <iostream>
#include "indapper.h"
#include <vector>
#include <algorithm>
#include <string>
#include "indapper.h"
#include <deque>

const int max = 1000;

bool check()
{
  std::deque<int> da;
  index_appender_view<std::deque<int>, int> idi;
  for( int i = 0; i < max; ++i )
  {
    da.push_back( i );
  }
  std::deque<int> db = da;
  std::deque<int> dc = da;
  idi.add( da );
  idi.add( db );
  idi.add( dc );

  index_appender_view<std::string, char> is;
  std::string h( "Hallo" );
  std::string w( "Worl" );
  is.add( h );
  is.add( w );
  h[ 1 ] = 'e';
  w.push_back( 'd' );

  const index_appender_view<std::string, char> cis = is;

  std::vector<double> v;
  v.push_back( 1.76 );
  v.push_back( 3.31 );
  index_appender_view<std::vector<double>, double> ivd;

  ivd.add( v );

  v[ 0 ] = 5.45;
  
  if ( 3 * max != idi.size() || ivd.at( 0 ) <= v[ 1 ] ||
       0 != idi.at( max ) || 'H' != cis.at( 0 ) ||
       'e' != is.at( 1 ) || 'o' != cis.at( 6 ) ||
       10 != cis.size() || 0 != idi.at( 2 * max ) )
  {
    return false;
  }

  ivd[ 1 ] += 4.58;
  std::swap( idi[ 0 ], idi[ 1 ] );

  if ( 7.2 >= ivd[ 1 ] || 'l' != cis[ 2 ] || 0 != idi[ max ] ||
       7.3 >= v[ 1 ] || 0 != da[ 1 ] || 1 != da[ 0 ] )
  {
    return false;
  }

  index_appender_view<std::string> s;
  s.add( w );

  std::vector<bool> c;
  c.push_back( true );
  c.push_back( false );
  index_appender_view<std::vector<bool> > ivb;
  ivb.add( c );
  
  ivb[ 0 ] = false;
  ivb[ 1 ] = true;
  
  const index_appender_view<std::vector<bool> > civb = ivb;
  
  return ( c[ 1 ] && 2 == ivb.size() && 'o' == s[ 1 ] && 5 == s.size() );
}

int main()
{
  std::cout
    << "Your solution is " << (check() ? "" : "not ")
    << "ready for submission.\n";
}