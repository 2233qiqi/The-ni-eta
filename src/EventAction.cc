#include "EventAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "RadialEnergyDepositSD.hh"

void EventAction::BeginOfEventAction(const G4Event *) {}

void EventAction::EndOfEventAction(const G4Event *event)
{
    // 定期保存中间结果
    /*if (event->GetEventID() % 10000 == 0 && G4Threading::IsMasterThread())
    {
        G4SDManager *SDman = G4SDManager::GetSDMpointer();
        RadialEnergyDepositSD *radialSD = dynamic_cast<RadialEnergyDepositSD *>(
            SDman->FindSensitiveDetector("RadialEnergyDeposit"));

        if (radialSD)
        {
            G4String filename = "radial_edep_intermediate_" +
                                std::to_string(event->GetEventID()) + ".root";
            radialSD->SaveToROOT(filename);
        }
    }*/
}