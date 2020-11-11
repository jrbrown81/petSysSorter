#define petSysSorter_cxx
#include "petSysSorter.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include <iostream>

void petSysSorter::Loop()
{
	cout << "Switching to Batch mode" << endl;
	gROOT->SetBatch(1);
	cout << "Executing Loop()" << endl;
//   In a ROOT session, you can do:
//      root> .L petSysSorter.C
//      root> petSysSorter t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

	TString str=fChain->GetCurrentFile()->GetName();
	cout << "Reading data from file: " << str << endl;

   Long64_t nentries = fChain->GetEntriesFast();

//	Int_t minMult=1;
//
//	Long64_t tWindow=1e5; // 3.1us
////	Long64_t tWindow=3e5; // 9.3us
//	Long64_t tWindowArr[10]={20,100,200,1000,2000,10000,20000,100000,200000,1000000};
//	Double_t tWindowLabels[10]={20,100,200,1000,2000,10000,20000,100000,200000,1000000};
	
	TH1I* qdc_h[256];
	for(int i=0;i<256;i++) {
		if(i<128) qdc_h[i]=new TH1I(Form("qdc%i_h",i),Form("QDC spectrum for chn %i",i),1100,-10,100);
		else qdc_h[i]=new TH1I(Form("qdc%i_h",i+256),Form("QDC spectrum for chn %i",i+256),1100,-10,100);
//		if(i<128) qdc_h[i]=new TH1I(Form("qdc%i_h",i),Form("QDC spectrum for chn %i",i),1500,-500,1000);
//		else qdc_h[i]=new TH1I(Form("qdc%i_h",i+256),Form("QDC spectrum for chn %i",i+256),1500,-500,1000);
	}
//	TH1I* qdc2_h[256];
//	for(int i=0;i<256;i++) {
//		if(i<128) qdc2_h[i]=new TH1I(Form("qdc2_%i_h",i),Form("QDC spectrum for chn %i",i),505,-10,1000);
//		else qdc2_h[i]=new TH1I(Form("qdc2_%i_h",i+256),Form("QDC spectrum for chn %i",i+256),505,-10,1000);
//	}
	TH1I* tot_h[256];
	for(int i=0;i<256;i++) {
		if(i<128) tot_h[i]=new TH1I(Form("tot%i_h",i),Form("TOT spectrum for chn %i",i),500,0,5e6);
		else tot_h[i]=new TH1I(Form("tot%i_h",i+256),Form("TOT spectrum for chn %i",i+256),500,0,5e6);
	}

	TH2F* chnVsQDC_h = new TH2F("chnVsQDC_h","ChannelID vs. QDC value",550,-10,100,400,0,400);
//	TH2F* chnVsQDC_h = new TH2F("chnVsQDC_h","ChannelID vs. QDC value",500,-500,1000,400,0,400);
	chnVsQDC_h->SetXTitle("QDC value");
	chnVsQDC_h->SetYTitle("channelID");
	TH2F* chnVsTOT_h = new TH2F("chnVsTOT_h","ChannelID vs. TOT value",550,-1e6,1e7,400,0,400);
	chnVsTOT_h->SetXTitle("TOT value");
	chnVsTOT_h->SetYTitle("channelID");

	TH1F* sumEnergyQDC_h = new TH1F("sumEnergyQDC_h",Form("Total Energy (QDC) for mult#geq%i",minMult),2200,-100,1000);
//	TH1F* sumEnergyQDC_h = new TH1F("sumEnergyQDC_h",Form("Total Energy (QDC) for mult#geq%i",minMult),2000,-10000,1000);
	TH1F* sumEnergyTOT_h = new TH1F("sumEnergyTOT_h",Form("Total Energy (TOT) for mult#geq%i",minMult),5500,-1e4,1e5);
	TH1F* sumTOT_h = new TH1F("sumTOT_h",Form("Sum of TOT signals for mult#geq%i",minMult),5500,-3e6,3e7);
	TH1I* mult_h = new TH1I("mult_h",Form("Number of SiPMs fired within time window (%.2f us)",tWindow*31e-12/1e-6),300,0,300);
	mult_h->SetXTitle("# SiPMs");
	TH1F* timeDiff_h = new TH1F("timeDiff_h","Time difference between consecutive entries",1100,-5,50);
	timeDiff_h->SetXTitle("Time difference, us");

	TH2F* sumQDCvsMult_h = new TH2F("sumQDCvsMult_h","Multiplicity vs. total energy (QDC)",1000,-100,1000,100,0,100);
//	TH2F* sumQDCvsMult_h = new TH2F("sumQDCvsMult_h","Multiplicity vs. total energy (QDC)",1000,-10000,1000,100,0,100);
	sumQDCvsMult_h->SetYTitle("multiplicity");
	sumQDCvsMult_h->SetXTitle("sum energy (QDC)");
	TH2F* sumTOTvsMult_h = new TH2F("sumTOTvsMult_h","Multiplicity vs. total energy (TOT)",1100,-1e4,1e5,100,0,100);
	sumTOTvsMult_h->SetYTitle("multiplicity");
	sumTOTvsMult_h->SetXTitle("sum energy (TOT)");

	TH2F* multVsTime_h = new TH2F("multVsTime_h","Multiplicity vs time window",10,0,10,100,0,300);
	multVsTime_h->SetXTitle("Coincidnce Time Window, ns");
	for(int i=0;i<10;i++) multVsTime_h->GetXaxis()->SetBinLabel(i+1,Form("%.2f",tWindowArr[i]*31.e-12/1e-9));

	TH2I* coincPlot_h = new TH2I("coincPlot_h","Coincidence Plot of largest energies",550,-10,100,550,-10,100);
	coincPlot_h->SetXTitle("energy");
	coincPlot_h->SetYTitle("energy");
	TH2I* coincPlot_21_22_h = new TH2I("coincPlot_21_22_h","Coincidence Plot of chn 22 vs chn 21",550,-10,100,550,-10,100);
	coincPlot_21_22_h->SetXTitle("energy (chn21)");
	coincPlot_21_22_h->SetYTitle("energy (chn22)");

	TH2I* chnCorrelation1_h = new TH2I("chnCorrelation1_h","Channel correlation plot (first vs current)",400,0,400,400,0,400);
	TH2I* chnCorrelation2_h = new TH2I("chnCorrelation2_h","Channel correlation plot (previous vs current)",400,0,400,400,0,400);
	TH2I* chnCorrelation3_h = new TH2I("chnCorrelation3_h","Channel correlation plot (largest energies)",400,0,400,400,0,400);
	TH1I* hitPattern_h = new TH1I("hitPattern_h","Channel hit pattern",400,0,400);

	TH1F* intTime_h = new TH1F("intTime_h","Integration time (QDC mode only)",1000,0,2.5e3);
	intTime_h->SetXTitle("Integration time, ns");
	
	Long64_t prevTime=0;
	Long64_t tmpTime=0;
	Long64_t tmpTimeArr[10]={0,0,0,0,0,0,0,0,0,0};
	Long64_t timeDiff=0;
	Long64_t timeDiffArr[10]={0,0,0,0,0,0,0,0,0,0};
	Float_t sumEnergy=0;
	Long64_t sumTOT=0;
	Int_t mult=0;
	Int_t multArr[10]={0,0,0,0,0,0,0,0,0,0};
	
	Float_t energyList[256];
	Int_t chnArray[256];
	Int_t hitList[256];
	Int_t sortList[256];
	for(int i=0;i<256;i++) {
		energyList[i]=0;
		chnArray[i]=0;
		hitList[i]=0;
		sortList[i]=0;
	}
	
	Int_t tmpChn=0;
	Int_t prevChn=0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       if (Cut(ientry) < 0) continue;
       
      timeDiff=time-tmpTime;
      if(timeDiff<=tWindow) { // good coincidense
			sumEnergy+=energy;
			sumTOT+=tot;
			mult++;
			chnCorrelation1_h->Fill(channelID,tmpChn);
			chnCorrelation2_h->Fill(channelID,prevChn);
			
			energyList[channelID]=energy;
//			chnArray[mult-1]=channelID;
			hitList[mult-1]=channelID;
			
		} else { // not good coincidense
		// Fill histograms
			if(mult>=minMult) {
				sumEnergyQDC_h->Fill(sumEnergy);
				sumTOT_h->Fill(sumTOT);
				sumEnergyTOT_h->Fill(sumEnergy);
			}
			sumQDCvsMult_h->Fill(sumEnergy,mult);
			sumTOTvsMult_h->Fill(sumEnergy,mult);
			mult_h->Fill(mult);
			
			TMath::Sort(256,energyList,sortList);
			coincPlot_h->Fill(energyList[sortList[1]],energyList[sortList[0]]);
			coincPlot_h->Fill(energyList[sortList[0]],energyList[sortList[1]]);
			chnCorrelation3_h->Fill(sortList[1],sortList[0]);
			chnCorrelation3_h->Fill(sortList[0],sortList[1]);
			if(energyList[21]!=0&&energyList[22]!=0) coincPlot_21_22_h->Fill(energyList[21],energyList[22]);

// Zeros arrays
			for(int i=0;i<mult;i++) {
				energyList[hitList[i]]=0;
				hitList[i]=0;
			}
// Write next entry to temporary variables

			energyList[channelID]=energy;
//			chnArray[0]=channelID;
			hitList[0]=channelID;
			
			sumEnergy=energy;
			sumTOT=tot;
			mult=1;
			tmpTime=time;
			tmpChn=channelID;
		}
      
// Test of how number of coincidenses evolves with time window
      for(int i=0;i<10;i++) {
			if((time-tmpTimeArr[i])<=tWindowArr[i]) {
				multArr[i]++;
			} else {
				multVsTime_h->Fill(i,multArr[i]);
				
				multArr[i]=0;
				tmpTimeArr[i]=time;
			}
		}
////////////

		chnVsQDC_h->Fill(energy,channelID);
		chnVsTOT_h->Fill(tot,channelID);
		if(channelID<128) {
			qdc_h[channelID]->Fill(energy);
			tot_h[channelID]->Fill(tot);
		}
		if(channelID>=256) {
			qdc_h[channelID-128]->Fill(energy);
			tot_h[channelID-128]->Fill(tot);
		}
		intTime_h->Fill(tot/1000);
		hitPattern_h->Fill(channelID);
		timeDiff_h->Fill((time-prevTime)*31e-12/1e-6);
//      if(time<tmpTime) cout << "Smaller" << endl;
//      tmpTime=time;
		prevTime=time;
		prevChn=channelID;
				
   } // end of loop over entries
   
   TCanvas* qdcMode_c=new TCanvas("qdcMode_c","QDC mode");
   qdcMode_c->Divide(2,2);
   qdcMode_c->cd(1);
   sumEnergyQDC_h->Draw();
   qdcMode_c->cd(2);
   sumQDCvsMult_h->Draw("colz");
	qdcMode_c->cd(3);
	chnVsQDC_h->Draw("colz");
	qdcMode_c->cd(4);
	intTime_h->Draw();
	
	TCanvas* totMode_c=new TCanvas("totMode_c","TOT mode");
   totMode_c->Divide(2,2);
   totMode_c->cd(1);
   sumEnergyTOT_h->Draw();
   totMode_c->cd(2);
   sumTOTvsMult_h->Draw("colz");
	totMode_c->cd(3);
	chnVsTOT_h->Draw("colz");
	totMode_c->cd(4);
   sumTOT_h->Draw();

   TCanvas* mult_c=new TCanvas("mult_c","Timing and multiplicity plots");
   mult_c->Divide(2,2);
   mult_c->cd(1);
   mult_c->GetPad(1)->SetLogy(1);
   timeDiff_h->Draw();
   mult_c->cd(2);
   mult_c->GetPad(2)->SetLogy(1);
   mult_h->Draw();
   mult_c->cd(3);
   multVsTime_h->SetStats(0);
   multVsTime_h->Draw("colz");
   mult_c->cd(4);
   intTime_h->Draw();
   
   TCanvas* hitPatt_c=new TCanvas("hitPatt_c","Hit patterns etc.");
   hitPatt_c->Divide(2,2);
   hitPatt_c->cd(1);
   hitPattern_h->Draw();
   hitPatt_c->cd(2);
   chnCorrelation1_h->SetStats(0);
   chnCorrelation1_h->Draw("colz");
   hitPatt_c->cd(3);
   chnCorrelation2_h->SetStats(0);
   chnCorrelation2_h->Draw("colz");

	TCanvas* coinc_c=new TCanvas("coinc_c","Coincidense plots");
	coinc_c->Divide(2,2);
	coinc_c->cd(1);
	chnCorrelation3_h->Draw("colz");
   coinc_c->cd(2);
   coincPlot_h->Draw("colz");
   coinc_c->cd(3);
   coincPlot_21_22_h->Draw("colz");
   
   TCanvas* qdc_c1=new TCanvas("qdc_c1","QDC plots 1");
   qdc_c1->Divide(16,8);
   TCanvas* qdc_c2=new TCanvas("qdc_c2","QDC plots 2");
   qdc_c2->Divide(16,8);
	for(int i=0;i<128;i++) {
		qdc_c1->cd(i+1);
		qdc_h[i]->Draw();
		qdc_c2->cd(i+1);
		qdc_h[i+128]->Draw();
	}
	TCanvas* tot_c1=new TCanvas("tot_c1","TOT plots 1");
   tot_c1->Divide(16,8);
   TCanvas* tot_c2=new TCanvas("tot_c2","TOT plots 2");
   tot_c2->Divide(16,8);
	for(int i=0;i<128;i++) {
		tot_c1->cd(i+1);
		tot_h[i]->Draw();
		tot_c2->cd(i+1);
		tot_h[i+128]->Draw();
	}
   
   str.ReplaceAll(".root","_out.root");
   TFile* outFile = new TFile(str,"recreate");
	cout << "Outputting to file: " << str << endl;
   sumEnergyQDC_h->Write();
   sumTOT_h->Write();
   sumEnergyTOT_h->Write();
   chnVsQDC_h->Write();
   chnVsTOT_h->Write();
