/* Copyright (C) 2020 Dylan Evans - All Rights Reserved
 * You may use, distribute, or modify this code under the terms of the MIT license
 * You should have received a copy of the license with this file. If not, you may visit https://opensource.org/licenses/MIT
*/

#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

class IOException : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "One or more necessary files could not be opened. Make sure the following files are in the directory of the program: \n"
               "cube_moves_face_turns.bin \n"
               "cube_moves_directions.bin \n"
               "phase_1_patterns.bin \n"
               "phase_2_patterns.bin \n"
               "phase_2_transpositions.bin";
    }
};

struct pattern{
    int corner_orientations[8] = { 0,0,0,0,0,0,0,0 }; //these contain the number for which the amount of clockwise turns applied to each corner from its correct orientation.
    int edge_orientations[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //1's represent bad edges and 0's represent good edges (look up the tutorial fot the ZZ method for more info)
    std::string cornerPerm = "12345678";//These three variables contain the placement of the pieces
    std::string edgePerm = "123456789ABC";
    int ud_slice_edges[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
};
struct phase1_pattern{
    short corner_orientation_set = 0;
    short edge_orientation_set = 0;
    short ud_slice_permutation = 0;
    short solution_face_turns_index = 0;
    short solution_directions_index = 0;

    struct phase1_pattern& operator=(const phase1_pattern& p)
    {
        corner_orientation_set = p.corner_orientation_set;
        edge_orientation_set =  p.edge_orientation_set;
        ud_slice_permutation = p.ud_slice_permutation;

        solution_directions_index = p.solution_directions_index;
        solution_face_turns_index = p.solution_face_turns_index;
        return *this;
    }
};
struct phase2_pattern{
    std::string corner_permutation = "12345678";
    std::string edge_permutation = "123456789ABC";
    int solution_face_turns_index = 0;
    short solution_directions_index = 0;

    struct phase2_pattern& operator=(const phase2_pattern& p)
    {
        corner_permutation = p.corner_permutation;
        edge_permutation = p.edge_permutation;
        solution_face_turns_index = p.solution_face_turns_index;
        solution_directions_index = p.solution_directions_index;

        return *this;
    }
};

bool operator>(const phase1_pattern &first, const phase1_pattern &second);
bool operator<(const phase1_pattern &first, const phase1_pattern &second);
bool operator==(const phase1_pattern &first, const phase1_pattern &second);

bool operator>(const phase2_pattern &first, const phase2_pattern &second);
bool operator<(const phase2_pattern &first, const phase2_pattern &second);
bool operator==(const phase2_pattern &first, const phase2_pattern &second);

class Cube
{
private:
    const int NUM_OF_FACE_TURN_COMBINATIONS = 117186;
    const int NUM_OF_DIRECTION_COMBINATIONS = 3279;
    const int NUM_OF_PHASE_1_PATTERNS = 1138856;
    const int NUM_OF_PHASE_2_MOVE_STRS = 146634;
    const int NUM_OF_PHASE_2_PATTERNS = 883485;

    const int CORNERS_TO_SWAP[6][4] = {{0, 1, 5, 4}, {4, 7, 3, 0}, {4, 5, 6, 7}, {2, 3, 7, 6}, {1, 2, 6, 5}, {0, 3, 2, 1}};
    const int EDGES_TO_SWAP[6][4] = {{0, 9, 4, 8}, {3, 8, 7, 11}, {4, 5, 6, 7}, {2, 11, 6, 10}, {1, 10, 5, 9}, {0, 3, 2, 1}};
    const int indices_for_face_turn_str_length[7] = {0, 6, 36, 186, 936, 4686, 23436};
    const int indices_for_dir_length[7] = {0, 3, 12, 39, 120, 363, 1092};

    std::chrono::duration<double> solution_time_in_seconds;

    int * face_turns_of_move_strs;
    int * directions_of_move_strs;

    phase1_pattern * intermediate_phase_1_patterns;
    phase2_pattern * intermediate_phase_2_patterns;
    phase2_pattern * phase_2_transpositions;

    pattern starting_pattern;
    pattern working_pattern;
    pattern working_pattern_after_phase_1;

    phase1_pattern current_phase_1_pattern;
    phase2_pattern current_phase_2_pattern;

    bool cube_is_solved = false;

    int solution_move_strings_face_turns[4] = {0, 0, 0, 0};
    int solution_move_strings_directions[4] = {0, 0, 0, 0};

    std::string solution_move_str_face_turns = "";
    std::string solution_move_str_directions = "";

public:
    //each of these functions will load the move tables and pattern databases from their respective file.
    void loadMoveTables();
    /* loads the tables containing all combinations of moves which are length 7 or less. One table contains every combination of
     * face turns and the other table contains all combinations of directions in which to turn the faces. These combinations are represented by
     * int values where each digit corresponds with a particular move or direction.
     */

    void loadP2Transpositions();
    // loads patterns that were reached by applying moves (6 or less) that do not affect orientation of corners or edges and are used in phase 2

    void loadP1Patterns();
    // loads the orientation sets and the permutation of the middle slice edges contained in each phase 1 pattern and places them into a table

    void loadP2Patterns();
    // loads the permutation sets for the corners and edges contained in the phase 2 patterns and places them into a table

    void applyMoveString(int face_turns, int directions, pattern &p);
    //applies a sequence of moves, taking an int representing the sequence of face turns and another int for the sequence of directions in which
    //each face should be turned. Each digit of these ints represents a single move to apply to the pattern passed into the function

    void makeFaceTurn(int face_to_turn, int direction, pattern &current_cube_state);
    //Applies a move given parameter 1-6 that represents the face to turn and another that is 1-3, representing the number of quarter turns to make
    //as well as the pattern to modify. (ex: 2, 3 will rotate the blue face counter clockwise)

    void transposePieces(phase2_pattern &current_transpos, phase2_pattern &current_p2_pattern);
    /* Takes the current phase 2 pattern and maps the pieces to a destination based on another pattern reached in 6 or less moves.
     * Each piece in the current pattern will be adjusted based on how each piece in the transposing pattern was affected by applying the
     * corresponding moves from a solved state. For example, if in the transposing pattern the corner that belongs in the first slot
     * moved to the third slot, then the first corner in the current pattern will be moved to the third.
     */

    phase1_pattern constructP1Pattern(pattern p);
    //calculates the orientation values for corners and edges based on (turns the base 2 and 3 elements of each array in the pattern to a
    //single base 10 int respectively) for comparison against the values contained in the pattern database

    phase2_pattern constructP2Pattern(pattern p);
    //reduces the pattern to only its permutation sets for comparison against the table of (depth 7 or fewer) phase 2 patterns

    template<class patternType>
    int pattern_exists(patternType p_to_search, patternType collection_to_search[] ,int collection_length);
    //uses binary search to determine if the reached pattern can be solved in 6 moves or less (or 7 in phase 2) by determining if the current
    //pattern is a member of the table of patterns that were reached by applying that number of moves or less.

    void setPatternEqualTo(pattern &p, pattern &q);
    //sets the first parameter equal to the second

    void setStartingPattern(pattern p);
    //obtains the pattern from the user interface
    void solveCube();

    std::string getSolutionString();


    Cube();
    ~Cube();
};

#endif // CUBE_H
