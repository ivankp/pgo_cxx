#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

template <typename... Args>
inline std::string cat(Args&&... args) {
  std::stringstream ss;
  (ss << ... << args);
  return ss.str();
}

int main(int argc, char* argv[]) {
  
  cout << cat("char_array",' ',5,' ',std::fixed,std::setprecision(2),4.2)
       << endl;

}

