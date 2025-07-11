// RunAction.cc
#include "RunAction.hh"
#include "RadialEnergyDepositSD.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"

RunAction::RunAction() : fPrimaryEnergy(0.0) {}
RunAction::~RunAction() {}
void RunAction::BeginOfRunAction(const G4Run *)
{
    // 可在此处初始化
}

/*void RunAction::EndOfRunAction(const G4Run* run)
{
    /*G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SingleParticleSD* radialSD = dynamic_cast<SingleParticleSD*>(
        SDman->FindSensitiveDetector("SingleParticleSD"));

    if(radialSD) {
        // 按事件数归一化
        radialSD->NormalizePerEvent(run->GetNumberOfEvent());

        // 或者按初始粒子能量归一化
        /*if(fPrimaryEnergy > 0) {
            radialSD->NormalizePerPrimaryEnergy(fPrimaryEnergy);
        }

        // 保存结果
        radialSD->SaveToROOT("radial_edep_results.root");
    }

}*/

RunAction::RunAction(BoundarySD *sd) : fSD(sd)
{
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    // 获取敏感探测器实例
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    BoundarySD *sd = dynamic_cast<BoundarySD *>(
        sdManager->FindSensitiveDetector("BoundarySD"));

    if (sd)
    {
    }
}
