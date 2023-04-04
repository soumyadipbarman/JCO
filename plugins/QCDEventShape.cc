// -*- C++ -*-
//
// Package:    Test/QCDEventShape
// Class:      QCDEventShape
// 
/**\class QCDEventShape QCDEventShape.cc Test/QCDEventShape/plugins/QCDEventShape.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Soumyadip Barman
//         Created:  Tue, 02 Feb 2021 10:24:21 GMT
//
//


// system include files

#define DIJETAVE 

////for data
//#define JETENERGY
//#define TRIGGER

////for Madgraph
//#define LHAPDF
//#define JETRESO
//#define TRACKSYS
//#define TRIGGER

////for Pythia8 & Herwig7
#define JETRESO
#define TRIGGER

////For Flat
//#define FLAT

//#define LUMIWEIGHT

//#define PREFIRE


//#define MERGE_BIN
//#define PUNOMI
//#define PUUP
//#define PUDOWN

////For GenParticle only
//#define GENPART


#include <memory>
#include <map>
#include <string>
#include <vector>
#include "TCanvas.h"
#include "TFormula.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include <cmath>
#include "TMath.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"
#include "TUnfoldBinning.h"
#include "TUnfoldDensity.h"
#include "TUnfoldBinningXML.h"
#include "TUnfold.h"
#include "TUnfoldSys.h"

#include "TH2F.h"
#include "TProfile.h"
#include <fstream>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <time.h>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReport.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReportEntry.h"
#include "CondFormats/DataRecord/interface/L1GtStableParametersRcd.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "FWCore/Framework/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"

#include "Test/QCDEventShape/plugins/EventShape_vector.h" 


#include "DataFormats/Common/interface/View.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

//#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"
#include <JetMETCorrections/Modules/interface/JetResolution.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <CondFormats/DataRecord/interface/JetResolutionRcd.h>
#include <CondFormats/DataRecord/interface/JetResolutionScaleFactorRcd.h>
#include "FWCore/Utilities/interface/typelookup.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TProfile.h"
#include "CLHEP/Vector/ThreeVector.h"

using namespace edm;
using namespace reco;
using namespace std;
using namespace CLHEP;
using namespace trigger;
using namespace math;

static const int nvar=32;
static const int nhist=10;
static const int typen=2; 
static const int nHLTmx=10;

const int ndef=3;
const int njet=2;
const int nkappa=10;

const char* jcodef[ndef]={"D","L","T"};
double jetname[njet]={1,2};
double kappa[nkappa]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
//double kappa[nkappa]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,};

double recojet1_pt, recojet2_pt; 
double genrecojet1_pt, genrecojet2_pt;

//Fine Binning
/*
double recobins[ndef][njet][nkappa]={{{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}},
                                        {{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}},
                                        {{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}}};
double genbins[ndef][njet][nkappa]={{{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}},
                                        {{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}},
                                        {{40,40,40,40,40,40,40,40,40,40},{40,40,40,40,40,40,40,40,40,40}}};
*/
double recobins[ndef][njet][nkappa]={{{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}},
                                        {{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}},
                                        {{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}}};
double genbins[ndef][njet][nkappa]={{{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}},
                                        {{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}},
                                        {{120,120,120,120,120,120,120,120,120,120},{120,120,120,120,120,120,120,120,120,120}}};
/*
//Final Binning
double recobins[ndef][njet][nkappa]={{{60,60,60,60,60,40,40,40,40,40},{60,60,60,60,60,40,40,40,40,40}},
					{{20,20,30,36,36,40,40,40,40,40},{20,20,30,36,36,40,40,40,40,40}},
					{{20,20,30,36,36,40,40,40,40,40},{20,20,30,36,36,40,40,40,40,40}}};
double genbins[ndef][njet][nkappa]={{{30,30,30,30,30,20,20,20,20,20},{30,30,30,30,30,20,20,20,20,20}},
					{{10,10,15,18,18,20,20,20,20,20},{10,10,15,18,18,20,20,20,20,20}},
					{{10,10,15,18,18,20,20,20,20,20},{10,10,15,18,18,20,20,20,20,20}}};
*/

//Reco Ranges
double recomin[ndef][njet][nkappa]={{{-4.0,-4.0,-3.0,-2.0,-2.0,-1.0,-1.0,-1.0,-1.0,-1.0},{-4.0,-4.0,-3.0,-2.0,-2.0,-1.0,-1.0,-1.0,-1.0,-1.0}},
					{{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0},{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0}},
					{{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0},{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0}}};
double recomax[ndef][njet][nkappa]={{{4.0,4.0,3.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0},{4.0,4.0,3.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0}},
					{{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0},{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0}},
					{{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0},{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0}}};

//Gen Ranges
double genmin[ndef][njet][nkappa]={{{-4.0,-4.0,-3.0,-2.0,-2.0,-1.0,-1.0,-1.0,-1.0,-1.0},{-4.0,-4.0,-3.0,-2.0,-2.0,-1.0,-1.0,-1.0,-1.0,-1.0}},
					{{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0},{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0}},
					{{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0},{-0.4,-0.6,-0.6,-0.8,-0.8,-1.0,-1.0,-1.0,-1.0,-1.0}}};
double genmax[ndef][njet][nkappa]={{{4.0,4.0,3.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0},{4.0,4.0,3.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0}},
					{{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0},{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0}},
					{{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0},{0.4,0.6,0.6,0.8,0.8,1.0,1.0,1.0,1.0,1.0}}};

//----------------------------------------HT2 Binning For 2D unfold 
double recohtbins[nHLTmx+1] = {92, 119, 185, 251, 319, 388, 467, 518, 579, 669, 3000.0};
//double recohtbins[nHLTmx+1] = {92, 119, 185, 251, 319, 388, 467, 518, 579, 669, 6000.0};

/*
#ifdef MERGE_BIN
double recohtbins[nHLTmx+1] = {83, 109, 176, 247, 318, 387, 477, 573, 3000.0}; //For 2018
#else
double recohtbins[nHLTmx+1] = {66, 95, 155, 227, 286, 350, 444, 557, 3000.0}; // For 2016 Trigger
#endif
*/

//---------------------------------------------Lumi weight
/*
int iera = 2;// 0 for Run 2016, 1 for Run 2017 , 2 for Run 2018
double lumi[3] = {36330, 41480, 59830};
double total_lumi = lumi[0]+lumi[1]+lumi[2];
double lumiwtt = lumi[iera]/total_lumi;
*/
//-------------------------------------------
const int npileupmx=99; //49;
double rat_pileup[nHLTmx][npileupmx]={{0}};
//clock_t t1,t2;

//UL PU
double mcpileup[npileupmx] ={ 1.1840841518e-05, 3.46661037703e-05, 8.98772521472e-05, 7.47400487733e-05, 0.000123005176624,
    0.000156501700614, 0.000154660478659, 0.000177496185603, 0.000324149805611, 0.000737524009713,
    0.00140432980253, 0.00244424508696, 0.00380027898037, 0.00541093042612, 0.00768803501793,
    0.010828224552, 0.0146608623707, 0.01887739113, 0.0228418813823, 0.0264817796874,
    0.0294637401336, 0.0317960986171, 0.0336645950831, 0.0352638818387, 0.036869429333,
    0.0382797316998, 0.039386705577, 0.0398389681346, 0.039646211131, 0.0388392805703,
    0.0374195678161, 0.0355377892706, 0.0333383902828, 0.0308286549265, 0.0282914440969,
    0.0257860718304, 0.02341635055, 0.0213126338243, 0.0195035612803, 0.0181079838989,
    0.0171991315458, 0.0166377598339, 0.0166445341361, 0.0171943735369, 0.0181980997278,
    0.0191339792146, 0.0198518804356, 0.0199714909193, 0.0194616474094, 0.0178626975229,
    0.0153296785464, 0.0126789254325, 0.0100766041988, 0.00773867100481, 0.00592386091874,
    0.00434706240169, 0.00310217013427, 0.00213213401899, 0.0013996000761, 0.000879148859271,
    0.000540866009427, 0.000326115560156, 0.000193965828516, 0.000114607606623, 6.74262828734e-05,
    3.97805301078e-05, 2.19948704638e-05, 9.72007976207e-06, 4.26179259146e-06, 2.80015581327e-06,
    1.14675436465e-06, 2.52452411995e-07, 9.08394910044e-08, 1.14291987912e-08, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0};

//HLT Path PileUP
double datpileup[nHLTmx][npileupmx] ={{1.2261e-05, 3.25983e-05, 9.35687e-05, 0.0001699, 0.000139256, 0.000180311, 0.000187726, 0.000187903, 0.000305346, 0.00106055, 0.00224675, 0.0041572, 0.0056444, 0.00624168, 0.00810533, 0.0122968, 0.019227, 0.0280904, 0.0373568, 0.0467056, 0.0556469, 0.0618341, 0.0629647, 0.0592638, 0.0532431, 0.0475882, 0.043455, 0.0406739, 0.0386113, 0.0367205, 0.0347792, 0.0327671, 0.0306462, 0.0283367, 0.02581, 0.0231219, 0.0203712, 0.0176587, 0.0150804, 0.0127326, 0.0107031, 0.00904938, 0.00778586, 0.00688539, 0.00628898, 0.00591491, 0.00566643, 0.00544368, 0.00516112, 0.00476436, 0.00424043, 0.00361885, 0.00295392, 0.00230621, 0.00172573, 0.00124209, 0.000863727, 0.000583162, 0.000384216, 0.000248216, 0.000157935, 9.93742e-05, 6.20605e-05, 3.86037e-05, 2.39999e-05, 1.49631e-05, 9.38534e-06, 5.93849e-06, 3.79797e-06, 2.45746e-06, 1.60848e-06, 1.06377e-06, 7.09552e-07, 4.76282e-07, 3.20995e-07, 2.1675e-07, 1.46363e-07, 9.86812e-08, 6.63442e-08, 4.443e-08, 2.96124e-08, 1.96278e-08, 1.29301e-08, 8.46096e-09, 5.49688e-09, 3.54407e-09, 2.26679e-09, 1.43778e-09, 9.0409e-10, 5.63447e-10, 3.47948e-10, 2.12864e-10, 1.28986e-10, 7.74034e-11, 4.59938e-11, 2.70587e-11, 1.57592e-11, 9.08545e-12, 5.18446e-12},
{9.4803e-06, 2.43905e-05, 6.70879e-05, 0.000127414, 0.000117507, 0.000162817, 0.000201244, 0.000203821, 0.000302931, 0.000881722, 0.00181937, 0.00337518, 0.00470357, 0.00543067, 0.00697829, 0.00975552, 0.0137474, 0.0185058, 0.0233242, 0.028136, 0.0331135, 0.0378768, 0.0418185, 0.0447997, 0.0471482, 0.0491591, 0.0507096, 0.0514705, 0.05121, 0.0498862, 0.0476408, 0.0446857, 0.0411886, 0.0372795, 0.0331211, 0.0289208, 0.0248784, 0.0211437, 0.0178131, 0.0149509, 0.0125983, 0.0107695, 0.00944514, 0.00857149, 0.00806291, 0.00780614, 0.00766833, 0.00751382, 0.00722893, 0.00674512, 0.0060521, 0.00519882, 0.00426791, 0.00334978, 0.00251928, 0.00182181, 0.00127217, 0.000861816, 0.000569053, 0.000367888, 0.00023384, 0.0001467, 9.11635e-05, 5.63139e-05, 3.4702e-05, 2.14091e-05, 1.32703e-05, 8.29051e-06, 5.23356e-06, 3.34337e-06, 2.16219e-06, 1.41444e-06, 9.34406e-07, 6.21997e-07, 4.16207e-07, 2.79319e-07, 1.87618e-07, 1.25915e-07, 8.43107e-08, 5.62583e-08, 3.73741e-08, 2.46996e-08, 1.62275e-08, 1.05924e-08, 6.866e-09, 4.41749e-09, 2.8199e-09, 1.78534e-09, 1.12072e-09, 6.97335e-10, 4.29974e-10, 2.62666e-10, 1.58944e-10, 9.52561e-11, 5.65307e-11, 3.32173e-11, 1.93235e-11, 1.11277e-11, 6.34289e-12},
{1.30648e-05, 3.37663e-05, 9.12109e-05, 0.000170794, 0.000133763, 0.000188243, 0.000206265, 0.000198962, 0.000349243, 0.00119873, 0.00263237, 0.00502284, 0.00704542, 0.00811181, 0.0102334, 0.0138368, 0.0187139, 0.0241071, 0.0288303, 0.0325694, 0.0358095, 0.0387399, 0.0410596, 0.042627, 0.0437118, 0.0446279, 0.0453181, 0.0454978, 0.0449377, 0.0435849, 0.0415752, 0.0390991, 0.0362649, 0.0331213, 0.0297665, 0.0263672, 0.0230922, 0.0200491, 0.0172941, 0.0148753, 0.0128537, 0.0112901, 0.010217, 0.00961726, 0.00941714, 0.00948889, 0.00966428, 0.00976155, 0.00962373, 0.0091542, 0.00833831, 0.00724787, 0.00600549, 0.00474767, 0.00359006, 0.00260609, 0.00182396, 0.00123648, 0.000815649, 0.000525855, 0.000332673, 0.000207274, 0.000127623, 7.79163e-05, 4.73332e-05, 2.87189e-05, 1.74725e-05, 1.07015e-05, 6.62187e-06, 4.15074e-06, 2.63935e-06, 1.7025e-06, 1.11256e-06, 7.3488e-07, 4.89303e-07, 3.2748e-07, 2.19741e-07, 1.47498e-07, 9.88584e-08, 6.60615e-08, 4.39621e-08, 2.91067e-08, 1.91581e-08, 1.25279e-08, 8.13458e-09, 5.2422e-09, 3.35148e-09, 2.12495e-09, 1.33571e-09, 8.32159e-10, 5.1372e-10, 3.14182e-10, 1.90323e-10, 1.14179e-10, 6.78275e-11, 3.9893e-11, 2.32281e-11, 1.3388e-11, 7.63778e-12},
{1.28126e-05, 3.34441e-05, 8.92851e-05, 0.000170918, 0.000137532, 0.000210186, 0.00023046, 0.000215237, 0.000375096, 0.00120188, 0.00258399, 0.0048825, 0.00662783, 0.00716984, 0.00856015, 0.0111956, 0.0148646, 0.0190208, 0.022816, 0.0261005, 0.0294923, 0.0332697, 0.0369061, 0.0399426, 0.0425614, 0.0450982, 0.0474048, 0.0489871, 0.0494621, 0.0487723, 0.0471259, 0.0447763, 0.041865, 0.0384599, 0.0346883, 0.0307604, 0.0268976, 0.023252, 0.0199101, 0.0169348, 0.0143851, 0.0123128, 0.0107426, 0.00965859, 0.00899747, 0.00864905, 0.00846704, 0.00829293, 0.00798951, 0.00747089, 0.00671881, 0.00578429, 0.00475809, 0.00374104, 0.00281748, 0.00203933, 0.00142442, 0.000964327, 0.000635579, 0.000409543, 0.000258998, 0.00016132, 9.92926e-05, 6.05896e-05, 3.67804e-05, 2.22931e-05, 1.35443e-05, 8.2809e-06, 5.11303e-06, 3.19702e-06, 2.02737e-06, 1.30401e-06, 8.49702e-07, 5.59682e-07, 3.71656e-07, 2.4812e-07, 1.66104e-07, 1.11257e-07, 7.44217e-08, 4.96423e-08, 3.29811e-08, 2.18032e-08, 1.4331e-08, 9.35941e-09, 6.07006e-09, 3.90752e-09, 2.49568e-09, 1.58087e-09, 9.92849e-10, 6.18053e-10, 3.81255e-10, 2.33001e-10, 1.41049e-10, 8.45636e-11, 5.02034e-11, 2.95098e-11, 1.71725e-11, 9.89228e-12, 5.64048e-12},
{1.40344e-05, 3.64128e-05, 9.89987e-05, 0.000182249, 0.000136458, 0.000175894, 0.000187971, 0.00018103, 0.000327709, 0.0012372, 0.00274328, 0.00521054, 0.0073317, 0.00851708, 0.010838, 0.0148209, 0.0202994, 0.0263458, 0.0314896, 0.035271, 0.0381437, 0.0403982, 0.0420175, 0.0430443, 0.0436453, 0.0439649, 0.0439474, 0.0434663, 0.0424258, 0.0407842, 0.0386302, 0.036122, 0.0333579, 0.0303821, 0.0272792, 0.0241946, 0.021273, 0.0186067, 0.0162464, 0.0142361, 0.0126261, 0.011458, 0.0107435, 0.0104501, 0.0104952, 0.010745, 0.0110258, 0.0111518, 0.010967, 0.0103857, 0.00941182, 0.00814097, 0.006718, 0.00529534, 0.00399742, 0.0029002, 0.00203045, 0.00137756, 0.000909539, 0.000586819, 0.000371421, 0.000231511, 0.000142654, 8.72417e-05, 5.31722e-05, 3.24355e-05, 1.98865e-05, 1.23009e-05, 7.69906e-06, 4.8844e-06, 3.14202e-06, 2.04746e-06, 1.34893e-06, 8.96297e-07, 5.99031e-07, 4.01697e-07, 2.69677e-07, 1.80921e-07, 1.21111e-07, 8.07983e-08, 5.36685e-08, 3.54637e-08, 2.32968e-08, 1.52054e-08, 9.85528e-09, 6.34024e-09, 4.04699e-09, 2.56206e-09, 1.60819e-09, 1.00059e-09, 6.16922e-10, 3.7685e-10, 2.28027e-10, 1.36651e-10, 8.10928e-11, 4.76477e-11, 2.77168e-11, 1.59604e-11, 9.09719e-12},
{1.50897e-05, 3.93997e-05, 0.00010682, 0.000196268, 0.000143931, 0.000183437, 0.000195187, 0.000185572, 0.000341132, 0.00131967, 0.00293127, 0.00555634, 0.00776068, 0.0088927, 0.0111914, 0.0152094, 0.0207495, 0.026851, 0.032001, 0.0357213, 0.0385119, 0.0407166, 0.042307, 0.0432853, 0.0437876, 0.0439548, 0.0437578, 0.0431164, 0.0419738, 0.040301, 0.0381741, 0.0357292, 0.0330441, 0.0301501, 0.0271253, 0.0241123, 0.0212519, 0.0186327, 0.0163021, 0.0143035, 0.0126882, 0.0114998, 0.0107508, 0.0104102, 0.0103979, 0.0105858, 0.0108087, 0.0108898, 0.0106804, 0.0100967, 0.00914045, 0.00790102, 0.00651628, 0.00513302, 0.00387185, 0.00280673, 0.00196362, 0.00133182, 0.000879676, 0.000568294, 0.000360544, 0.000225492, 0.000139532, 8.5738e-05, 5.2511e-05, 3.21793e-05, 1.98067e-05, 1.22881e-05, 7.70578e-06, 4.89312e-06, 3.14789e-06, 2.05028e-06, 1.34968e-06, 8.9595e-07, 5.98245e-07, 4.00832e-07, 2.68902e-07, 1.8029e-07, 1.20627e-07, 8.0441e-08, 5.34116e-08, 3.52827e-08, 2.31714e-08, 1.51199e-08, 9.79765e-09, 6.30189e-09, 4.02176e-09, 2.54565e-09, 1.59764e-09, 9.93873e-10, 6.12696e-10, 3.74219e-10, 2.26407e-10, 1.35664e-10, 8.04981e-11, 4.72931e-11, 2.75077e-11, 1.58384e-11, 9.02676e-12},
{1.3538e-05, 3.51595e-05, 9.54755e-05, 0.000176364, 0.00013294, 0.00017296, 0.000185989, 0.00018022, 0.000328806, 0.0012275, 0.00273387, 0.00520954, 0.00738149, 0.0086785, 0.011099, 0.0151369, 0.0206256, 0.0267004, 0.0319878, 0.0360219, 0.0391458, 0.0415667, 0.0432558, 0.0442686, 0.0447952, 0.0450095, 0.0448818, 0.0442959, 0.0431527, 0.0414022, 0.0391214, 0.0364629, 0.0335337, 0.0303975, 0.0271591, 0.023976, 0.0209928, 0.0182929, 0.0159137, 0.0138867, 0.0122515, 0.0110414, 0.0102615, 0.00987638, 0.00980622, 0.00992878, 0.0100896, 0.0101254, 0.00989974, 0.00933577, 0.00843501, 0.00727919, 0.00599442, 0.00471506, 0.00355142, 0.00257079, 0.00179617, 0.00121689, 0.000803132, 0.000518657, 0.000329085, 0.000205925, 0.000127535, 7.84492e-05, 4.80993e-05, 2.95043e-05, 1.81737e-05, 1.12801e-05, 7.07519e-06, 4.49287e-06, 2.89032e-06, 1.88256e-06, 1.23946e-06, 8.23038e-07, 5.49823e-07, 3.68617e-07, 2.47469e-07, 1.66052e-07, 1.11191e-07, 7.42096e-08, 4.93136e-08, 3.26007e-08, 2.14257e-08, 1.39903e-08, 9.07146e-09, 5.83827e-09, 3.72795e-09, 2.3609e-09, 1.4824e-09, 9.22599e-10, 5.68999e-10, 3.4767e-10, 2.10424e-10, 1.26133e-10, 7.48684e-11, 4.40002e-11, 2.56006e-11, 1.47448e-11, 8.40601e-12},
{8.21463e-06, 2.13834e-05, 5.97399e-05, 0.000113044, 9.91145e-05, 0.000143799, 0.000163109, 0.000174258, 0.000300787, 0.000951537, 0.00213666, 0.00412879, 0.00619767, 0.00798274, 0.0104905, 0.0141701, 0.0192486, 0.0251988, 0.0308561, 0.0356524, 0.0396484, 0.0428207, 0.0450378, 0.0464128, 0.0472937, 0.0479609, 0.0483734, 0.048296, 0.0474884, 0.045818, 0.0433431, 0.0402448, 0.0366963, 0.03284, 0.0288474, 0.0249247, 0.0212587, 0.0179685, 0.0151122, 0.0127183, 0.0108027, 0.00936726, 0.00838952, 0.00781723, 0.00756684, 0.007526, 0.00756181, 0.0075387, 0.00734445, 0.00691409, 0.00624294, 0.00538744, 0.0044382, 0.00349306, 0.00263292, 0.00190743, 0.00133378, 0.000904348, 0.000597316, 0.000386009, 0.000245065, 0.000153418, 9.50392e-05, 5.84592e-05, 3.58302e-05, 2.1962e-05, 1.35119e-05, 8.37307e-06, 5.24122e-06, 3.32051e-06, 2.13074e-06, 1.38421e-06, 9.09011e-07, 6.02127e-07, 4.01319e-07, 2.68484e-07, 1.79893e-07, 1.20492e-07, 8.05513e-08, 5.36795e-08, 3.56219e-08, 2.35194e-08, 1.54394e-08, 1.00707e-08, 6.52352e-09, 4.19465e-09, 2.67619e-09, 1.69351e-09, 1.06258e-09, 6.60873e-10, 4.07326e-10, 2.48736e-10, 1.50461e-10, 9.01409e-11, 5.34775e-11, 3.14134e-11, 1.82686e-11, 1.05172e-11, 5.9932e-12},
{4.24759e-06, 1.09596e-05, 3.12109e-05, 6.1272e-05, 6.43298e-05, 0.000106733, 0.000125148, 0.000138472, 0.000199589, 0.000507884, 0.00103917, 0.00198071, 0.00316141, 0.0045428, 0.00643408, 0.00907755, 0.0126714, 0.016877, 0.0210418, 0.0248802, 0.0282544, 0.0309868, 0.033079, 0.0347016, 0.0360907, 0.0374025, 0.0385229, 0.0392181, 0.0393333, 0.0388254, 0.0377583, 0.0362433, 0.0343571, 0.0321569, 0.0297518, 0.0273015, 0.0249464, 0.022769, 0.0208224, 0.0191734, 0.0179099, 0.0171132, 0.0168239, 0.0170182, 0.0175927, 0.0183597, 0.0190611, 0.0194126, 0.0191731, 0.0182099, 0.0165386, 0.0143293, 0.0118379, 0.00933643, 0.00704939, 0.00511515, 0.00358324, 0.00243512, 0.00161331, 0.00104688, 0.00066824, 0.000421236, 0.00026318, 0.000163541, 0.000101421, 6.2984e-05, 3.92956e-05, 2.47007e-05, 1.56773e-05, 1.00592e-05, 6.52612e-06, 4.27749e-06, 2.82796e-06, 1.88202e-06, 1.25805e-06, 8.42925e-07, 5.65057e-07, 3.78376e-07, 2.52763e-07, 1.68264e-07, 1.11524e-07, 7.35393e-08, 4.82121e-08, 3.14073e-08, 2.03198e-08, 1.30504e-08, 8.31695e-09, 5.25748e-09, 3.29549e-09, 2.0477e-09, 1.26095e-09, 7.69349e-10, 4.64998e-10, 2.78361e-10, 1.65016e-10, 9.68619e-11, 5.62905e-11, 3.2384e-11, 1.84417e-11},
{4.24759e-06, 1.09596e-05, 3.12109e-05, 6.1272e-05, 6.43298e-05, 0.000106733, 0.000125148, 0.000138472, 0.000199589, 0.000507884, 0.00103917, 0.00198071, 0.00316141, 0.0045428, 0.00643408, 0.00907755, 0.0126714, 0.016877, 0.0210418, 0.0248802, 0.0282544, 0.0309868, 0.033079, 0.0347016, 0.0360907, 0.0374025, 0.0385229, 0.0392181, 0.0393333, 0.0388254, 0.0377583, 0.0362433, 0.0343571, 0.0321569, 0.0297518, 0.0273015, 0.0249464, 0.022769, 0.0208224, 0.0191734, 0.0179099, 0.0171132, 0.0168239, 0.0170182, 0.0175927, 0.0183597, 0.0190611, 0.0194126, 0.0191731, 0.0182099, 0.0165386, 0.0143293, 0.0118379, 0.00933643, 0.00704939, 0.00511515, 0.00358324, 0.00243512, 0.00161331, 0.00104688, 0.00066824, 0.000421236, 0.00026318, 0.000163541, 0.000101421, 6.2984e-05, 3.92956e-05, 2.47007e-05, 1.56773e-05, 1.00592e-05, 6.52612e-06, 4.27749e-06, 2.82796e-06, 1.88202e-06, 1.25805e-06, 8.42925e-07, 5.65057e-07, 3.78376e-07, 2.52763e-07, 1.68264e-07, 1.11524e-07, 7.35393e-08, 4.82121e-08, 3.14073e-08, 2.03198e-08, 1.30504e-08, 8.31695e-09, 5.25748e-09, 3.29549e-09, 2.0477e-09, 1.26095e-09, 7.69349e-10, 4.64998e-10, 2.78361e-10, 1.65016e-10, 9.68619e-11, 5.62905e-11, 3.2384e-11, 1.84417e-11}};

