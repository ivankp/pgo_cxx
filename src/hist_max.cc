#include <TCanvas.h>
#include <TH1D.h>
#include <TStyle.h>
#include <algorithm>
#include <array>
#include <cat.hh>
#include <cstdlib>
#include <string>

int main() {

    constexpr std::size_t n_hists    = 3;
    constexpr auto        half_width = 3.0;

    std::array<TH1D*,       n_hists> hists;
    std::array<std::string, n_hists> names;
    
    for (std::size_t i = 0; i < n_hists; ++i) {
        names[i] = cat(i);
        hists[i] = new TH1D(names[i].c_str(), "", 100, -half_width,
                            half_width);
        hists[i]->FillRandom("gaus", 1000);
    }
    
    // The good part.  Find the maximum of the histograms' maxima in a single
    // statement.
    const auto max_max = 1.1 * (
        *std::max_element(
            hists.cbegin(), hists.cend(), [](const auto x, const auto y) {
                return x->GetMaximum() < y->GetMaximum();
            }
        )
    )->GetMaximum();
    
    gStyle->SetOptStat(false);
    
    for (std::size_t i = 0; i < n_hists; ++i) {
        hists[i]->SetMaximum(max_max);
        TCanvas canvas;
        hists[i]->Draw();
        canvas.SaveAs(cat(names[i], ".pdf").c_str());
    }

}