//   for(int i=0;i<256;i++) {
//		qdc_h[i]->Write();
//		tot_h[i]->Write();
//	}
   mult_h->Write();
   intTime_h->Write();
   multVsTime_h->Write();
   sumQDCvsMult_h->Write();
   sumTOTvsMult_h->Write();
   coincPlot_h->Write();
   coincPlot_21_22_h->Write();
   timeDiff_h->Write();
   chnCorrelation1_h->Write();
   chnCorrelation2_h->Write();
   chnCorrelation3_h->Write();
   hitPattern_h->Write();
   intTime_h->Write();
   qdcMode_c->Write();
   totMode_c->Write();
   mult_c->Write();
   hitPatt_c->Write();
   coinc_c->Write();
   qdc_c1->Write();
   qdc_c2->Write();
   tot_c1->Write();
   tot_c2->Write();
   outFile->Close();
   delete qdcMode_c;
   delete totMode_c;
   delete mult_c;
   delete hitPatt_c;
   delete coinc_c;
   delete qdc_c1;
   delete qdc_c2;
   delete tot_c1;
   delete tot_c2;

//	save(step1,step2);

   gROOT->SetBatch(0);
   cout << "Return to normal mode" << endl;
}

void run(TString string)
{
	TFile f1(string);
	TTree* tree;
	f1.GetObject("data",tree);
	if(tree) cout << "data tree found in file: " << string << endl;
	else cout << "Error!" << endl;
	petSysSorter pss(tree);
	
	pss.Loop();
	
	delete tree;
}

