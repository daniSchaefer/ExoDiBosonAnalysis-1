//======================= some random tools ==============================================
#ifndef SOMETOOLS_H
#define SOMETOOLS_H

#include "include/InputData.h"
#include <vector>
#include <TLorentzVector.h>
#include <map>


bool ComesFromGraviton(InputData& data, int index);
std::vector<int> FindDaughterIndex(std::vector<int>* pdgID, std::vector<std::vector<int> >* mothers,std::vector<int> daughtersV , int Vindex);
double CalculateCOSTheta1(InputData& data, bool genStudies);
void PrintLV(TLorentzVector V);
void PrintPdgIDs(InputData& t21);
double getGravitonGenMass(InputData& data);
TLorentzVector getGENLVParticle(InputData& data, int index);
bool isHadronicEvent(InputData& data);
#endif
