#pragma once
namespace CS175
{
    namespace WarBoats
    {
        struct Ocean;  // Forward declaration

        enum Orientation { oHORIZONTAL, oVERTICAL };
        enum ShotResult { srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL };
        enum DamageType { dtOK = 0, dtBLOWNUP = -1 };
        enum BoatPlacement { bpACCEPTED, bpREJECTED };

        struct Point
        {
            int x;
            int y;
        };

        struct Boat
        {
            int hits;                 // Hits taken so far
            int ID;                   // Unique ID 
            Orientation orientation;  // Horizontal/Vertical
            Point position;           // x-y coordinate (left-top)
        };

        struct ShotStats
        {
            int hits;
            int misses;
            int duplicates;
            int sunk;
        };

        // The interface

        // Creates the ocean struct and dynamically allocates the arrays
        // Params:
        //   num_boats = the number of boats that can be placed
        //   x_quadrants = the horizontal size of the ocean grid
        //   y_quadrants = the vertical size of the ocean grid
        // Return:
        //   a pointer to the created ocean struct
        Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants);

        // Frees the data of the ocean struct
        // Params:
        //   theOcean = the ocean to be destroyed
        void DestroyOcean(Ocean *theOcean);

        // Manages taking a shot at a boat
        // Params:
        //   ocean = the ocean in which the boat resides
        //   coordinate = the point at which the shot is taken
        // Return:
        //   a code that determines the succes of the shot
        ShotResult TakeShot(Ocean &ocean, const Point &coordinate);

        // Manages placing a boat
        // Params:
        //   ocean = the ocean in which the boat resides
        //   boat = the boat to be placed
        // Return:
        //   a code that determines the succes of the placement
        BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat);

        // determines how many hits, misses, duplicates, and sunk spots there are
        // Params:
        //   ocean = the ocean to be checked
        // Return:
        //   a struct that contains the hits, misses, and duplicates on board
        ShotStats GetShotStats(const Ocean &ocean);

        // Provided
        void DumpOcean(const Ocean &ocean, 
                       int width = 4,
                       bool extraline = false,
                       bool showboats = true);

    } // namespace WarBoats

} // namespace CS175