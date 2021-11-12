#include "WarBoats.h"
#include "Ocean.h"

namespace CS175
{
    namespace WarBoats
    {  
        Ocean::Ocean(int num_boats_, int x_quadrants_, int y_quadrants_)
            : x_quadrants(x_quadrants_), y_quadrants(y_quadrants_)
        {
            // Set Up Grid
            grid = new int* [x_quadrants];
            for (int i = 0; i < x_quadrants; i++)
            {
                grid[i] = new int[y_quadrants];

                // Initialize values
                for (int j = 0; j < y_quadrants; j++)
                    grid[i][j] = 0;
            }

            // Set Up Boats
            boats = new int[num_boats_];
            // Initialize values
            for (int i = 0; i < num_boats_; i++)
                boats[i] = 0;
        }

        Ocean::~Ocean(void)
        {
            // Delete Grid
            for (int i = 0; i < x_quadrants; i++)
                delete[] grid[i];
            delete[] grid;

            // Delete Boats Array
            delete[] boats;
        }

        BoatPlacement Ocean::PlaceBoat(void)
        {

        }

        const int **Ocean::GetGrid(void) const
        {
            return grid;
        }
  
        Point Ocean::GetDimensions(void) const
        {
            Point pt = {x_quadrants, y_quadrants};
            return pt;
        }

    } // namespace WarBoats

} // namespace CS175

