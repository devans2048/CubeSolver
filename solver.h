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
    void connectSignals();
    void setupFaceTurnButtons();

    void getCoords();
    bool validPattern();
    bool completeCube();
    void displaySolution();


    void colorCubeTiles();
signals:
    //emits an int denoting the face of one of 24 edge or corner faces so that the selected color can be applied
    void cubePieceTileClicked(int piece_face_num);

private slots:
    void makeFaceTurn(int face_to_turn, int direction);
    void changeCornerTileColor(int);
    void changeEdgeTileColor(int);

    void on_blue_button_clicked();

    void on_red_button_clicked();

    void on_yellow_button_clicked();

    void on_green_button_clicked();

    void on_orange_button_clicked();

    void on_white_button_clicked();


    void on_solve_button_clicked();

    void on_reset_cube_clicked();

    void on_random_pattern_clicked();

    void on_solved_cube_clicked();
private:
    Ui::Solver *ui;
    Cube * solver;
    //Cube cube;
    const int CORNER_BUTTON_LOCATIONS_X[24] = {};
    const int CORNER_BUTTON_LOCATIONS_Y[24] = {};
    const int EDGE_BUTTON_LOCATIONS_X[24] = {};
    const int EDGE_BUTTON_LOCATIONS_Y[24] = {};
    QPushButton * corners[24];
    QPushButton * edges[24];
    QPushButton * face_turn_buttons[18];

    std::string button_color_stylesheet = "";
    int color_num = 0;
    int color_of_corners[24];
    int color_of_edges[24];
    int random_moves[20];

    int solution_move_strings_face_turns[4];
    int solution_move_strings_directions[4];
    pattern entered_pattern;
};
#endif // SOLVER_H
