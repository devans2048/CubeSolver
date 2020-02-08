#include "solver.h"
#include "ui_solver.h"
#include <QTextBrowser>
#include <QMessageBox>
#include <random>
#include <ctime>
#include <chrono>

Solver::Solver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Solver)
{
    ui->setupUi(this);
    //cube = new Cube();
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

void Solver::on_pushButton_clicked()
{
    ui->pushButton->setStyleSheet(color.c_str());
    corners[22] = color_num;
}

void Solver::on_pushButton_2_clicked()
{
    ui->pushButton_2->setStyleSheet(color.c_str());
    edges[15] = color_num;
}

void Solver::on_pushButton_3_clicked()
{
    ui->pushButton_3->setStyleSheet(color.c_str());
    corners[14] = color_num;
}

void Solver::on_pushButton_4_clicked()
{
    ui->pushButton_4->setStyleSheet(color.c_str());
    edges[23] = color_num;
}

void Solver::on_pushButton_6_clicked()
{
    ui->pushButton_6->setStyleSheet(color.c_str());
    edges[17] = color_num;
}

void Solver::on_pushButton_7_clicked()
{
    ui->pushButton_7->setStyleSheet(color.c_str());
    corners[11] = color_num;
}

void Solver::on_pushButton_8_clicked()
{
    ui->pushButton_8->setStyleSheet(color.c_str());
    edges[7] = color_num;
}

void Solver::on_pushButton_9_clicked()
{
    ui->pushButton_9->setStyleSheet(color.c_str());
    corners[1] = color_num;
}

void Solver::on_pushButton_10_clicked()
{
    ui->pushButton_10->setStyleSheet(color.c_str());
    corners[13] = color_num;
}

void Solver::on_pushButton_11_clicked()
{
    ui->pushButton_11->setStyleSheet(color.c_str());
    edges[9] = color_num;
}

void Solver::on_pushButton_12_clicked()
{
    ui->pushButton_12->setStyleSheet(color.c_str());
    corners[17] = color_num;
}
void Solver::on_pushButton_13_clicked()
{
    ui->pushButton_13->setStyleSheet(color.c_str());
    edges[16] = color_num;
}
void Solver::on_pushButton_15_clicked()
{
    ui->pushButton_15->setStyleSheet(color.c_str());
    edges[18] = color_num;
}

void Solver::on_pushButton_16_clicked()
{
    ui->pushButton_16->setStyleSheet(color.c_str());
    corners[2] = color_num;
}

void Solver::on_pushButton_17_clicked()
{
    ui->pushButton_17->setStyleSheet(color.c_str());
    edges[1] = color_num;
}

void Solver::on_pushButton_18_clicked()
{
    ui->pushButton_18->setStyleSheet(color.c_str());
    corners[4] = color_num;
}

void Solver::on_pushButton_19_clicked()
{
    ui->pushButton_19->setStyleSheet(color.c_str());
    corners[21] = color_num;
}

void Solver::on_pushButton_20_clicked()
{
    ui->pushButton_20->setStyleSheet(color.c_str());
    edges[12] = color_num;
}

void Solver::on_pushButton_21_clicked()
{
    ui->pushButton_21->setStyleSheet(color.c_str());
    corners[18] = color_num;
}

void Solver::on_pushButton_22_clicked()
{
    ui->pushButton_22->setStyleSheet(color.c_str());
    edges[14] = color_num;
}

void Solver::on_pushButton_24_clicked()
{
    ui->pushButton_24->setStyleSheet(color.c_str());
    edges[10] = color_num;
}

void Solver::on_pushButton_25_clicked()
{
    ui->pushButton_25->setStyleSheet(color.c_str());
    corners[12] = color_num;
}
void Solver::on_pushButton_26_clicked()
{
    ui->pushButton_26->setStyleSheet(color.c_str());
    edges[8] = color_num;
}
void Solver::on_pushButton_27_clicked()
{
    ui->pushButton_27->setStyleSheet(color.c_str());
    corners[15] = color_num;
}

void Solver::on_pushButton_28_clicked()
{
    ui->pushButton_28->setStyleSheet(color.c_str());
    corners[0] = color_num;
}

void Solver::on_pushButton_29_clicked()
{
    ui->pushButton_29->setStyleSheet(color.c_str());
    edges[0] = color_num;
}

void Solver::on_pushButton_30_clicked()
{
    ui->pushButton_30->setStyleSheet(color.c_str());
    corners[3] = color_num;
}

void Solver::on_pushButton_31_clicked()
{
    ui->pushButton_31->setStyleSheet(color.c_str());
    edges[6] = color_num;
}

void Solver::on_pushButton_33_clicked()
{
    ui->pushButton_33->setStyleSheet(color.c_str());
    edges[2] = color_num;
}

void Solver::on_pushButton_34_clicked()
{
    ui->pushButton_34->setStyleSheet(color.c_str());
    corners[9] = color_num;
}

void Solver::on_pushButton_35_clicked()
{
    ui->pushButton_35->setStyleSheet(color.c_str());
    edges[4] = color_num;
}

void Solver::on_pushButton_36_clicked()
{
    ui->pushButton_36->setStyleSheet(color.c_str());
    corners[6] = color_num;
}

void Solver::on_pushButton_37_clicked()
{
    ui->pushButton_37->setStyleSheet(color.c_str());
    corners[16] = color_num;
}
void Solver::on_pushButton_38_clicked()
{
    ui->pushButton_38->setStyleSheet(color.c_str());
    edges[11] = color_num;
}
void Solver::on_pushButton_39_clicked()
{
    ui->pushButton_39->setStyleSheet(color.c_str());
    corners[20] = color_num;
}

void Solver::on_pushButton_40_clicked()
{
    ui->pushButton_40->setStyleSheet(color.c_str());
    edges[19] = color_num;
}

void Solver::on_pushButton_42_clicked()
{
    ui->pushButton_42->setStyleSheet(color.c_str());
    edges[21] = color_num;
}

void Solver::on_pushButton_43_clicked()
{
    ui->pushButton_43->setStyleSheet(color.c_str());
    corners[5] = color_num;
}

void Solver::on_pushButton_44_clicked()
{
    ui->pushButton_44->setStyleSheet(color.c_str());
    edges[3] = color_num;
}

void Solver::on_pushButton_45_clicked()
{
    ui->pushButton_45->setStyleSheet(color.c_str());
    corners[7] = color_num;
}

void Solver::on_pushButton_46_clicked()
{
    ui->pushButton_46->setStyleSheet(color.c_str());
    corners[19] = color_num;
}

void Solver::on_pushButton_47_clicked()
{
    ui->pushButton_47->setStyleSheet(color.c_str());
    edges[13] = color_num;
}

void Solver::on_pushButton_48_clicked()
{
    ui->pushButton_48->setStyleSheet(color.c_str());
    corners[23] = color_num;
}

void Solver::on_pushButton_49_clicked()
{
    ui->pushButton_49->setStyleSheet(color.c_str());
    edges[20] = color_num;
}

void Solver::on_pushButton_51_clicked()
{
    ui->pushButton_51->setStyleSheet(color.c_str());
    edges[22] = color_num;
}
void Solver::on_pushButton_52_clicked()
{
    ui->pushButton_52->setStyleSheet(color.c_str());
    corners[8] = color_num;
}

void Solver::on_pushButton_53_clicked()
{
    ui->pushButton_53->setStyleSheet(color.c_str());
    edges[5] = color_num;
}

void Solver::on_pushButton_54_clicked()
{
    ui->pushButton_54->setStyleSheet(color.c_str());
    corners[10] = color_num;
}

void Solver::on_blue_button_clicked()
{
    color = "QPushButton{background-color: blue; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: blue; border: 2px solid black}");
    color_num = 1;
}

