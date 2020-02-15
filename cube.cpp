#include "cube.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;


bool operator>(const phase1_pattern &first, const phase1_pattern &second)
{
    if (first.corner_orientation_set > second.corner_orientation_set)
        return true;
    else if (first.corner_orientation_set < second.corner_orientation_set)
        return false;
    else
    {
        if (first.edge_orientation_set > second.edge_orientation_set)
            return true;
        else if (first.edge_orientation_set < second.edge_orientation_set)
            return false;
        else
        {
            if (first.ud_slice_permutation> second.ud_slice_permutation)
                return true;
            else if (first.ud_slice_permutation < second.ud_slice_permutation)
                return false;
        }
    }
    return false;
}
bool operator<(const phase1_pattern &first, const phase1_pattern &second)
{
    return !(first > second || first == second);
}
bool operator==(const phase1_pattern &first, const phase1_pattern &second)
{
    return (first.edge_orientation_set == second.edge_orientation_set && first.corner_orientation_set
            == second.corner_orientation_set && first.ud_slice_permutation == second.ud_slice_permutation);
}

bool operator>(const phase2_pattern &first, const phase2_pattern &second)
{
    if (first.corner_permutation > second.corner_permutation)
        return true;
    else if (first.corner_permutation < second.corner_permutation)
        return false;
    else
    {
        if (first.edge_permutation > second.edge_permutation)
            return true;
        else if (first.edge_permutation <= second.edge_permutation)
            return false;
    }
    return false;
}
bool operator<(const phase2_pattern &first, const phase2_pattern &second)
{
    return !(first > second || first == second);
}
bool operator==(const phase2_pattern &first, const phase2_pattern &second)
{
    return (first.edge_permutation == second.edge_permutation && first.corner_permutation
            == second.corner_permutation);
}

Cube::Cube()
{
    face_turns_of_move_strs = new int[NUM_OF_FACE_TURN_COMBINATIONS];
    directions_of_move_strs = new int[NUM_OF_DIRECTION_COMBINATIONS];

    intermediate_phase_1_patterns = new phase1_pattern[NUM_OF_PHASE_1_PATTERNS];
    intermediate_phase_2_patterns = new phase2_pattern[NUM_OF_PHASE_2_PATTERNS];
    phase_2_transpositions = new phase2_pattern[NUM_OF_PHASE_2_MOVE_STRS];

    loadMoveTables();
    loadP2Transpositions();
    loadP1Patterns();
    loadP2Patterns();
}

void Cube::loadMoveTables()
{
   ifstream in;

   in.open("cube_moves_face_turns.bin", ios::binary | ios::in);
   if (!in.is_open())
       throw IOException();

   in.read((char*)(face_turns_of_move_strs), sizeof (int) * NUM_OF_FACE_TURN_COMBINATIONS);
   in.close();

   in.open("cube_moves_directions.bin", ios::binary | ios::in);
   if (!in.is_open())
       throw IOException();

   in.read((char*)(directions_of_move_strs), sizeof(int) * NUM_OF_DIRECTION_COMBINATIONS);
   in.close();
}

void Cube::loadP2Transpositions()
{
    ifstream in;
    phase2_pattern current_tr_pos;
    in.open("phase_2_transpositions.bin", ios::binary | ios::in);
    if (!in.is_open())
        throw IOException();

    for (int i = 0; i < NUM_OF_PHASE_2_MOVE_STRS; i++)
    {
        in.read((char*)current_tr_pos.corner_permutation.c_str(), current_tr_pos.corner_permutation.size());
        in.read((char*)current_tr_pos.edge_permutation.c_str(), current_tr_pos.edge_permutation.size());
        in.read((char*)&current_tr_pos.solution_face_turns_index, sizeof(int));
        in.read((char*)&current_tr_pos.solution_directions_index, sizeof(short));
        phase_2_transpositions[i] = current_tr_pos;
        //cout << phase_2_transpositions[i].corner_permutation << " " << phase_2_transpositions[i].edge_permutation << endl;
    }
    in.close();
}

