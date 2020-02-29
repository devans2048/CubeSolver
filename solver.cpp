/* Copyright (C) 2020 Dylan Evans - All Rights Reserved
 * You may use, distribute, or modify this code under the terms of the MIT license
 * You should have received a copy of the license with this file. If not, you may visit https://opensource.org/licenses/MIT
*/

#include "solver.h"
#include "ui_solver.h"
#include <QTextBrowser>
#include <QMessageBox>
#include <QSignalMapper>
#include <random>

Solver::Solver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Solver)
{
    ui->setupUi(this);
    solver = new Cube();

    connectSignals();
    renderCube();
    setupFaceTurnButtons();
}

Solver::~Solver()
{
    delete ui;
}

void Solver::renderCube()
{
    //These contain the x and y coordinates for each face
    const int FACE_LOCATIONS_X[6] = {10, 170, 170, 170, 330, 490};
    const int FACE_LOCATIONS_Y[6] = {170, 170, 10, 330, 170, 170};
    //contains information about how many tiles away from the starting corner of each face
    //in the x and y directions respectively
    const int CORNER_TILE_OFFSETS_X[4] = {0, 2, 2, 0};
    const int CORNER_TILE_OFFSETS_Y[4] = {0, 0, 2, 2};
    const int EDGE_TILE_OFFSETS_X[4] = {1, 2, 1, 0};
    const int EDGE_TILE_OFFSETS_Y[4] = {0, 1, 2, 1};

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            corners[4 * i + j]->setGeometry(FACE_LOCATIONS_X[i] + CORNER_TILE_OFFSETS_X[j] * 50,
                                    FACE_LOCATIONS_Y[i] + CORNER_TILE_OFFSETS_Y[j] * 50, 51, 51);
            edges[4 * i + j]->setGeometry(FACE_LOCATIONS_X[i] + EDGE_TILE_OFFSETS_X[j] * 50,
                                   FACE_LOCATIONS_Y[i] + EDGE_TILE_OFFSETS_Y[j] * 50, 51, 51);
        }
    }
    on_reset_cube_clicked();
}

void Solver::connectSignals()
{
    for (int i = 0; i < 24; i++)
    {
        corners[i] = new QPushButton(this);
        edges[i] = new QPushButton(this);
        connect(corners[i], &QPushButton::clicked, this, [this, i]{changeCornerTileColor(i); });
        connect(edges[i], &QPushButton::clicked, this, [this, i]{changeEdgeTileColor(i); });
    }
}

void Solver::setupFaceTurnButtons()
{
    const std::string MOVE_NOTATION[18] = {"F", "F2", "Fi", "L", "L2", "Li", "U", "U2", "Ui", "B", "B2", "Bi" ,"R", "R2", "Ri", "D", "D2", "Di"};

    for (int i = 0; i < 18; i++)
    {
        face_turn_buttons[i] = new QPushButton(this);
        face_turn_buttons[i]->setText(MOVE_NOTATION[i].c_str());
    }

    for (int i = 0; i < 6; i++)
    {
        int button_location_y = 380 + 40 * i;
        for (int j = 0; j < 3; j++)
        {
            int button_location_x = 360 + 50 * j;
            face_turn_buttons[i * 3 + j]->setGeometry(button_location_x, button_location_y, 41, 31);
            connect(face_turn_buttons[i * 3 + j], &QPushButton::clicked, this, [this, i, j]{makeFaceTurn(i, j + 1);});
        }
    }
}

void Solver::on_blue_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: blue; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: blue; border: 2px solid black}");
    color_num = 1;
}

void Solver::on_red_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: red; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: red; border: 2px solid black}");
    color_num = 2;
}

void Solver::on_yellow_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: yellow; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: yellow; border: 2px solid black}");
    color_num = 3;
}

void Solver::on_green_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: green; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: green; border: 2px solid black}");
    color_num = 5;
}

void Solver::on_orange_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: orange; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: orange; border: 2px solid black}");
    color_num = 6;
}

void Solver::on_white_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: white; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: white; border: 2px solid black}");
    color_num = 4;
}

void Solver::on_solve_button_clicked()
{
    getCoords();
    if (isCompleteCube() && validPattern())
    {
        solver->solveCube();
        displaySolution();
    }
}

