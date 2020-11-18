//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec  9 14:37:03 2019 by ROOT version 6.16/00
// from TTree data/Event List
// found on file: 22Na_BGO_5_Dec_2019_29V_single.root
//////////////////////////////////////////////////////////

#ifndef petSysSorter_h
#define petSysSorter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

class petSysSorter {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
	
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         step1;	// value of parameter 1 (when doing parameter scans)
   Float_t         step2;	// value of parameter 2 (when doing parameter scans)
   Long64_t        time;	// time of event, in picoseconds
   UInt_t          channelID;
   Float_t         tot;
   Float_t         energy;
   UShort_t        tacID;
   Int_t           xi;
   Int_t           yi;
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         tqT;	// the fine timing of the chn (crossing time threshold), in TDC clock units (200 MHz => 5ns
   Float_t         tqE;

   // List of branches
   TBranch        *b_step1;   //!
   TBranch        *b_step2;   //!
   TBranch        *b_time;   //!
   TBranch        *b_channelID;   //!
   TBranch        *b_tot;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_tacID;   //!
   TBranch        *b_xi;   //!
   TBranch        *b_yi;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_tqT;   //!
   TBranch        *b_tqE;   //!

   petSysSorter(TTree *tree=0);
   virtual ~petSysSorter();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

// Some global variables //
//	TString *str;

	Int_t minMult=2;

	Double_t tWindow=100000; // in picoseconds

//	Long64_t tWindow=1e5; // 3.1us. I think these units are wrong
//	Long64_t tWindow=3e5; // 9.3us
//	Long64_t tWindowArr[10]={20,100,200,1000,2000,10000,20000,100000,200000,1000000};
//	Double_t tWindowLabels[10]={20,100,200,1000,2000,10000,20000,100000,200000,1000000};
	Double_t tWindowArr[10]={1000,5000,10000,20000,50000,100000,500000,1000000,2000000,10000000};
//	Double_t tWindowLabels[10]={20,100,200,1000,2000,10000,20000,100000,200000,1000000};
///////////////////////////

// Histograms //
//	TH1I* qdc_h[256];
//	for(int i=0;i<256;i++) {
//		if(i<128) qdc_h[i]=new TH1I(Form("qdc%i_h",i),Form("QDC spectrum for chn %i",i),1500,-500,1000);
//		else qdc_h[i]=new TH1I(Form("qdc%i_h",i+256),Form("QDC spectrum for chn %i",i+256),1500,-500,1000);
//	}
////	TH1I* qdc2_h[256];
////	for(int i=0;i<256;i++) {
////		if(i<128) qdc2_h[i]=new TH1I(Form("qdc2_%i_h",i),Form("QDC spectrum for chn %i",i),505,-10,1000);
////		else qdc2_h[i]=new TH1I(Form("qdc2_%i_h",i+256),Form("QDC spectrum for chn %i",i+256),505,-10,1000);
////	}
//	TH1I* tot_h[256];
//	for(int i=0;i<256;i++) {
//		if(i<128) tot_h[i]=new TH1I(Form("tot%i_h",i),Form("TOT spectrum for chn %i",i),500,0,5e6);
//		else tot_h[i]=new TH1I(Form("tot%i_h",i+256),Form("TOT spectrum for chn %i",i+256),500,0,5e6);
//	}
//
//	TH2F* chnVsQDC_h = new TH2F("chnVsQDC_h","ChannelID vs. QDC value",500,-500,1000,400,0,400);
//	chnVsQDC_h->SetXTitle("QDC value");
//	chnVsQDC_h->SetYTitle("channelID");
//	TH2F* chnVsTOT_h = new TH2F("chnVsTOT_h","ChannelID vs. TOT value",550,-1e6,1e7,400,0,400);
//	chnVsTOT_h->SetXTitle("TOT value");
//	chnVsTOT_h->SetYTitle("channelID");
//
//	TH1F* sumEnergyQDC_h = new TH1F("sumEnergyQDC_h",Form("Total Energy (QDC) for mult#geq%i",minMult),2000,-10000,1000);
//	TH1F* sumEnergyTOT_h = new TH1F("sumEnergyTOT_h",Form("Total Energy (TOT) for mult#geq%i",minMult),5500,-1e4,1e5);
//	TH1F* sumTOT_h = new TH1F("sumTOT_h",Form("Sum of TOT signals for mult#geq%i",minMult),5500,-3e6,3e7);
//	TH1I* mult_h = new TH1I("mult_h",Form("Number of SiPMs fired within time window (%.2f us)",tWindow*31e-12/1e-6),300,0,300);
//	mult_h->SetXTitle("# SiPMs");
//	TH1F* timeDiff_h = new TH1F("timeDiff_h","Time difference between consecutive entries",1100,-5,50);
//	timeDiff_h->SetXTitle("Time difference, us");
//
//	TH2F* sumQDCvsMult_h = new TH2F("sumQDCvsMult_h","Multiplicity vs. total energy (QDC)",1000,-10000,1000,100,0,100);
//	sumQDCvsMult_h->SetYTitle("multiplicity");
//	sumQDCvsMult_h->SetXTitle("sum energy (QDC)");
//	TH2F* sumTOTvsMult_h = new TH2F("sumTOTvsMult_h","Multiplicity vs. total energy (TOT)",1100,-1e4,1e5,100,0,100);
//	sumTOTvsMult_h->SetYTitle("multiplicity");
//	sumTOTvsMult_h->SetXTitle("sum energy (TOT)");
//
//	TH2F* multVsTime_h = new TH2F("multVsTime_h","Multiplicity vs time window",10,0,10,100,0,300);
//	multVsTime_h->SetXTitle("Coincidnce Time Window, ns");
//	for(int i=0;i<10;i++) multVsTime_h->GetXaxis()->SetBinLabel(i+1,Form("%.2f",tWindowArr[i]*31.e-12/1e-9));
//
//	TH2I* chnCorrelation1_h = new TH2I("chnCorrelation1_h","Channel correlation plot (first vs current)",400,0,400,400,0,400);
//	TH2I* chnCorrelation2_h = new TH2I("chnCorrelation2_h","Channel correlation plot (previous vs current)",400,0,400,400,0,400);
//	TH1I* hitPattern_h = new TH1I("hitPattern_h","Channel hit pattern",400,0,400);
//
//	TH1F* intTime_h = new TH1F("intTime_h","Integration time (QDC mode only)",1000,0,2.5e3);
//	intTime_h->SetXTitle("Integration time, ns");
////////////////
};

