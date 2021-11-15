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
                boats[i] = -1;

            stats.duplicates = 0;
            stats.hits = 0;
            stats.misses = 0;
            stats.sunk = 0;
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

        BoatPlacement Ocean::PlaceBoat(const Boat& boat)
        {
            if (boat.position.x > x_quadrants || boat.position.y > y_quadrants ||
                boat.position.x < 0 || boat.position.y < 0)
                return bpREJECTED;
            else if (boat.orientation == oHORIZONTAL && boat.position.x + BOAT_LENGTH > x_quadrants)
                return bpREJECTED;
            else if (boat.orientation == oVERTICAL && boat.position.y + BOAT_LENGTH > y_quadrants)
                return bpREJECTED;

            for (int i = 0; i < BOAT_LENGTH; i++)
            {
                if (boat.orientation == oHORIZONTAL)
                {
                    if (grid[boat.position.x + i][boat.position.y] != 0)
                        return bpREJECTED;
                }
                else
                {
                    if (grid[boat.position.x][boat.position.y + i] != 0)
                        return bpREJECTED;
                }
            }

            for (int i = 0; i < BOAT_LENGTH; i++)
            {
                if (boat.orientation == oHORIZONTAL)
                    grid[boat.position.x + i][boat.position.y] = boat.ID;
                else
                    grid[boat.position.x][boat.position.y + i] = boat.ID;
            }

            boats[boat.ID - 1] = 0;
            return bpACCEPTED;
        }


        ShotResult Ocean::TakeShot(const Point& coordinate_)
        {
            if (coordinate_.x > x_quadrants || coordinate_.y > y_quadrants ||
                coordinate_.x < 0 || coordinate_.y < 0)
                return srILLEGAL;

            int shotValue = grid[coordinate_.x][coordinate_.y];

            if (shotValue < 0 || shotValue > 100)
            {
                stats.duplicates++;
                return srDUPLICATE;
            }
            else if (shotValue == 0)
            {
                grid[coordinate_.x][coordinate_.y]--;
                stats.misses++;
                return srMISS;
            }
            else
            {
                boats[shotValue - 1]++;
                grid[coordinate_.x][coordinate_.y] += HIT_OFFSET;
                stats.hits++;

                // Check if the boat has been hit enough to be sunk
                if (boats[shotValue - 1] == BOAT_LENGTH)
                {
                    stats.sunk++;
                    return srSUNK;
                }
                else
                    return srHIT;
            }
        }

        const ShotStats& Ocean::GetShotStats(void) const
        {
            return stats;
        }

        const int **Ocean::GetGrid(void) const
        {
            return const_cast<const int**>(grid);
        }
  
        Point Ocean::GetDimensions(void) const
        {
            Point pt = {x_quadrants, y_quadrants};
            return pt;
        }

    } // namespace WarBoats

} // namespace CS175

