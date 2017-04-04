#ifndef MINUIT_HH
#define MINUIT_HH

#include <utility>
#include <functional>

#include <TMinuit.h>

class Minuit: private TMinuit {
  std::function<double(double*)> m_fcn;

public:
  Minuit(size_t maxnpar): TMinuit(maxnpar) { }

  Minuit(const Minuit&) = delete;
  Minuit(const TMinuit&) = delete;

  template <typename F>
  void SetFCN(F&& fcn) { m_fcn = std::forward<F>(fcn); }

  template <typename F>
  Minuit& operator()(F&& fcn) {
    SetFCN(std::forward<F>(fcn));
    return *this;
  }

  inline auto get(int i) const noexcept {
    std::pair<double,double> p;
    GetParameter(i,p.first,p.second);
    return p;
  }

  using TMinuit::SetPrintLevel;
  using TMinuit::DefineParameter;
  using TMinuit::Migrad;
 
private:
  // Evaluate the minimisation function (called internally)
  //  Input parameters:
  //    npar:    number of currently variable parameters
  //    par:     array of (constant and variable) parameters
  //    flag:    Indicates what is to be calculated (see example below)
  //    grad:    array of gradients
  //  Output parameters:
  //    fval:    The calculated function value.
  //    grad:    The (optional) vector of first derivatives).
  virtual Int_t Eval(
    Int_t npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag
  ) final {
    fval = m_fcn(par);
    return 0;
  }
};

#endif