void Solver::on_reset_cube_clicked()
{
    for (int i = 0; i < 24; i++)
    {
        corners[i]->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
        edges[i]->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    }
    ui->pushButton_64->setStyleSheet("background-color: rgb(200, 200, 200); border: 2px solid black");

    color_num = 0;
    button_color_stylesheet = "";

    for (int i = 0; i < 24; i++)
    {
        color_of_corners[i] = 0;
        color_of_edges[i] = 0;
    }
}

void Solver::on_random_pattern_clicked()
{
    bool matching_moves = true;
    static std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 17);

    //set the cube to a solved state first to ensure that a valid pattern is reached
    on_solved_cube_clicked();

    for (int i = 0; i < 40; i++)
    {
        random_moves[i] = dist(generator);
    }

    while (matching_moves == true)
    {
        matching_moves = false;
        for (int i = 0; i < 19; i++)
        {
            if (random_moves[i] / 3 == random_moves[i + 1] / 3)
            {
                random_moves[i] = dist(generator);
                matching_moves = true;
            } 
        }
    }

    for (int i = 0; i < 20; i++)
    {
       makeFaceTurn(random_moves[i] / 3, (random_moves[i] % 3) + 1);
    }
}

void Solver::getCoords()//
{
    unsigned int i = 0;
    //the number associated with each color for all tiles of each corner are multiplied together to produce unique values
    //for each corner that can be used to determine which piece is in the current slot regardless of orientation
    const int CORNER_COLOR_VALS[8] = {8, 40, 120, 24, 6, 30, 90, 18};

    //Same here, except that the sum of the squares of each color number are used to produce unique values
    const int EDGE_COLOR_VALS[12] = {20, 41, 52, 17, 13, 34, 45, 10, 5, 29, 61, 37};

    for (i = 0; i < 24; i++)
    {
        if (color_of_corners[i] == 3 || color_of_corners[i] == 4)
        {
            entered_pattern.corner_orientations[i / 3] = (i % 3);
        }
    }

    for (i = 0; i < 24; i+=2)
    {
        if (color_of_edges[i] == 3 || color_of_edges[i] == 4 ||
                color_of_edges[i + 1] == 1 || color_of_edges[i + 1] == 5)
            entered_pattern.edge_orientations[i / 2] = 0;
        else
            entered_pattern.edge_orientations[i / 2] = 1;
    }

    for (i = 0; i < 24; i += 3)
    {
        int current_corner = color_of_corners[i] * color_of_corners[i + 1] * color_of_corners[i + 2];
        bool valid_corner_found = false;
        for (int j = 0; j < 8; j++)
        {
            if (current_corner == CORNER_COLOR_VALS[j])
            {
                entered_pattern.cornerPerm[i / 3] = (char)j + '1';
                valid_corner_found = true;
            }
        }
        if (!valid_corner_found)
            entered_pattern.cornerPerm[i / 3] = '0';
    }

    for (i = 0; i < 24; i += 2)
    {
        int current_edge = color_of_edges[i] * color_of_edges[i] + color_of_edges[i + 1] * color_of_edges[i + 1];
        bool valid_corner_found = false;
        for (int j = 0; j < 12; j++)
        {
            if (current_edge == EDGE_COLOR_VALS[j])
            {
                if (j < 9)
                    entered_pattern.edgePerm[i / 2] = (char)j + '1';
                else
                    entered_pattern.edgePerm[i / 2] = (char)j + '8';
                valid_corner_found = true;
            }
        }
        if (!valid_corner_found)
            entered_pattern.edgePerm[i / 3] = '0';
    }

    for (i = 0; i < 12; i++)
    {
        if (entered_pattern.edgePerm[i] > '8')
            entered_pattern.ud_slice_edges[i] = 1;
        else
            entered_pattern.ud_slice_edges[i] = 0;
    }
    solver->setStartingPattern(entered_pattern);
}

