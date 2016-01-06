#include <iostream>

enum class Mark { X, O, EMPTY, TIE };

class Board {
public:
    Board();

    void printBoard();

    void setCheck(int x, int y, Mark mark);
    Mark checkWinner();

private:
    static const int m_width = 3;
    static const int m_height = 3;
    Mark m_marks[m_width][m_height];

    void clearBoard();
};

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    Board board;

    board.printBoard();

    board.setCheck(0, 0, Mark::X);
    board.printBoard();
    board.setCheck(1, 1, Mark::X);
    board.printBoard();
    board.setCheck(1, 2, Mark::O);
    board.printBoard();
    board.setCheck(1, 3, Mark::X);
    board.printBoard();
    board.setCheck(2, 1, Mark::O);
    board.printBoard();
    board.setCheck(3, 1, Mark::X);
    board.printBoard();
    board.setCheck(2, 2, Mark::O);
    board.printBoard();
    board.setCheck(3, 3, Mark::X);
    board.printBoard();
    printf("%d\n", board.checkWinner());

    return 0;
}


Board::Board() {
    clearBoard();
}

void Board::clearBoard() {
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            m_marks[i][j] = Mark::EMPTY;
        }
    }
}

void Board::printBoard() {
    printf("--------------------------------\n");
    printf("   1 2 3\n\n");
    for (int i = 0; i < m_width; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < m_height; j++) {
            switch (m_marks[i][j]) {
                case Mark::X:
                    printf("X");
                    break;
                case Mark::O:
                    printf("O");
                    break;
                case Mark::EMPTY:
                default:
                    printf("-");
                    break;
            }

            if (j < m_height - 1)
                printf("|");
        }

        if (i < m_height - 1)
            printf("\n   -+-+-");

        printf("\n");
    }
}

void Board::setCheck(int x, int y, Mark mark) {
    if (x <= 0 || y <= 0 || x > m_width || y > m_width) {
        printf("Invalid position\n");
        return;
    }

    m_marks[y - 1][x - 1] = mark;
}

Mark Board::checkWinner() {
    for (int i = 0; i < m_width; i++) {
        if (m_marks[i][0] == m_marks[i][1] && m_marks[i][1] == m_marks[i][2])
            return m_marks[i][0];
        if (m_marks[0][i] == m_marks[1][i] && m_marks[1][i] == m_marks[2][i])
            return m_marks[0][i];
    }

    if (m_marks[0][0] == m_marks[1][1] && m_marks[1][1] == m_marks[2][2])
        return m_marks[0][0];

    if (m_marks[2][0] == m_marks[1][1] && m_marks[1][1] == m_marks[0][2])
        return m_marks[2][0];

    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            if (m_marks[i][j] == Mark::EMPTY)
                return Mark::EMPTY;
        }
    }

    return Mark::TIE;
}

