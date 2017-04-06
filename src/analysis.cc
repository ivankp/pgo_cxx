#include <iostream>
#include <unordered_map>
#include <cmath>

#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH1.h>

#include "timed_counter.hh"
#include "cat.hh"
#include "sq.hh"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
  if (argc!=2) {
    cout << "usage: " << argv[0] << " file.root" << endl;
    return 1;
  }

  TFile file(argv[1]); // open input root file

  // read branches
  TTreeReader reader("tree",&file);
  TTreeReaderValue<Int_t> id(reader, "id"); // event type
  TTreeReaderValue<Double_t>
    px(reader, "px"),
    py(reader, "py"),
    pz(reader, "pz"),
    E (reader, "E" );

  // container for histograms
  std::unordered_map<Int_t,TH1D> hists;

  // loop over TTree entries
  using tc = timed_counter<Long64_t>;
  for (tc ent(reader.GetEntries(true)); reader.Next(); ++ent) {
    const auto this_id = *id; // event type
    auto it = hists.find(this_id); // find the map iterator corresponding to
                                   // the event type
    if (it==hists.end()) { // create histogram if it does not exist
      it = hists.emplace( // construct in place (avoid copying)
        std::piecewise_construct,
        // map key (event type) constructor arguments
        std::forward_as_tuple(this_id),
        // map value (histogram) constructor arguments
        std::forward_as_tuple(cat("id_",this_id).c_str(),"",100,0.,1e3)
      ).first; // returns std::pair<iterator,bool>
    }

    it->second.Fill(std::sqrt(sq(*px,*py))); // fill the histogram with pT
  }

  for (auto& id_h : hists) {
    TH1D& h = id_h.second;
    // Do something with the histograms
  }

  return 0;
}