void Cube::loadP1Patterns()
{
    ifstream in;
    phase1_pattern current_pattern;
    in.open("phase_1_patterns.bin", ios::binary | ios::in);
    if (!in.is_open())
        throw IOException();

    for (int i = 0; i < NUM_OF_PHASE_1_PATTERNS; i++)
    {
        in.read((char*)&current_pattern.corner_orientation_set, sizeof(short));
        in.read((char*)&current_pattern.edge_orientation_set, sizeof(short));
        in.read((char*)&current_pattern.ud_slice_permutation, sizeof(short));
        in.read((char*)&current_pattern.solution_face_turns_index, sizeof(short));
        in.read((char*)&current_pattern.solution_directions_index, sizeof(short));
        intermediate_phase_1_patterns[i] = current_pattern;
    }
    in.close();
}

void Cube::loadP2Patterns()
{
    ifstream in;
    phase2_pattern current_pattern;
    in.open("phase_2_patterns.bin", ios::binary | ios::in);
    if (!in.is_open())
        throw IOException();

    for (int i = 0; i < NUM_OF_PHASE_2_PATTERNS; i++)
    {
        in.read((char*)current_pattern.corner_permutation.c_str(), current_pattern.corner_permutation.size());
        in.read((char*)current_pattern.edge_permutation.c_str(), current_pattern.edge_permutation.size());
        in.read((char*)&current_pattern.solution_face_turns_index, sizeof(int));
        in.read((char*)&current_pattern.solution_directions_index, sizeof(short));
        intermediate_phase_2_patterns[i] = current_pattern;
    }
    in.close();
}

void Cube::applyMoveString(int face_turns, int directions, pattern &p)
{
    for (int current_digit_val = 1000000; current_digit_val >= 1; current_digit_val /= 10)
    {
        if (face_turns / current_digit_val > 0 && directions / current_digit_val > 0)
        {
            makeFaceTurn(face_turns / current_digit_val, directions / current_digit_val, p);
            face_turns -= (face_turns / current_digit_val) * current_digit_val;
            directions -= (directions / current_digit_val) * current_digit_val;
        }
    }
}

void Cube::makeFaceTurn(int face_to_turn, int direction, pattern &current_cube_state)
{
    const int NUMBER_OF_EDGES = 4;
    pattern mapping_pattern;
    setPatternEqualTo(mapping_pattern, current_cube_state);

    face_to_turn -= 1; //because the number representing the face to turn is used as an index and formatting issues with using 0 when storing int
    //move strings, shift the value so the range is 0-5
    for (int i = 0; i < NUMBER_OF_EDGES; i++)
    {
        current_cube_state.corner_orientations[CORNERS_TO_SWAP[face_to_turn][i]] = mapping_pattern.corner_orientations[CORNERS_TO_SWAP[face_to_turn][(i + direction) % 4]];
        current_cube_state.cornerPerm[CORNERS_TO_SWAP[face_to_turn][i]] = mapping_pattern.cornerPerm[CORNERS_TO_SWAP[face_to_turn][(i + direction) % 4]];
        current_cube_state.edge_orientations[EDGES_TO_SWAP[face_to_turn][i]] = mapping_pattern.edge_orientations[EDGES_TO_SWAP[face_to_turn][(i + direction) % 4]];
        current_cube_state.edgePerm[EDGES_TO_SWAP[face_to_turn][i]] = mapping_pattern.edgePerm[EDGES_TO_SWAP[face_to_turn][(i + direction) % 4]];
        current_cube_state.ud_slice_edges[EDGES_TO_SWAP[face_to_turn][i]] = mapping_pattern.ud_slice_edges[EDGES_TO_SWAP[face_to_turn][(i + direction) % 4]];
        //swaps the pieces, depending on the face turned and the direction;
    }

    if (face_to_turn != 2 && face_to_turn != 5 && direction != 2)
        //only a quarter turn on the front, left, right, and back faces will change the orientation of the corners or edges
    {
        for (int i = 0; i < 4; i++)
        {
            current_cube_state.corner_orientations[CORNERS_TO_SWAP[face_to_turn][i]] =
                (current_cube_state.corner_orientations[CORNERS_TO_SWAP[face_to_turn][i]] + 1 + (i % 2)) % 3;
           //rotates each corner that was shifted. Note that a modulus of 3 is used since a corner only has 3 possible orientations
        }
        if (face_to_turn == 0 || face_to_turn == 3)
            //only a turn on the front and back faces will change the orientation of the edges
        {
            for (int i = 0; i < 4; i++)
                current_cube_state.edge_orientations[EDGES_TO_SWAP[face_to_turn][i]] = (current_cube_state.edge_orientations[EDGES_TO_SWAP[face_to_turn][i]] + 1) % 2;
            //flips edge orientation. Edges have 2 possible orientations, therefore mod 2 is used
        }
    }
}

