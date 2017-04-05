#include <TCanvas.h>
#include <TH1.h>
#include <TH1D.h>
#include <TStyle.h>
#include <cstdlib>
#include <memory>
#include <random>

int main() {

    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> dist;

    TH1::AddDirectory(false);

    auto sample_mean = std::make_unique<TH1D>("sample_mean", "", 100, 0.0,
                                              1.0);
    for (std::size_t i = 0; i < 1'000'000; ++i) {
        auto sample = std::make_unique<TH1D>("sample", "", 100, 0.0, 1.0);
        for (std::size_t j = 0; j < 10; ++j) sample->Fill(dist(engine));
        sample_mean->Fill(sample->GetMean());
    }
    
    gStyle->SetOptStat(false);
    TCanvas canvas;
    sample_mean->Draw();
    canvas.SaveAs("sample_mean.pdf");

}
