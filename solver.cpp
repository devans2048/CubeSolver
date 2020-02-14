#include "solver.h"
#include "ui_solver.h"
#include <QTextBrowser>
#include <QMessageBox>
#include <QSignalMapper>
#include <random>
#include <ctime>
#include <chrono>

Solver::Solver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Solver)
{
    ui->setupUi(this);
    //cube = new Cube();
    connectSignals();
    renderCube();
    setupFaceTurnButtons();
}

Solver::~Solver()
{
    delete ui;
}

void Solver::show_exception_bad_alloc()
{
    QMessageBox::information(this, tr("Error"), tr("There is not enough free memory. Make sure you have at least 150 MB of free memory."));
}

void Solver::show_exception_io_error(const char* fileName)
{
    QMessageBox::information(this, tr("Error"), tr(fileName));
}

void Solver::show_exception_timeout()
{
    QMessageBox::information(this, tr("Error"), tr("The solver timed out. Make sure that the entered pattern has s"));
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
    const string MOVE_NOTATION[18] = {"F", "F2", "Fi", "L", "L2", "Li", "U", "U2", "Ui", "B", "B2", "Bi" ,"R", "R2", "Ri", "D", "D2", "Di"};

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

void Solver::on_pushButton_clicked()
{
    ui->pushButton->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[22] = color_num;
}

void Solver::on_pushButton_2_clicked()
{
    ui->pushButton_2->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[15] = color_num;
}

void Solver::on_pushButton_3_clicked()
{
    ui->pushButton_3->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[14] = color_num;
}

void Solver::on_pushButton_4_clicked()
{
    ui->pushButton_4->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[23] = color_num;
}

void Solver::on_pushButton_6_clicked()
{
    ui->pushButton_6->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[17] = color_num;
}

void Solver::on_pushButton_7_clicked()
{
    ui->pushButton_7->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[11] = color_num;
}

void Solver::on_pushButton_8_clicked()
{
    ui->pushButton_8->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[7] = color_num;
}

void Solver::on_pushButton_9_clicked()
{
    ui->pushButton_9->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[1] = color_num;
}

void Solver::on_pushButton_10_clicked()
{
    ui->pushButton_10->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[13] = color_num;
}

void Solver::on_pushButton_11_clicked()
{
    ui->pushButton_11->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[9] = color_num;
}

void Solver::on_pushButton_12_clicked()
{
    ui->pushButton_12->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[17] = color_num;
}
void Solver::on_pushButton_13_clicked()
{
    ui->pushButton_13->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[16] = color_num;
}
void Solver::on_pushButton_15_clicked()
{
    ui->pushButton_15->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[18] = color_num;
}

void Solver::on_pushButton_16_clicked()
{
    ui->pushButton_16->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[2] = color_num;
}

void Solver::on_pushButton_17_clicked()
{
    ui->pushButton_17->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[1] = color_num;
}

void Solver::on_pushButton_18_clicked()
{
    ui->pushButton_18->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[4] = color_num;
}

void Solver::on_pushButton_19_clicked()
{
    ui->pushButton_19->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[21] = color_num;
}

void Solver::on_pushButton_20_clicked()
{
    ui->pushButton_20->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[12] = color_num;
}

void Solver::on_pushButton_21_clicked()
{
    ui->pushButton_21->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[18] = color_num;
}

void Solver::on_pushButton_22_clicked()
{
    ui->pushButton_22->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[14] = color_num;
}

void Solver::on_pushButton_24_clicked()
{
    ui->pushButton_24->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[10] = color_num;
}

void Solver::on_pushButton_25_clicked()
{
    ui->pushButton_25->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[12] = color_num;
}
void Solver::on_pushButton_26_clicked()
{
    ui->pushButton_26->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[8] = color_num;
}
void Solver::on_pushButton_27_clicked()
{
    ui->pushButton_27->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[15] = color_num;
}

void Solver::on_pushButton_28_clicked()
{
    ui->pushButton_28->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[0] = color_num;
}

void Solver::on_pushButton_29_clicked()
{
    ui->pushButton_29->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[0] = color_num;
}

void Solver::on_pushButton_30_clicked()
{
    ui->pushButton_30->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[3] = color_num;
}

void Solver::on_pushButton_31_clicked()
{
    ui->pushButton_31->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[6] = color_num;
}

void Solver::on_pushButton_33_clicked()
{
    ui->pushButton_33->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[2] = color_num;
}

void Solver::on_pushButton_34_clicked()
{
    ui->pushButton_34->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[9] = color_num;
}

void Solver::on_pushButton_35_clicked()
{
    ui->pushButton_35->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[4] = color_num;
}

void Solver::on_pushButton_36_clicked()
{
    ui->pushButton_36->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[6] = color_num;
}

void Solver::on_pushButton_37_clicked()
{
    ui->pushButton_37->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[16] = color_num;
}
void Solver::on_pushButton_38_clicked()
{
    ui->pushButton_38->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[11] = color_num;
}
void Solver::on_pushButton_39_clicked()
{
    ui->pushButton_39->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[20] = color_num;
}

void Solver::on_pushButton_40_clicked()
{
    ui->pushButton_40->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[19] = color_num;
}

void Solver::on_pushButton_42_clicked()
{
    ui->pushButton_42->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[21] = color_num;
}

void Solver::on_pushButton_43_clicked()
{
    ui->pushButton_43->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[5] = color_num;
}

void Solver::on_pushButton_44_clicked()
{
    ui->pushButton_44->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[3] = color_num;
}

void Solver::on_pushButton_45_clicked()
{
    ui->pushButton_45->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[7] = color_num;
}

void Solver::on_pushButton_46_clicked()
{
    ui->pushButton_46->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[19] = color_num;
}

void Solver::on_pushButton_47_clicked()
{
    ui->pushButton_47->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[13] = color_num;
}

void Solver::on_pushButton_48_clicked()
{
    ui->pushButton_48->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[23] = color_num;
}

void Solver::on_pushButton_49_clicked()
{
    ui->pushButton_49->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[20] = color_num;
}

void Solver::on_pushButton_51_clicked()
{
    ui->pushButton_51->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[22] = color_num;
}
void Solver::on_pushButton_52_clicked()
{
    ui->pushButton_52->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[8] = color_num;
}

void Solver::on_pushButton_53_clicked()
{
    ui->pushButton_53->setStyleSheet(button_color_stylesheet.c_str());
    color_of_edges[5] = color_num;
}

void Solver::on_pushButton_54_clicked()
{
    ui->pushButton_54->setStyleSheet(button_color_stylesheet.c_str());
    color_of_corners[10] = color_num;
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
    color_num = 4;
}

void Solver::on_orange_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: orange; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: orange; border: 2px solid black}");
    color_num = 5;
}