void Cube::transposePieces(phase2_pattern &mapping_pattern, phase2_pattern &current_p2_pattern)
{
    string x = current_p2_pattern.corner_permutation;
    string y = current_p2_pattern.edge_permutation;
    int i = 0;

    for (i = 0; i < 8; i++)
    {
        current_p2_pattern.corner_permutation[i] = x[static_cast<int>(mapping_pattern.corner_permutation[i] - '1')];
        //get the numerical value of the char so that it can be used as index in the permutation set
    }

    for (i = 0; i < 12; i++)
    {
        if (mapping_pattern.edge_permutation[i] < 'A')
        {
            current_p2_pattern.edge_permutation[i] = y[static_cast<int>(mapping_pattern.edge_permutation[i]- '1')];
        }
        else
            current_p2_pattern.edge_permutation[i] = y[static_cast<int>(mapping_pattern.edge_permutation[i]- '8')];
            //this removes the offset from A B or C to 9, 10, and 11 respectively
    }
}

phase1_pattern Cube::constructP1Pattern(pattern p)
{
    short corner_orientation_num_val = 2187;
    short edge_orientation_num_val = 2048;
    short ud_slice_permutation = 2048;

    phase1_pattern q;

    for (int i = 0; i < 8; i++)
    {
        q.corner_orientation_set += (short)(p.corner_orientations[i] * corner_orientation_num_val);
        corner_orientation_num_val /= 3;
    }
    for (int i = 0; i < 12; i++)
    {
        q.edge_orientation_set += (short)(p.edge_orientations[i] * edge_orientation_num_val);
        q.ud_slice_permutation += (short)(p.ud_slice_edges[i] * ud_slice_permutation);
        edge_orientation_num_val /= 2;
        ud_slice_permutation /= 2;
    }
    return q;
}

phase2_pattern Cube::constructP2Pattern(pattern p)
{
    phase2_pattern q;
    q.corner_permutation = p.cornerPerm;
    q.edge_permutation = p.edgePerm;

    return q;
}

void Cube::setPatternEqualTo(pattern &p, pattern &q)
{
    p.edgePerm = q.edgePerm;
    p.cornerPerm = q.cornerPerm;
    for (int i = 0; i < 12; i++)
    {
        p.ud_slice_edges[i] = q.ud_slice_edges[i];
        p.edge_orientations[i] = q.edge_orientations[i];
    }
    for (int i = 0; i < 8; i++)
        p.corner_orientations[i] = q.corner_orientations[i];
}

void Cube::setStartingPattern(pattern p)
{
    setPatternEqualTo(starting_pattern, p);
}