/*int save(Float_t step1,Float_t step2)
{
	
	str.ReplaceAll(".root","_out.root");
	TFile* outFile = new TFile(str,"recreate");
	cout << "Outputting to file: " << str << endl;
	sumEnergyQDC_h->Write();
	sumTOT_h->Write();
	sumEnergyTOT_h->Write();
	chnVsQDC_h->Write();
	chnVsTOT_h->Write();
//   for(int i=0;i<256;i++) {
//		qdc_h[i]->Write();
//		tot_h[i]->Write();
//	}
	mult_h->Write();
	intTime_h->Write();
	multVsTime_h->Write();
	sumQDCvsMult_h->Write();
	sumTOTvsMult_h->Write();
	timeDiff_h->Write();
	chnCorrelation1_h->Write();
	chnCorrelation2_h->Write();
	hitPattern_h->Write();
	intTime_h->Write();
	qdcMode_c->Write();
	totMode_c->Write();
	mult_c->Write();
	hitPatt_c->Write();
	qdc_c1->Write();
	qdc_c2->Write();
	tot_c1->Write();
	tot_c2->Write();
	outFile->Close();
	delete qdcMode_c;
	delete totMode_c;
	delete mult_c;
	delete hitPatt_c;
	delete qdc_c1;
	delete qdc_c2;
	delete tot_c1;
	delete tot_c2;
	
	return 1;
}
*/
