cmake_minimum_required(VERSION 3.16)
project(Geant4Losses)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WITH_GEANT4_UIVIS "Build simulation with Geant4 UI and Vis drivers" ON)

if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

option(WITH_MPI_SUPPORT "Build simulation with MPI support" OFF)

if(WITH_MPI_SUPPORT)
  find_package(G4mpi REQUIRED)
  include_directories(${G4mpi_INCLUDE_DIR})
endif()

set(INC_FILES
  "include/NeutronAnalysis.hpp"
  "include/NeutronTargetSD.hpp"
  "include/NeutronDetectorConstruction.hpp"
  "include/NeutronActionInitialization.hpp"
  "include/NeutronRunAction.hpp"
  "include/NeutronEventAction.hpp"
  "include/NeutronTargetHit.hpp"
  "include/NeutronPrimaryGeneratorAction.hpp"
  "include/NeutronPhysicsList.hpp")

set(SRC_FILES
  "src/NeutronTargetSD.cpp"
  "src/NeutronDetectorConstruction.cpp"
  "src/NeutronActionInitialization.cpp"
  "src/NeutronEventAction.cpp"
  "src/NeutronRunAction.cpp"
  "src/NeutronTargetHit.cpp"
  "src/NeutronPrimaryGeneratorAction.cpp"
  "src/NeutronPhysicsList.cpp")

add_executable(Geant4Losses main.cpp ${INC_FILES} ${SRC_FILES})

if(WITH_MPI_SUPPORT)
  target_link_libraries(Geant4Losses ${G4mpi_LIBRARIES} ${Geant4_LIBRARIES})
  target_compile_definitions(Geant4Losses PUBLIC -DG4MPI)
else()
  target_link_libraries(Geant4Losses ${Geant4_LIBRARIES})
endif()

target_include_directories(
  Geant4Losses
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/init_vis.mac
  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/init_gps.mac
  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/icons.mac
  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vis.mac ${CMAKE_CURRENT_BINARY_DIR}
  COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_losses.mac ${CMAKE_CURRENT_BINARY_DIR}
  COPYONLY)
