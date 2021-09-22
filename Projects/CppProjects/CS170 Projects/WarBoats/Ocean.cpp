#include "WarBoats.h"
#include "Ocean.h"
#include <iostream> // cout, endl
#include <iomanip>  // setw

namespace CS175
{
    namespace WarBoats
    {
        const int BOAT_LENGTH = 4;  // Length of a boat
        const int HIT_OFFSET = 100; // Add this to the boat ID


        // Creates the ocean struct and dynamically allocates the arrays
        // Params:
        //   num_boats = the number of boats that can be placed
        //   x_quadrants = the horizontal size of the ocean grid
        //   y_quadrants = the vertical size of the ocean grid
        // Return:
        //   a pointer to the created ocean struct
        Ocean* CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
        {
            Ocean* newOcean = new Ocean;

            // Set up grid
            newOcean->grid = new int* [x_quadrants];
            for (int i = 0; i < x_quadrants; i++)
            {
                newOcean->grid[i] = new int[y_quadrants];

                // Initialize values
                for (int j = 0; j < y_quadrants; j++)
                    newOcean->grid[i][j] = 0;
            }

            // Set up Boat array
            newOcean->boats = new Boat[num_boats];

            // Set up stats struct
            newOcean->stats.hits = 0;
            newOcean->stats.misses = 0;
            newOcean->stats.duplicates = 0;
            newOcean->stats.sunk = 0;

            // Assign extra variables
            newOcean->num_boats = num_boats;
            newOcean->x_quadrants = x_quadrants;
            newOcean->y_quadrants = y_quadrants;

            // Return ocean
            return newOcean;
        }

        // Frees the data of the ocean struct
        // Params:
        //   ocean = the ocean to be destroyed
        void DestroyOcean(Ocean* theOcean)
        {
            // Delete grid 2D array
            // Loop through and free the internal grid arrays
            for (int i = 0; i < theOcean->x_quadrants; i++)
                delete[] theOcean->grid[i];
            // Delete overhead array
            delete[] theOcean->grid;

            // Delete boats array
            delete[] theOcean->boats;

            // Delete the struct
            delete theOcean;
        }

        // Manages taking a shot at a boat
        // Params:
        //   ocean = the ocean in which the boat resides
        //   coordinate = the point at which the shot is taken
        // Return:
        //   a code that determines the succes of the shot
        ShotResult TakeShot(Ocean& ocean, const Point& coordinate)
        {
            if (coordinate.x != ocean.boats[0].position.x)
                return srILLEGAL;
            return srILLEGAL;
        }

        // Manages placing a boat
        // Params:
        //   ocean = the ocean in which the boat resides
        //   boat = the boat to be placed
        // Return:
        //   a code that determines the succes of the placement
        BoatPlacement PlaceBoat(Ocean& ocean, const Boat& boat)
        {
            // Check to make sure it isn't out of bounds
            if (boat.position.x > ocean.x_quadrants || boat.position.y > ocean.y_quadrants)
                return bpREJECTED;

            // Check if position is occupied, if so, reject placement
            for (int i = 0; i < BOAT_LENGTH; i++)
            {
                if (boat.orientation == oHORIZONTAL)
                {
                    if (ocean.grid[boat.position.x + i][boat.position.y] != 0)
                        return bpREJECTED;
                }
                else
                {
                    if (ocean.grid[boat.position.x][boat.position.y + i] != 0)
                        return bpREJECTED;
                }
            }

            // If we've gotten here, then the place is available to place the boat
            ocean.boats[boat.ID] = boat;
            // Place boat
            for (int i = 0; i < BOAT_LENGTH; i++)
            {
                if (boat.orientation == oHORIZONTAL)
                    ocean.grid[boat.position.x + i][boat.position.y] = boat.ID;
                else
                    ocean.grid[boat.position.x][boat.position.y + i] = boat.ID;
            }

            return bpACCEPTED;
        }

        // determines how many hits, misses, duplicates, and sunk spots there are
        // Params:
        //   ocean = the ocean to be checked
        // Return:
        //   a struct that contains the hits, misses, and duplicates on board
        ShotStats GetShotStats(const Ocean& ocean)
        {
            return ocean.stats;
        }
        
        
        // Prints the grid (ocean) to the screen.
        // Params:
        //   ocean = The Ocean to print
        //   field_width = How much space each position takes when printed.
        //   extraLine = If true, an extra line is printed after each row. If false, no extra line is printed.
        //   showboats = If true, the boats are shown in the output. (Debugging feature)
        void DumpOcean(const Ocean &ocean,
            int field_width,
            bool extraline,
            bool showboats)
        {
            // For each row
            for (int y = 0; y < ocean.y_quadrants; y++)
            {
                // For each column
                for (int x = 0; x < ocean.x_quadrants; x++)
                {
                    int value = ocean.grid[x][y];

                    // Is it a boat?
                    if ((value > 0) && (value < HIT_OFFSET) && 
                        (showboats == false))
                    {
                        value = 0;
                    }

                    std::cout << std::setw(field_width) << value;
                }
                std::cout << std::endl;
                if (extraline)
                {
                    std::cout << std::endl;
                }
            }
        }

    } // namespace WarBoats
} // namespace CS175