void Cube::solveCube()
{
    bool cube_is_solved = false;
    int current_p1_face_turn_combination = 0;
    int length_of_current_move_str = 0;
    float count = 0;
    while (!cube_is_solved)
    {
        setPatternEqualTo(working_pattern, starting_pattern);

        int index_of_matching_pattern = 0;
        bool phase_1_solution_found = false;

        solution_move_str_directions = "";
        solution_move_str_face_turns = "";

        for (;current_p1_face_turn_combination < 23436 && !phase_1_solution_found; current_p1_face_turn_combination++)
        {
            if (current_p1_face_turn_combination == indices_for_face_turn_str_length[length_of_current_move_str])
                length_of_current_move_str++;
            for (int current_p1_direction_combination = indices_for_dir_length[length_of_current_move_str - 1]; current_p1_direction_combination < indices_for_dir_length[length_of_current_move_str] && !phase_1_solution_found; current_p1_direction_combination++)
            {
                applyMoveString(face_turns_of_move_strs[current_p1_face_turn_combination], directions_of_move_strs[current_p1_direction_combination], working_pattern);
                current_phase_1_pattern = constructP1Pattern(working_pattern);
                index_of_matching_pattern = pattern_exists(current_phase_1_pattern, intermediate_phase_1_patterns, NUM_OF_PHASE_1_PATTERNS);
                if (index_of_matching_pattern > -1)
                {
                    phase_1_solution_found = true;
                    solution_move_str_face_turns += to_string(face_turns_of_move_strs[current_p1_face_turn_combination]);
                    solution_move_str_face_turns += to_string(face_turns_of_move_strs[intermediate_phase_1_patterns[index_of_matching_pattern].solution_face_turns_index]);
                    solution_move_str_directions += to_string(directions_of_move_strs[current_p1_direction_combination]);
                    solution_move_str_directions += to_string(directions_of_move_strs[intermediate_phase_1_patterns[index_of_matching_pattern].solution_directions_index]);
                    applyMoveString(face_turns_of_move_strs[intermediate_phase_1_patterns[index_of_matching_pattern].solution_face_turns_index]
                            , directions_of_move_strs[intermediate_phase_1_patterns[index_of_matching_pattern].solution_directions_index], working_pattern);
                }
                else
                    setPatternEqualTo(working_pattern, starting_pattern);
            }
        }

        phase2_pattern starting_p2_pattern = constructP2Pattern(working_pattern);
        for (int i = 0; i < NUM_OF_PHASE_2_MOVE_STRS && !cube_is_solved; i++)
        {
            current_phase_2_pattern = starting_p2_pattern;
            transposePieces(phase_2_transpositions[i], current_phase_2_pattern);
            index_of_matching_pattern = pattern_exists(current_phase_2_pattern, intermediate_phase_2_patterns, NUM_OF_PHASE_2_PATTERNS);
            if (index_of_matching_pattern > -1)
            {
                cube_is_solved = true;
                solution_move_str_face_turns += to_string(face_turns_of_move_strs[phase_2_transpositions[i].solution_face_turns_index]);
                solution_move_str_face_turns += to_string(face_turns_of_move_strs[intermediate_phase_2_patterns[index_of_matching_pattern].solution_face_turns_index]);
                solution_move_str_directions += to_string(directions_of_move_strs[phase_2_transpositions[i].solution_directions_index]);
                solution_move_str_directions += to_string(directions_of_move_strs[intermediate_phase_2_patterns[index_of_matching_pattern].solution_directions_index]);
                applyMoveString(face_turns_of_move_strs[phase_2_transpositions[i].solution_face_turns_index], directions_of_move_strs[phase_2_transpositions[i].solution_directions_index], working_pattern);
                applyMoveString(face_turns_of_move_strs[intermediate_phase_2_patterns[index_of_matching_pattern].solution_face_turns_index]
                        , directions_of_move_strs[intermediate_phase_2_patterns[index_of_matching_pattern].solution_directions_index], working_pattern);
                count += i;
            }
        }
        if (!cube_is_solved)
            count += NUM_OF_PHASE_2_MOVE_STRS;
    }
    cout << "Phase 2 cycles: " << count / NUM_OF_PHASE_2_MOVE_STRS << " " << "times" << endl;
}

string Cube::getSolutionString()
{
    string solution = "";
    for (int i = 0; i < (int)solution_move_str_directions.length(); i++)
    {
        string face_color = "";
        string direction = "";
        string notation = "";
        switch(solution_move_str_face_turns[i])
        {
            case '1':
            {
                face_color = "red";
                notation += "F";
                break;
            }
            case '2':
            {
                face_color = "blue";
                notation += "L";
                break;
            }
            case '3':
            {
                face_color = "yellow";
                notation += "U";
                break;
            }
            case '4':
            {
                face_color = "orange";
                notation += "B";
                break;
            }
            case '5':
            {
                face_color = "green";
                notation += "R";
                break;
            }
            case '6':
            {
                face_color = "white";
                notation += "D";
                break;
            }
            default:
                break;
        }
        switch(solution_move_str_directions[i])
        {
            case '1':
            {
                direction = "clockwise";
                break;
            }
            case '2':
            {
                direction = "a half turn";
                notation += "2";
                break;
            }
            case '3':
            {
                direction = "counterclockwise";
                notation += "i";
                break;
            }
            default:
                break;
        }
        solution += to_string(i + 1) + ". " + "Turn the " + face_color + " face " + direction + ". (" + notation + ")" + "\n";
    }
    return solution;
}

void Cube::optimizeSolutionSeq()
{

}

Cube::~Cube()
{
}

template<class patternType>
int Cube::pattern_exists(patternType p_to_search, patternType collection_to_search[], int collection_length)
{
    int begin = 0;
    int end = collection_length - 1;
    int mean = 0;

    if (collection_length == 0)
        return false;

    while (end >= begin)
    {
        mean = begin + (end - begin) / 2;
        if (collection_to_search[mean] < p_to_search)
            begin = mean + 1;
        else if (collection_to_search[mean] == p_to_search)
            return mean;
        else
            end = mean - 1;
    }

    if (collection_to_search[mean] == p_to_search)
        return mean;
    else
        return -1;
}
