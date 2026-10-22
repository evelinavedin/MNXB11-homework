#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "MovingObject.h"

void read()
{
    //open file
    auto file = TFile::Open("tree_file.root", "READ"); 
    //check that the file opened sucessfully
    if (file == nullptr || file->IsZombie()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    //get tree
    auto tree = file->Get<TTree>("tree");
    //check if it was sucessful
    if (tree == nullptr) {
        std::cout << "Error: tree not found" << std::endl;
        file->Close();
        return;
    }

    //adress of brach
    MovingObject *object = nullptr;
    tree->SetBranchAddress("movingObject", &object);

    //Create histogram
    auto hist = new TH2D(
    "hist",
    "Velocity components;vx (m/s);vy (m/s)",
    100, -1.5, 1.5,
    100, -1.5, 1.5
    );

    //get number of entries
    Long64_t nEntries = tree->GetEntries();

    //loop over entries
    for (Long64_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);
    //fill histogram
    hist->Fill(object->Vx(), object->Vy());
    }

    auto canvas = new TCanvas("canvas", "Velocity components");

    hist->Draw("COLZ");
    canvas->SaveAs("velocity_components.pdf");

    tree->Print();
}