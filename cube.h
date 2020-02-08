#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct pattern{
    int corner_orientations[8] = { 0,0,0,0,0,0,0,0 }; //these contain the number for which the amount of clockwise turns applied to each corner from its correct orientation.
    int edge_orientations[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //1's represent bad edges and 0's represent good edges (look up the tutorial fot the ZZ method for more info)
    string cornerPerm = "12345678";//These three variables contain the placement of the pieces
    string edgePerm = "123456789ABC";
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
    string corner_permutation = "12345678";
    string edge_permutation = "123456789ABC";
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

    int * face_turns_of_move_strs = new int[NUM_OF_FACE_TURN_COMBINATIONS];
    int * directions_of_move_strs = new int[NUM_OF_DIRECTION_COMBINATIONS];

    phase1_pattern * intermediate_phase_1_patterns = new phase1_pattern[NUM_OF_PHASE_1_PATTERNS];
    phase2_pattern * intermediate_phase_2_patterns = new phase2_pattern[NUM_OF_PHASE_2_PATTERNS];
    phase2_pattern * phase_2_transpositions = new phase2_pattern[NUM_OF_PHASE_2_MOVE_STRS];

    pattern starting_pattern;
    pattern working_pattern;
    pattern working_pattern_after_phase_1;

    phase1_pattern current_phase_1_pattern;
    phase2_pattern current_phase_2_pattern;

    bool cube_is_solved = false;

    int solution_move_strings_face_turns[4] = {0, 0, 0, 0};
    int solution_move_strings_directions[4] = {0, 0, 0, 0};

    string solution_move_str_face_turns = "";
    string solution_move_str_directions = "";

public:
    //each of these functions will load the move tables and pattern databases from their respective file.
    void loadMoveTables();
    void loadP2Transpositions();
    void loadP1Patterns();
    void loadP2Patterns();

    void applyMoveString(int face_turns, int directions, pattern &p);
    //applies a sequence of moves

    void performMove(int face_to_turn, int direction, pattern &current_cube_state);
    //Applies a move given parameter 1-6 that represents the face to turn and another that is 1-3, representing the number of quarter turns to make
    //as well as the pattern to modify. (ex: 2, 3 will rotate the blue face counter clockwise)
    void transposePieces(phase2_pattern &current_transpos, phase2_pattern &current_p2_pattern);
    //swaps the pieces in the pattern to assimilate the turning of a face by mapping them from a copied pattern (source) to the parameter pattern(destination)

    phase1_pattern constructP1Pattern(pattern p);
    //separates the orientation sets and the placements of the middle slice edge
    //calculates a numerical value for each set for more efficient operation

    phase2_pattern constructP2Pattern(pattern p);
    //separates the permutation sets and stores them in FIXED LENGTH strings

    template<class patternType>
    int pattern_exists(patternType p_to_search, patternType collection_to_search[] ,int collection_length);
    //uses binary search to determine if a pattern exists in the collection and returns the index if found or -1 if not

    void setPatternEqualTo(pattern &p, pattern &q);
    //sets the first parameter equal to the second

    void setStartingPattern(pattern p);
    //obtains the pattern from the user interface
    void solveCube();

    string getSolutionString();
    void optimizeSolutionSeq();


    Cube();
    ~Cube();
};

#endif // CUBE_H