void Solver::on_red_button_clicked()
{
    color = "QPushButton{background-color: red; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: red; border: 2px solid black}");
    color_num = 2;
}

void Solver::on_yellow_button_clicked()
{
    color = "QPushButton{background-color: yellow; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: yellow; border: 2px solid black}");
    color_num = 3;
}

void Solver::on_green_button_clicked()
{
    color = "QPushButton{background-color: green; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: green; border: 2px solid black}");
    color_num = 4;
}

void Solver::on_orange_button_clicked()
{
    color = "QPushButton{background-color: orange; border: 1px solid black}";
    ui->pushButton_64->setStyleSheet("QPushButton{background-color: orange; border: 2px solid black}");
    color_num = 5;
}

void Solver::on_white_button_clicked()
{
    color = "QPushButton{background-color: white; border: 1px solid black}";
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
    ui->pushButton->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_2->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_3->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_4->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_6->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_7->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_8->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_9->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_10->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_11->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_12->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_13->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_15->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_16->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_17->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_18->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_19->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_20->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_21->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_22->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_24->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_25->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_26->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_27->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_28->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_29->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_30->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_31->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_33->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_34->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_35->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_36->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_37->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_38->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_39->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_40->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_42->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_43->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_44->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_45->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_46->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_47->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_48->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_49->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_51->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_52->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_53->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_54->setStyleSheet("background-color: rgb(200, 200, 200); border: 1px solid black");
    ui->pushButton_64->setStyleSheet("background-color: rgb(200, 200, 200); border: 2px solid black");

    color_num = 0;
    color = "";

    for (int i = 0; i < 24; i++)
    {
        corners[i] = 0;
        edges[i] = 0;
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

    for (i = 0; i < 24; i++)
    {
        if (corners[i] == 3 || corners[i] == 6)
        {
            entered_pattern.corner_orientations[i / 3] = (i % 3);
        }
    }

    for (i = 0; i < 24; i += 2)
    {
        if (edges[i] == 3 || edges[i] == 6)
            entered_pattern.edge_orientations[i / 2] = 0;
        if (edges[i + 1] == 3 || edges[i + 1] == 6)
            entered_pattern.edge_orientations[i / 2] = 1;
        if ((edges[i] == 1 || edges[i] == 4) && edges[i + 1] != 3 && edges[i + 1] != 6)
            entered_pattern.edge_orientations[i / 2] = 1;
        if ((edges[i] == 2 || edges[i] == 5) && edges[i + 1] != 3 && edges[i + 1] != 6)
            entered_pattern.edge_orientations[i / 2] = 0;
    }

    for (i = 0; i < 24; i += 3)
    {
        if (corners[i] == 3 || corners[i +1] == 3 || corners[i + 2] == 3)
        {
            if (corners[i] == 1 || corners[i + 1] == 1 || corners[i + 2] == 1 )
            {
                if (corners[i] == 2 || corners[i + 1] == 2 || corners[i + 2] == 2)
                {
                    entered_pattern.cornerPerm[i / 3] = '5';
                }
                else
                    entered_pattern.cornerPerm[i / 3] = '8';
            }
            if (corners[i] == 4 || corners[i + 1] == 4 || corners[i + 2] == 4)
            {
                if (corners[i] == 2 || corners[i + 1] == 2 || corners[i + 2] == 2)
                {
                    entered_pattern.cornerPerm[i / 3] = '6';
                }
                else
                    entered_pattern.cornerPerm[i / 3] = '7';
            }
        }
        if (corners[i] == 6 || corners[i +1] == 6 || corners[i + 2] == 6)
        {
            if (corners[i] == 1 || corners[i + 1] == 1 || corners[i + 2] == 1 )
            {
                if (corners[i] == 2 || corners[i + 1] == 2 || corners[i + 2] == 2)
                {
                    entered_pattern.cornerPerm[i / 3] = '1';
                }
                else
                    entered_pattern.cornerPerm[i / 3] = '4';
            }
            if (corners[i] == 4 || corners[i + 1] == 4 || corners[i + 2] == 4)
            {
                if (corners[i] == 2 || corners[i + 1] == 2 || corners[i + 2] == 2)
                {
                    entered_pattern.cornerPerm[i / 3] = '2';
                }
                else
                    entered_pattern.cornerPerm[i / 3] = '3';
            }
        }
    }

    for (i = 0; i < 24; i += 2)
    {
        if (edges[i] == 3 || edges[i + 1] == 3)
        {
            if (edges[i] == 1 || edges[i + 1] == 1)
                entered_pattern.edgePerm[i / 2] = '8';
            if (edges[i] == 2 || edges[i + 1] == 2)
                entered_pattern.edgePerm[i / 2] = '5';
            if (edges[i] == 4 || edges[i + 1] == 4)
                entered_pattern.edgePerm[i / 2] = '6';
            if (edges[i] == 5 || edges[i + 1] == 5)
                entered_pattern.edgePerm[i / 2] = '7';
        }

        if (edges[i] == 6 || edges[i + 1] == 6)
        {
            if (edges[i] == 1 || edges[i + 1] == 1)
                entered_pattern.edgePerm[i / 2] = '4';
            if (edges[i] == 2 || edges[i + 1] == 2)
                entered_pattern.edgePerm[i / 2] = '1';
            if (edges[i] == 4 || edges[i + 1] == 4)
                entered_pattern.edgePerm[i / 2] = '2';
            if (edges[i] == 5 || edges[i + 1] == 5)
                entered_pattern.edgePerm[i / 2] = '3';
        }

        if (edges[i] == 1 || edges[i + 1] == 1)
        {
            if (edges[i] == 2 || edges[i + 1] == 2)
                entered_pattern.edgePerm[i / 2] = '9';
            if (edges[i] == 5 || edges[i + 1] == 5)
                entered_pattern.edgePerm[i / 2] = 'C';
        }

        if (edges[i] == 4 || edges[i + 1] == 4)
        {
            if (edges[i] == 2 || edges[i + 1] == 2)
                entered_pattern.edgePerm[i / 2] = 'A';
            if (edges[i] == 5 || edges[i + 1] == 5)
                entered_pattern.edgePerm[i / 2] = 'B';
        }
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
        if (corners[i] == 1)
            blue++;
        if (corners[i] == 2)
            red++;
        if (corners[i] == 3)
            yellow++;
        if (corners[i] == 4)
            green++;
        if (corners[i] == 5)
            orange++;
        if (corners[i] == 6)
            white++;

        if (edges[i] == 1)
            blue++;
        if (edges[i] == 2)
            red++;
        if (edges[i] == 3)
            yellow++;
        if (edges[i] == 4)
            green++;
        if (edges[i] == 5)
            orange++;
        if (edges[i] == 6)
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

    int cpy_c1 = corners[2];
    int cpy_c2 = corners[0];
    int cpy_c3 = corners[1];

    int cpy_e1 = edges[1];
    int cpy_e2 = edges[0];

    corners[2] = corners[4];
    corners[4] = corners[17];
    corners[17] = corners[13];
    corners[13] = cpy_c1;

    corners[0] = corners[5];
    corners[5] = corners[15];
    corners[15] = corners[14];
    corners[14] = cpy_c2;

    corners[1] = corners[3];
    corners[3] = corners[16];
    corners[16] = corners[12];
    corners[12] = cpy_c3;

    edges[1] = edges[18];
    edges[18] = edges[9];
    edges[9] = edges[16];
    edges[16] = cpy_e1;

    edges[0] = edges[19];
    edges[19] = edges[8];
    edges[8] = edges[17];
    edges[17] = cpy_e2;
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

    int cpy_c1 = corners[11];
    int cpy_c2 = corners[9];
    int cpy_c3 = corners[10];

    int cpy_e1 = edges[7];
    int cpy_e2 = edges[6];

    corners[11] = corners[1];
    corners[1] = corners[14];
    corners[14] = corners[22];
    corners[22] = cpy_c1;

    corners[9] = corners[2];
    corners[2] = corners[12];
    corners[12] = corners[23];
    corners[23] = cpy_c2;

    corners[10] = corners[0];
    corners[0] = corners[13];
    corners[13] = corners[21];
    corners[21] = cpy_c3;

    edges[7] = edges[17];
    edges[17] = edges[15];
    edges[15] = edges[23];
    edges[23] = cpy_e1;

    edges[6] = edges[16];
    edges[16] = edges[14];
    edges[14] = edges[22];
    edges[22] = cpy_e2;
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

    int cpy_c1 = corners[12];
    int cpy_c2 = corners[13];
    int cpy_c3 = corners[14];

    int cpy_e1 = edges[8];
    int cpy_e2 = edges[9];

    corners[12] = corners[15];
    corners[15] = corners[18];
    corners[18] = corners[21];
    corners[21] = cpy_c1;

    corners[13] = corners[16];
    corners[16] = corners[19];
    corners[19] = corners[22];
    corners[22] = cpy_c2;

    corners[14] = corners[17];
    corners[17] = corners[20];
    corners[20] = corners[23];
    corners[23] = cpy_c3;

    edges[8] = edges[10];
    edges[10] = edges[12];
    edges[12] = edges[14];
    edges[14] = cpy_e1;

    edges[9] = edges[11];
    edges[11] = edges[13];
    edges[13] = edges[15];
    edges[15] = cpy_e2;
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

    int cpy_c1 = corners[8];
    int cpy_c2 = corners[6];
    int cpy_c3 = corners[7];

    int cpy_e1 = edges[5];
    int cpy_e2 = edges[4];

    corners[8] = corners[10];
    corners[10] = corners[23];
    corners[23] = corners[19];
    corners[19] = cpy_c1;

    corners[6] = corners[11];
    corners[11] = corners[21];
    corners[21] = corners[20];
    corners[20] = cpy_c2;

    corners[7] = corners[9];
    corners[9] = corners[22];
    corners[22] = corners[18];
    corners[18] = cpy_c3;

    edges[5] = edges[22];
    edges[22] = edges[13];
    edges[13] = edges[20];
    edges[20] = cpy_e1;

    edges[4] = edges[23];
    edges[23] = edges[12];
    edges[12] = edges[21];
    edges[21] = cpy_e2;
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

    int cpy_c1 = corners[5];
    int cpy_c2 = corners[3];
    int cpy_c3 = corners[4];

    int cpy_e1 = edges[3];
    int cpy_e2 = edges[2];

    corners[5] = corners[7];
    corners[7] = corners[20];
    corners[20] = corners[16];
    corners[16] = cpy_c1;

    corners[3] = corners[8];
    corners[8] = corners[18];
    corners[18] = corners[17];
    corners[17] = cpy_c2;

    corners[4] = corners[6];
    corners[6] = corners[19];
    corners[19] = corners[15];
    corners[15] = cpy_c3;

    edges[3] = edges[21];
    edges[21] = edges[11];
    edges[11] = edges[19];
    edges[19] = cpy_e1;

    edges[2] = edges[20];
    edges[20] = edges[10];
    edges[10] = edges[18];
    edges[18] = cpy_e2;
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

    int cpy_c1 = corners[9];
    int cpy_c2 = corners[10];
    int cpy_c3 = corners[11];

    int cpy_e1 = edges[4];
    int cpy_e2 = edges[5];

    corners[9] = corners[6];
    corners[6] = corners[3];
    corners[3] = corners[0];
    corners[0] = cpy_c1;

    corners[10] = corners[7];
    corners[7] = corners[4];
    corners[4] = corners[1];
    corners[1] = cpy_c2;

    corners[11] = corners[8];
    corners[8] = corners[5];
    corners[5] = corners[2];
    corners[2] = cpy_c3;

    edges[4] = edges[2];
    edges[2] = edges[0];
    edges[0] = edges[6];
    edges[6] = cpy_e1;

    edges[5] = edges[3];
    edges[3] = edges[1];
    edges[1] = edges[7];
    edges[7] = cpy_e2;
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
    on_blue_button_clicked();
    on_pushButton_clicked();

    on_pushButton_2_clicked();

    on_pushButton_3_clicked();

    on_pushButton_4_clicked();

    on_pushButton_6_clicked();

    on_pushButton_7_clicked();

    on_pushButton_8_clicked();

    on_pushButton_9_clicked();

    on_red_button_clicked();
    on_pushButton_10_clicked();

    on_pushButton_11_clicked();

    on_pushButton_12_clicked();

    on_pushButton_13_clicked();

    on_pushButton_15_clicked();

    on_pushButton_16_clicked();

    on_pushButton_17_clicked();

    on_pushButton_18_clicked();

    on_yellow_button_clicked();
    on_pushButton_19_clicked();

    on_pushButton_20_clicked();

    on_pushButton_21_clicked();

    on_pushButton_22_clicked();

    on_pushButton_24_clicked();

    on_pushButton_25_clicked();

    on_pushButton_26_clicked();

    on_pushButton_27_clicked();

    on_white_button_clicked();
    on_pushButton_28_clicked();

    on_pushButton_29_clicked();

    on_pushButton_30_clicked();

    on_pushButton_31_clicked();

    on_pushButton_33_clicked();

    on_pushButton_34_clicked();

    on_pushButton_35_clicked();

    on_pushButton_36_clicked();

    on_green_button_clicked();
    on_pushButton_37_clicked();

    on_pushButton_38_clicked();

    on_pushButton_39_clicked();

    on_pushButton_40_clicked();

    on_pushButton_42_clicked();

    on_pushButton_43_clicked();

    on_pushButton_44_clicked();

    on_pushButton_45_clicked();

    on_orange_button_clicked();
    on_pushButton_46_clicked();

    on_pushButton_47_clicked();

    on_pushButton_48_clicked();

    on_pushButton_49_clicked();

    on_pushButton_51_clicked();

    on_pushButton_52_clicked();

    on_pushButton_53_clicked();

    on_pushButton_54_clicked();

    ui->pushButton_64->setStyleSheet("background-color: rgb(200, 200, 200); border: 2px solid black");

    color_num = 0;
    color = "";

}