#endif

#ifdef petSysSorter_cxx
petSysSorter::petSysSorter(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("22Na_BGO_5_Dec_2019_29V_single.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("22Na_BGO_5_Dec_2019_29V_single.root");
      }
      f->GetObject("data",tree);

   }
   Init(tree);
}

petSysSorter::~petSysSorter()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t petSysSorter::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t petSysSorter::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void petSysSorter::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("step1", &step1, &b_step1);
   fChain->SetBranchAddress("step2", &step2, &b_step2);
   fChain->SetBranchAddress("time", &time, &b_time);
   fChain->SetBranchAddress("channelID", &channelID, &b_channelID);
   fChain->SetBranchAddress("tot", &tot, &b_tot);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("tacID", &tacID, &b_tacID);
   fChain->SetBranchAddress("xi", &xi, &b_xi);
   fChain->SetBranchAddress("yi", &yi, &b_yi);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("tqT", &tqT, &b_tqT);
   fChain->SetBranchAddress("tqE", &tqE, &b_tqE);
   
   Notify();
}

Bool_t petSysSorter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   
//   str=fChain->GetCurrentFile()->GetName();
//	cout << "Reading data from file: " << str << endl;

   return kTRUE;
}

void petSysSorter::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t petSysSorter::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.

//	if(step1==20 && step2==20)   return 1;
//	else return -1;
	
	return 1;
}
#endif // #ifdef petSysSorter_cxx
