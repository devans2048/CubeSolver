#ifndef SOLVER_H
#define SOLVER_H

#include <QMainWindow>
#include <QTextBrowser>
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

    void show_exception_bad_alloc();
    void show_exception_io_error(const char* fileName);
    void show_exception_timeout();

    void getCoords();
    bool validPattern();
    bool completeCube();
    void displaySolution();

    void move_F();
    void move_Fi();
    void move_F2();

    void move_L();
    void move_Li();
    void move_L2();

    void move_U();
    void move_Ui();
    void move_U2();

    void move_B();
    void move_Bi();
    void move_B2();

    void move_R();
    void move_Ri();
    void move_R2();

    void move_D();
    void move_Di();
    void move_D2();

    Cube solver;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();


    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();


    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();


    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();


    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();


    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();


    void on_blue_button_clicked();

    void on_red_button_clicked();

    void on_yellow_button_clicked();

    void on_green_button_clicked();

    void on_orange_button_clicked();

    void on_white_button_clicked();


    void on_solve_button_clicked();

    void on_reset_cube_clicked();

    void on_random_pattern_clicked();


    void on_fF_clicked();

    void on_fF2_clicked();

    void on_L_button_clicked();

    void on_U_button_clicked();

    void on_B_button_clicked();

    void on_R_button_clicked();

    void on_D_button_clicked();


    void on_L2_button_clicked();

    void on_U2_button_clicked();

    void on_B2_button_clicked();

    void on_R2_button_clicked();

    void on_D2_button_clicked();

    void on_Fi_button_clicked();

    void on_Li_button_clicked();

    void on_Ui_button_clicked();

    void on_Bi_button_clicked();

    void on_Ri_button_clicked();

    void on_Di_button_clicked();

    void on_solved_cube_clicked();
private:
    Ui::Solver *ui;
    //Cube cube;

    std::string color = "";
    int color_num = 0;
    int corners[24];
    int edges[24];
    int random_moves[20];

    int solution_move_strings_face_turns[4];
    int solution_move_strings_directions[4];
    pattern entered_pattern;
};
#endif // SOLVER_H
