#pragma once

#include "WarBoats.h"

namespace CS175
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID

    class Ocean
    {
      public:
        
          Ocean(int num_boats_, int x_quadrants_, int y_quadrants_);
          ~Ocean(void);
          BoatPlacement PlaceBoat(void);
        
           // Provided
        const int **GetGrid(void) const;
        Point GetDimensions(void) const;

      private:
        int **grid;        // The 2D ocean
        int* boats;       // How many hits each boat has taken
        int x_quadrants;  // Ocean size along x-axis
        int y_quadrants;  // Ocean size along y-axis
        
        /*
         * Other private data
        */
        
    }; // class Ocean

  } // namespace WarBoats

} // namespace CS175