bool Solver::isCompleteCube()
{
    using std::string;
    int num_of_each_color[6] = {0, 0, 0, 0, 0, 0};
    const string COLORS[6] = {"blue", "red", "yellow", "white", "green", "orange"};
    string error_msg;

    for (int i = 0; i < 24; i++)
    {
        if (color_of_corners[i] > 0 && color_of_corners[i] < 7)
            num_of_each_color[color_of_corners[i] - 1] += 1;
        if (color_of_edges[i] > 0  && color_of_edges[i] < 7)
            num_of_each_color[color_of_edges[i] - 1] += 1;
    }
    for (int i = 0; i < 6; i++)
    {
        if (num_of_each_color[i] < 8 || num_of_each_color[i] > 8)
        {
            error_msg = "There must be 9 tiles colored " + COLORS[i] + " in total.";
            QMessageBox::information(this, tr("Error"), tr(error_msg.c_str()));
            return false;
        }
    }
    return true;
}

bool Solver::validPattern()
{
    int inversions = 0;
    int sgn_c_perm;
    int sgn_e_perm;

    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            if (entered_pattern.cornerPerm[i] > entered_pattern.cornerPerm[j])
            {
                inversions++;
            }
        }
    }
    sgn_c_perm = inversions % 2;
    inversions = 0;

    for (int i = 0; i < 12; i++)
    {
        for (int j = i + 1; j < 12; j++)
        {
            if (entered_pattern.edgePerm[i] > entered_pattern.edgePerm[j])
            {
                inversions++;
            }
        }
    }
    sgn_e_perm = inversions % 2;

    if (sgn_c_perm != sgn_e_perm)
    {
        QMessageBox::information(this, tr("Error"), tr("The parity of the corners and edges does not match"));
        return false;
    }

    inversions = 0;

    for (int i = 0; i < 8; i++)
    {
        inversions += entered_pattern.corner_orientations[i];
    }

    if (inversions % 3 != 0)
    {
        QMessageBox::information(this, tr("Error"), tr("The corners have an invalid orientation"));
        return false;
    }

    inversions = 0;

    for (int i = 0; i < 12; i++)
    {
        inversions += entered_pattern.edge_orientations[i];
    }
    if (inversions % 2 != 0)
    {
        QMessageBox::information(this, tr("Error"), tr("The edges have an invalid orientation"));
        return false;
    }
    return true;
}

void Solver::displaySolution()
{
    std::string temp = solver->getSolutionString();

    QString str = QString::fromStdString(temp);
    ui->textBrowser->setFontPointSize(9);
    ui->textBrowser->setText(str);
}

void Solver::makeFaceTurn(int face_to_turn, int direction)
{
    const int CORNER_TILES_TO_SWAP[6][4][3] = {{{0, 1, 2}, {5, 3, 4}, {15, 16, 17}, {14, 12, 13}}, {{9, 10, 11}, {2, 0, 1}, {12, 13, 14}, {23, 21, 22}},
                                               {{13, 14, 12}, {16, 17, 15}, {19, 20, 18}, {22, 23, 21}}, {{6, 7, 8}, {11, 9, 10}, {21, 22, 23}, {20, 18, 19}},
                                               {{3, 4, 5}, {8, 6, 7}, {18, 19, 20}, {17, 15, 16}}, {{10, 11, 9}, {7, 8, 6}, {4, 5, 3}, {1, 2, 0}}};

    const int EDGE_TILES_TO_SWAP[6][4][2] = {{{0, 1}, {19, 18}, {8, 9}, {17, 16}}, {{6, 7}, {16, 17}, {14, 15}, {22, 23}}, {{9, 8}, {11, 10}, {13, 12}, {15, 14}},
                                             {{4, 5}, {23, 22}, {12, 13}, {21, 20}}, {{2, 3}, {20, 21}, {10, 11}, {18, 19}}, {{5, 4}, {3, 2}, {1, 0}, {7, 6}}};
    int copy_of_corners[24];
    int copy_of_edges[24];

    for (int i = 0; i < 24; i++)
    {
        copy_of_corners[i] = color_of_corners[i];
        copy_of_edges[i] = color_of_edges[i];
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
            color_of_corners[CORNER_TILES_TO_SWAP[face_to_turn][i][j]] = copy_of_corners[CORNER_TILES_TO_SWAP[face_to_turn][(i + direction) % 4][j]];
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
            color_of_edges[EDGE_TILES_TO_SWAP[face_to_turn][i][j]] = copy_of_edges[EDGE_TILES_TO_SWAP[face_to_turn][(i + direction) % 4][j]];
    }
    colorCubeTiles();
}

