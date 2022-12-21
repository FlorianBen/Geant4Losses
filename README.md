# Geant4Spallation

This repository contains a small Geant4 sample code that represents an extremely simple spallation neutron target.
## Geometry

The geometry is a simple box volume (3 m\*3 m\*3 m) world volume. The target is sphere, located in the middle of the world volume.

## Particle gun

The simulation uses G4ParticleGun object to launch particle on the target. The gun can be configured via the default messenger.

## Physics

The simulation uses the `QGSP_BERT_HP` preconfigured PhysicList. Custom PhysicList is an ongoing work.

## Sensitive detector, hit and analysis

The target itself is a Sensitive Detector. A TargetHit object is also available but not used at this point. The program uses the AnalysisManager with the ROOT interface. Currently, only the energy of neutrons that escape the target is recorded to a histogram.

## Usage 

Edit the script `run_spallation.mac` according to your study.
Then, run the simulation in batch mode `./Geant4Spallation run_spallation.mac`.

## Post-processing

TBD