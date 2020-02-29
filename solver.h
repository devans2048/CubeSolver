/* Copyright (C) 2020 Dylan Evans - All Rights Reserved
 * You may use, distribute, or modify this code under the terms of the MIT license
 * You should have received a copy of the license with this file. If not, you may visit https://opensource.org/licenses/MIT
*/

#ifndef SOLVER_H
#define SOLVER_H
#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include "cube.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Solver; }
QT_END_NAMESPACE

class Solver : public QMainWindow
{
    Q_OBJECT

public:
    Solver(QWidget *parent = nullptr);
    ~Solver();

    void renderCube();
    //shows displays the cube by placing all of its buttons on the screen

    void connectSignals();
    //connects each button to a parameterized slot that depends on the button clicked

    void setupFaceTurnButtons();
    //places the buttons for each of the face turns on the screen

    void getCoords();
    //takes the user input pattern and generates a pattern as defined in cube.h

    bool validPattern();
    //checks the orientation and permutation of the edges and corners and displays an error message accordingly if
    //the pattern entered is not possible on a standard cube

    bool isCompleteCube();
    //ensures that the correct number of tiles of all colors are on the cube and displays an error message otherwise

    void displaySolution();
    //displays the solution and time spent finding it in the text browser

    void colorCubeTiles();
    //colors each tile based on the contents of each corner and edge

private slots:
    void makeFaceTurn(int face_to_turn, int direction);

    void changeCornerTileColor(int);
    //changes the color of the button clicked to the color that was selected in the editor
    void changeEdgeTileColor(int);
    //same as above but for the edges instead of corners

    void on_blue_button_clicked();

    void on_red_button_clicked();

    void on_yellow_button_clicked();

    void on_green_button_clicked();

    void on_orange_button_clicked();

    void on_white_button_clicked();
    //These buttons all change the selected color to match the color of the button clicked


    void on_solve_button_clicked();
    //solves the cube

    void on_reset_cube_clicked();
    //makes an empty cube, where only the centers are colored

    void on_random_pattern_clicked();
    //generates a sequence of 40 moves at random

    void on_solved_cube_clicked();
    //sets the cube to a solved state
private:
    Ui::Solver *ui;
    Cube * solver;

    const int CORNER_BUTTON_LOCATIONS_X[24] = {};
    const int CORNER_BUTTON_LOCATIONS_Y[24] = {};
    const int EDGE_BUTTON_LOCATIONS_X[24] = {};
    const int EDGE_BUTTON_LOCATIONS_Y[24] = {};
    //Where the buttons for each edge or corner face should be placed

    QPushButton * corners[24];
    QPushButton * edges[24];
    //Buttons which represent each of the 24 sides of the corners and edges

    QPushButton * face_turn_buttons[18];
    //Buttons for each of the different single face turns

    std::string button_color_stylesheet = "";
    int color_num = 0;
    int color_of_corners[24];
    int color_of_edges[24];
    int random_moves[40];
    //40 random moves will result in an acceptably uniform distribution of random patterns reached

    int solution_move_strings_face_turns[4];
    int solution_move_strings_directions[4];
    pattern entered_pattern;
};
#endif // SOLVER_H
