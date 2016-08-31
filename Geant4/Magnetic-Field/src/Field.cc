#include "Field.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include <fstream>

Field::Field():
G4ElectroMagneticField(){}

Field::~Field(){}

void Field::GetFieldValue(const G4double Point[4], G4double* Bfield) const
{
    if(Point[2] >= 107.*mm && Point[2] <= 307.*mm)
    {
        std::ofstream file("FIELD.dat", std::ios::app);
        file
        << std::setw(20) << Point[0] << " "
        << std::setw(20) << Point[1] << " "
        << std::setw(20) << Point[2] << " "
        << std::setw(20) << Point[3] << " "
        << std::endl;
        // Point[0],Point[1],Point[2] are x-, y-, z-cordinates, Point[3] is time
        Bfield[0] = 0;
        Bfield[1] = 0;
        Bfield[2] = (6/(1+55*(Point[2]-107.)/1000))*tesla;
    }
    else
    {
        Bfield[0] = 0;
        Bfield[1] = 0;
        Bfield[2] = 0;
    }
    return;
}
