#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "sq.hh"
#include "minuit.hh"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

  struct point { double x, y; };
  std::vector<point> points {
    {1,  0.9},
    {2,  4.1},
    {3,  8.7},
    {4, 16.5},
    {5, 24.9}
  };
  
  Minuit minuit(4);
  minuit.SetPrintLevel(0);

  auto pearson = [](double o, double e){ return sq(o-e)/std::abs(e); };

  auto poly = [](unsigned deg, double x, double* a){
    double p = 1., f = 0.;
    for (unsigned i=0; i<=deg; ++i) {
      f += ( a[i]*p );
      p *= x;
    }
    return f;
  };

  cout << std::fixed << std::setprecision(2);
  for (unsigned deg=1; deg<=3; ++deg) {
    cout << "\n\033[36mFitting polynomial of order " << deg
         << "\033[0m" << endl;

    minuit.clear();

    char name[] = "a";
    for (unsigned i=0; i<=deg; ++i) {
      minuit.DefineParameter(
        i,    // parameter number
        name, // parameter name
        1.,   // start value
        0.01, // step size
        -10., // minimum
        10.   // maximum
      );
      ++name[0];
    }

    minuit( [&,deg](double* a){
      double chi2 = 0.;
      for (auto& p : points) chi2 += pearson( p.y, poly(deg, p.x, a) );
      return chi2;
    } ).Migrad();

    cout << "\n\033[32m";
    for (unsigned i=0; i<=deg; ++i) std::cout << ' ' << minuit.get(i).first;
    cout << "\033[0m" << endl;
  }

}
