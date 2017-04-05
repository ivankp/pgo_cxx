#include <TFile.h>
#include <TH1D.h>
#include <TObject.h>
#include <iostream>
#include <string>

void make_hist(const std::string& name, bool write = true) {

    auto hist = new TH1D(name.c_str(), "", 10, 0.0, 1.0);
    if (write) hist->Write(nullptr, TObject::kOverwrite);
    
}

int main() {

    make_hist("not_in_file", false);

    std::string file_name = "file.root";
    TFile file(file_name.c_str(), "recreate");
    make_hist("owned_by_root_dir");

    std::string dir_name = "dir";
    auto        dir      = file.mkdir(dir_name.c_str());
    dir->cd();
    make_hist("owned_by_subdir");
    
    file.Close();
    
    TFile same_file(file_name.c_str());
    same_file.cd(dir_name.c_str());
    same_file.ls();

}