//-------------------------------------------
static const int nsrc = 27;   // Change form 26 as for 2015 data .  See JEC for 2017 94X
const char* srcnames[nsrc] = {"AbsoluteStat", "AbsoluteScale", "AbsoluteMPFBias", "Fragmentation", "SinglePionECAL", "SinglePionHCAL", "FlavorQCD", "TimePtEta", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF","RelativePtBB", "RelativePtEC1", "RelativePtEC2","RelativePtHF","RelativeBal", "RelativeSample", "RelativeFSR", "RelativeStatFSR", "RelativeStatEC", "RelativeStatHF", "PileUpDataMC", "PileUpPtRef", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF"};
//-------------------------------------------
double intlumi[nHLTmx]={1., 1, 1, 1, 1, 1,1,1,1,1};
double lumiwt[nHLTmx]={1., 1, 1, 1, 1, 1,1,1,1,1};
//unsigned int l1trg[4], hlttr[8], tetrg[2];
unsigned int mypow_2[32];

//std::ofstream myfile;
//myfile.open("txt.log");

//const bool m_trigeff = true;
const int njetptmn=nHLTmx; // 8; //10
const int njetptbin=120;

#ifdef DIJETAVE
const char* jethlt_name[nHLTmx]={"HLT_PFJet60_v","HLT_PFJet80_v","HLT_PFJet140_v","HLT_PFJet200_v","HLT_PFJet260_v","HLT_PFJet320_v","HLT_PFJet400_v","HLT_PFJet450_v","HLT_PFJet500_v","HLT_PFJet550_v"};
const char* jethlt_lowest={"HLT_PFJet40_v"};

double leadingPtThreshold[njetptmn+1] ={92, 119, 185, 251, 319, 388, 467, 518, 579, 669, 3000.0}; //trigger turn on for 2017 UL JetHT sample
//double leadingPtThreshold[njetptmn+1] ={92, 119, 185, 251, 319, 388, 467, 518, 579, 669, 6000.0};

/*
#ifdef MERGE_BIN
double leadingPtThreshold[njetptmn+1] ={83, 109, 176, 247, 318, 387, 477, 573, 3000.0}; //Fit Value dijet trigger 2018
#else
double leadingPtThreshold[njetptmn+1] ={66, 95, 155, 227, 286, 350, 444, 557, 3000.0}; //Fit Value dijet trigger 2016
#endif
//double leadingPtThreshold[njetptmn+1] ={83, 109, 172, 241, 309, 377, 462, 570, 3000.0}; //Fit Value dijet trigger 2017
*/

//double compres[njetptmn] = {1630, 5320, 62.1, 38.9, 27.0, 4.33, 1.23, 1.0};
//double compres[njetptmn] = {1630, 5320, 62.1, 38.9, 27.0, 4.33, 1.23, 1.0};

//#else

#endif

#ifdef DIJETAVE
double jethlt_thr[nHLTmx]={60,80,140,200,260,320,400,450,500,550};
//#else

#endif
double prescl[nHLTmx];

#ifdef TRACKSYS
const int ntype=3; 
#else
const int ntype=2;
#endif

const int njetetamn=1; // GMA 4;
#ifdef  LHAPDF
const int nnnmx=101;
double pdfwt[nnnmx];
#endif

#ifdef  JETENERGY//const int nsrc = 26;
//const int nsrc = 26;
const int njecmx=2*nsrc+1;
#elif defined(JETRESO)
const int njecmx = 3;
#else
const int njecmx=1;
#endif

const int nGenReso=1;
double etarange[njetetamn] ={2.1}; //2.5
double resetarange[njetetamn+4] ={0, 0.5, 1.0, 1.5}; //, 2.0, 2.5, 3.0, 3.5};
double par0[njetetamn+4]={1.02, 1.02, 1.022, 1.017, 0.98}; //, 0.9327};
double par1[njetetamn+4]={7.3e-6, -7.3e-6, -5.66e-6, -9.9e-6, 1.41e-4}; //, 4.6e-4};
double par2[njetetamn+4]={-8.2e-9, -8.2e-9, -3.58e-9, -4.18e-9, -6.104e-8}; //, -4.041e-7};
double particlept[4]={0.0, 0.25, 0.50, 1.00};

#ifdef TRACKSYS
const char* typname[ntype]={"Jets", "Charged Particles"};
#else
const char* typname[ntype]={"Jets", "Charged Particles"};
#endif
static const int njetmx =30;

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double Phi_0_2pi(double x) {
  while (x >= 2*M_PI) x -= 2*M_PI;
  while (x <     0.)  x += 2*M_PI;
  return x;
}

double Phi_mpi_pi(double x) {
  while (x >= M_PI) x -= 2*M_PI;
  while (x < -M_PI) x += 2*M_PI;
  return x;
}

double dPhi(double phi1,double phi2){
  phi1=Phi_0_2pi(phi1);
  phi2=Phi_0_2pi(phi2);
  return Phi_mpi_pi(phi1-phi2);
}

double dPT(double pt1, double pt2){
	double pt = ((pt1 - pt2) / (pt1 + pt2));
	return pt;
}

 int sbitx(unsigned ival, int ibit) {
 unsigned den = mypow_2[ibit]; // unsigned(pow(2., double(ibit)));
 int isel = unsigned(ival/den)%2;
 //  int isel = unsigned(ival/den);
 //cout <<"iv "<< ival<<" "<<ibit<<" "<<den<<" "<<ival/den<<" "<<unsigned(ival/den)<<" "<<isel<<endl;

 return isel;
}

double respfun(double a, double b, double c, double x){
  double func=a+b*x+c*x*x;
  return func;
}

double JetCharge1(int charge, double candspt, double jpt, double k);

double candsmom(int charge, double candspt, double k);
double candsmom2(double p, double k);

double dotproduct(double candspx, double candspy, double candspz, double jpx, double jpy, double jpz, double jpt, double k);
double crossproduct(double candspx, double candspy, double candspz, double jpx, double jpy, double jpz, double jpt, double k);

double dotProductPower(const Hep3Vector& v1, const Hep3Vector& v2, double k);
double crossProductPower(const Hep3Vector& v1, const Hep3Vector& v2, double k);

struct triggervar{
  HepLorentzVector trg4v;
  bool		  both;
  bool            level1;
  bool            highl;
  int             ihlt;
  int             prescl;
};

//
// class declaration
//

class QCDEventShape : public edm::EDAnalyzer {
   public:
      explicit QCDEventShape(const edm::ParameterSet&);
      ~QCDEventShape();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
 
  // int sbitx(unsigned ival, int ibit);

  bool isHistFill;
  bool isTrigger;
  bool isRECO[ntype][njetetamn];
  bool isMC;
  //bool isRECOJC;
  //bool isGENJC;
  //  bool isParticle; //Do we want particle level informations, other than jets ?
  //  bool isGenParticle; //Do we want Simulated particle level informations, other than jets ?
  bool isReconstruct; // otherwise Only generator level informations  
  //  bool isPartQCD; //For tracker variables, recosntruct QCD EVT variables
  bool isJetQCD;  //For Jet variables, recosntruct QCD EVT variables
  bool isGenJET; // Genjet information or note (for herwig/alpgen, donot store this ?)
  //  double trackPtThreshold; //Threshold of track Pt to store it in root file, -ve implies don't store

  //  double etarange; //Eta range of all jets
  double ptthreshold; //Pt threshold of JEC jets
  double leadingPtthreshold; //Pt threshold of JEC leading jet
  bool   isOtherAlgo; // store Kt4 and ak7 variables or not
  double weight=1; //weight for histogramme fit
  double weight2=1;
 
  std::string m_resolutions_file;
  std::string scalefile;

  std::string theHLTTag;
  //unsigned int mypow_2[32];
  int nevt;

  std::string theRootFileName;
  //TFile* //theFile;
  //TTree* //T1;

  //ifstream myfile ("example.txt");
  //std::ofstream myfile;
  //myfile.open("txt.log");
  TDirectoryFile *TUnfoldBinng2D =new TDirectoryFile("analyzeBasicPat2D","2D Unfolding Historgams");
  TH2F* h_2ht;

  TH1F* vec_anglex[nhist];

  //Jet Charge 1D
  TH1F* h_recovar[njetptmn][njetetamn][ndef][njet][nkappa];
  TH1F* h_genvar[njetptmn][njetetamn][ndef][njet][nkappa];
  TH1F* h_recofake[njetptmn][njetetamn][ndef][njet][nkappa];
  TH1F* h_genmiss[njetptmn][njetetamn][ndef][njet][nkappa]; 
  TH2F* h_RM[njetptmn][njetetamn][ndef][njet][nkappa];
  //TH2F* RM_test[njetptmn][njetetamn];
  TH2F* RM_test[njetetamn];

  //Profile histogram
  TProfile* hprof;
  TProfile* hchpt; // jetpt vs. charge

  //static const int njetmx =30;
  //int npfjets; 
  int nchg;
  int pfjetmul[njetmx];
  float pfjetpx[njetmx], pfjetpy[njetmx], pfjetpz[njetmx], pfjeten[njetmx],  pfjetenuc[njetmx], neuemf[njetmx], neuhad[njetmx];
  float pfjetenscl[njetmx], pfjetensmr[njetmx];
  float jetpt, jeteta, jetphi; 
  int nallpf, ncharged;
  float thphi[nhist], thrust[nhist], anglex[nhist];
  float jtthan;
  int irunhlt, l1pres[nHLTmx],  hltpres[nHLTmx], compres[nHLTmx]; 
  static const int nprimx=150;
  int nprim, ntkpm[nprimx];
  //float  primdx[nprimx], primdy[nprimx], primdz[nprimx], 
  float primpr[nprimx];
  int irun, ilumi, ibrnc;
  unsigned int ievt;
  float inslumi;
  int nsicls, ntottrk;
//#ifdef FLAT 
  bool isFlat=1;
//#else 
  //bool isFlat=0;
//#endif

   float defweight=1.0, weighttrg=1., qlow=-10., qhigh=100000.;
//-------------------------------------------TunfoldBinning
//-------------------------------------------2D Bining using TUnfoldBinning Jet Charge

  TUnfoldBinning *binsRec2D[njetetamn][ndef][njet][nkappa];
  TUnfoldBinning *binsGen2D[njetetamn][ndef][njet][nkappa];
  TUnfoldBinning *RecoBinning2D[njetetamn][ndef][njet][nkappa];
  TUnfoldBinning *GenBinning2D[njetetamn][ndef][njet][nkappa];  
//-------------------------------------------Jet Charge 2D TUnfoldBinning Histograms

  TH1* h_recovar2D[njetetamn][ndef][njet][nkappa];
  TH1* h_genvar2D[njetetamn][ndef][njet][nkappa];
  TH1* h_recofake2D[njetetamn][ndef][njet][nkappa];
  TH1* h_genmiss2D[njetetamn][ndef][njet][nkappa];
  TH2* h_RM2D[njetetamn][ndef][njet][nkappa];
//-------------------------------------------
  //TH1F* recojt_hist;
  //TH1F* recojt_pt[njetetamn][nHLTmx];
  TH1F* recojt_pt[njetetamn];
  TH1F* recojt_eta;
  TH1F* recojt_phi;

  TH1F* recojtallave_pt[njetetamn];
  TH1F* recojtallavewt1_pt[njetetamn];

  TH1F* recojtave_pt[njetetamn][nHLTmx];
  TH1F* recojtavewt1_pt[njetetamn][nHLTmx];
  TH1F* recojt1_pt[njetetamn];
  TH1F* recojt1_eta;
  TH1F* recojt1_phi;

  TH1F* recojt2_pt[njetetamn];
  TH1F* recojt2_eta;
  TH1F* recojt2_phi;

  TH1F* recojt3_pt[njetetamn];
  TH1F* recojt3_eta;
  TH1F* recojt3_phi;

  TH1F* recoht2_pt[njetetamn];

  TH1F* hjetdpt[njetetamn];
  TH1F* hjetdphi[njetetamn];
  TH1F* hjetptbypl[njetetamn];
  TH1F* hjetpt2bypt1[njetetamn];
  TH1F* hjetpt3bypt2[njetetamn];
  //TH1F* recochg_hist;
  TH1F* recochg_pt;
  TH1F* recochg_eta;
  TH1F* recochg_phi;

  TH1F* recochg1_pt;
  TH1F* recochg1_eta;
  TH1F* recochg1_phi;

  TH1F* recochg2_pt;
  TH1F* recochg2_eta;
  TH1F* recochg2_phi;

  TH1F* recochg3_pt;
  TH1F* recochg3_eta;
  TH1F* recochg3_phi;
//-------------------------------------------
  //TH1F* genjt_hist;
  TH1F* genjt_pt[njetetamn];
  TH1F* genjt_eta;
  TH1F* genjt_phi;
  TH1F* genjtallave_pt[njetetamn];

  TH1F* genjt1_pt[njetetamn];
  TH1F* genjt1_eta;
  TH1F* genjt1_phi;

  TH1F* genjt2_pt[njetetamn];
  TH1F* genjt2_eta;
  TH1F* genjt2_phi;

  TH1F* genjt3_pt[njetetamn];
  TH1F* genjt3_eta;
  TH1F* genjt3_phi;

  TH1F* genjetdpt[njetetamn];
  TH1F* genjetdphi[njetetamn];
  TH1F* genjetptbypl[njetetamn];
  TH1F* genjetpt2bypt1[njetetamn];
  TH1F* genjetpt3bypt2[njetetamn];

  //TH1F* genchg_hist;
  TH1F* genchg_pt;
  TH1F* genchg_eta;
  TH1F* genchg_phi;

  TH1F* genchg1_pt;
  TH1F* genchg1_eta;
  TH1F* genchg1_phi;

  TH1F* genchg2_pt;
  TH1F* genchg2_eta;
  TH1F* genchg2_phi;

  TH1F* genchg3_pt;
  TH1F* genchg3_eta;
  TH1F* genchg3_phi;
/*
  TH1F* genneu_hist;
  TH1F* genneu_pt;
  TH1F* genneu_eta;
  TH1F* genneu_phi;

  TH1F* genjt_oth_pt[njetetamn];
  TH1F* genjt_oth_eta;
  TH1F* genjt_oth_phi;

  TH1F* genchg_oth_hist;
  TH1F* genchg_oth_pt;
  TH1F* genchg_oth_eta;
  TH1F* genchg_oth_phi;

  TH1F* genneu_oth_hist;
  TH1F* genneu_oth_pt;
  TH1F* genneu_oth_eta;
  TH1F* genneu_oth_phi;
*/

  TH1F* prim_hist[nHLTmx+1];
  TH1F* prim_sel[nHLTmx+1];

  TH1F* prim_hist_rewt[nHLTmx+1];
  TH1F* prim_sel_rewt[nHLTmx+1];

  TH2F* prim_correl;

  TH1F* prim_alltrk[2];
  TH1F* prim_seltrk[2];
  TH1F* prim_goodtrk[2];
  TH1F* prim_dx[2];
  TH1F* prim_dy[2];
  TH2F* prim_dxy[2];
  TH1F* prim_dz[2];  
  TH1F* prim_prob[2];

  TH1F* h_jetpt[nHLTmx][njetetamn];
  TH1F* h_jeteta[nHLTmx];
  TH1F* h_jetphi[nHLTmx][njetetamn];
  TH1F* h_njets[njetetamn];
  TH1F* h_nchg[njetetamn];

  TH1F* gen_njets[njetetamn];

  TH1F* trgjet_angle[nHLTmx][2];
  TH2F* trgjet_2dangle[nHLTmx][2];
  TH1F* trgjet_pt[nHLTmx][2];
  TH1F* trgjet_eta[nHLTmx][2];
  TH1F* trgjet_phi[nHLTmx][2];
  TH1F* prbjet_pt[nHLTmx][2];
  TH1F* prbjet_eta[nHLTmx][2];
  TH1F* prbjet_phi[nHLTmx][2];

  //Dijet trigger efficiency
  TH1F* hlt_dijettag[nHLTmx][njetetamn];
  TH1F* hlt_dijetprob[nHLTmx][njetetamn];

  //Trigger Normal case
  TH1F* counthist; 

//-------------------------------------------Member data
  edm::EDGetTokenT<GenEventInfoProduct> generator1_;
  edm::EDGetTokenT<pat::JetCollection> jetSrcToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > genSrcToken_;
  edm::EDGetTokenT<pat::PackedCandidateCollection> PFSrcToken_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  edm::EDGetTokenT<pat::METCollection> metToken_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<reco::BeamSpot> beamSpot_;
  edm::EDGetTokenT<reco::GenJetCollection> genjetToken_;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileup_;
  edm::EDGetTokenT<reco::PFJetCollection> ak5PFjetToken_;
  edm::EDGetTokenT<reco::GenJetCollection> ak5GenJetToken_;
  const edm::EDGetTokenT<std::vector<double> > pdfCTEQWeightsInputToken_;
  const edm::EDGetTokenT<std::vector<double> > pdfMMTHWeightsInputToken_;
  const edm::EDGetTokenT<std::vector<double> > pdfNNPDFWeightsInputToken_;
  const edm::EDGetTokenT<LHERunInfoProduct> LHERunInfoToken_;
  const edm::EDGetTokenT<LHEEventProduct> lheEventProductToken_;
  edm::EDGetTokenT<double> m_rho_token;

