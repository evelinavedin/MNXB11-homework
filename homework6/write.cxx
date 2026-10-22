#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>

void write()
{
    // Initialize your object e.g. as a pointer
    MovingObject *mObj = new MovingObject; 
    // Create your root file here
    TFile *file = new TFile("tree_file.root", "RECREATE");
    // Create your TTree here
    TTree *tree = new TTree("tree", "Velocity measurements");
    // And the associated branches underneath
    // for example a branch with your personal object type
    tree->Branch("movingObject", &mObj);

    // define how many events you want
    Int_t nEntries = 10000; 

    gRandom->SetSeed(12345); 

    // For loop
    for (Int_t i{0}; i<nEntries; i++)
    {
    Double_t vx = gRandom->Gaus(0.0, 0.30);
    Double_t vy = gRandom->Gaus(0.0, 0.30);
    Double_t vz = gRandom->Gaus(0.0, 0.30);

        //call tree->Fill() after updating the velocity
        mObj->SetVelocity(vx, vy, vz);
        tree->Fill(); 
    } 

    file->cd();
    tree->Write();
    file->Close();

    // Remember to delete it again otherwise you will have memory leak!
    delete mObj;
    delete file;
}
// save the tree/file