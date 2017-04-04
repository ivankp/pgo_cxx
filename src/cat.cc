#include <iostream>
#include <iomanip>

#include "cat.hh"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  
  cout << cat("char_array",' ',5,' ',std::fixed,std::setprecision(2),4.2)
       << endl;

}