void Solver::colorCubeTiles()
{
    using std::string;
    const int CORNER_FACE_TO_TILE_MAPPING[24] = {12, 2, 7, 13, 6, 19, 14, 18, 23, 15, 22, 3, 11, 4, 1, 10, 16, 5, 9, 20, 17, 8, 0, 21};
    const int EDGE_FACE_TO_TILE_MAPPING[24] = {12, 6, 13, 18, 14, 22, 15, 2, 10, 4, 9, 16, 8, 20, 11, 0, 7, 1, 5, 19, 23, 17, 21, 3};
    const string COLOR_STYLESHEETS[6] = {"blue", "red", "yellow", "white", "green", "orange"};
    string color =  "";
    for (int i = 0; i < 24; i++)
    {
        if (color_of_corners[i] > 0 && color_of_corners[i] < 7)
        {
            color = "QPushButton{background-color: " + COLOR_STYLESHEETS[color_of_corners[i] - 1] + "; border: 1px solid black}";
            corners[CORNER_FACE_TO_TILE_MAPPING[i]]->setStyleSheet(color.c_str());
        }
        if (color_of_edges[i] > 0 && color_of_edges[i] < 7)
        {
            color = "QPushButton{background-color: " + COLOR_STYLESHEETS[color_of_edges[i] - 1] + "; border: 1px solid black}";
            edges[EDGE_FACE_TO_TILE_MAPPING[i]]->setStyleSheet(color.c_str());
        }
    }

}

void Solver::changeCornerTileColor(int changed_corner_id)
{
    //Each button is mapped to one of 3 sides of each of the 8 corners, which are labeled in a particular order that
    //differs from their placement on the screen. This mapping allows permutation and orientation to be found by simply
    //iterating through the set of 24 colors.
    const int TILE_TO_CORNER_FACE_MAPPING[24] = {22, 14, 1, 11, 13, 17, 4, 2, 21, 18, 15, 12, 0, 3, 6, 9, 16, 20, 7, 5, 19, 23, 10, 8};

    corners[changed_corner_id]->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[TILE_TO_CORNER_FACE_MAPPING[changed_corner_id]] = color_num;
}

void Solver::changeEdgeTileColor(int changed_edge_id)
{
    //Same thing done here as the corners, but for the edges. Note that because edges have 2 faces instead of 3, the mapping
    //differs from that of the corners
    const int TILE_TO_EDGE_FACE_MAPPING[24] = {15, 17, 7, 23, 9, 18, 1, 16, 12, 10, 8, 14, 0, 2, 4, 6, 11, 21, 3, 19, 13, 22, 5, 20};

    edges[changed_edge_id]->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[TILE_TO_EDGE_FACE_MAPPING[changed_edge_id]] = color_num;
}

void Solver::on_solved_cube_clicked()
{
    using std::string;
    const string COLORS[6] = {"blue", "red", "yellow", "white", "green", "orange"};
    const int TILE_TO_CORNER_FACE_MAPPING[24] = {22, 14, 1, 11, 13, 17, 4, 2, 21, 18, 15, 12, 0, 3, 6, 9, 16, 20, 7, 5, 19, 23, 10, 8};
    const int TILE_TO_EDGE_FACE_MAPPING[24] = {15, 17, 7, 23, 9, 18, 1, 16, 12, 10, 8, 14, 0, 2, 4, 6, 11, 21, 3, 19, 13, 22, 5, 20};
    for (int i = 0; i < 24; i++)
    {
        string color_stylesheet = "background-color: " + COLORS[i / 4] + "; border: 1px solid black";
        corners[i]->setStyleSheet(color_stylesheet.c_str());
        edges[i]->setStyleSheet(color_stylesheet.c_str());
        color_of_corners[TILE_TO_CORNER_FACE_MAPPING[i]] = (i / 4) + 1;
        color_of_edges[TILE_TO_EDGE_FACE_MAPPING[i]] = (i / 4) + 1;
    }
    ui->pushButton_64->setStyleSheet("background-color: rgb(200, 200, 200); border: 2px solid black");

    color_num = 0;
    button_color_stylesheet = "";
    colorCubeTiles();
}