void Solver::on_white_button_clicked()
{
    button_color_stylesheet = "QPushButton{background-color: white; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: white; border: 2px solid black}");
    color_num = 6;
}

void Solver::on_solve_button_clicked()
{
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;
    typedef std::chrono::high_resolution_clock clock;
    auto start = clock::now();
    getCoords();
    if (completeCube() && validPattern())
    {
        solver.solveCube();
        displaySolution();
        auto end = clock::now();
        cout << duration_cast<nanoseconds>(end-start).count() << "ns\n" << endl;
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

    for (int i = 0; i < 20; i++)
    {
        random_moves[i] = dist(generator);
    }

    while (matching_moves == true)
    {
        matching_moves = false;
        for (int i = 0; i < 19; i++)
        {
            if (random_moves[i] == 0 || random_moves[i] == 1 || random_moves[i] == 2)
            {
                if (random_moves[i + 1] == 0 || random_moves[i + 1] == 1 || random_moves[i + 1] == 2)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
            if (random_moves[i] == 3 || random_moves[i] == 4 || random_moves[i] == 5)
            {
                if (random_moves[i + 1] == 3 || random_moves[i + 1] == 4 || random_moves[i + 1] == 5)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
            if (random_moves[i] == 6 || random_moves[i] == 7 || random_moves[i] == 8)
            {
                if (random_moves[i + 1] == 6 || random_moves[i + 1] == 7 || random_moves[i + 1] == 8)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
            if (random_moves[i] == 9 || random_moves[i] == 10 || random_moves[i] == 11)
            {
                if (random_moves[i + 1] == 9 || random_moves[i + 1] == 10 || random_moves[i + 1] == 11)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
            if (random_moves[i] == 12 || random_moves[i] == 13 || random_moves[i] == 14)
            {
                if (random_moves[i + 1] == 12 || random_moves[i + 1] == 13 || random_moves[i + 1] == 14)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
            if (random_moves[i] == 15 || random_moves[i] == 16 || random_moves[i] == 17)
            {
                if (random_moves[i + 1] == 15 || random_moves[i + 1] == 16 || random_moves[i + 1] == 17)
                {
                    random_moves[i] = dist(generator);
                    matching_moves = true;
                }
            }
        }
    }

    for (int i = 0; i < 20; i++)
    {
        switch(random_moves[i])
        {
        case(0):
            move_F();
            break;
        case(1):
            move_F2();
            break;
        case(2):
            move_Fi();
            break;
        case(3):
            move_L();
            break;
        case(4):
            move_L2();
            break;
        case(5):
            move_Li();
            break;
        case(6):
            move_U();
            break;
        case(7):
            move_U2();
            break;
        case(8):
            move_Ui();
            break;
        case(9):
            move_B();
            break;
        case(10):
            move_B2();
            break;
        case(11):
            move_Bi();
            break;
        case(12):
            move_R();
            break;
        case(13):
            move_R2();
            break;
        case(14):
            move_Ri();
            break;
        case(15):
            move_D();
            break;
        case(16):
            move_D2();
            break;
        case(17):
            move_Di();
            break;
        }
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
    solver.setStartingPattern(entered_pattern);
}

bool Solver::completeCube()
{
    int blue = 0;
    int red = 0;
    int yellow = 0;
    int green = 0;
    int orange = 0;
    int white = 0;

    for (int i = 0; i < 24; i++)
    {
        if (color_of_corners[i] == 1)
            blue++;
        if (color_of_corners[i] == 2)
            red++;
        if (color_of_corners[i] == 3)
            yellow++;
        if (color_of_corners[i] == 4)
            green++;
        if (color_of_corners[i] == 5)
            orange++;
        if (color_of_corners[i] == 6)
            white++;

        if (color_of_edges[i] == 1)
            blue++;
        if (color_of_edges[i] == 2)
            red++;
        if (color_of_edges[i] == 3)
            yellow++;
        if (color_of_edges[i] == 4)
            green++;
        if (color_of_edges[i] == 5)
            orange++;
        if (color_of_edges[i] == 6)
            white++;
    }

    if (blue != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored blue"));
        return false;
    }
    if (red != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored red"));
        return false;
    }
    if (yellow != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored yellow"));
        return false;
    }
    if (green != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored green"));
        return false;
    }
    if (orange != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored orange"));
        return false;
    }
    if (white != 8)
    {
        QMessageBox::information(this, tr("Error"), tr("There should be 9 tiles colored white"));
        return false;
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
        if (entered_pattern.corner_orientations[i] == 1)
        {
            inversions++;
        }
        if (entered_pattern.corner_orientations[i] == 2)
        {
            inversions += 2;
        }
    }
    if (inversions % 3 != 0)
    {
        QMessageBox::information(this, tr("Error"), tr("The corners have an invalid orientation"));
        return false;
    }

    inversions = 0;

    for (int i = 0; i < 12; i++)
    {
        if (entered_pattern.edge_orientations[i] == 1)
        {
            inversions++;
        }
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
    string temp = solver.getSolutionString();

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

void Solver::move_F()
{
    QString temp_corner1 = ui->pushButton_16->styleSheet();
    QString temp_corner2 = ui->pushButton_28->styleSheet();
    QString temp_corner3 = ui->pushButton_9->styleSheet();

    QString temp_edge1 = ui->pushButton_17->styleSheet();
    QString temp_edge2 = ui->pushButton_29->styleSheet();

    ui->pushButton_16->setStyleSheet(ui->pushButton_18->styleSheet());
    ui->pushButton_18->setStyleSheet(ui->pushButton_12->styleSheet());
    ui->pushButton_12->setStyleSheet(ui->pushButton_10->styleSheet());
    ui->pushButton_10->setStyleSheet(temp_corner1);

    ui->pushButton_28->setStyleSheet(ui->pushButton_43->styleSheet());
    ui->pushButton_43->setStyleSheet(ui->pushButton_27->styleSheet());
    ui->pushButton_27->setStyleSheet(ui->pushButton_3->styleSheet());
    ui->pushButton_3->setStyleSheet(temp_corner2);

    ui->pushButton_9->setStyleSheet(ui->pushButton_30->styleSheet());
    ui->pushButton_30->setStyleSheet(ui->pushButton_37->styleSheet());
    ui->pushButton_37->setStyleSheet(ui->pushButton_25->styleSheet());
    ui->pushButton_25->setStyleSheet(temp_corner3);

    ui->pushButton_17->setStyleSheet(ui->pushButton_15->styleSheet());
    ui->pushButton_15->setStyleSheet(ui->pushButton_11->styleSheet());
    ui->pushButton_11->setStyleSheet(ui->pushButton_13->styleSheet());
    ui->pushButton_13->setStyleSheet(temp_edge1);

    ui->pushButton_29->setStyleSheet(ui->pushButton_40->styleSheet());
    ui->pushButton_40->setStyleSheet(ui->pushButton_26->styleSheet());
    ui->pushButton_26->setStyleSheet(ui->pushButton_6->styleSheet());
    ui->pushButton_6->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[2];
    int cpy_c2 = color_of_corners[0];
    int cpy_c3 = color_of_corners[1];

    int cpy_e1 = color_of_edges[1];
    int cpy_e2 = color_of_edges[0];

    color_of_corners[2] = color_of_corners[4];
    color_of_corners[4] = color_of_corners[17];
    color_of_corners[17] = color_of_corners[13];
    color_of_corners[13] = cpy_c1;

    color_of_corners[0] = color_of_corners[5];
    color_of_corners[5] = color_of_corners[15];
    color_of_corners[15] = color_of_corners[14];
    color_of_corners[14] = cpy_c2;

    color_of_corners[1] = color_of_corners[3];
    color_of_corners[3] = color_of_corners[16];
    color_of_corners[16] = color_of_corners[12];
    color_of_corners[12] = cpy_c3;

    color_of_edges[1] = color_of_edges[18];
    color_of_edges[18] = color_of_edges[9];
    color_of_edges[9] = color_of_edges[16];
    color_of_edges[16] = cpy_e1;

    color_of_edges[0] = color_of_edges[19];
    color_of_edges[19] = color_of_edges[8];
    color_of_edges[8] = color_of_edges[17];
    color_of_edges[17] = cpy_e2;
}
void Solver::move_Fi()
{
    for (int i = 0; i < 3; i++)
    {
        move_F();
    }
}
void Solver::move_F2()
{
    move_F();
    move_F();
}

void Solver::move_L()
{
    QString temp_corner1 = ui->pushButton_7->styleSheet();
    QString temp_corner2 = ui->pushButton_34->styleSheet();
    QString temp_corner3 = ui->pushButton_54->styleSheet();

    QString temp_edge1 = ui->pushButton_8->styleSheet();
    QString temp_edge2 = ui->pushButton_31->styleSheet();

    ui->pushButton_7->setStyleSheet(ui->pushButton_9->styleSheet());
    ui->pushButton_9->setStyleSheet(ui->pushButton_3->styleSheet());
    ui->pushButton_3->setStyleSheet(ui->pushButton->styleSheet());
    ui->pushButton->setStyleSheet(temp_corner1);

    ui->pushButton_34->setStyleSheet(ui->pushButton_16->styleSheet());
    ui->pushButton_16->setStyleSheet(ui->pushButton_25->styleSheet());
    ui->pushButton_25->setStyleSheet(ui->pushButton_48->styleSheet());
    ui->pushButton_48->setStyleSheet(temp_corner2);

    ui->pushButton_54->setStyleSheet(ui->pushButton_28->styleSheet());
    ui->pushButton_28->setStyleSheet(ui->pushButton_10->styleSheet());
    ui->pushButton_10->setStyleSheet(ui->pushButton_19->styleSheet());
    ui->pushButton_19->setStyleSheet(temp_corner3);

    ui->pushButton_8->setStyleSheet(ui->pushButton_6->styleSheet());
    ui->pushButton_6->setStyleSheet(ui->pushButton_2->styleSheet());
    ui->pushButton_2->setStyleSheet(ui->pushButton_4->styleSheet());
    ui->pushButton_4->setStyleSheet(temp_edge1);

    ui->pushButton_31->setStyleSheet(ui->pushButton_13->styleSheet());
    ui->pushButton_13->setStyleSheet(ui->pushButton_22->styleSheet());
    ui->pushButton_22->setStyleSheet(ui->pushButton_51->styleSheet());
    ui->pushButton_51->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[11];
    int cpy_c2 = color_of_corners[9];
    int cpy_c3 = color_of_corners[10];

    int cpy_e1 = color_of_edges[7];
    int cpy_e2 = color_of_edges[6];

    color_of_corners[11] = color_of_corners[1];
    color_of_corners[1] = color_of_corners[14];
    color_of_corners[14] = color_of_corners[22];
    color_of_corners[22] = cpy_c1;

    color_of_corners[9] = color_of_corners[2];
    color_of_corners[2] = color_of_corners[12];
    color_of_corners[12] = color_of_corners[23];
    color_of_corners[23] = cpy_c2;

    color_of_corners[10] = color_of_corners[0];
    color_of_corners[0] = color_of_corners[13];
    color_of_corners[13] = color_of_corners[21];
    color_of_corners[21] = cpy_c3;

    color_of_edges[7] = color_of_edges[17];
    color_of_edges[17] = color_of_edges[15];
    color_of_edges[15] = color_of_edges[23];
    color_of_edges[23] = cpy_e1;

    color_of_edges[6] = color_of_edges[16];
    color_of_edges[16] = color_of_edges[14];
    color_of_edges[14] = color_of_edges[22];
    color_of_edges[22] = cpy_e2;
}
void Solver::move_Li()
{
    for (int i = 0; i < 3; i++)
    {
        move_L();
    }
}
void Solver::move_L2()
{
    move_L();
    move_L();
}

void Solver::move_U()
{
    QString temp_corner1 = ui->pushButton_25->styleSheet();
    QString temp_corner2 = ui->pushButton_10->styleSheet();
    QString temp_corner3 = ui->pushButton_3->styleSheet();

    QString temp_edge1 = ui->pushButton_26->styleSheet();
    QString temp_edge2 = ui->pushButton_11->styleSheet();

    ui->pushButton_25->setStyleSheet(ui->pushButton_27->styleSheet());
    ui->pushButton_27->setStyleSheet(ui->pushButton_21->styleSheet());
    ui->pushButton_21->setStyleSheet(ui->pushButton_19->styleSheet());
    ui->pushButton_19->setStyleSheet(temp_corner1);

    ui->pushButton_10->setStyleSheet(ui->pushButton_37->styleSheet());
    ui->pushButton_37->setStyleSheet(ui->pushButton_46->styleSheet());
    ui->pushButton_46->setStyleSheet(ui->pushButton->styleSheet());
    ui->pushButton->setStyleSheet(temp_corner2);

    ui->pushButton_3->setStyleSheet(ui->pushButton_12->styleSheet());
    ui->pushButton_12->setStyleSheet(ui->pushButton_39->styleSheet());
    ui->pushButton_39->setStyleSheet(ui->pushButton_48->styleSheet());
    ui->pushButton_48->setStyleSheet(temp_corner3);

    ui->pushButton_26->setStyleSheet(ui->pushButton_24->styleSheet());
    ui->pushButton_24->setStyleSheet(ui->pushButton_20->styleSheet());
    ui->pushButton_20->setStyleSheet(ui->pushButton_22->styleSheet());
    ui->pushButton_22->setStyleSheet(temp_edge1);

    ui->pushButton_11->setStyleSheet(ui->pushButton_38->styleSheet());
    ui->pushButton_38->setStyleSheet(ui->pushButton_47->styleSheet());
    ui->pushButton_47->setStyleSheet(ui->pushButton_2->styleSheet());
    ui->pushButton_2->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[12];
    int cpy_c2 = color_of_corners[13];
    int cpy_c3 = color_of_corners[14];

    int cpy_e1 = color_of_edges[8];
    int cpy_e2 = color_of_edges[9];

    color_of_corners[12] = color_of_corners[15];
    color_of_corners[15] = color_of_corners[18];
    color_of_corners[18] = color_of_corners[21];
    color_of_corners[21] = cpy_c1;

    color_of_corners[13] = color_of_corners[16];
    color_of_corners[16] = color_of_corners[19];
    color_of_corners[19] = color_of_corners[22];
    color_of_corners[22] = cpy_c2;

    color_of_corners[14] = color_of_corners[17];
    color_of_corners[17] = color_of_corners[20];
    color_of_corners[20] = color_of_corners[23];
    color_of_corners[23] = cpy_c3;

    color_of_edges[8] = color_of_edges[10];
    color_of_edges[10] = color_of_edges[12];
    color_of_edges[12] = color_of_edges[14];
    color_of_edges[14] = cpy_e1;

    color_of_edges[9] = color_of_edges[11];
    color_of_edges[11] = color_of_edges[13];
    color_of_edges[13] = color_of_edges[15];
    color_of_edges[15] = cpy_e2;
}
void Solver::move_Ui()
{
    for (int i = 0; i < 3; i++)
    {
        move_U();
    }
}
void Solver::move_U2()
{
    move_U();
    move_U();
}

void Solver::move_B()
{
    QString temp_corner1 = ui->pushButton_52->styleSheet();
    QString temp_corner2 = ui->pushButton_36->styleSheet();
    QString temp_corner3 = ui->pushButton_45->styleSheet();

    QString temp_edge1 = ui->pushButton_53->styleSheet();
    QString temp_edge2 = ui->pushButton_35->styleSheet();

    ui->pushButton_52->setStyleSheet(ui->pushButton_54->styleSheet());
    ui->pushButton_54->setStyleSheet(ui->pushButton_48->styleSheet());
    ui->pushButton_48->setStyleSheet(ui->pushButton_46->styleSheet());
    ui->pushButton_46->setStyleSheet(temp_corner1);

    ui->pushButton_36->setStyleSheet(ui->pushButton_7->styleSheet());
    ui->pushButton_7->setStyleSheet(ui->pushButton_19->styleSheet());
    ui->pushButton_19->setStyleSheet(ui->pushButton_39->styleSheet());
    ui->pushButton_39->setStyleSheet(temp_corner2);

    ui->pushButton_45->setStyleSheet(ui->pushButton_34->styleSheet());
    ui->pushButton_34->setStyleSheet(ui->pushButton->styleSheet());
    ui->pushButton->setStyleSheet(ui->pushButton_21->styleSheet());
    ui->pushButton_21->setStyleSheet(temp_corner3);

    ui->pushButton_53->setStyleSheet(ui->pushButton_51->styleSheet());
    ui->pushButton_51->setStyleSheet(ui->pushButton_47->styleSheet());
    ui->pushButton_47->setStyleSheet(ui->pushButton_49->styleSheet());
    ui->pushButton_49->setStyleSheet(temp_edge1);

    ui->pushButton_35->setStyleSheet(ui->pushButton_4->styleSheet());
    ui->pushButton_4->setStyleSheet(ui->pushButton_20->styleSheet());
    ui->pushButton_20->setStyleSheet(ui->pushButton_42->styleSheet());
    ui->pushButton_42->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[8];
    int cpy_c2 = color_of_corners[6];
    int cpy_c3 = color_of_corners[7];

    int cpy_e1 = color_of_edges[5];
    int cpy_e2 = color_of_edges[4];

    color_of_corners[8] = color_of_corners[10];
    color_of_corners[10] = color_of_corners[23];
    color_of_corners[23] = color_of_corners[19];
    color_of_corners[19] = cpy_c1;

    color_of_corners[6] = color_of_corners[11];
    color_of_corners[11] = color_of_corners[21];
    color_of_corners[21] = color_of_corners[20];
    color_of_corners[20] = cpy_c2;

    color_of_corners[7] = color_of_corners[9];
    color_of_corners[9] = color_of_corners[22];
    color_of_corners[22] = color_of_corners[18];
    color_of_corners[18] = cpy_c3;

    color_of_edges[5] = color_of_edges[22];
    color_of_edges[22] = color_of_edges[13];
    color_of_edges[13] = color_of_edges[20];
    color_of_edges[20] = cpy_e1;

    color_of_edges[4] = color_of_edges[23];
    color_of_edges[23] = color_of_edges[12];
    color_of_edges[12] = color_of_edges[21];
    color_of_edges[21] = cpy_e2;
}
void Solver::move_Bi()
{
    for (int i = 0; i < 3; i++)
    {
        move_B();
    }
}
void Solver::move_B2()
{
    move_B();
    move_B();
}

void Solver::move_R()
{
    QString temp_corner1 = ui->pushButton_43->styleSheet();
    QString temp_corner2 = ui->pushButton_30->styleSheet();
    QString temp_corner3 = ui->pushButton_18->styleSheet();

    QString temp_edge1 = ui->pushButton_44->styleSheet();
    QString temp_edge2 = ui->pushButton_33->styleSheet();

    ui->pushButton_43->setStyleSheet(ui->pushButton_45->styleSheet());
    ui->pushButton_45->setStyleSheet(ui->pushButton_39->styleSheet());
    ui->pushButton_39->setStyleSheet(ui->pushButton_37->styleSheet());
    ui->pushButton_37->setStyleSheet(temp_corner1);

    ui->pushButton_30->setStyleSheet(ui->pushButton_52->styleSheet());
    ui->pushButton_52->setStyleSheet(ui->pushButton_21->styleSheet());
    ui->pushButton_21->setStyleSheet(ui->pushButton_12->styleSheet());
    ui->pushButton_12->setStyleSheet(temp_corner2);

    ui->pushButton_18->setStyleSheet(ui->pushButton_36->styleSheet());
    ui->pushButton_36->setStyleSheet(ui->pushButton_46->styleSheet());
    ui->pushButton_46->setStyleSheet(ui->pushButton_27->styleSheet());
    ui->pushButton_27->setStyleSheet(temp_corner3);

    ui->pushButton_44->setStyleSheet(ui->pushButton_42->styleSheet());
    ui->pushButton_42->setStyleSheet(ui->pushButton_38->styleSheet());
    ui->pushButton_38->setStyleSheet(ui->pushButton_40->styleSheet());
    ui->pushButton_40->setStyleSheet(temp_edge1);

    ui->pushButton_33->setStyleSheet(ui->pushButton_49->styleSheet());
    ui->pushButton_49->setStyleSheet(ui->pushButton_24->styleSheet());
    ui->pushButton_24->setStyleSheet(ui->pushButton_15->styleSheet());
    ui->pushButton_15->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[5];
    int cpy_c2 = color_of_corners[3];
    int cpy_c3 = color_of_corners[4];

    int cpy_e1 = color_of_edges[3];
    int cpy_e2 = color_of_edges[2];

    color_of_corners[5] = color_of_corners[7];
    color_of_corners[7] = color_of_corners[20];
    color_of_corners[20] = color_of_corners[16];
    color_of_corners[16] = cpy_c1;

    color_of_corners[3] = color_of_corners[8];
    color_of_corners[8] = color_of_corners[18];
    color_of_corners[18] = color_of_corners[17];
    color_of_corners[17] = cpy_c2;

    color_of_corners[4] = color_of_corners[6];
    color_of_corners[6] = color_of_corners[19];
    color_of_corners[19] = color_of_corners[15];
    color_of_corners[15] = cpy_c3;

    color_of_edges[3] = color_of_edges[21];
    color_of_edges[21] = color_of_edges[11];
    color_of_edges[11] = color_of_edges[19];
    color_of_edges[19] = cpy_e1;

    color_of_edges[2] = color_of_edges[20];
    color_of_edges[20] = color_of_edges[10];
    color_of_edges[10] = color_of_edges[18];
    color_of_edges[18] = cpy_e2;
}
void Solver::move_Ri()
{
    for (int i = 0; i < 3; i++)
    {
        move_R();
    }
}
void Solver::move_R2()
{
    move_R();
    move_R();
}

void Solver::move_D()
{
    QString temp_corner1 = ui->pushButton_34->styleSheet();
    QString temp_corner2 = ui->pushButton_54->styleSheet();
    QString temp_corner3 = ui->pushButton_7->styleSheet();

    QString temp_edge1 = ui->pushButton_35->styleSheet();
    QString temp_edge2 = ui->pushButton_53->styleSheet();

    ui->pushButton_34->setStyleSheet(ui->pushButton_36->styleSheet());
    ui->pushButton_36->setStyleSheet(ui->pushButton_30->styleSheet());
    ui->pushButton_30->setStyleSheet(ui->pushButton_28->styleSheet());
    ui->pushButton_28->setStyleSheet(temp_corner1);

    ui->pushButton_54->setStyleSheet(ui->pushButton_45->styleSheet());
    ui->pushButton_45->setStyleSheet(ui->pushButton_18->styleSheet());
    ui->pushButton_18->setStyleSheet(ui->pushButton_9->styleSheet());
    ui->pushButton_9->setStyleSheet(temp_corner2);

    ui->pushButton_7->setStyleSheet(ui->pushButton_52->styleSheet());
    ui->pushButton_52->setStyleSheet(ui->pushButton_43->styleSheet());
    ui->pushButton_43->setStyleSheet(ui->pushButton_16->styleSheet());
    ui->pushButton_16->setStyleSheet(temp_corner3);

    ui->pushButton_35->setStyleSheet(ui->pushButton_33->styleSheet());
    ui->pushButton_33->setStyleSheet(ui->pushButton_29->styleSheet());
    ui->pushButton_29->setStyleSheet(ui->pushButton_31->styleSheet());
    ui->pushButton_31->setStyleSheet(temp_edge1);

    ui->pushButton_53->setStyleSheet(ui->pushButton_44->styleSheet());
    ui->pushButton_44->setStyleSheet(ui->pushButton_17->styleSheet());
    ui->pushButton_17->setStyleSheet(ui->pushButton_8->styleSheet());
    ui->pushButton_8->setStyleSheet(temp_edge2);

    int cpy_c1 = color_of_corners[9];
    int cpy_c2 = color_of_corners[10];
    int cpy_c3 = color_of_corners[11];

    int cpy_e1 = color_of_edges[4];
    int cpy_e2 = color_of_edges[5];

    color_of_corners[9] = color_of_corners[6];
    color_of_corners[6] = color_of_corners[3];
    color_of_corners[3] = color_of_corners[0];
    color_of_corners[0] = cpy_c1;

    color_of_corners[10] = color_of_corners[7];
    color_of_corners[7] = color_of_corners[4];
    color_of_corners[4] = color_of_corners[1];
    color_of_corners[1] = cpy_c2;

    color_of_corners[11] = color_of_corners[8];
    color_of_corners[8] = color_of_corners[5];
    color_of_corners[5] = color_of_corners[2];
    color_of_corners[2] = cpy_c3;

    color_of_edges[4] = color_of_edges[2];
    color_of_edges[2] = color_of_edges[0];
    color_of_edges[0] = color_of_edges[6];
    color_of_edges[6] = cpy_e1;

    color_of_edges[5] = color_of_edges[3];
    color_of_edges[3] = color_of_edges[1];
    color_of_edges[1] = color_of_edges[7];
    color_of_edges[7] = cpy_e2;
}
void Solver::move_Di()
{
    for (int i = 0; i < 3; i++)
    {
        move_D();
    }
}
void Solver::move_D2()
{
    move_D();
    move_D();
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

void Solver::on_fF_clicked()
{
    move_F();
}

void Solver::on_fF2_clicked()
{
    move_F2();
}

void Solver::on_L_button_clicked()
{
    move_L();
}

void Solver::on_U_button_clicked()
{
    move_U();
}

void Solver::on_B_button_clicked()
{
    move_B();
}

void Solver::on_R_button_clicked()
{
    move_R();
}

void Solver::on_D_button_clicked()
{
    move_D();
}

void Solver::on_L2_button_clicked()
{
    move_L2();
}

void Solver::on_U2_button_clicked()
{
    move_U2();
}

void Solver::on_B2_button_clicked()
{
    move_B2();
}

void Solver::on_R2_button_clicked()
{
    move_R2();
}

void Solver::on_D2_button_clicked()
{
    move_D2();
}

void Solver::on_Fi_button_clicked()
{
    move_Fi();
}

void Solver::on_Li_button_clicked()
{
    move_Li();
}

void Solver::on_Ui_button_clicked()
{
    move_Ui();
}

void Solver::on_Bi_button_clicked()
{
    move_Bi();
}

void Solver::on_Ri_button_clicked()
{
    move_Ri();
}

void Solver::on_Di_button_clicked()
{
    move_Di();
}

void Solver::on_solved_cube_clicked()
{
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