  edm::EDGetTokenT< double > prefweight_token;
  edm::EDGetTokenT< double > prefweightup_token;
  edm::EDGetTokenT< double > prefweightdown_token;

  float qscale;
  float wtfact; //MC : eventinfo->weight(); data : hltpres[ihltfill]*l1pres[ihltfill];
  int procid, npilup1, npilup2; //1:-5 to -1, 2:0 to 3

  int idall;
  float xfrac1, xfrac2, xpdf1, xpdf2;  

  //HLTConfigProvider hltConfig_;
  HLTPrescaleProvider hltPrescaleProvider_;
  int nreco, naa, nbb, ncc;
  int Reco=0,Gen=0,RM=0;

std::vector<JetCorrectionUncertainty*> vsrc; // (nsrc);
reweight::PoissonMeanShifter PShiftUp_;
reweight::PoissonMeanShifter PShiftDown_;
edm::LumiReWeighting *LumiWeights_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
  QCDEventShape::QCDEventShape(const edm::ParameterSet& iConfig):
  generator1_(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("evtinfo"))),
  jetSrcToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  genSrcToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getUntrackedParameter<edm::InputTag>("genSrc"))),
  PFSrcToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfSrc"))),
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("metSrc"))),
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  beamSpot_(consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("bsSrc"))),
  genjetToken_(consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genjetSrc"))),
  pileup_(consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("pileupSrc"))),
  ak5PFjetToken_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("ak5pfJetSrc"))),
  ak5GenJetToken_(consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("ak5genJetSrc"))),
  pdfCTEQWeightsInputToken_(consumes<std::vector<double> >(iConfig.getParameter<edm::InputTag>("PDFCTEQWeightsInputTag"))),
  pdfMMTHWeightsInputToken_(consumes<std::vector<double> >(iConfig.getParameter<edm::InputTag>("PDFMMTHWeightsInputTag"))),
  pdfNNPDFWeightsInputToken_(consumes<std::vector<double> >(iConfig.getParameter<edm::InputTag>("PDFNNPDFWeightsInputTag"))),
  LHERunInfoToken_(consumes<LHERunInfoProduct, edm::InRun >(iConfig.getParameter<edm::InputTag>("LHERunInfoProductInputTag"))),
  lheEventProductToken_(consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("LHEEventProductInputTag"))),
  prefweight_token(consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProb"))),
  prefweightup_token(consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProbUp"))),
  prefweightdown_token(consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProbDown"))),
  hltPrescaleProvider_(iConfig, consumesCollector(), *this)
{
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  m_rho_token = consumes<double>(iConfig.getParameter<edm::InputTag>("rho"));
  //m_resolutions_file = iConfig.getParameter<edm::FileEEInPath>("resolutionsFile").fullPath();
  //scalefile = iConfig.getParameter<edm::FileInPath>("scaleFactorsFile").fullPath();
  isHistFill = iConfig.getUntrackedParameter<bool>("HistFill", true);
  //isHistFill2 = pset.getUntrackedParameter<bool>("HistFill2", false);                                            
  isTrigger = iConfig.getUntrackedParameter<bool>("Trigger", true);
  //isRECO = iConfig.getUntrackedParameter<bool>("RECO", false);
  isMC = iConfig.getUntrackedParameter<bool>("MonteCarlo", false);
  isReconstruct = iConfig.getUntrackedParameter<bool>("Reconstruct", true);
  isJetQCD = iConfig.getUntrackedParameter<bool>("JetQCD", false);
  isGenJET = iConfig.getUntrackedParameter<bool>("GenJET", false);
  //etarange = iConfig.getUntrackedParameter<double>("EtaRange", 5.0);
  ptthreshold = iConfig.getUntrackedParameter<double>("PtThreshold", 10.0);
  //leadingPtthreshold = iConfig.getUntrackedParameter<double>("LeadingPtThreshold", 40.0);
  isOtherAlgo = iConfig.getUntrackedParameter<bool>("OtherAlgo", false);
  weight2 = iConfig.getUntrackedParameter<double>("HistWeight", 1.0);
  weight = weight2;
  theHLTTag = iConfig.getUntrackedParameter<string>("HLTTag", "HLT");
  theRootFileName = iConfig.getUntrackedParameter<string>("RootFileName");
 
  //cout << "Testing 1 ==== " <<njecmx<< endl;
                                                                                                                                                                        
//Define TUnfoldBinning
  char RecoBinName[100], GenBinName[100], Axisname[100]; 
  char name[200];
  char title[200];
//-------------------------------------------Define TUnfoldBinning Jet Charge
for (int iet=0; iet<njetetamn; iet++) {
	for(int id=0; id<ndef; id++){
		for(int ij=0; ij<njet; ij++){
			for (int ik=0; ik<nkappa; ik++){
				sprintf(RecoBinName, "Detector2d_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
		                binsRec2D[iet][id][ij][ik] = new TUnfoldBinning(RecoBinName);
                		sprintf(RecoBinName, "Recobin2d_eta%i_d%i_j%i_k%i",iet, id,ij,ik);
                		RecoBinning2D[iet][id][ij][ik] = binsRec2D[iet][id][ij][ik]->AddBinning(RecoBinName);
                		sprintf(Axisname, "d%i_j%i_k%i", id,ij,ik);
                		RecoBinning2D[iet][id][ij][ik]->AddAxis(Axisname, recobins[id][ij][ik], recomin[id][ij][ik], recomax[id][ij][ik], false, false);
                		sprintf(Axisname, "pt");
                		RecoBinning2D[iet][id][ij][ik]->AddAxis(Axisname, nHLTmx, recohtbins, false, false);

				sprintf(GenBinName, "Generator2d_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
		                binsGen2D[iet][id][ij][ik] = new TUnfoldBinning(GenBinName);
                		sprintf(GenBinName, "Genbin2d_eta%i_d%i_j%i_k%i",iet,id,ij,ik);
                		GenBinning2D[iet][id][ij][ik] = binsGen2D[iet][id][ij][ik]->AddBinning(GenBinName);
               			sprintf(Axisname, "d%i_j%i_k%i", id, ij, ik);
                		GenBinning2D[iet][id][ij][ik]->AddAxis(Axisname, genbins[id][ij][ik], genmin[id][ij][ik], genmax[id][ij][ik], false, false);
                		sprintf(Axisname, "pt");
                		GenBinning2D[iet][id][ij][ik]->AddAxis(Axisname, nHLTmx, recohtbins, false, false);
				}
			}
		}
	}

for (int iet=0; iet<njetetamn; iet++) {
        for(int id=0; id<ndef; id++){
                for(int ij=0; ij<njet; ij++){
                        for (int ik=0; ik<nkappa; ik++){
				if (isReconstruct) {
					sprintf(name, "dd_reco_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
                        		sprintf(title, "2D Reco %g Q_{%s,%g}^{%g}", etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                        		h_recovar2D[iet][id][ij][ik] = binsRec2D[iet][id][ij][ik]->CreateHistogram(name,false,0,title);
					h_recovar2D[iet][id][ij][ik]->Sumw2();

					sprintf(name, "dd_recofake_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
                                        sprintf(title, "2D Reco Fake %g Q_{%s,%g}^{%g}", etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                                        h_recofake2D[iet][id][ij][ik] = binsRec2D[iet][id][ij][ik]->CreateHistogram(name,false,0,title);
                                        h_recofake2D[iet][id][ij][ik]->Sumw2(); 
					}
					
					sprintf(name, "dd_gen_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
		                        sprintf(title, "2D Gen %g Q_{%s,%g}^{%g}", etarange[iet], jcodef[id], jetname[ij],kappa[ik]);
                		        h_genvar2D[iet][id][ij][ik] = binsGen2D[iet][id][ij][ik]->CreateHistogram(name,false,0,title);
                        		h_genvar2D[iet][id][ij][ik]->Sumw2();

					sprintf(name, "dd_genmiss_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
                                        sprintf(title, "2D Gen Miss %g Q_{%s,%g}^{%g}", etarange[iet], jcodef[id], jetname[ij],kappa[ik]);
                                        h_genmiss2D[iet][id][ij][ik] = binsGen2D[iet][id][ij][ik]->CreateHistogram(name,false,0,title);
                                        h_genmiss2D[iet][id][ij][ik]->Sumw2();

					if (isReconstruct) {
						sprintf(name, "dd_corr_eta%i_d%i_j%i_k%i", iet, id,ij,ik);
		                                sprintf(title, "Gen_Reco %g Q_{%s,%g}^{%g}", etarange[iet], jcodef[id], jetname[ij],kappa[ik]);
                		                h_RM2D[iet][id][ij][ik] = TUnfoldBinning::CreateHistogramOfMigrations(binsRec2D[iet][id][ij][ik], binsGen2D[iet][id][ij][ik], name ,0,0, title);
                                		h_RM2D[iet][id][ij][ik]->Sumw2();
					}
				}
			}
		}
	}
//-------------------------------------------Jet Charge Histogram
for(int ipt=0; ipt<njetptmn; ipt++){
        for(int iet=0; iet<njetetamn; iet++){
		for(int id=0; id<ndef; id++){
			for(int ij=0; ij<njet; ij++){
                		for (int ik=0; ik<nkappa; ik++){
					if (isReconstruct) {
					sprintf(name, "reco_jc_pt%i_eta%i_d%i_j%i_k%i",ipt,iet, id, ij, ik);
		                        sprintf(title, "Reco %i %g Q_{%s,%g}^{%g}", int(leadingPtThreshold[ipt]), etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                		        h_recovar[ipt][iet][id][ij][ik] = fs->make<TH1F>(name, title, recobins[id][ij][ik], recomin[id][ij][ik], recomax[id][ij][ik]);
                                	h_recovar[ipt][iet][id][ij][ik]->Sumw2();

					sprintf(name, "recofake_jc_pt%i_eta%i_d%i_j%i_k%i",ipt,iet, id, ij, ik);
                                	sprintf(title, "Reco Fake %i %g Q_{%s,%g}^{%g}", int(leadingPtThreshold[ipt]), etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                               	 	h_recofake[ipt][iet][id][ij][ik] = fs->make<TH1F>(name, title, recobins[id][ij][ik], recomin[id][ij][ik], recomax[id][ij][ik]);
                                	h_recofake[ipt][iet][id][ij][ik]->Sumw2();

					sprintf(name, "RM_jc_pt%i_eta%i_d%i_j%i_k%i",ipt,iet, id, ij, ik);
                               	 	sprintf(title, "RM %i %g Q_{%s,%g}^{%g}",int(leadingPtThreshold[ipt]), etarange[iet] , jcodef[id], jetname[ij], kappa[ik]);
                                	h_RM[ipt][iet][id][ij][ik] = fs->make<TH2F>(name, title, recobins[id][ij][ik], recomin[id][ij][ik], recomax[id][ij][ik], genbins[id][ij][ik], genmin[id][ij][ik], genmax[id][ij][ik]);
                                	h_RM[ipt][iet][id][ij][ik]->Sumw2();
					}		
					
					sprintf(name, "gen_jc_pt%i_eta%i_d%i_j%i_k%i",ipt,iet, id, ij, ik);
		                       	sprintf(title, "Gen %i %g Q_{%s,%g}^{%g}", int(leadingPtThreshold[ipt]), etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                		        h_genvar[ipt][iet][id][ij][ik] = fs->make<TH1F>(name, title, genbins[id][ij][ik], genmin[id][ij][ik], genmax[id][ij][ik]);
                                	h_genvar[ipt][iet][id][ij][ik]->Sumw2();
						
					sprintf(name, "genmiss_jc_pt%i_eta%i_d%i_j%i_k%i",ipt,iet, id, ij, ik);
                                       	sprintf(title, "Gen %i %g Q_{%s,%g}^{%g}", int(leadingPtThreshold[ipt]), etarange[iet], jcodef[id], jetname[ij], kappa[ik]);
                                        h_genmiss[ipt][iet][id][ij][ik] = fs->make<TH1F>(name, title, genbins[id][ij][ik], genmin[id][ij][ik], genmax[id][ij][ik]);
                                        h_genmiss[ipt][iet][id][ij][ik]->Sumw2();
						
					}
				}
			}
		}
	}

//for(int ipt=0; ipt<njetptmn; ipt++){
        for(int iet=0; iet<njetetamn; iet++){
		sprintf(name, "RMtest_jc_eta%i",iet);
                sprintf(title, "RMtest %g",etarange[iet]);
                //RM_test[iet] = fs->make<TH2F>(name, title, 40, -1, 1, 40, -1,1);
		RM_test[iet] = fs->make<TH2F>(name, title, 200, 0, 2000, 200, 0, 2000);
                RM_test[iet]->Sumw2();
	}
//}
//-------------------------------------------
 sprintf(name, "corr_jet");
 sprintf(title, "Gen_Reco_HT2");
 h_2ht=fs->make<TH2F>(name, title, 10, leadingPtThreshold, 10, leadingPtThreshold);
//-------------------------------------------
#ifndef GENPART                     
  //recojt_hist = fs->make<TH1F>("recojt_hist","# of recojets",20,-0.5, 19.5);
  //recojt_hist->Sumw2();
  //recojt_pt = fs->make<TH1F>("recojt_pt","Et_{recojets}",100,20., 2020.);
  //recojt_pt->Sumw2();
  recojt_eta = fs->make<TH1F>("recojt_eta","#eta_{recojets}",100,-2.5, 2.5);
  recojt_eta->Sumw2();
  recojt_phi = fs->make<TH1F>("recojt_phi","#phi_{recojets}",100,-M_PI, M_PI);
  recojt_phi->Sumw2();

  //recojt1_pt = fs->make<TH1F>("recojet1_pt","Et_{recojets}",100,20., 2020.);
  //recojt1_pt->Sumw2();
  recojt1_eta = fs->make<TH1F>("recojet1_eta","#eta_{recojets}",100,-2.5, 2.5);
  recojt1_eta->Sumw2();
  recojt1_phi = fs->make<TH1F>("recojet1_phi","#phi_{recojets}",100,-M_PI, M_PI);
  recojt1_phi->Sumw2();

  //recojt2_pt = fs->make<TH1F>("recojet2_pt","Et_{recojets}",100,20., 2020.);
  //recojt2_pt->Sumw2();
  recojt2_eta = fs->make<TH1F>("recojet2_eta","#eta_{recojets}",100,-2.5, 2.5);
  recojt2_eta->Sumw2();
  recojt2_phi = fs->make<TH1F>("recojet2_phi","#phi_{recojets}",100,-M_PI, M_PI);
  recojt2_phi->Sumw2();

  //recojt3_pt = fs->make<TH1F>("recojet2_pt","Et_{recojets}",100,20., 2020.);
  //recojt3_pt->Sumw2();
  recojt3_eta = fs->make<TH1F>("recojet3_eta","#eta_{recojets}",100,-2.5, 2.5);
  recojt3_eta->Sumw2();
  recojt3_phi = fs->make<TH1F>("recojet3_phi","#phi_{recojets}",100,-M_PI, M_PI);
  recojt3_phi->Sumw2();

  hprof = fs->make<TProfile>("hprof","hprof",40,60,2000);
  hprof->Sumw2();

  hchpt = fs->make<TProfile>("hchpt","hchpt",40,60,2000);
  hchpt->Sumw2();

  for(int jk=0; jk<njetetamn; jk++){
    sprintf(name, "recojetallave_pt_%i",jk);
    sprintf(title, "Et_{recojetsallave}_%g", etarange[jk]);
    recojtallave_pt[jk] = fs->make<TH1F>(name,title,400, 20., 2020.);
    recojtallave_pt[jk]->Sumw2();

    sprintf(name, "recojetallavewt1_pt_%i",jk);
    sprintf(title, "Et_{recojetsallavewt1}_%g", etarange[jk]);
    recojtallavewt1_pt[jk] = fs->make<TH1F>(name,title,400, 20., 2020.);
    recojtallavewt1_pt[jk]->Sumw2();

    sprintf(name, "recojt_pt_%i",jk);
    sprintf(title, "Et_{recojets}_%g", etarange[jk]);
    recojt_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    recojt_pt[jk]->Sumw2();

    sprintf(name, "recojet1_pt_%i",jk);
    sprintf(title, "Et_{recojets1}_%g", etarange[jk]);
    recojt1_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    recojt1_pt[jk]->Sumw2();

    sprintf(name, "recojet2_pt_%i",jk);
    sprintf(title, "Et_{recojets2}_%g", etarange[jk]);
    recojt2_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    recojt2_pt[jk]->Sumw2();

    sprintf(name, "recojet3_pt_%i",jk);
    sprintf(title, "Et_{recojets3}_%g", etarange[jk]);
    recojt3_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    recojt3_pt[jk]->Sumw2();
    sprintf(title, "Et_{recojets3}_%g", etarange[jk]);
    recojt3_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    recojt3_pt[jk]->Sumw2();

    for (int kl=0; kl<nHLTmx; kl++) { 
      //sprintf(name, "recojt_pt_%i_%i",jk, kl);
      //sprintf(title, "Et_{recojets}_%g_%i", etarange[jk], kl);
      //recojt_pt[jk][kl] = fs->make<TH1F>(name,title, 400, 20., 2020.);
      //recojt_pt[jk][kl]->Sumw2();

      sprintf(name, "recojetave_pt_%i_%i",jk, kl);
      sprintf(title, "Et_{recojetsave}_%g_%i", etarange[jk], kl);
      recojtave_pt[jk][kl] = fs->make<TH1F>(name,title, 400, 20., 2020.);
      recojtave_pt[jk][kl]->Sumw2();

      sprintf(name, "recojetavewt1_pt_%i_%i",jk, kl);
      sprintf(title, "Et_{recojetsavewt1}_%g_%i", etarange[jk], kl);
      recojtavewt1_pt[jk][kl] = fs->make<TH1F>(name,title, 400, 20., 2020.);
      recojtavewt1_pt[jk][kl]->Sumw2();
    }

    sprintf(name, "recojetHT2_%i",jk);
    sprintf(title, "recojetsHT2_%g", etarange[jk]);

    recoht2_pt[jk] = fs->make<TH1F>(name, title, 400,20., 1500.);
    recoht2_pt[jk]->Sumw2();


    sprintf(name, "hjetdpt_%i",jk);
    sprintf(title, "dpt_{recojets12}_%g", etarange[jk]);

    hjetdpt[jk] = fs->make<TH1F>(name, title, 100,20., 500.);
    hjetdpt[jk]->Sumw2();

    sprintf(name, "hjetpt2bypt1_%i",jk);
    sprintf(title, "hjetpt2bypt1 reco jet_%g", etarange[jk]);

    hjetpt2bypt1[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    hjetpt2bypt1[jk]->Sumw2();

    sprintf(name, "hjetpt3bypt2_%i",jk);
    sprintf(title, "hjetpt3bypt2 reco jet_%g", etarange[jk]);
    hjetpt3bypt2[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    hjetpt3bypt2[jk]->Sumw2();

    sprintf(name, "hjetdphi_%i",jk);
    sprintf(title, "#phi_{recojets}_%g", etarange[jk]);
    hjetdphi[jk] = fs->make<TH1F>(name,title,100,-M_PI, M_PI);
    hjetdphi[jk]->Sumw2();
    sprintf(name, "hjetptbypl_%i",jk);
    sprintf(title, "1st recojet Pt*sin/1st Recojet_%g", etarange[jk]);
    hjetptbypl[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    hjetptbypl[jk]->Sumw2();

    //hjetpt2bypt1 = fs->make<TH1F>("hjetpt2bypt1", "hjetpt2bypt1 reco jet", 60, 0., 1.0);
    //hjetpt2bypt1->Sumw2();
    //hjetpt3bypt2 = fs->make<TH1F>("hjetpt2bypt1", "hjetpt2bypt1 reco jet", 60, 0., 1.0);
    //hjetpt3bypt2->Sumw2();
  }

  recochg_pt = fs->make<TH1F>("recochg_pt","Et_{recocharge_alljet}",100, 1., 101.);
  recochg_pt->Sumw2();
  recochg_eta = fs->make<TH1F>("recochg_eta","#eta_{recocharge_alljet}",100,-3., 3.);
  recochg_eta->Sumw2();
  recochg_phi = fs->make<TH1F>("recochg_phi","#phi_{recocharge_alljet}",100,-M_PI, M_PI);
  recochg_phi->Sumw2();

  recochg1_pt = fs->make<TH1F>("recochg1_pt","Et_{recocharge_jet1}",100, 1., 101.);
  recochg1_pt->Sumw2();
  recochg1_eta = fs->make<TH1F>("recochg1_eta","#eta_{recocharge_jet1}",100,-3., 3.);
  recochg1_eta->Sumw2();
  recochg1_phi = fs->make<TH1F>("recochg1_phi","#phi_{recocharge_jet1}",100,-M_PI, M_PI);
  recochg1_phi->Sumw2();

  recochg2_pt = fs->make<TH1F>("recochg2_pt","Et_{recocharge_jet2}",100, 1., 101.);
  recochg2_pt->Sumw2();
  recochg2_eta = fs->make<TH1F>("recochg2_eta","#eta_{recocharge_jet2}",100,-3., 3.);
  recochg2_eta->Sumw2();
  recochg2_phi = fs->make<TH1F>("recochg2_phi","#phi_{recocharge_jet2}",100,-M_PI, M_PI);
  recochg2_phi->Sumw2();

  recochg3_pt = fs->make<TH1F>("recochg3_pt","Et_{recocharge_jet3}",100, 1., 101.);
  recochg3_pt->Sumw2();
  recochg3_eta = fs->make<TH1F>("recochg3_eta","#eta_{recocharge_jet3}",100,-3., 3.);
  recochg3_eta->Sumw2();
  recochg3_phi = fs->make<TH1F>("recochg3_phi","#phi_{recocharge_jet3}",100,-M_PI, M_PI);
  recochg3_phi->Sumw2();

#endif
//-------------------------------------------
  for (int ij=0; ij<nhist; ij++) {
    sprintf(name, "anglex_%i", ij);
    vec_anglex[ij] = fs->make<TH1F>(name, name, 240, 0.7, 1.0);
  }
  //genjt_hist = fs->make<TH1F>("genjt_hist","# of genjets",20,-0.5, 19.5);
  //genjt_hist->Sumw2();
  for(int jk=0; jk<njetetamn; jk++){
    sprintf(name, "genjetallave_pt_%i",jk);
    sprintf(title, "Et_{genjetsallave}_%g", etarange[jk]);
    genjtallave_pt[jk] = fs->make<TH1F>(name,title,400, 20., 2020.);
    genjtallave_pt[jk]->Sumw2();

    sprintf(name, "genjt_pt_%i",jk);
    sprintf(title, "Et_{genjets}_%g", etarange[jk]);
    genjt_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    genjt_pt[jk]->Sumw2();

    sprintf(name, "genjet1_pt_%i",jk);
    sprintf(title, "Et_{genjets1}_%g", etarange[jk]);
    genjt1_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    genjt1_pt[jk]->Sumw2();

    sprintf(name, "genjet2_pt_%i",jk);
    sprintf(title, "Et_{genjets2}_%g", etarange[jk]);
    genjt2_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    genjt2_pt[jk]->Sumw2();

    sprintf(name, "genjet3_pt_%i",jk);
    sprintf(title, "Et_{genjets3}_%g", etarange[jk]);
    genjt3_pt[jk] = fs->make<TH1F>(name,title, 400, 20., 2020.);
    genjt3_pt[jk]->Sumw2();

    /*sprintf(name, "genjt_oth_pt_%i",jk);
    sprintf(title, "#Et_{genjets_oth}_%g", etarange[jk]);

    genjt_oth_pt[jk] = fs->make<TH1F>(name,title,100, 20., 2020.);
    genjt_oth_pt[jk]->Sumw2();
   */
    sprintf(name, "genjetdpt_%i",jk);
    sprintf(title, "dpt_{genjets12}_%g", etarange[jk]);

    genjetdpt[jk] = fs->make<TH1F>(name, title, 100,20., 500.);
    genjetdpt[jk]->Sumw2();

    sprintf(name, "genjetpt2bypt1_%i",jk);
    sprintf(title, "jetpt2bypt1 gen jet_%g", etarange[jk]);

    genjetpt2bypt1[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    genjetpt2bypt1[jk]->Sumw2();

    sprintf(name, "genjetpt3bypt2_%i",jk);
    sprintf(title, "hjetpt3bypt2 gen jet_%g", etarange[jk]);
    genjetpt3bypt2[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    genjetpt3bypt2[jk]->Sumw2();

    sprintf(name, "genjetdphi_%i",jk);
    sprintf(title, "#phi_{genjets}_%g", etarange[jk]);
    genjetdphi[jk] = fs->make<TH1F>(name,title,100,-M_PI, M_PI);
    genjetdphi[jk]->Sumw2();
    sprintf(name, "genjetptbypl_%i",jk);
    sprintf(title, "1st genjet Pt*sin/1st genjet_%g", etarange[jk]);
    genjetptbypl[jk] = fs->make<TH1F>(name, title, 60, 0., 1.0);
    genjetptbypl[jk]->Sumw2();
  }

  //genjt_pt = fs->make<TH1F>("genjt_pt","Et_{genjets}",100,20., 2020.);
  //genjt_pt->Sumw2();
  genjt_eta = fs->make<TH1F>("genjt_eta","#eta_{genjets}",100,-2.5, 2.5);
  genjt_eta->Sumw2();
  genjt_phi = fs->make<TH1F>("genjt_phi","#phi_{genjets}",100,-M_PI, M_PI);
  genjt_phi->Sumw2();

  genjt1_eta = fs->make<TH1F>("genjet1_eta","#eta_{genjets}",100,-2.5, 2.5);
  genjt1_eta->Sumw2();
  genjt1_phi = fs->make<TH1F>("genjet1_phi","#phi_{genjets}",100,-M_PI, M_PI);
  genjt1_phi->Sumw2();

  genjt2_eta = fs->make<TH1F>("genjet2_eta","#eta_{genjets}",100,-2.5, 2.5);
  genjt2_eta->Sumw2();
  genjt2_phi = fs->make<TH1F>("genjet2_phi","#phi_{genjets}",100,-M_PI, M_PI);
  genjt2_phi->Sumw2();

  genjt3_eta = fs->make<TH1F>("genjet3_eta","#eta_{genjets}",100,-2.5, 2.5);
  genjt3_eta->Sumw2();
  genjt3_phi = fs->make<TH1F>("genjet3_phi","#phi_{genjets}",100,-M_PI, M_PI);
  genjt3_phi->Sumw2();
  //genjt_oth_pt = fs->make<TH1F>("genjt_oth_pt","Et_{genjets_oth}",100, 20., 2020.);
  //genjt_oth_pt->Sumw2();
  /*  
  genjt_oth_eta = fs->make<TH1F>("genjt_oth_eta","#eta_{genjets_oth}",100,-5., 5.);
  genjt_oth_eta->Sumw2();
  genjt_oth_phi = fs->make<TH1F>("genjt_oth_phi","#phi_{genjets_oth}",100,-M_PI, M_PI);
  genjt_oth_phi->Sumw2();
  */
  //genchg_hist = fs->make<TH1F>("genchg_hist","# of genchargeds",120,-0.5, 239.5);
  //genchg_hist->Sumw2();
  genchg_pt = fs->make<TH1F>("genchg_pt","Et_{gencharge_alljet}",100, 1., 101.);
  genchg_pt->Sumw2();
  genchg_eta = fs->make<TH1F>("genchg_eta","#eta_{gencharge_alljet)",100,-3., 3.);
  genchg_eta->Sumw2();
  genchg_phi = fs->make<TH1F>("genchg_phi","#phi_{gencharge_alljet}",100,-M_PI, M_PI);
  genchg_phi->Sumw2();

  genchg1_pt = fs->make<TH1F>("genchg1_pt","Et_{gencharge_jet1}",100, 1., 101.);
  genchg1_pt->Sumw2();
  genchg1_eta = fs->make<TH1F>("genchg1_eta","#eta_{gencharge_jet1}",100,-3., 3.);
  genchg1_eta->Sumw2();
  genchg1_phi = fs->make<TH1F>("genchg1_phi","#phi_{gencharge_jet1}",100,-M_PI, M_PI);
  genchg1_phi->Sumw2(); 

  genchg2_pt = fs->make<TH1F>("genchg2_pt","Et_{gencharge_jet2}",100, 1., 101.);
  genchg2_pt->Sumw2();
  genchg2_eta = fs->make<TH1F>("genchg2_eta","#eta_{gencharge_jet2}",100,-3., 3.);
  genchg2_eta->Sumw2();
  genchg2_phi = fs->make<TH1F>("genchg2_phi","#phi_{gencharge_jet2}",100,-M_PI, M_PI);
  genchg2_phi->Sumw2();

  genchg3_pt = fs->make<TH1F>("genchg3_pt","Et_{gencharge_jet3}",100, 1., 101.);
  genchg3_pt->Sumw2();
  genchg3_eta = fs->make<TH1F>("genchg3_eta","#eta_{gencharge_jet3}",100,-3., 3.);
  genchg3_eta->Sumw2();
  genchg3_phi = fs->make<TH1F>("genchg3_phi","#phi_{gencharge_jet3}",100,-M_PI, M_PI);
  genchg3_phi->Sumw2();

  //genchg_oth_hist = fs->make<TH1F>("genchg_oth_hist","# of genchargeds (others)",120,-0.5, 239.5);
  //genchg_oth_hist->Sumw2();
  /* 
  genchg_oth_pt = fs->make<TH1F>("genchg_oth_pt","Et_{genchargeds_oth}",100,1., 101.);
  genchg_oth_pt->Sumw2();
  genchg_oth_eta = fs->make<TH1F>("genchg_oth_eta","#eta_{genchargeds_oth}",100,-5., 5.);
  genchg_oth_eta->Sumw2();
  genchg_oth_phi = fs->make<TH1F>("genchg_oth_phi","#phi_{genchargeds_oth}",100,-M_PI, M_PI);
  genchg_oth_phi->Sumw2();
  genneu_hist = fs->make<TH1F>("genneu_hist","# of genneutrals",120,-0.5, 239.5);
  genneu_hist->Sumw2();
  genneu_pt = fs->make<TH1F>("genneu_pt","Et_{genneutrals}",100,1., 101.);
  genneu_pt->Sumw2();
  genneu_eta = fs->make<TH1F>("genneu_eta","#eta_{genneutrals}",100,-3., 3.);
  genneu_eta->Sumw2();
  genneu_phi = fs->make<TH1F>("genneu_phi","#phi_{genneutrals}",100,-M_PI, M_PI);
  genneu_phi->Sumw2();

  genneu_oth_hist = fs->make<TH1F>("genneu_oth_hist","# of genneutrals (others)",120,-0.5, 239.5);
  genneu_oth_hist->Sumw2();
  genneu_oth_pt = fs->make<TH1F>("genneu_oth_pt","Et_{genneutrals_oth}",100, 1., 101.);
  genneu_oth_pt->Sumw2();
  genneu_oth_eta = fs->make<TH1F>("genneu_oth_eta","#eta_{genneutrals_oth}",100,-5., 5.);
  genneu_oth_eta->Sumw2();
  genneu_oth_phi = fs->make<TH1F>("genneu_oth_phi","#phi_{genneutrals_oth}",100,-M_PI, M_PI);
  genneu_oth_phi->Sumw2();
  */
  for (int ij=0; ij<nHLTmx; ij++) { 
    sprintf(name, "nprimall_%i", ij);
    sprintf(title, "# of primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_hist[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_hist[ij]->Sumw2();

    sprintf(name, "nprimsel_%i", ij);
    sprintf(title, "Selected # of primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_sel[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_sel[ij]->Sumw2();

    sprintf(name, "nprimall_rewt_%i", ij);
    sprintf(title, "# of rewighted primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_hist_rewt[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_hist_rewt[ij]->Sumw2();

    sprintf(name, "nprimsel_rewt_%i", ij);
    sprintf(title, "Selected # of reweighted primary vtx (%s)", (ij==0) ? "ALL" : jethlt_name[ij-1]);
    prim_sel_rewt[ij] = fs->make<TH1F>(name, title, 60, -0.5, 59.5);
    prim_sel_rewt[ij]->Sumw2();
  }

  prim_correl = fs->make<TH2F>("correl", "Correlation of all and Selected # of primary vtx", 60, -0.5, 59.5, 60, -0.5, 59.5);
  const char* namex[2]={"Selected", "Rejected"};
  for (int ij=0; ij<2; ij++) {
    sprintf(name, "primalltrk_%i", ij);
    sprintf(title, "All tracks in primary vtx (%s)", namex[ij]);
    prim_alltrk[ij] = fs->make<TH1F>(name, title, 240, -0.5, 239.5);

    sprintf(name, "primgoodtrk_%i", ij);
    sprintf(title, "Good tracks in primary vtx (%s)", namex[ij]);
    prim_goodtrk[ij] = fs->make<TH1F>(name, title, 240, -0.5, 239.5);

    sprintf(name, "primseltrk_%i", ij);
    sprintf(title, "Selected tracks in primary vtx (%s)", namex[ij]);
    prim_seltrk[ij] = fs->make<TH1F>(name, title, 240, -0.5, 239.5);

    sprintf(name, "primdx_%i", ij);
    sprintf(title, "#Delta x of prim wrt beam spot (%s)", namex[ij]);
    prim_dx[ij] = fs->make<TH1F>(name, title, 120, -2.4, 2.4);

    sprintf(name, "primdy_%i", ij);
    sprintf(title, "#Delta y of prim wrt beam spot (%s)", namex[ij]);
    prim_dy[ij] = fs->make<TH1F>(name, title, 120, -2.4, 2.4);

    sprintf(name, "primdxy_%i", ij);
    sprintf(title, "#Delta y vs #Delta x of prim (%s)", namex[ij]);
    prim_dxy[ij] = fs->make<TH2F>(name, title, 60, -0.15, 0.15, 60, -0.15, 0.15);

    sprintf(name, "primdz_%i", ij);
    sprintf(title, "#Delta z of prim wrt beam spo (%s)", namex[ij]);
    prim_dz[ij] = fs->make<TH1F>(name, title, 120, -30.0, 30.0); 

    sprintf(name, "primprob_%i", ij);
    sprintf(title, "log10(vertex fit prob) (%s)", namex[ij]);
    prim_prob[ij] = fs->make<TH1F>(name, title, 120, -20.0, 0.0);   
  }

  for(int ij=0; ij<njetetamn; ij++){
    sprintf(name, "njets_%i",ij);
    sprintf(title, "No of Jets_eta range_%gs", etarange[ij]);
    h_njets[ij] = fs->make<TH1F>(name, title, 9, 1, 10);
    h_njets[ij]->Sumw2();
  }

  for(int ij=0; ij<njetetamn; ij++){
    sprintf(name, "ncharges_%i",ij);
    sprintf(title, "No of charge particles_eta range_%gs", etarange[ij]);
    h_nchg[ij] = fs->make<TH1F>(name, title, 139, 1, 140);
    h_nchg[ij]->Sumw2();
  }


  for(int ij=0; ij<njetetamn; ij++){
    sprintf(name, "gennjets_%i",ij);
    sprintf(title, "No of GenJets_eta range_%gs", etarange[ij]);
    gen_njets[ij] = fs->make<TH1F>(name, title, 9, 1, 10);
    gen_njets[ij]->Sumw2();
  }
//-------------------------------------------
#ifdef TRIGGER
  const char* trigvar[2]={"L1", "HLT"};
  for(int ij=0; ij<nHLTmx; ij++){
    for(int jk=0; jk<2; jk++){
      sprintf(name, "trgjet_pt_%i_%i", ij, jk);
      sprintf(title, "trgjet_pt_%s_%s", jethlt_name[ij], trigvar[jk]);
      trgjet_pt[ij][jk] = fs->make<TH1F>(name, title, njetptbin, 20,1500);
      trgjet_pt[ij][jk]->Sumw2();

      sprintf(name, "trgjet_eta_%i_%i", ij, jk);
      sprintf(title, "trgjet_eta_%s_%s", jethlt_name[ij], trigvar[jk]);
      trgjet_eta[ij][jk] = fs->make<TH1F>(name, title, njetptbin, -5., 5.);
      trgjet_eta[ij][jk]->Sumw2();

      sprintf(name, "trgjet_phi_%i_%i", ij, jk);
      sprintf(title, "trgjet_phi_%s_%s", jethlt_name[ij], trigvar[jk]);
      trgjet_phi[ij][jk] = fs->make<TH1F>(name, title, 180,-M_PI, M_PI);
      trgjet_phi[ij][jk]->Sumw2();

      sprintf(name, "prbjet_pt_%i_%i", ij, jk);
      sprintf(title, "prbjet_pt_%s_%s", jethlt_name[ij], trigvar[jk]);
      prbjet_pt[ij][jk] = fs->make<TH1F>(name, title, njetptbin, 20,1500);
      prbjet_pt[ij][jk]->Sumw2();

      sprintf(name, "prbjet_eta_%i_%i", ij, jk);
      sprintf(title, "prbjet_eta_%s_%s", jethlt_name[ij], trigvar[jk]);
      prbjet_eta[ij][jk] = fs->make<TH1F>(name, title, 100,-5., 5.);
      prbjet_eta[ij][jk]->Sumw2();

      sprintf(name, "prbjet_phi_%i_%i", ij, jk);
      sprintf(title, "prbjet_phi_%s_%s", jethlt_name[ij], trigvar[jk]);
      prbjet_phi[ij][jk] = fs->make<TH1F>(name, title, 180,-M_PI, M_PI);
      prbjet_phi[ij][jk]->Sumw2();
    }
  } 
#endif
//Trigger special
//-------------------------------------------
	if (isReconstruct) { 
		for(int ij=0; ij<nHLTmx; ij++){
			for(int jk=0; jk<njetetamn; jk++){
				sprintf(name, "jetpt_%i_%i",jk,ij);
				sprintf(title, "jetpt_%s_%g", jethlt_name[ij], etarange[jk]);
				h_jetpt[ij][jk] = fs->make<TH1F>(name, title, 300, 50, 1550);
				h_jetpt[ij][jk]->Sumw2();
				
				sprintf(name, "jetphi_%i_%i",jk, ij);
				sprintf(title, "jetphi_%s_%g", jethlt_name[ij],etarange[jk]);
				h_jetphi[ij][jk] = fs->make<TH1F>(name, title, 180,-M_PI, M_PI);
				h_jetphi[ij][jk]->Sumw2();				
			}
		}
	}
#ifdef TRIGGER
  for(int ij=0; ij<nHLTmx; ij++){

    sprintf(name, "jeteta_%i", ij);
    sprintf(title, "jetphi_%s", jethlt_name[ij]);//, jetvar[ij]);
    h_jeteta[ij] = fs->make<TH1F>(name, title, 100, -5, 5);
    h_jeteta[ij]->Sumw2();

    for (int jk=0; jk<2; jk++){ 
      sprintf(name, "angle1d_%s_%i", jethlt_name[ij], jk);
      sprintf(title, "Angle%s_%i", jethlt_name[ij], jk);
      trgjet_angle[ij][jk] = fs->make<TH1F>(name, title, 90 , 0.1, 2.5);

      sprintf(name, "angle2d_%s_%i", jethlt_name[ij], jk);
      sprintf(title, "Angle_2d_hist%s_%i", jethlt_name[ij], jk);
      trgjet_2dangle[ij][jk] = fs->make<TH2F>(name, title, njetptbin, 20, 1500, 30 , 0.1, 2.5);
    }
  }

  for (int ij=0; ij<nHLTmx; ij++) {
    for (int jk=0; jk<njetetamn; jk++) {
      sprintf(name, "hlt_dijettag_%i_%i", ij, jk);
      sprintf(title, "dijet tagged P_T : (%s) |i#eta|<%g", jethlt_name[ij], etarange[jk]);
      hlt_dijettag[ij][jk] = fs->make<TH1F>(name, title, 60, 0.4*leadingPtThreshold[ij], 2.5*leadingPtThreshold[ij]);
      hlt_dijettag[ij][jk]->Sumw2();

      sprintf(name, "hlt_dijetprob_%i_%i", ij, jk);
      sprintf(title, "dijet probed P_T : (%s) |i#eta|<%g", jethlt_name[ij], etarange[jk]);
      hlt_dijetprob[ij][jk] = fs->make<TH1F>(name, title, 60, 0.4*leadingPtThreshold[ij], 2.5*leadingPtThreshold[ij]);
      hlt_dijetprob[ij][jk]->Sumw2();
    }
  }
#endif
  counthist = fs->make<TH1F>("count","No of events",2,0,2); 

  for (int ix=0; ix<32; ix++) { mypow_2[ix] = pow(2,ix);}
  nevt = 0;
  //irun_old=-1;
  //trig_init=0;
  nreco=naa= nbb= ncc=0;
}

QCDEventShape::~QCDEventShape()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//member functions

// ------------ method called for each event  ------------
void QCDEventShape::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  //t1=clock();
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;
  //gRandom->SetSeed(19919925);
  //float rn=gRandom->Uniform();
  //cout << " Random Number ini = " << rn << endl;
  //if (rn >0.90) return;
  //cout << " Random Number = " << rn << endl;
  //cout << "Time = " << t1 << "; " << t2 << endl;
  nevt++;
  //int ievt = iEvent.id().event();
  counthist->Fill(1); 
  //if (nevt%100==1)   std::cout<<"QCDEventShape::analyze "<< nevt<<" IRUN= "<<iEvent.id().run()<<" ievt= "<< iEvent.id().event()<<" "<<ievt<<endl;
  if (nevt%10000==1)   std::cout<<"Jet Charge Analysis Run No. =  "<< nevt<<endl;
  //std::cout << "ok1"<<endl;

  //" ilumi" <<
  //iEvent.luminosityBlock() << " ibunch " << iEvent.bunchCrossing() <<std::endl;
  //cout << "NEvent = " <<  nevt << endl;
  //if(iEvent.luminosityBlock()==9881 || iEvent.luminosityBlock()==23185 || iEvent.luminosityBlock()==25334 || iEvent.luminosityBlock()== 26584 ||iEvent.luminosityBlock()== 35674 || iEvent.luminosityBlock()==32764 || iEvent.luminosityBlock()== 35675 || iEvent.luminosityBlock()==53681) return ;
  //if(iEvent.luminosityBlock()==2 || iEvent.luminosityBlock()==7175 || iEvent.luminosityBlock()==41151 || iEvent.luminosityBlock()==7389697 || iEvent.luminosityBlock()==60334 || iEvent.luminosityBlock()==51317 || iEvent.luminosityBlock()==53654 || iEvent.luminosityBlock()==10333 || iEvent.luminosityBlock()==54778 || iEvent.luminosityBlock()==10082 || iEvent.luminosityBlock()==54322 || iEvent.luminosityBlock()==64667 || iEvent.luminosityBlock()==65977 || iEvent.luminosityBlock()==55534 || iEvent.luminosityBlock()==55781 || iEvent.luminosityBlock()==55782 || iEvent.luminosityBlock()==55783 || iEvent.luminosityBlock()==61360 || iEvent.luminosityBlock()==61370 ||iEvent.luminosityBlock()==68258 || iEvent.luminosityBlock()==62147 || iEvent.luminosityBlock()==67194 || iEvent.luminosityBlock()==43070 || iEvent.luminosityBlock()==49429 || iEvent.luminosityBlock()==15102 || iEvent.luminosityBlock()==23306 || iEvent.luminosityBlock()==14242|| iEvent.luminosityBlock()==19080 || iEvent.luminosityBlock()==9312025) return;
  //npfjets = 0;
  //nchg =0;
  //if(iEvent.luminosityBlock()<4401) return; 
  //if(nevt<3442) return;
  //if(nevt!=3080) return;
  //cout << "Write test 1 = ok " << endl;
//-------------------------------------------
  //vector<double> recovar;
  //vector<double> recovar1;
  std::vector<HepLorentzVector> recomom[njecmx][ntype][njetetamn];
  //std::vector<HepLorentzVector> mom[njecmx][njetetamn];
  std::vector<HepLorentzVector> tmpjt4v; 
  //std::vector<HepLorentzVector> tmpcand4v;                
  std::vector<HepLorentzVector> tmpgen4v;                                                                                               
  std::vector<HepLorentzVector> genmom[nGenReso][ntype][njetetamn];
  //vector<double> genvar;
  
  recojet1_pt = 0.0, recojet2_pt = 0.0;
  genrecojet1_pt = 0.0, genrecojet2_pt = 0.0;
 
  double RecoJCO[ndef][njet][nkappa] = {{{0.0}}};
  double GenJCO[ndef][njet][nkappa] = {{{0.0}}};

  double recomomJCO[ndef][njet][nkappa] = {{{0.0}}};
  double genmomJCO[ndef][njet][nkappa] = {{{0.0}}}; 
//------------------------------------------

  //double recojet1 = 0.0, genjet1 = 0.0;
  double ijet1candsmom[nkappa] = {0.0}, ijet1_long_num[nkappa] = {0.0}, ijet1_long_den[nkappa] = {0.0}, ijet1_tran_num[nkappa] = {0.0}, ijet1_tran_den[nkappa] = {0.0};
  double ijet2candsmom[nkappa] = {0.0}, ijet2_long_num[nkappa] = {0.0}, ijet2_long_den[nkappa] = {0.0}, ijet2_tran_num[nkappa] = {0.0}, ijet2_tran_den[nkappa] = {0.0}; 
  
  double igenjet1candsmom[nkappa] = {0.0}, igenjet1_long_num[nkappa] = {0.0}, igenjet1_long_den[nkappa] = {0.0}, igenjet1_tran_num[nkappa] = {0.0}, igenjet1_tran_den[nkappa] = {0.0}; 
  double igenjet2candsmom[nkappa] = {0.0}, igenjet2_long_num[nkappa] = {0.0}, igenjet2_long_den[nkappa] = {0.0}, igenjet2_tran_num[nkappa] = {0.0}, igenjet2_tran_den[nkappa] = {0.0};

//-------------------------------------------
  wtfact=1.0;
  //double px=0;
  //double py=0;
  //double ptxy=0;

  //int ncount=0;
  unsigned ncount=0;
  //double recterm=0;
  //int ithird=-1;
  int irecoht=-1;
	//#ifdef JETENERGY
	int irecohtjec[njecmx];
	for (int ij=0; ij<njecmx; ij++) { irecohtjec[ij]=-1;}
	//#endif	
  double leadingptjec[njecmx] ={0};   // jet charge 

  //int igenht=-1;
	//#ifdef  JETRESO
	int igenhtres[nGenReso];
	for (int ij=0; ij<nGenReso; ij++) { igenhtres[ij]=-1;}
	//#endif
	double leadgenptres[nGenReso]={0};// jet charge

#ifdef TRIGGER
  const char* variab1;
#endif
#ifndef DIJETAVE
  const char* variab2; 
#endif

  if (isMC) {
#ifdef LHAPDF
    edm::Handle<LHEEventProduct> EvtHandle ;
    iEvent.getByToken( lheEventProductToken_ , EvtHandle ) ;
		
		for ( unsigned int weightIndex = 0; weightIndex < EvtHandle->weights().size(); ++weightIndex ) {
			//cout<< EvtHandle->weights()[weightIndex].wgt <<endl;
                        //systematicWeightIDs->push_back( atoi(EvtHandle->weights()[weightIndex].id.c_str()) );
			if (weightIndex>=9 && weightIndex<=109) {
				pdfwt[weightIndex-9] = EvtHandle->weights()[weightIndex].wgt/EvtHandle->originalXWGTUP(); 
				//std::cout << weightIndex << " " << EvtHandle->weights()[weightIndex].id << " " << EvtHandle->weights()[weightIndex].wgt <<" "<<pdfwt[weightIndex-9]<< std::endl;
				}
    			}
#endif
    edm::Handle<GenEventInfoProduct> eventinfo;
    iEvent.getByToken(generator1_, eventinfo);
    if (eventinfo.isValid()) { 
      qscale = eventinfo->qScale(); 
      wtfact = eventinfo->weight();
      //weight = weight2*wtfact;
      procid = eventinfo->signalProcessID();
      //cout << " qscale = " <<setw(14)<< qscale << " ; wtfact = " << wtfact << " ; procid = " << procid  << endl;

      if (eventinfo->hasPDF()) {
	const gen::PdfInfo* xpdf = eventinfo->pdf();
	
	int id1 = xpdf->id.first;
	int id2 = xpdf->id.second;
	
	idall = 100*(id1+50)+ (id2+50); 
	
	qscale = xpdf->scalePDF;
	
	xfrac1 = xpdf->x.first;
	xfrac2 = xpdf->x.second;
	
	xpdf1 = xfrac1*xpdf->xPDF.first;
	xpdf2 = xfrac2*xpdf->xPDF.second; 
      }
    }
  }
 
/*
edm::Handle< double > theprefweight;
iEvent.getByToken(prefweight_token, theprefweight ) ;
double _prefiringweight =(*theprefweight);

edm::Handle< double > theprefweightup;
iEvent.getByToken(prefweightup_token, theprefweightup ) ;
double _prefiringweightup =(*theprefweightup);

edm::Handle< double > theprefweightdown;
iEvent.getByToken(prefweightdown_token, theprefweightdown ) ;
double _prefiringweightdown =(*theprefweightdown);
*/
//cout << "Prefire  wt : " << _prefiringweight << endl;
//cout << "Prefire up wt : " << _prefiringweightup << endl;
//cout << "Prefire down wt : " << _prefiringweightdown << endl;
 
#ifdef TRIGGER
  edm::Handle<edm::TriggerResults> trigRes;
  iEvent.getByToken(triggerBits_, trigRes);
  
  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  iEvent.getByToken(triggerObjects_, triggerObjects);
  
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
  iEvent.getByToken(triggerPrescales_, triggerPrescales);
//-------------------------------------------Trigger
  const edm::TriggerNames &names = iEvent.triggerNames(*trigRes);
  //int ihltfill = -1;
#endif
  tmpjt4v.clear();
  //tmpcand4v.clear();
  tmpgen4v.clear();

  double aveleadingpt =0;  //ESVs (dijet)
  double leadingpt = 0;    //Jet charge (single jet)
  bool isInEtaRange[njetetamn]={0}; //GMA{0,0,0,0};
 /* 
  recojet1_pt = 0.0;  
  recojet2_pt = 0.0; 
  
  genrecojet1_pt = 0.0; 
  genrecojet2_pt = 0.0; 
*/
#ifndef GENPART
  edm::Handle<pat::JetCollection> ak4PFJets;
  if (isReconstruct) { 
    iEvent.getByToken(jetSrcToken_, ak4PFJets);
  }
  //cout<<"Check 0 : "<<leadingpt<<endl;
  //cout<< "Checking....."<<endl;
  if (isReconstruct && ((!ak4PFJets.isValid()) || ak4PFJets->size() <2)) return; //GMA, do we use this
  //cout<<"Check 1 : Lead Jet pt : "<< (*ak4PFJets)[0].pt()<<endl;
  //cout<<"Check 1 : Sub-Lead Jet pt : "<< (*ak4PFJets)[1].pt()<<endl;
  if (ak4PFJets.isValid() && ak4PFJets->size()>=2) {
#ifdef DIJETAVE
    for (int iet=0; iet<njetetamn; iet++) {
      isInEtaRange[iet] = true;
      }
    
    for (int ij=0; ij<2; ij++) { 
      for (int iet=0; iet<njetetamn; iet++) {
	if (abs((*ak4PFJets)[ij].eta())>etarange[iet]) { isInEtaRange[iet] = false;}
      }
      
      //Jet ID ================= 2017 & 2018 UL jetID recomendation 
      double NHF = (*ak4PFJets)[ij].neutralHadronEnergyFraction();
      double NEMF = (*ak4PFJets)[ij].neutralEmEnergyFraction();
      double CHF = (*ak4PFJets)[ij].chargedHadronEnergyFraction();
      //double MUF = (*ak4PFJets)[ij].muonEnergyFraction();
      //double CEMF = (*ak4PFJets)[ij].chargedEmEnergyFraction();
      int NumConst = (*ak4PFJets)[ij].chargedMultiplicity()+(*ak4PFJets)[ij].neutralMultiplicity();
      //int NumNeutralParticles =(*ak4PFJets)[ij].neutralMultiplicity();
      int CHM = (*ak4PFJets)[ij].chargedMultiplicity();

      bool TightJetID =false;
      if(abs((*ak4PFJets)[ij].eta())<=2.7){
      if(NHF<0.90 && NEMF<0.90 && NumConst>1 && CHF>0 && CHM>0  && abs((*ak4PFJets)[ij].eta())<=2.6 )  TightJetID =true;
      if(NHF<0.90 && NEMF<0.99 && abs((*ak4PFJets)[ij].eta())>2.6 )  TightJetID =true;}
      else {TightJetID =false;}
      if (abs((*ak4PFJets)[ij].eta())>2.1) {TightJetID = false;}  //2.5 or 2.6
      if ((*ak4PFJets)[ij].pt()<30.0) {TightJetID = false;}

	/*
      if (TightJetID) { aveleadingpt +=(*ak4PFJets)[ij].pt();
			leadingpt = (*ak4PFJets)[0].pt();
      //std::cout<<"ok2"<<endl;
      std::cout << "Leading jet pt :"<<leadingpt<<endl;
      //std::cout << "Sub-Leading jet pt :"<<(*ak4PFJets)[1].pt()<<endl;
      //std::cout << "Avg. Leading jet pt :"<<aveleadingpt<<endl;
			} else {aveleadingpt -=100000;
			        leadingpt -=100000;}
	*/

	if(!TightJetID) continue;
	aveleadingpt +=(*ak4PFJets)[ij].pt();
	leadingpt = (*ak4PFJets)[0].pt();
    }
    //std::cout << "Check 2 : Lead Jet pt : at end of the loop :"<<leadingpt<<endl;
    //std::cout << "Check 2 : Sub-Lead Jet pt : at the end of the loop :"<<(*ak4PFJets)[1].pt()<<endl;
    //std::cout << "Check 2 : Sum of 2 Jet pt at end of the loop :"<<aveleadingpt<<endl;
    aveleadingpt /=2.0;
    //cout << "Check 2 : Avg of 2 Jet pt at end of the loop : "<<aveleadingpt<<endl;
#else

#endif
  }//if (ak4PFJets.isValid() && ak4PFJets->size()>=2) {
#endif
  //cout<<"Check 3 : Lead Jet pt :"<<leadingpt<<endl;
  //cout<<"Check 3 : Sub-Lead Jet pt :"<<aveleadingpt<<endl;
  if (isReconstruct && isMC && leadingpt>3*qscale) return;
  irecoht = getbinid(leadingpt, nHLTmx, leadingPtThreshold);
  //cout<<"irecoht : "<<irecoht<<endl;

#ifdef TRIGGER
  bool trgpas[nHLTmx]={0,0,0,0,0,0,0,0,0,0};  //8 or 10
  //Calcualte Trigger Efficiency for dijet events
  bool trg_prev=false;

  //if (!isMC) {
  for (int jk=-1; jk<nHLTmx; jk++) {
    for(unsigned ij = 0; ij<trigRes->size(); ++ij) {
      std::string name = names.triggerName(ij);
      variab1 = name.c_str(); 
      if ((jk<0 && strstr(variab1,jethlt_lowest) && strlen(variab1)-strlen(jethlt_lowest)<5) || 
	  (jk>=0 && strstr(variab1,jethlt_name[jk]) && strlen(variab1)-strlen(jethlt_name[jk])<5)) {
	
	 //const std::pair<std::vector<std::pair<std::string,int> >,int> prescalesInDetail(hltConfig_.prescaleValuesInDetail(iEvent,iSetup, variab1));
	 const std::pair<std::vector<std::pair<std::string,int> >,int> prescalesInDetail(hltPrescaleProvider_.prescaleValuesInDetail(iEvent,iSetup,variab1));
	 if (jk>=0) { 
          //cout<<variab1<<endl;
	  //==============================================================================
	  //double tmpp1= prescalesInDetail.first[0].second;
	  //double tmpp2 = prescalesInDetail.first[1].second;
	  //l1pres[jk] =min(tmpp1, tmpp2);
	  //==============================================================================
	  l1pres[jk] = prescalesInDetail.first[0].second;
	  
	 //if (jk>=3 && l1pres[jk]>1) { l1pres[jk]=1.0;}
	 if(l1pres[jk]<=0){l1pres[jk]=1.0;}
         hltpres[jk] = prescalesInDetail.second;	  

	 //compres[jk] = (l1pres[jk])*(triggerPrescales->getPrescaleForIndex(ij)); 
	 //compres[jk] = triggerPrescales->getPrescaleForIndex(ij);
	 compres[jk] = (l1pres[jk])*(hltpres[jk]);
         //if (jk==9){compres[jk]=1.0;} // fix for 2017E sample pt spike
	         	//cout<<"Print Trigger : "<<variab1<< ":"<< compres[jk]<<endl;} 
	 //cout << "Prescale" << "Path " << variab1 <<" " <<   compres[jk] << endl;
	 //cout<<"Run NO= "<< iEvent.id().run()<<" ; Event No = "<< iEvent.id().event()<< " ; ilumi = " << iEvent.luminosityBlock() << 
	 //	" ; ibunch = " << iEvent.bunchCrossing()<<" ; L1 Pres0 = " << l1pres[jk] <<" "<<
	 //            " ; HLT Path= "<<name <<" ; HLT Pres = " <<hltpres[jk]<<" ; compres ="<<compres[jk] <<"; irecoht = "<< irecoht <<"; Pt=" <<aveleadingpt<<endl;
	 if (trigRes->accept(ij)) {trgpas[jk] = true;
		//cout << "Prescale" << "Path " << variab1 <<" " <<   compres[jk] << endl;} // ihltfill = jk;}
	 }
	 //if (trg_prev && compres[jk]>0.99) {
	 if (trg_prev){
	    for (int iet=0; iet<njetetamn; iet++) {
	      if (isInEtaRange[iet]) { 
		//hlt_dijettag[jk][iet]->Fill(aveleadingpt,compres[jk]);
                hlt_dijettag[jk][iet]->Fill(leadingpt,compres[jk]);
		//if (trigRes->accept(ij)) {hlt_dijetprob[jk][iet]->Fill(aveleadingpt, compres[jk]);} //{, (isMC) ? 1.0 : compres[jk]);}
                if (trigRes->accept(ij)) {hlt_dijetprob[jk][iet]->Fill(leadingpt, compres[jk]);}
	      }
	    }
	  }
	  /*
 	    for (int iet=0; iet<njetetamn; iet++) {
	    if (isInEtaRange[iet]) { 
	    if(trg_prev) hlt_dijettag[jk][iet]->Fill(aveleadingpt);
	    if (trg_prev && trigRes->accept(ij)) {hlt_dijetprob[jk][iet]->Fill(aveleadingpt);} 
	    }    
	    }*/
	  //if (trg_prev) cout << "Accept =" << " name = " <<name <<endl;
	  trg_prev = trigRes->accept(ij);
	  //trg_prev = trg_prev|trigRes->accept(ij);
	  //if (!trg_prev) { trg_prev = trigRes->accept(ij);}
	  break;
	} else {
	  trg_prev = trigRes->accept(ij);
	  break;
	}
      }
    }
  }
#endif
  //cout<<"ihltfill "<<ihltfill<<endl;
  //cout<<"3 aveleadingpt "<<aveleadingpt<< " ; "<<ihltfill<<" "<<irecoht<<endl;
  
  //if ((irecoht <0 || irecoht >=nHLTmx) || ((!isMC) && (!trgpas[irecoht]))) return; //GMA remopve this condition
  //cout <<"irecoht = "<<irecoht<<endl;
  //if (irecoht==-3) return;
#ifdef TRIGGER
  if (irecoht>=0 && ((!isMC) && (!trgpas[irecoht]))) return;
  if (irecoht==-2 && ((!isMC) && (!trgpas[0]))) return;
  //cout<<"Check 4 : Lead Jet pt : "<<leadingpt<<endl;
#endif
  
  if (!isMC) {
    if (irecoht>=0) {
      wtfact = compres[irecoht];
    } else if (irecoht==-2) {
      wtfact = compres[0];
    } else {
      return ;
    }
  }
  //cout<<"Check 5 : Lead Jet pt : "<<leadingpt<<endl;
  //for (int ij=0; ij<nHLTmx; ij++) {lumiwt[ij]=intlumi[nHLTmx-1]/intlumi[ij];}// cout<<"nt "<<datpileup[ij][0]<<endl;}
  if (isMC) {
#ifndef GENPART
    //Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    //iEvent.getByLabel("addPileupInfo", PupInfo);
    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
    iEvent.getByToken(pileup_, PupInfo);
    int npu = -1;
    //int tnpv  = -1;
    PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
    PShiftUp_ = reweight::PoissonMeanShifter(0.5);
    if (PupInfo.isValid()) {
      std::vector<PileupSummaryInfo>::const_iterator PVI;
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
	if (PVI->getBunchCrossing()==0) {
          //npu = PVI->getPU_NumInteractions();
	  npu = PVI->getTrueNumInteractions();
          //tnpv  = PVI->getTrueNumInteractions();
	  break;
	}
      }
    }
    //double MyWeight = LumiWeights_->weight(npu);
    
    //cout << "Main weight = " <<MyWeight << endl;
    //double TotalWeight_plus = MyWeight*PShiftUp_.ShiftWeight( npu );
    //double TotalWeight_plus = PShiftUp_.ShiftWeight( npu );
    //double TotalWeight_minus = PShiftDown_.ShiftWeight( npu ); 

    //cout << "Plus " << wtfact*TotalWeight_plus << " Mi = " << endl;
    //cout << "wt= " <<  wtfact << " : weightmi" <<wtfact*TotalWeight_minus << " Mi = " << endl;
    //wtfact=wtfact*TotalWeight_plus; 
    //wtfact=wtfact-TotalWeight_minus; 
    //cout << "npu Number of interactions : " << npu << endl; 
    //cout << "tnpv Number of true interactions : " << tnpv << endl; 
    if (npu<0) return; //GMA  
    if (isFlat) {
      weight =weight2*wtfact; // for flat MC sample
    } else {
      weight =weight2;
    }
#endif
    defweight = weight;
//-------------------------------------------
#ifndef GENPART
    int tmprecht = (irecoht>=0) ? irecoht : 0; //GMA
    
    if (npu<npileupmx) {
          weight *=rat_pileup[tmprecht][npu]; //GMA
    } else {
            weight *=rat_pileup[tmprecht][npileupmx-1]; //GMA
    }
#endif
    
    weighttrg = weight;
    //cout <<"weight  "<<weight<<" "<< weight2<<endl;
    //sar 3D PU reweighting 111028
  } else {
    weight = weight2;
    defweight = weight2;
    weighttrg = weight*wtfact; // *lumiwt[irecoht];
    //weighttrg = weight*lumiwt[3];
    //cout <<"TEST2  weighttrg "<< weighttrg<<" ; weight "<<weight<<" ; "<< wtfact<<endl;
  }

/*
#ifdef PREFIRE
double tmpwt = weighttrg;
weighttrg = tmpwt*_prefiringweight;
//weighttrg = tmpwt*_prefiringweightup;
//weighttrg = tmpwt*_prefiringweightdown;
#endif
*/

//---------------Lumiweight------------------
/*
//cout << "before lumi " << weighttrg ;
#ifdef LUMIWEIGHT
double tmpwt = weighttrg;
weighttrg = tmpwt*lumiwtt;
#endif
//cout << "   After lumi " << weighttrg << endl;
*/

//-------------------------------------------
#ifndef GENPART
  if(!isMC){
    reco::TrackBase::Point beamPoint(0,0, 0);
    //math::XYZPoint beamPoint(0,0, 0); 
    
    edm::Handle<reco::BeamSpot> beamSpotH;
    iEvent.getByToken(beamSpot_,beamSpotH);
    if (beamSpotH.isValid()){
      beamPoint = beamSpotH->position();
    }
    
    edm::Handle<reco::VertexCollection> primaryVertices;
    iEvent.getByToken(vtxToken_, primaryVertices);
    
    int tmpvert=0;
    nprim=0;
    if (primaryVertices.isValid()) {
      tmpvert = primaryVertices->size();
      //cout<<"temp"<<tmpvert<<endl;
      for (reco::VertexCollection::const_iterator vert=primaryVertices->begin(); vert<primaryVertices->end(); vert++) {
	int isel = (vert->isValid() && !vert->isFake()) ? 1 : 0;
	int ngoodtrk = 0;
	int nseltrk = 0;
	double prob = ChiSquaredProbability(vert->chi2(),vert->ndof());
	for (reco::Vertex::trackRef_iterator reftrk =vert->tracks_begin(); reftrk<vert->tracks_end(); reftrk++) {
	  if ((*reftrk)->quality(TrackBase::highPurity) && vert->trackWeight(*reftrk)>0) {
	    ngoodtrk++; 
	    if ((*reftrk)->normalizedChi2()<100000 && 
		abs((*reftrk)->dxy()) < 10000 && 
		(*reftrk)->pt() >0.50) {nseltrk++; } 
	  }
	}
	prim_alltrk[isel]->Fill(vert->tracksSize());
	prim_goodtrk[isel]->Fill(ngoodtrk);
	prim_seltrk[isel]->Fill(nseltrk);
	prim_dx[isel]->Fill(vert->position().x() - beamPoint.x());
	prim_dy[isel]->Fill(vert->position().y() - beamPoint.y());
	prim_dxy[isel]->Fill(vert->position().x() - beamPoint.x(), vert->position().y() - beamPoint.y());
	prim_dz[isel]->Fill(vert->position().z() - beamPoint.z());
	prim_prob[isel]->Fill(max(-20.0, log10(prob)));
	
	if (isel==1 && nprim < nprimx-1) {
	  primpr[nprim] = prob;
	  ntkpm[nprim] = 1000*(1000*min(int(vert->tracksSize()),999) + min(ngoodtrk,999)) + min(999, nseltrk);
	  nprim++;
	}
      }
    }
    
    prim_hist[0]->Fill(tmpvert);
    prim_sel[0]->Fill(nprim);
    
    prim_hist_rewt[0]->Fill(tmpvert, weighttrg);
    prim_sel_rewt[0]->Fill(nprim, weighttrg);

    if (irecoht>=0 && irecoht<nHLTmx) { 
      prim_hist[irecoht]->Fill(tmpvert);
      prim_sel[irecoht]->Fill(nprim);
      
      prim_hist_rewt[irecoht]->Fill(tmpvert, weighttrg);
      prim_sel_rewt[irecoht]->Fill(nprim, weighttrg);   
    }
    prim_correl->Fill(tmpvert, nprim);
  } 
#endif 
  //cout<<"Check 6 : Lead Jet pt : "<<leadingpt<< " irecoht : "<<irecoht<<endl; 
   
//start finding Jet mactching...

if(isMC) {

//    edm::Handle<reco::GenJetCollection> genjets;
//    iEvent.getByToken(genjetToken_,genjets);
} 
  vector<double> jetptx[njecmx];
  vector<double> jetscl[njecmx];
  vector<int> jetindx[njecmx];

#ifndef GENPART
  if (ak4PFJets.isValid()) { 
    for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++) {
      double pt = (*ak4PFJets)[ijet].pt();
      //cout<<"Check 7: Lead Jet pt : "<<(*ak4PFJets)[0].pt()<<endl;
      
      //#ifndef JETENERGY
      //#ifdef JETRESO
      
#if defined(JETRESO)&&(!defined(JETENERGY))
      //resolution file 
      JME::JetResolution resolution;
      //resolution = JME::JetResolution("Summer19UL17_JRV2_DATA_PtResolution_AK4PFchs.txt");    // for DATA
      resolution = JME::JetResolution("Summer19UL17_JRV2_MC_PtResolution_AK4PFchs.txt");      // for MC
 
      //Scalefactor file
      JME::JetResolutionScaleFactor res_sf;
      //cout<<"Filename="<<scalefile<<endl;
      //res_sf = JME::JetResolutionScaleFactor("Summer19UL17_JRV2_DATA_SF_AK4PFchs.txt");        // for DATA
      res_sf = JME::JetResolutionScaleFactor("Summer19UL17_JRV2_MC_SF_AK4PFchs.txt");          // for MC
      
      edm::Handle<double> rho;
      iEvent.getByToken(m_rho_token, rho);
      //cout<< "  rho=" << *rho << endl;
      
      //cout << "Write test 3 = ok " << endl;
      double eta = (*ak4PFJets)[ijet].eta();
      double reso = 1;
      JME::JetParameters parameters_5 = {{JME::Binning::JetPt, pt}, {JME::Binning::JetEta, eta}, {JME::Binning::Rho, *rho}};
      float rp = resolution.getResolution(parameters_5);
      float sf = res_sf.getScaleFactor({{JME::Binning::JetEta, eta}});
      float sf_up= res_sf.getScaleFactor({{JME::Binning::JetEta, eta}}, Variation::UP);
      float sf_dn= res_sf.getScaleFactor({{JME::Binning::JetEta, eta}}, Variation::DOWN);
      //#endif
      //#endif
#endif 
      for (int isrc = 0; isrc < njecmx; isrc++) {
	double sup = 1;
#ifdef JETENERGY
	double eta = (*ak4PFJets)[ijet].eta();
	if (isrc>0 && isrc<=nsrc) {
	  JetCorrectionUncertainty *jecUnc = vsrc[isrc-1];
	  jecUnc->setJetEta(eta);
	  jecUnc->setJetPt(pt);
	  
	  sup += jecUnc->getUncertainty(true);
	} else if (isrc>nsrc) {
	  JetCorrectionUncertainty *jecUnc = vsrc[isrc-nsrc-1];
	  jecUnc->setJetEta(eta);
	  jecUnc->setJetPt(pt);
	  sup -= jecUnc->getUncertainty(false);
	}
#elif defined(JETRESO)
	if (isrc==0) {  
	  reso = sqrt(abs(sf*sf - 1))*rp;
	} else if (isrc==1) {
	  reso = sqrt(abs(sf_up*sf_up - 1))*rp;
	} else if (isrc==2) {
	  reso = sqrt(abs(sf_dn*sf_dn - 1))*rp;
	}
	sup = gRandom->Gaus(1.0, reso);			
#endif
	jetptx[isrc].push_back(sup*pt);
	jetscl[isrc].push_back(sup);
	jetindx[isrc].push_back(ijet);
      }
    }
//#if defined(JETENERGY)||defined(JETRESO)
    
    for (int isrc = 0; isrc < njecmx; isrc++) {
      for (unsigned int ij=0; ij<jetptx[isrc].size()-1; ij++) {
	for (unsigned int jk=ij+1; jk<jetptx[isrc].size(); jk++) {
	  if (jetptx[isrc][jk]>jetptx[isrc][ij]) {
	    double tmppt = jetptx[isrc][ij];
	    double tmpscl = jetscl[isrc][ij];
	    int tmpindx = jetindx[isrc][ij];
	    
	    jetptx[isrc][ij] = jetptx[isrc][jk];
	    jetscl[isrc][ij] = jetscl[isrc][jk];
	    jetindx[isrc][ij] = jetindx[isrc][jk];					
	    
	    jetptx[isrc][jk] = tmppt;
	    jetscl[isrc][jk] = tmpscl;
	    jetindx[isrc][jk] = tmpindx;
	  }
	}
      }
    }
    //#endif
    
    //cout<<"Check 8 : Lead Jet pt : "<<leadingpt<< " irecoht : "<<irecoht<<endl;
    
    for (int isrc = 0; isrc < njecmx; isrc++) {
      if (jetptx[isrc].size()>=2) {
	leadingptjec[isrc] = jetptx[isrc][0];
        irecohtjec[isrc] = getbinid(leadingptjec[isrc], nHLTmx, leadingPtThreshold);
      } else {
	irecohtjec[isrc] = -1;
      }
    }

   //cout<<"Check 9 : Lead Jet pt : "<<leadingpt<< " irecoht : "<<irecoht<<endl;
   //cout<<"Check 9 : Lead Jet pt after correction (*ak4PFJets)[jetindx[0][0]] : "<<(*ak4PFJets)[jetindx[0][0]].pt()<< " irecohtjec[0] : "<<irecohtjec[0]<<endl;
   //cout<<"Check 9 : Lead Jet pt after correction leadingptjec[0] : "<<leadingptjec[0]<<endl; 
   //cout<<"Check 9 : Lead Jet pt after correction (*ak4PFJets)[jetscl[0][0]] : "<<(*ak4PFJets)[jetscl[0][0]].pt()<<endl;

    //GMA Need the corection on aveleadingpt
    if (ak4PFJets.isValid() && ak4PFJets->size() >=2) { //  && aveleadingpt >leadingPtThreshold[0]) { //GMA look on this
      
      for (int iet=0; iet<njetetamn; iet++) {
	for (int isrc = 0; isrc < njecmx; isrc++) {
	  //if (aveleadingptjec[isrc] >leadingPtThreshold[0]) {
	  if (leadingptjec[isrc] >leadingPtThreshold[0]) {
	  //cout<<"Check 10 : Lead Jet pt after correction in the jet loop leadingptjec[0] : "<<leadingptjec[0]<<endl; 
          //cout<<"Check 10 : Lead Jet pt after correction in the jet loop (*ak4PFJets)[jetindx[0][0]] : "<<(*ak4PFJets)[jetindx[0][0]].pt()<<endl;
	  //cout<<"Check 10 : Lead Jet pt after correction in the jet loop (*ak4PFJets)[jetscl[0][0]] : "<<(*ak4PFJets)[jetscl[0][0]].pt()<<endl;
	    //int njets=0;
	    ncount=0;
	    //recterm=0;
	    //ithird=-1;
	    //double sup = 1;	
	    //px=0;
	    //py=0;
	    //ptxy=0;
	    tmpjt4v.clear();
	    //tmpcand4v.clear();
	    //tmpgen4v.clear();
	    
	    //if (abs((*ak4PFJets)[0].eta())<etarange[iet] && abs((*ak4PFJets)[1].eta())<etarange[iet]) {
	    //for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++) {
	    
	    for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++) {
	      if (abs((*ak4PFJets)[jetindx[isrc][0]].eta())<etarange[iet] && abs((*ak4PFJets)[jetindx[isrc][1]].eta())<etarange[iet]) {
		//if (abs((*ak4PFJets)[jetindx[isrc][ijet]].eta())<etarange[iet]) {
		//if (deltaR(((*ak4PFJets)[jetindx[isrc][0]]),((*ak4PFJets)[jetindx[isrc][ijet]]))<1.6) continue;
	        if (dPhi(((*ak4PFJets)[jetindx[isrc][0]].phi()), ((*ak4PFJets)[jetindx[isrc][1]].phi()))<2.0) continue;
		if (dPT(((*ak4PFJets)[jetindx[isrc][0]].pt()), ((*ak4PFJets)[jetindx[isrc][1]].pt()))>0.3) continue;
		//if ((((*ak4PFJets)[jetindx[isrc][0]].pt()) / ((*ak4PFJets)[jetindx[isrc][1]].pt()))>1.5) continue;
	      	//int flavour = (*ak4PFJets)[ijet].partonFlavour();
        	//cout << "Flavour : "<<flavour<<endl;
	        //cout<<"Check 11 : Lead Jet pt after correction in the second jet loop (*ak4PFJets)[jetindx[0][0]] : "<<(*ak4PFJets)[jetindx[0][0]].pt()<<" eta "<<(*ak4PFJets)[jetindx[0][0]].eta()<<endl;
		//cout<<"Check 11 : Lead Jet pt after correction in the second jet loop (*ak4PFJets)[jetscl[0][0]] : "<<(*ak4PFJets)[jetscl[0][0]].pt()<<" eta "<<(*ak4PFJets)[jetscl[0][0]].eta()<<endl;
		
		int ireorjt = jetindx[isrc][ijet];
		
		//int jetflav = (*ak4PFJets)[ireorjt].partonFlavour();	
		//if(jetflav==5){cout << "Flavour : "<<jetflav<<endl;}	
		
		double pt = jetptx[isrc][ijet];
		double sup = jetscl[isrc][ijet];
		double abseta = abs((*ak4PFJets)[ireorjt].eta());
	        if (pt<30.0 || abseta >etarange[iet]) continue;	
		//if (iet==0 && isrc==0) cout <<"pteta "<<pt<<" "<<abseta<<endl;
		//bool isEta = (abseta<2.5) ? true : false;
		bool isEta = (abseta<2.1) ? true : false;
		
		//if (isEta && pt>30.0) { njets++;}
		if (abseta>5.0) continue;
		bool isPt = (pt>30.0) ? true : false;
		if (isEta && isPt) {ncount++;}
		
		//cout<< "ncount = " << ncount << endl;
		//Jet ID ================= Tight ID 2017 Recomendation  check for 2018
		double NHF = (*ak4PFJets)[ireorjt].neutralHadronEnergyFraction();
		double NEMF = (*ak4PFJets)[ireorjt].neutralEmEnergyFraction();
		double CHF = (*ak4PFJets)[ireorjt].chargedHadronEnergyFraction();
		//double MUF = (*ak4PFJets)[ireorjt].muonEnergyFraction();
		//double CEMF = (*ak4PFJets)[ireorjt].chargedEmEnergyFraction();
		int NumConst = (*ak4PFJets)[ireorjt].chargedMultiplicity()+(*ak4PFJets)[ireorjt].neutralMultiplicity();
		//int NumNeutralParticles =(*ak4PFJets)[ireorjt].neutralMultiplicity();
		int CHM = (*ak4PFJets)[ireorjt].chargedMultiplicity();
                //cout<<"NHF== "<< NHF << "; NEF== " << NEMF <<" ; CHF==" <<CHF <<" ;cef==" << CEMF <<"; no= " << NumConst <<" ; nch==" << CHM <<" ; NO of part==" << NumNeutralParticles <<endl;
		bool TightJetID =false;
                //if (abs((*ak4PFJets)[ireorjt].eta())<=2.6 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 ) {TightJetID =true;}
      		//else {TightJetID =false;}
      		if(abs((*ak4PFJets)[ireorjt].eta())<=2.7){
                if(NHF<0.90 && NEMF<0.90 && NumConst>1 && CHF>0 && CHM>0 && abs((*ak4PFJets)[ireorjt].eta())<=2.6)  TightJetID =true;
                if(NHF<0.90 && NEMF<0.99 && abs((*ak4PFJets)[ireorjt].eta())>2.6)  TightJetID =true;}
                else {TightJetID =false;}
                if (abs((*ak4PFJets)[ireorjt].eta())>2.7) {TightJetID = false;}
                if ((*ak4PFJets)[ireorjt].pt()<30.0) {TightJetID = false;}
		
		if( ireorjt<=1 && !TightJetID) break;
		if (!TightJetID) continue;
			
		HepLorentzVector tmp4v((*ak4PFJets)[ireorjt].px(), (*ak4PFJets)[ireorjt].py(), (*ak4PFJets)[ireorjt].pz(), (*ak4PFJets)[ireorjt].energy()); tmp4v *=sup;
                Hep3Vector tmp3v((*ak4PFJets)[ireorjt].px(), (*ak4PFJets)[ireorjt].py(), (*ak4PFJets)[ireorjt].pz()); tmp3v *=sup;
	        //cout <<"Test " << sup <<endl;
		//(*ak4PFJets)[jetindx[isrc][ijet]] *=sup;
		//if(ijet==0 && isrc==0){cout<<"Check 12 : Lead Jet pt after using HepLorentzVector : "<<tmp4v.perp()<< " eta "<<tmp4v.eta()<<endl;}
		if (isEta && isPt) { tmpjt4v.push_back(tmp4v);}
		//tmpjt4v.push_back(tmp4v);	  
		//if (isEta && isPt) {allrecojetmom.push_back(tmp4v);}
		//if (ncount<=2) {  //change for all jet 26th June
		  if (isEta && isPt) {recomom[isrc][0][iet].push_back(tmp4v);}
		  //}
		  //cout <<"ncount filled "<<ncount<<" "<<isrc<<" "<<iet<<" "<<recomom[isrc][0][iet].size()<<endl;
		  //px +=tmp4v.px();
		  //py +=tmp4v.py();
		  //ptxy +=tmp4v.perp();
		  if (isrc==0) { 
		    if ((isInEtaRange[iet])) {recojt_pt[iet]->Fill(tmp4v.perp(), weighttrg);}
		    if (isPt && iet==0) {recojt_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isEta && isPt) {recojt_phi->Fill(tmp4v.phi(), weighttrg);}
		    if (isEta && ncount==1) {recoht2_pt[iet]->Fill(aveleadingpt,weighttrg);}
		  }//if (isrc==0) {
		
		if (isrc==0) { 
		  if(ijet==0) { 
		    if (isInEtaRange[iet]) {recojt1_pt[iet]->Fill(tmp4v.perp(), weighttrg);} //recojet1_pt = tmp4v.perp();}
		    if (isPt && iet==0) {recojt1_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isEta && isPt) {recojt1_phi->Fill(tmp4v.phi(), weighttrg);}
			//cout<<"Check 13 : Lead Jet pt isrc==0 : "<<tmp4v.perp()<< "eta "<< tmp4v.eta()<<endl;
		  } else if(ijet==1){
		    if (isInEtaRange[iet]) {recojt2_pt[iet]->Fill(tmp4v.perp(), weighttrg);} //recojet2_pt = tmp4v.perp();}
		    if (isPt && iet==0) {recojt2_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isInEtaRange[iet] && isPt) {recojt2_phi->Fill(tmp4v.phi(), weighttrg);}

		    if (isInEtaRange[iet] && ncount==2) { 
		      if (irecoht>=0 && irecoht<nHLTmx) { 
			recojtave_pt[iet][irecoht]->Fill(aveleadingpt, weighttrg);
			recojtavewt1_pt[iet][irecoht]->Fill(aveleadingpt);
		      }
		      
		      recojtallavewt1_pt[iet]->Fill(aveleadingpt);
		      recojtallave_pt[iet]->Fill(aveleadingpt, weighttrg);
		    }
		    
		  } else if(ijet==2) {
		    if (isInEtaRange[iet]) {recojt3_pt[iet]->Fill(tmp4v.perp(), weighttrg);}
		    if (isPt && iet==0 ) {recojt3_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isInEtaRange[iet] && isPt) {recojt3_phi->Fill(tmp4v.phi(), weighttrg);} 
		  }
		  
		  if (tmpjt4v.size()==2 && isInEtaRange[iet]) { 
		    double dphi = dPhi(tmpjt4v[0].phi(), tmpjt4v[1].phi());
		    double dpt = tmpjt4v[0].perp() - tmpjt4v[1].perp();
		    double dperp = fabs(tmpjt4v[1].perp()*sin(dphi))/tmpjt4v[0].perp();
		    hjetdphi[iet]->Fill(dphi, weighttrg);
		    hjetdpt[iet]->Fill(dpt, weighttrg);
		    hjetptbypl[iet]->Fill(dperp, weighttrg);
		    hjetpt2bypt1[iet]->Fill(tmpjt4v[1].perp()/tmpjt4v[0].perp(), weighttrg);
		  }
		  
		  if (tmpjt4v.size()==3) {hjetpt3bypt2[iet]->Fill(tmpjt4v[2].perp()/tmpjt4v[1].perp(), weighttrg);}
		  } //if (isrc==0) {
		
		//int nchg=0;
		nchg = 0;
		//(*ak4PFJets)[ireorjt] *=sup;
		std::vector<reco::CandidatePtr> daus((*ak4PFJets)[ireorjt].daughterPtrVector());           
		std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });               
      		                                                                   
		for (unsigned int i2 = 0; i2< daus.size(); ++i2) { //particle loop  
		  const pat::PackedCandidate &pfcand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
		  int charge = pfcand.charge();
		  HepLorentzVector cand4v(pfcand.px(), pfcand.py(), pfcand.pz(), pfcand.energy());
		  //tmpcand4v.push_back(cand4v);	
                  //nchg++;
		  if (charge !=0){
                  	//h_nchg[iet]->Fill(nchg, weighttrg);   // need to check
			nchg++;
                  	}
		  //if (cand4v.perp()<0.5) continue;
		  //if (ncount<=2 && isEta && isPt) { 
		  //recomom[isrc][1][iet].push_back(cand4v);
		    
		    if (charge !=0) {
		      recomom[isrc][1][iet].push_back(cand4v);
                      //if(cand4v.perp()>1.0){mom[isrc][iet].push_back(cand4v);}
#ifdef TRACKSYS
		      if (gRandom->Uniform() < 0.96) {recomom[isrc][2][iet].push_back(cand4v); }
#endif
		}
		  if (isrc==0) { 
		    //if (isEta && isPt) {
		      if (charge !=0) {
			recochg_phi->Fill(cand4v.phi(), weighttrg);
			recochg_pt->Fill(cand4v.perp(), weighttrg);
			recochg_eta->Fill(cand4v.eta(), weighttrg);
		      }
		    
		      if (ijet==0 && charge !=0) {
                        recochg1_phi->Fill(cand4v.phi(), weighttrg);
                        recochg1_pt->Fill(cand4v.perp(), weighttrg);
                        recochg1_eta->Fill(cand4v.eta(), weighttrg);
		      }
                     else if (ijet==1 && charge !=0) {
                        recochg2_phi->Fill(cand4v.phi(), weighttrg);
                        recochg2_pt->Fill(cand4v.perp(), weighttrg);
                        recochg2_eta->Fill(cand4v.eta(), weighttrg);
                      }
                     else if (ijet==2 && charge !=0) {
                        recochg3_phi->Fill(cand4v.phi(), weighttrg);
                        recochg3_pt->Fill(cand4v.perp(), weighttrg);
                        recochg3_eta->Fill(cand4v.eta(), weighttrg);
                      }                     

		    }//if (isrc==0) {
		     //}
	} //for (unsigned int i2 = 0; i2< daus.size(); ++i2
        h_nchg[iet]->Fill(nchg, weighttrg);    

	if(ijet==0){ 
		for (int ik=0; ik<10; ik++){                                                        
                for (unsigned int i2 = 0; i2< daus.size(); ++i2) { //particle loop  
                const pat::PackedCandidate &pfcand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
                int charge = pfcand.charge();
		Hep3Vector cand3v(pfcand.px(), pfcand.py(), pfcand.pz());
		if(cand3v.perp()>1.0 && abs(cand3v.eta())<2.5){
		if(isrc==0){
			recojet1_pt = tmp3v.perp();
			
			ijet1candsmom[ik] += charge*(pow(cand3v.perp(), kappa[ik])); 

			ijet1_long_num[ik] += (charge*(dotProductPower(cand3v,tmp3v,kappa[ik])));
			ijet1_long_den[ik] += (dotProductPower(cand3v,tmp3v,kappa[ik]));
			
			ijet1_tran_num[ik] += (charge*(crossProductPower(cand3v,tmp3v,kappa[ik])));
			ijet1_tran_den[ik] += (crossProductPower(cand3v,tmp3v,kappa[ik]));
			//cout<<" Reco particle check 1 : "<<" pt : "<<pfcand.pt()<<" eta : "<<pfcand.eta()<<" id : "<<pfcand.pdgId()<<endl;
			//cout<<" Reco particle from HepLorentzVector check 1 : "<<" pt : "<<pfcand.pt()<<" eta : "<<pfcand.eta()<<" id : "<<pfcand.pdgId()<<endl;
					}
				}
			}
		}
	}
	//cout<<"Check 14 : Lead Jet pt : "<<recojet1_pt<<endl;
	if(ijet==1){
		for (int ik=0; ik<10; ik++){
                for (unsigned int i2 = 0; i2< daus.size(); ++i2) { //particle loop
		const pat::PackedCandidate &pfcand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
                int charge = pfcand.charge();
		Hep3Vector cand3v(pfcand.px(), pfcand.py(), pfcand.pz());
		if(cand3v.perp()>1.0 && abs(cand3v.eta())<2.5){
                if(isrc==0){
			recojet2_pt = tmp3v.perp();
                        
			ijet2candsmom[ik] += candsmom(charge, cand3v.perp(), kappa[ik]);
		
			ijet2_long_num[ik] += (charge*(dotProductPower(cand3v,tmp3v,kappa[ik])));
                        ijet2_long_den[ik] += (dotProductPower(cand3v,tmp3v,kappa[ik]));

                        ijet2_tran_num[ik] += (charge*(crossProductPower(cand3v,tmp3v,kappa[ik])));
                        ijet2_tran_den[ik] += (crossProductPower(cand3v,tmp3v,kappa[ik]));			
                                        }
                                }
                        }
                }
	}//if(isrc==0){

		//  if(isEta && isPt) {ncount++;}
	   	//  }//if (abs((*ak4PFJets)[jetindx[isrc][0]].eta())<etarange[iet] && abs((*ak4PFJets)[jetindx[isrc][1]].eta())<etarange[iet])
	  	//  }//for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++)
/*	    if (ithird>=0) {
	      
	      recomom[isrc][0][iet].push_back(tmp4v);
	      //					cout <<"recomom[isrc][0][iet] "<< isrc<<" "<<iet<<" "<<recomom[isrc][0][iet].size()<<endl;
	      // tmpjt4v.push_back(tmp4v);   
	      
	      std::vector<reco::CandidatePtr> daus((*ak4PFJets)[ithird].daughterPtrVector());
	      std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2 ->pt(); });
	      for (unsigned int i2 = 0; i2< daus.size(); ++i2) {
		const pat::PackedCandidate &pfcand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
		int charge = pfcand.charge();
		HepLorentzVector cand4v(pfcand.px(), pfcand.py(), pfcand.pz(), pfcand.energy());
		//      if (cand4v.perp()<0.5) continue;                                                             
		recomom[isrc][1][iet].push_back(cand4v);
		
		if (charge !=0) {
		  recomom[isrc][2][iet].push_back(cand4v);
#ifdef TRACKSYS
		  if (gRandom->Uniform() < 0.96) {recomom[isrc][4][iet].push_back(cand4v); }
#endif
		  
		}
		if (charge==0){
		  if (cand4v.perp()>1.0) {
		    recomom[isrc][3][iet].push_back(cand4v);
		  }
		} else{
		  if (cand4v.perp()>0.5) {
		    recomom[isrc][3][iet].push_back(cand4v);
		  }
		}
	      }
	    }*/ //if (ithird>=0) 
	    h_njets[iet]->Fill(ncount, weighttrg);
              } //if (abs((*ak4PFJets)[jetindx[isrc][0]].eta())<etarange[iet] && abs((*ak4PFJets)[jetindx[isrc][1]].eta())<etarange[iet])
            } // for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++)
	  } //if (aveleadingptjec[isrc] >leadingPtThreshold[0])
	} // 	for (int isrc = 0; isrc < njecmx; isrc++)
      } //for (int iet=0; iet<njetetamn; iet++)	   
    } // if (ak4PFJets.isValid() && ak4PFJets->size()>=2 && (*ak4PFJets)[0].pt()>leadingPtThreshold[0])
  } // if (ak4PFJets.isValid())
#endif 
  //cout << "Write test 1 = ok " << endl;
  //==================================***GenJets*****=================================
  //cout<<"0 aveleadingpt "<<aveleadingpt<< " ; "<<ihltfill<<" "<<irecoht<<endl;
  edm::Handle<reco::GenJetCollection> genjets;
  if(isMC) {
    //edm::Handle<reco::GenJetCollection> genjets;
    iEvent.getByToken(genjetToken_,genjets);
    
    double avegenpt =0;
    double leadgenpt =0;
    //cout <<"HGebjet "<<endl;
    if (genjets.isValid() &&  genjets->size()>=2) {
#ifdef DIJETAVE
	//cout<<"Check 1 : Lead GetJet pt : "<<(*genjets)[0].pt()<<endl;
	//cout<<"Check 1 : Sub-Lead GetJet pt : "<<(*genjets)[1].pt()<<endl;
      for (int iet=0; iet<njetetamn; iet++) {
	isInEtaRange[iet] = true;
      }
      
      for (int ij=0; ij<2; ij++) {
	for (int iet=0; iet<njetetamn; iet++) {
	  if (abs((*genjets)[ij].eta())>etarange[iet]) { isInEtaRange[iet] = false;}
	}
	
	//if (abs((*genjets)[ij].eta())<2.5 && (*genjets)[ij].pt()>30.0 ) {
	
	if (abs((*genjets)[ij].eta())<2.1 && (*genjets)[ij].pt()>30.0 ) { 
	  avegenpt +=(*genjets)[ij].pt();
          leadgenpt = (*genjets)[0].pt();
	} else {avegenpt -=100000;
		leadgenpt -=100000;}
	/*
	if (abs((*genjets)[ij].eta())>2.1 && (*genjets)[ij].pt()<30.0 ) continue;
	  avegenpt +=(*genjets)[ij].pt();
          leadgenpt = (*genjets)[0].pt();
	*/
      }
	//cout<<"Check 2 : Lead GetJet pt : "<<leadgenpt<<endl;
        //cout<<"Check 2 : Sub-Lead GetJet pt : "<<(*genjets)[1].pt()<<endl;
	//cout<<"Check 2 : Sum of 2 GetJet pt : "<<avegenpt<<endl;
        avegenpt /=2.0;
	//cout<<"Check 2 : Avg of 2 GetJet pt : "<<avegenpt<<endl; 
#else 

#endif
    } 
    
    //igenht = getbinid(leadgenpt, njetptmn, leadingPtThreshold);
 
    //cout << "Write test 2 = ok " << endl;
    //cout << "Write test 321 = ok " << endl;
    vector<double> genjetptx[nGenReso];
    vector<double> genjetscl[nGenReso]; 
    vector<int> genjetindx[nGenReso];
    
    for(unsigned ijet = 0; ijet != genjets->size(); ijet++) {
      double pt = (*genjets)[ijet].pt();
      for (int isrc = 0; isrc < nGenReso; isrc++) {
	double sup = 1.0;	
	genjetptx[isrc].push_back(sup*pt);
	genjetscl[isrc].push_back(sup);
	genjetindx[isrc].push_back(ijet);
      }
    }
    
       //cout << "Write test 3 = ok " << endl;
       //cout << "Write test 322 = ok "<<nGenReso << endl;
//////#ifdef JETRESO
    for (int isrc = 0; isrc < nGenReso; isrc++) {
      if(genjetptx[isrc].size()==0) break;
      for (unsigned int ij=0; ij<genjetptx[isrc].size()-1; ij++) {
	for (unsigned int jk=ij+1; jk<genjetptx[isrc].size(); jk++) {  
	  if (genjetptx[isrc][jk]>genjetptx[isrc][ij]){ 
	    double tmppt = genjetptx[isrc][ij];
	    double tmpscl = genjetscl[isrc][ij];
	    int tmpindx = genjetindx[isrc][ij];
	    
	    genjetptx[isrc][ij] = genjetptx[isrc][jk];
	    genjetscl[isrc][ij] = genjetscl[isrc][jk];
	    genjetindx[isrc][ij] = genjetindx[isrc][jk];					
	    
	    genjetptx[isrc][jk] = tmppt;
	    genjetscl[isrc][jk] = tmpscl;
	    genjetindx[isrc][jk] = tmpindx;
	  }
	}
      }
    }
    //////#endif
    //cout << "Write test 4 = ok " << endl;
    //double avegenptres[nGenReso]={0};
    
    //cout<<"Check 3 : Lead GetJet pt : "<<leadgenpt<<endl;
    //cout<<"Check 3 : Sub-Lead GetJet pt : "<<(*genjets)[1].pt()<<endl;

    for (int isrc = 0; isrc < nGenReso; isrc++) {
      if (genjetptx[isrc].size()>=2) {
        leadgenptres[isrc] = (genjetptx[isrc][0]);
        igenhtres[isrc] = getbinid(leadgenptres[isrc], njetptmn, leadingPtThreshold);
      } else {
	igenhtres[isrc] = -1;
      }
    }
    
   //cout<<"Check 4 : Lead GetJet pt : "<<leadgenpt<<endl;
   //cout<<"Check 4 : Lead GetJet pt after correction (*genjets)[genjetindx[0][0]] : "<<(*genjets)[genjetindx[0][0]].pt()<< " igenhtres[0] : "<<igenhtres[0]<<endl;
   //cout<<"Check 4 : Lead GetJet pt after correction leadgenptres[0] : "<<leadgenptres[0]<<endl;
 
    if(genjets.isValid() && genjets->size() >=2) { //  && avegenpt>leadingPtThreshold[0]) {
    
     for (int iet=0; iet<njetetamn; iet++) {
	for (int isrc=0; isrc<nGenReso; isrc++) { 
          if (leadgenptres[isrc] > leadingPtThreshold[0]) {
	  //cout<<"Check 5 : Lead GetJet pt after correction in the jet loop leadgenptres[0] : "<<leadgenptres[0]<<endl;
          //cout<<"Check 5 : Lead GetJet pt after correction in the jet loop (*genjets)[genjetindx[0][0]].pt() : "<<(*genjets)[genjetindx[0][0]].pt()<<endl;
	    //double px =0;
	    //double py =0;
	    //double ptxy =0;
	    
	    ncount=0;
	    //int recterm=0;
	    //int ithird=-1;
	    tmpgen4v.clear(); 
	    for(unsigned ijet = 0; ijet != genjets->size(); ijet++) {
		if (abs((*genjets)[genjetindx[isrc][0]].eta())<etarange[iet] && abs((*genjets)[genjetindx[isrc][1]].eta())<etarange[iet]) {
	     /* if ((*genjets)[igenjt].pt()>25.0) {
		cout<<"ievt "<<ievt<<" "<<ijet<<" "<<igenjt<<" "<<genjetptx[isrc][ijet]<<" "<<(*genjets)[igenjt].pt()<<" "<<(*genjets)[igenjt].eta()<<" "<<(*genjets)[igenjt].phi()<<endl;
	      }*/

	        //if (abs((*genjets)[genjetindx[isrc][ijet]].eta())<etarange[iet]) {
		//if (deltaR(((*genjets)[genjetindx[isrc][0]]),((*genjets)[genjetindx[isrc][ijet]]))<1.6) continue;
		//cout << (deltaR(((*genjets)[genjetindx[isrc][0]]),((*genjets)[genjetindx[isrc][ijet]])))<<e
		if (dPhi(((*genjets)[genjetindx[isrc][0]].phi()), ((*genjets)[genjetindx[isrc][1]].phi()))<2.0) continue;
                if (dPT(((*genjets)[genjetindx[isrc][0]].pt()), ((*genjets)[genjetindx[isrc][1]].pt()))>0.3) continue; 
		//if ((((*genjets)[genjetindx[isrc][0]].pt()) / ((*genjets)[genjetindx[isrc][1]].pt()))>1.5) continue;
		//cout<<"Check 6 : Lead GetJet pt after correction in the second jet loop (*genjets)[genjetindx[0][0]].pt() : "<<(*genjets)[genjetindx[0][0]].pt()<<endl;
		int igenjt = genjetindx[isrc][ijet];
	
		double pt = genjetptx[isrc][ijet];
		double sup = genjetscl[isrc][ijet];
		double abseta = abs((*genjets)[igenjt].eta());
		if (pt<30.0 || abseta >etarange[iet]) continue;
		bool isEta = (abseta<2.1) ? true : false;
		
		//if (iet==0 && isrc==0) 
		//cout <<"MC:pteta "<<ijet<<" "<<pt<<" "<<abseta<<endl;
		if (abseta>5.0) continue;
		bool isPt = (pt>30.0) ? true : false;
		if (isEta && isPt) {ncount++;}	
		
		HepLorentzVector tmp4v((*genjets)[igenjt].px(), (*genjets)[igenjt].py(), (*genjets)[igenjt].pz(), (*genjets)[igenjt].energy()); tmp4v *=sup;
		Hep3Vector tmp3v((*genjets)[igenjt].px(), (*genjets)[igenjt].py(), (*genjets)[igenjt].pz()); tmp3v *=sup;
	        //if(ijet==0 && isrc==0){cout<<"Check 7 : Lead GetJet pt after using HepLorentzVector : "<<tmp4v.perp()<<endl;}
	
		if (isEta && isPt) { tmpgen4v.push_back(tmp4v);} 
	
		  if (isEta && isPt) {genmom[isrc][0][iet].push_back(tmp4v);}

		  if (isrc==0) { 
		    if (isInEtaRange[iet]) {genjt_pt[iet]->Fill(tmp4v.perp(), weighttrg);}
		    if (isPt && iet==0) {genjt_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isEta && isPt) {genjt_phi->Fill(tmp4v.phi(), weighttrg);}  
		  }
		
		if (isrc==0) { 
		  if(ijet==0) {
		    //cout<<"Gen Pt= " << avegenpt <<endl;
		    if (isInEtaRange[iet]) {genjt1_pt[iet]->Fill(tmp4v.perp(), weighttrg);} //genrecojet1_pt = tmp4v.perp();}
		    if (isPt && iet==0) {genjt1_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isEta && isPt) {genjt1_phi->Fill(tmp4v.phi(), weighttrg);}
			//cout<<"Check 8 : Lead GetJet pt : "<<tmp4v.perp()<<endl;
		  } else if(ijet==1){
		    //cout<<"okkkkkkkk" <<endl;
		    if (isInEtaRange[iet]) {genjt2_pt[iet]->Fill(tmp4v.perp(), weighttrg);} //genrecojet2_pt = tmp4v.perp();}
		    if (isPt && iet==0) {genjt2_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isInEtaRange[iet] && isPt) {genjt2_phi->Fill(tmp4v.phi(), weighttrg);}
		    if (isInEtaRange[iet] && ncount==2) {
		      //cout<<"Gen Pt 1= " << avegenpt <<endl;
		      genjtallave_pt[iet]->Fill(avegenpt, weighttrg);
		    }
		  } else if(ijet==2) {
		    if (isInEtaRange[iet]) {genjt3_pt[iet]->Fill(tmp4v.perp(), weighttrg);}
		    if (isPt && iet==0 ) {genjt3_eta->Fill(tmp4v.eta(), weighttrg);}
		    if (isInEtaRange[iet] && isPt) {genjt3_phi->Fill(tmp4v.phi(), weighttrg);}
		  }
		  if (tmpgen4v.size()==2 && isInEtaRange[iet]) {
		    double dphi = dPhi(tmpgen4v[0].phi(), tmpgen4v[1].phi());
		    double dpt = tmpgen4v[0].perp() - tmpgen4v[1].perp();
		    double dperp = fabs(tmpgen4v[1].perp()*sin(dphi))/tmpgen4v[0].perp();
		    
		    genjetdphi[iet]->Fill(dphi, weighttrg);
		    genjetdpt[iet]->Fill(dpt, weighttrg);
		    genjetptbypl[iet]->Fill(dperp, weight);
		    genjetpt2bypt1[iet]->Fill(tmpgen4v[1].perp()/tmpgen4v[0].perp(), weight);
		  }
		  
		  if (tmpgen4v.size()==3) {genjetpt3bypt2[iet]->Fill(tmpgen4v[2].perp()/tmpgen4v[1].perp(), weight);}
		}
#ifdef GENPART
		
		std::vector <const GenParticle*> daus ((*genjets)[igenjt].getGenConstituents ());
		std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });  //need to check 
		for (unsigned int i2 =0; i2< daus.size(); ++i2) {
		  const GenParticle* pfcand = daus[i2];
		  int charge = pfcand->charge();
		  HepLorentzVector cand4v(pfcand->px(), pfcand->py(), pfcand->pz(), pfcand->energy());
		  //int pdgid = pfcand->pdgId();
		 //std::cout<<"GENPART loop"<<endl; 
#else		
		
		  std::vector<reco::CandidatePtr> daus((*genjets)[igenjt].daughterPtrVector());
		  std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });                               
		  for (unsigned int i2 = 0; i2< daus.size(); ++i2) {
		    const pat::PackedCandidate &pfcand = static_cast<const pat::PackedCandidate &>(*daus[i2]);
		    int charge = pfcand.charge();
		    //std::cout<<"ALL loop"<<endl;
		    HepLorentzVector cand4v(pfcand.px(), pfcand.py(), pfcand.pz(), pfcand.energy());
#endif
		    //	    if (cand4v.perp()<0.5) continue;
		    
		    //if (ncount<=2 && isEta && isPt) {
		      //genmom[isrc][1][iet].push_back(cand4v);
		      if (charge !=0) {
			genmom[isrc][1][iet].push_back(cand4v);
#ifdef TRACKSYS
			if (gRandom->Uniform() < 0.96) {genmom[isrc][2][iet].push_back(cand4v); }
#endif
	}
	if (isrc==0) { 
               	if (charge !=0) {
			genchg_phi->Fill(cand4v.phi(), weighttrg);
			genchg_pt->Fill(cand4v.perp(), weighttrg);
			genchg_eta->Fill(cand4v.eta(), weighttrg);
		  	}
		if (ijet==0 && charge !=0) {
			genchg1_phi->Fill(cand4v.phi(), weighttrg);
                        genchg1_pt->Fill(cand4v.perp(), weighttrg);
                        genchg1_eta->Fill(cand4v.eta(), weighttrg);
			}
		else if (ijet==1 && charge !=0) {
			genchg2_phi->Fill(cand4v.phi(), weighttrg);
                        genchg2_pt->Fill(cand4v.perp(), weighttrg);
                        genchg2_eta->Fill(cand4v.eta(), weighttrg);
			}
		else if (ijet==2 && charge !=0) {
                        genchg3_phi->Fill(cand4v.phi(), weighttrg);
                        genchg3_pt->Fill(cand4v.perp(), weighttrg);
                        genchg3_eta->Fill(cand4v.eta(), weighttrg);
                        }
		}//if (isrc==0)
		} //for (unsigned int i2 = 0; i2< daus.size(); ++i2)
		if (ijet==0){
			for (int ik=0; ik<10; ik++){
			std::vector<reco::CandidatePtr> daus((*genjets)[igenjt].daughterPtrVector());
                        std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });
                        for (unsigned int i2 = 0; i2< daus.size(); ++i2) {
                        const pat::PackedCandidate &pfcand = static_cast<const pat::PackedCandidate &>(*daus[i2]);
                        int charge = pfcand.charge();
			Hep3Vector cand3v(pfcand.px(), pfcand.py(), pfcand.pz());
			if(cand3v.perp()>1.0 && abs(cand3v.eta()<2.5)){
                	if(isrc==0){
                        	genrecojet1_pt = tmp3v.perp();
				
				igenjet1candsmom[ik] += charge*(pow(cand3v.perp(), kappa[ik]));

				igenjet1_long_num[ik] += (charge*(dotProductPower(cand3v,tmp3v,kappa[ik])));
	                        igenjet1_long_den[ik] += (dotProductPower(cand3v,tmp3v,kappa[ik]));

        	                igenjet1_tran_num[ik] += (charge*(crossProductPower(cand3v,tmp3v,kappa[ik])));
                	        igenjet1_tran_den[ik] += (crossProductPower(cand3v,tmp3v,kappa[ik]));

				//cout<<" Gen particle check 1 : "<<" pt : "<<pfcand.pt()<<" eta : "<<pfcand.eta()<<" id : "<<pfcand.pdgId()<<endl;
	                        //cout<<" Gen particle from HepLorentzVector check 1 : "<<" pt : "<<pfcand.pt()<<" eta : "<<pfcand.eta()<<" id : "<<pfcand.pdgId()<<endl;
                    				}
					}
				}
			}
		}
		//cout<<"Check 9 : Lead GetJet pt : "<<genrecojet1_pt<<endl;
		if (ijet==1){
                        for (int ik=0; ik<10; ik++){
                        std::vector<reco::CandidatePtr> daus((*genjets)[igenjt].daughterPtrVector());
                        std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });
                        for (unsigned int i2 = 0; i2< daus.size(); ++i2) {
                        const pat::PackedCandidate &pfcand = static_cast<const pat::PackedCandidate &>(*daus[i2]);
                        int charge = pfcand.charge();
                        Hep3Vector cand3v(pfcand.px(), pfcand.py(), pfcand.pz());
                        if(cand3v.perp()>1.0 && abs(cand3v.eta()<2.5)){
                        if(isrc==0){
				genrecojet2_pt = tmp3v.perp();
	
				igenjet2candsmom[ik] += candsmom(charge, cand3v.perp(), kappa[ik]);

				igenjet2_long_num[ik] += (charge*(dotProductPower(cand3v,tmp3v,kappa[ik])));
                                igenjet2_long_den[ik] += (dotProductPower(cand3v,tmp3v,kappa[ik]));

                                igenjet2_tran_num[ik] += (charge*(crossProductPower(cand3v,tmp3v,kappa[ik])));
                                igenjet2_tran_den[ik] += (crossProductPower(cand3v,tmp3v,kappa[ik]));
						}
					}
				}
			}
		}
		  //  if (isEta && isPt) {ncount++;}
		} // if (abs((*genjets)[genjetindx[isrc][0]].eta())<etarange[iet] && 
		//								abs((*genjets)[genjetindx[isrc][1]].eta())<etarange[iet])
	      } //	for(unsigned ijet = 0; ijet != genjets->size(); ijet++) 
	      //cout << "Write test 324 = ok " << endl;
	     /* if (ithird>=0) {
		//							cout <<"ithird "<<isrc<<" "<< iet<<" "<< ithird<<endl;
		
		HepLorentzVector tmp4v((*genjets)[ithird].px(), (*genjets)[ithird].py(), (*genjets)[ithird].pz(), (*genjets)[ithird].energy());
		genmom[isrc][0][iet].push_back(tmp4v);
		//cout <<"thirdijxxx "<<isrc<<" "<<iet<<" "<< genmom[isrc][0][iet].size()<<" "<<genjets->size()<<" "<<ithird<<" "<<tmp4v.perp()<<" "<<tmp4v.eta()<<" "<<tmp4v.phi()<<" "<<setprecision(14)<<weighttrg<<endl;
#ifdef GENPART
		std::vector <const GenParticle*> daus ((*genjets)[ithird].getGenConstituents ());
		//								std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); }); 
		
		for (unsigned int i2 =0; i2< daus.size(); ++i2) {
		  const GenParticle* pfcand = daus[i2];
		  int charge = pfcand->charge();
		  HepLorentzVector cand4v(pfcand->px(), pfcand->py(), pfcand->pz(), pfcand->energy());
		  //								int pdgid = pfcand->pdgId();
		  
#else
		  std::vector<reco::CandidatePtr> daus((*genjets)[ithird].daughterPtrVector());
		  std::sort(daus.begin(),daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });    
		  
		  for (unsigned int i2 = 0; i2< daus.size(); ++i2) {
		    const pat::PackedCandidate &pfcand = static_cast<const pat::PackedCandidate &>(*daus[i2]);
		    
		    int charge = pfcand.charge();
		    HepLorentzVector cand4v(pfcand.px(), pfcand.py(), pfcand.pz(), pfcand.energy());
#endif
		    
		    
		    //      if (cand4v.perp()<0.5) continue;                                                                                                                     
		    genmom[isrc][1][iet].push_back(cand4v);
		    if (charge !=0) {
		      genmom[isrc][2][iet].push_back(cand4v);
#ifdef TRACKSYS
		      if (gRandom->Uniform() < 0.96) {genmom[isrc][4][iet].push_back(cand4v); }
#endif
		    }
		    
		    if(charge ==0) {
		      if (cand4v.perp()>1.0) {
			genmom[isrc][3][iet].push_back(cand4v);
		      }
		    } else {
		      if (cand4v.perp()>0.5) {
			genmom[isrc][3][iet].push_back(cand4v);
		      }
		    }
		  } //for (unsigned int i2 = 0; i2< daus.size(); ++i2) 
		}*/// if (ithird>=0)
		gen_njets[iet]->Fill(ncount,weighttrg); 
	      } // if (avegenptres[isrc] > leadingPtThreshold[0])
	    } //	for (int isrc=0; isrc<nGenReso; isrc++)
	  } //for (int iet=0; iet<njetetamn; iet++)
	} // if(genjets.isValid() && genjets->size()>=2 && (*genjets)[0].pt()>leadingPtThreshold[0])
	// } //if (genjets.isValid() &&  genjets->size()>=2) 
	h_2ht->Fill(aveleadingpt,avegenpt, weighttrg);
	///////Response
      } //isMC
      //	cout<<"22 aveleadingpt "<<aveleadingpt<< " ; "<<ihltfill<<" "<<irecoht<<endl;
      // if(isMC) h_2ht->Fill(aveleadingpt,avegenpt, weighttrg);
      //cout << "Write test 325 = ok " << endl;
      //for(int rnum=0; rnum<10; rnum++) {
      /*double rand=gRandom->Uniform();
      int k = rand/0.1;
      //cout << "Rand Number " << k << endl;*/
 
//-----------------------------------------------Calculate And Fill Jet Charge Obserables------------------------------------
	//Profile histograms
	//hprof->Fill(recojet0_pt,ijet0_candsmom_10/(pow(recojet0_pt,1.0)),weighttrg);
	hchpt->Fill(recojet1_pt,nchg,weighttrg);

	for (int ik=0; ik<nkappa; ik++){	
		RecoJCO[0][0][ik] = (ijet1candsmom[ik]/(pow(recojet1_pt,kappa[ik])));
		RecoJCO[0][1][ik] = (ijet2candsmom[ik]/(pow(recojet2_pt,kappa[ik])));

		RecoJCO[1][0][ik] = (ijet1_long_num[ik]/ijet1_long_den[ik]);
		RecoJCO[1][1][ik] = (ijet2_long_num[ik]/ijet2_long_den[ik]);

		RecoJCO[2][0][ik] = (ijet1_tran_num[ik]/ijet1_tran_den[ik]);
		RecoJCO[2][1][ik] = (ijet2_tran_num[ik]/ijet2_tran_den[ik]);

		GenJCO[0][0][ik] = (igenjet1candsmom[ik]/(pow(genrecojet1_pt,kappa[ik])));
		GenJCO[0][1][ik] = (igenjet2candsmom[ik]/(pow(genrecojet2_pt,kappa[ik])));

		GenJCO[1][0][ik] = (igenjet1_long_num[ik]/igenjet1_long_den[ik]);
		GenJCO[1][1][ik] = (igenjet2_long_num[ik]/igenjet2_long_den[ik]);

		GenJCO[2][0][ik] = (igenjet1_tran_num[ik]/igenjet1_tran_den[ik]);
		GenJCO[2][1][ik] = (igenjet2_tran_num[ik]/igenjet2_tran_den[ik]);
/*
		RecoJCO[0][0][ik] = ((pow(recojet1_pt,kappa[ik]))>0) ? (ijet1candsmom[ik]/(pow(recojet1_pt,kappa[ik]))) : 0 ;
		RecoJCO[0][1][ik] = ((pow(recojet2_pt,kappa[ik])>0)) ? (ijet2candsmom[ik]/(pow(recojet2_pt,kappa[ik]))) : 0 ;

		RecoJCO[1][0][ik] = (ijet1_long_den[ik]>0) ? (ijet1_long_num[ik]/ijet1_long_den[ik]) : 0 ;
		RecoJCO[1][1][ik] = (ijet2_long_den[ik]>0) ? (ijet2_long_num[ik]/ijet2_long_den[ik]) : 0 ;

		RecoJCO[2][0][ik] = (ijet1_tran_den[ik]>0) ? (ijet1_tran_num[ik]/ijet1_tran_den[ik]) : 0 ;
		RecoJCO[2][1][ik] = (ijet2_tran_den[ik]>0) ? (ijet2_tran_num[ik]/ijet2_tran_den[ik]) : 0 ;

		GenJCO[0][0][ik] = ((pow(genrecojet1_pt,kappa[ik]))>0) ? (igenjet1candsmom[ik]/(pow(genrecojet1_pt,kappa[ik]))) : 0 ;
		GenJCO[0][1][ik] = ((pow(genrecojet2_pt,kappa[ik]))>0) ? (igenjet2candsmom[ik]/(pow(genrecojet2_pt,kappa[ik]))) : 0 ;
		
		GenJCO[1][0][ik] = (igenjet1_long_den[ik]>0) ? (igenjet1_long_num[ik]/igenjet1_long_den[ik]) : 0 ;
		GenJCO[1][1][ik] = (igenjet2_long_den[ik]>0) ? (igenjet2_long_num[ik]/igenjet2_long_den[ik]) : 0 ;
		
		GenJCO[2][0][ik] = (igenjet1_tran_den[ik]>0) ? (igenjet1_tran_num[ik]/igenjet1_tran_den[ik]) : 0 ;
		GenJCO[2][1][ik] = (igenjet2_tran_den[ik]>0) ? (igenjet2_tran_num[ik]/igenjet2_tran_den[ik]) : 0 ;
*/	
		recomomJCO[0][0][ik] = (pow(recojet1_pt,kappa[ik]));
		recomomJCO[0][1][ik] = (pow(recojet2_pt,kappa[ik]));

		recomomJCO[1][0][ik] = (ijet1_long_den[ik]);
                recomomJCO[1][1][ik] = (ijet2_long_den[ik]);

		recomomJCO[2][0][ik] = (ijet1_tran_den[ik]);
                recomomJCO[2][1][ik] = (ijet2_tran_den[ik]);

		genmomJCO[0][0][ik] = (pow(genrecojet1_pt,kappa[ik]));
		genmomJCO[0][1][ik] = (pow(genrecojet2_pt,kappa[ik]));

		genmomJCO[1][0][ik] = (igenjet1_long_den[ik]);
                genmomJCO[1][1][ik] = (igenjet2_long_den[ik]);

		genmomJCO[2][0][ik] = (igenjet1_tran_den[ik]);
                genmomJCO[2][1][ik] = (igenjet2_tran_den[ik]);
		//cout<<"Final Check 1 : Lead Jet pt : "<<recojet1_pt<<endl;
		//cout<<"Final Check 1 : Lead GenJet pt : "<<genrecojet1_pt<<endl;
		}

bool matched_jet=false;
//double R =0.0;
for(unsigned ijet = 0; ijet != ak4PFJets->size(); ijet++) {
for(unsigned igjet = 0; igjet != genjets->size(); igjet++){
  	double dR = deltaR((*genjets)[igjet], (*ak4PFJets)[ijet]);
	//cout <<"dR "<<dR<<endl;
	if (dR < 0.2){matched_jet=true;} 
		//cout<<"test "<<dR<<endl;
		//R = dR;
			}
		}
	
//if(!matched_jet) return;

/*
for (int iet=0; iet<njetetamn; iet++){
	if(isMC){
        	for (int isrc=0; isrc<nGenReso; isrc++) {
			if (isrc==0 && isReconstruct){
                        	if( irecohtjec[isrc]==igenhtres[isrc] && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && recojet1_pt>0 && genrecojet1_pt>0 && matched_jet){
					if(ak4PFJets->size()>=2 && genjets->size()>=2){
                                                        RM_test[irecohtjec[isrc]][iet]->Fill(recojet1/pow(recojet1_pt,0.6),genjet1/pow(genrecojet1_pt,0.6),weighttrg);
							}
						}
					}
				}
			}				
		}
*/
for (int iet=0; iet<njetetamn; iet++){
        if(isMC){
                for (int isrc=0; isrc<nGenReso; isrc++) {
                        if (isrc==0 && isReconstruct){
                                //if( irecohtjec[isrc]==igenhtres[isrc] && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && matched_jet){
				if( igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && matched_jet){
                                        if(ak4PFJets->size()>=2 && genjets->size()>=2){
                                                        //RM_test[irecohtjec[isrc]][iet]->Fill(recojet1_pt,genrecojet1_pt,weighttrg);
							RM_test[iet]->Fill(recojet1_pt,genrecojet1_pt,weighttrg);
                                                        }
                                                }
                                        }
                                }
                        }
                }

bool isRecoJCO=false;
for (int iet=0; iet<njetetamn; iet++){
for(int id=0; id<ndef; id++){
for(int ij=0; ij<njet; ij++){
for(int ik=0; ik<nkappa; ik++){
                        if (isReconstruct) {
                                for (int isrc=0; isrc<njecmx; isrc++) {
					if (irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && recomomJCO[id][ij][ik]>0){
                                                if (isrc==0) {
							isRecoJCO=true;
							if(ak4PFJets->size()>=2){
							h_recovar[irecohtjec[isrc]][iet][id][ij][ik]->Fill(RecoJCO[id][ij][ik],weighttrg);
							int irecbin = RecoBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(RecoJCO[id][ij][ik],leadingptjec[isrc]);
							h_recovar2D[iet][id][ij][ik]->Fill(irecbin, weighttrg);
							//cout<<"Final Check 2 : Lead Jet pt : "<<recojet1_pt<<endl;
								}
							}
						}
					}
				}//if (isReconstruct) {
			if(isMC){
				 for (int isrc=0; isrc<nGenReso; isrc++) {
					bool isGenJCO=false;
					if (isMC && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && genmomJCO[id][ij][ik]>0){
						if(isrc==0){
							isGenJCO=true;
							if(genjets->size()>=2){
							h_genvar[igenhtres[isrc]][iet][id][ij][ik]->Fill(GenJCO[id][ij][ik],weighttrg);
							int igenbin = GenBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(GenJCO[id][ij][ik],leadgenptres[isrc]);
                                                        h_genvar2D[iet][id][ij][ik]->Fill(igenbin, weighttrg);
							//cout<<"Final Check 2 : Lead GenJet pt : "<<genrecojet1_pt<<endl;
								}
							}
						}
					if (isrc==0 && isReconstruct){
						if( isRecoJCO && isGenJCO && irecohtjec[isrc]==igenhtres[isrc] && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && recomomJCO[id][ij][ik]>0 && genmomJCO[id][ij][ik]>0 && matched_jet){
						//if( isRecoJCO && isGenJCO && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && recomomJCO[id][ij][ik]>0 && genmomJCO[id][ij][ik]>0 && matched_jet){
						if(ak4PFJets->size()>=2 && genjets->size()>=2){
							//RM_test[irecohtjec[isrc]][iet][id][ij][ik]->Fill(recojet1,genjet1,weighttrg);
							h_RM[irecohtjec[isrc]][iet][id][ij][ik]->Fill(RecoJCO[id][ij][ik],GenJCO[id][ij][ik],weighttrg);
							int irecbin = RecoBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(RecoJCO[id][ij][ik],leadingptjec[isrc]);
							int igenbin = GenBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(GenJCO[id][ij][ik],leadgenptres[isrc]);
							h_RM2D[iet][id][ij][ik]->Fill(irecbin,igenbin,weighttrg);	
							//cout<<"Final Check 3 : Lead Jet pt : "<<recojet1_pt<<endl;
							//cout<<"Final Check 3 : Lead GenJet pt : "<<genrecojet1_pt<<endl;
							}
						else if(ak4PFJets->size()>=2){
							h_recofake[irecohtjec[isrc]][iet][id][ij][ik]->Fill(RecoJCO[id][ij][ik],weighttrg);
                                                        int irecbin = RecoBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(RecoJCO[id][ij][ik],leadingptjec[isrc]);
                                                        h_recofake2D[iet][id][ij][ik]->Fill(irecbin, weighttrg);
							}
						else if(genjets->size()>=2){
							h_genmiss[igenhtres[isrc]][iet][id][ij][ik]->Fill(GenJCO[id][ij][ik],weighttrg);
                                                        int igenbin = GenBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(GenJCO[id][ij][ik],leadgenptres[isrc]);
                                                        h_genmiss2D[iet][id][ij][ik]->Fill(igenbin, weighttrg);
							}
						}
						else{
							if( isRecoJCO && irecohtjec[isrc]>=0 && irecohtjec[isrc]<njetptmn && recomomJCO[id][ij][ik]>0 && ak4PFJets->size()>=2){
								h_recofake[irecohtjec[isrc]][iet][id][ij][ik]->Fill(RecoJCO[id][ij][ik],weighttrg);
								int irecbin = RecoBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(RecoJCO[id][ij][ik],leadingptjec[isrc]);
                                                        	h_recofake2D[iet][id][ij][ik]->Fill(irecbin, weighttrg);
								//cout <<"RecoFake JCO : "<< RecoJCO[id][ij][ik]<< "  id : "<<id<< "  ij : "<<ij<<"  ik : "<<ik<<endl;
								}
							if(isGenJCO && igenhtres[isrc]>=0 && igenhtres[isrc]<njetptmn && genmomJCO[id][ij][ik]>0 && genjets->size()>=2){
								h_genmiss[igenhtres[isrc]][iet][id][ij][ik]->Fill(GenJCO[id][ij][ik],weighttrg);
								int igenbin = GenBinning2D[iet][id][ij][ik]->GetGlobalBinNumber(GenJCO[id][ij][ik],leadgenptres[isrc]);
	                                                        h_genmiss2D[iet][id][ij][ik]->Fill(igenbin, weighttrg);
								//cout <<"GenMiss JCO : "<< GenJCO[id][ij][ik]<< "  id : "<<id<< "  ij : "<<ij<<"  ik : "<<ik<<endl;
								}												
							}//else{
						}//if (isrc==0 && isReconstruct){
					}//for (int isrc=0; isrc<nGenReso; isrc++) {
				}//if(isMC){
			}//for (int ik=0; ik<nkappa; ik++){
		}//for(int ij=0; ij<njet; ij++){
	}//for(int id=0; id<ndef; id++){
}//for (int iet=0; iet<njetetamn; iet++){
//cout <<"-------------"<<endl;
      
	//if (nevt%1000==1) { std::cout <<"nevt "<<nevt<<" naa "<<naa<<" nbb "<<nbb<<" ncc "<<ncc<< std::endl;}
      	//if (nevt%1000==1) { std::cout <<"Reco "<< Reco << " Gen " <<Gen<< " RM " <<RM <<std::endl;}
      	//if(nevt==100){cout <<igenht <<endl;}
      	}//cout <<"END EVENT"<< endl;

// ------------ method called once each job just before starting event loop  ------------
void 
QCDEventShape::beginJob() {
//t1=clock();
  nevt = 0;
  if (isMC) { 
    double dattot[nHLTmx]={0};
    double mctot=0;
    for (int ij=0; ij<npileupmx; ij++) {
      for (int jk=0; jk<nHLTmx; jk++) {dattot[jk] +=datpileup[jk][ij];}
         mctot +=mcpileup[ij];
	}
    
      for (int ij=0; ij<npileupmx; ij++) {
        mcpileup[ij] /=max(1.e-6,mctot);
      	   for (int jk=0; jk<nHLTmx; jk++) {
		datpileup[jk][ij] /=max(1.e-6,dattot[jk]);
		rat_pileup[jk][ij] =  datpileup[jk][ij]/mcpileup[ij];
      		}
    	}
  }

#ifdef JETENERGY
  for (int isrc = 0; isrc < nsrc; isrc++) {
    const char *name = srcnames[isrc];
    //JetCorrectorParameters *p = new JetCorrectorParameters("Summer19UL17_RunF_V5_DATA_UncertaintySources_AK4PFchs.txt", name);  // data chnage eras for different era
    JetCorrectorParameters *p = new JetCorrectorParameters("Summer19UL17_V5_MC_UncertaintySources_AK4PFchs.txt", name);   // for mc
    JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
    //vsrc[isrc] = unc;vsrc.push_back(unc);
    vsrc.push_back(unc);
    }
#endif  

//cout << "Write test 34 = ok " << endl;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
QCDEventShape::endJob() 
{

   TUnfoldBinng2D->cd(); 
  //TUnfoldBinning Jet Charge
	for (int iet=0; iet<njetetamn; iet++) {
		for(int id=0; id<ndef; id++){
			for(int ij=0; ij<njet; ij++){
				for(int ik=0; ik<nkappa; ik++){
					h_recovar2D[iet][id][ij][ik]->Write();
					h_genvar2D[iet][id][ij][ik]->Write();
					h_recofake2D[iet][id][ij][ik]->Write();
					h_genmiss2D[iet][id][ij][ik]->Write();
					h_RM2D[iet][id][ij][ik]->Write();
					}
				}
			}
		}
}

// ------------ method called when starting to processes a run  ------------

void 
QCDEventShape::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
// Initialize hltConfig

#ifdef TRIGGER

// cout << "Write test 4 = ok " << endl;
  bool changed(true);
  if (hltPrescaleProvider_.init(iRun,iSetup,theHLTTag.c_str(),changed)) {
  HLTConfigProvider const&  hltConfig = hltPrescaleProvider_.hltConfigProvider();
  hltConfig.dump("Triggers");
  hltConfig.dump("PrescaleTable");

    for (unsigned int ij=0; ij<nHLTmx; ij++) {
      l1pres[ij] = hltpres[ij]=-7;
      }
	} 
	else {
         	}

#endif
 
  std::cout<<" End of QCDEventShape::beginRun"<<std::endl; //"nevt "<<nevt<<" naa "<<naa<<" nbb "<<nbb<<" ncc "<<ncc<< std::endl;
}


// ------------ method called when ending the processing of a run  ------------
/*
void 
QCDEventShape::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
std::cout<<" End of QCDEventShape::beginRun"<<std::endl;
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
QCDEventShape::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{


}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
QCDEventShape::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
QCDEventShape::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  //Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

double PhiInRange(const double& phi) {
      double phiout = phi;
      
      if( phiout > 2*M_PI || phiout < -2*M_PI) {
	phiout = fmod( phiout, 2*M_PI);
      }
      if (phiout <= -M_PI) phiout += 2*M_PI;
      else if (phiout >  M_PI) phiout -= 2*M_PI;
      
      return phiout;
}

template <class T, class U>
double deltaR(const T& t, const U& u) {
return sqrt(pow(t.eta()-u.eta(),2) +pow(PhiInRange(t.phi()-u.phi()),2));
}

// Default jet charge observable NOT USED
double JetCharge1(int charge, double candspt, double jpt, double k) {
	double Q1 = 0.0;
	//double j1 = 0.0;
	Q1 +=1.0*( charge*(pow(candspt,k)));
	//j1 = Q1/pow(jpt,k);
	return Q1/pow(jpt,k);
	//return j1;
}

// For default definition Q
double candsmom(int charge, double candspt, double k){	
	double q = 0.0;
	q = ( charge*(pow(candspt,k)));
	return q;
}
/*
double candsmom2(double p, double k) {
    double result = pow(p, k);
    	if (p > 0 && !isnan(result) && !isinf(result)) {
    		return result;
    	          } else {continue;}
}
*/ 
// For longitudinal definition Q(L)
double dotproduct(double candspx, double candspy, double candspz, double jpx, double jpy, double jpz, double jpt, double k) {
	double dot = 0.0;
	//double dotresult =0.0;
	dot = (pow((((candspx*jpx) + (candspy*jpy) + (candspz*jpz))/jpt),k));
	//dotresult = (charge*(pow(dot,k)));
	return dot;
	//return dotresult;
}

// For transverse definition Q(T)
double crossproduct(double candspx, double candspy, double candspz, double jpx, double jpy, double jpz, double jpt, double k){
	double cross = 0.0;
	//double crossresult =0.0;
	cross = (pow(((sqrt((pow(((candspy*jpz) - (candspz*jpy)),2)) + (pow(((candspz*jpx) - (candspx*jpz)),2)) + (pow(((candspx*jpy) - (candspy*jpx)),2))))/jpt),k));
	//crossreult = (charge*(pow(cross,k)));
	return cross;
	//return crossresult;
}

double dotProductPower(const Hep3Vector& v1, const Hep3Vector& v2, double k) {
    double dotProduct = v1.dot(v2);
    double magV2 = v2.mag();
    double dotOverMag = dotProduct / magV2;
    double result = std::pow(dotOverMag, k);
    return result;
}

double crossProductPower(const Hep3Vector& v1, const Hep3Vector& v2, double k) {
    Hep3Vector crossProduct = v1.cross(v2);
    double magV2 = v2.mag();
    double crossOverMag = crossProduct.mag() / magV2;
    double result = std::pow(crossOverMag, k);
    return result;
}

//define this as a plug-in
DEFINE_FWK_MODULE(QCDEventShape);
