#define _CRT_SECURE_NO_WARNINGS;

#include <cstdlib>
#include "stdio.h";
#include "ctype.h";
#include "BoardStruct.h";
#include "conio.h";

int Menu();

int GetSaved();

int GameOver(BoardStructure **board, int);

int SaveBoard(BoardStructure **board, int);

int BoardChecker(BoardStructure **board, int, int, int);

int DefaultCells(BoardStructure **board, int);

int GameEngine(BoardStructure **board, int);

int BoardToConsole(BoardStructure **board, int);

BoardStructure **LoadBoard(BoardStructure **board, int);

int WriteRecord();

int GetSaved();

int GetRecords();

int StartGame();

int main() {
    printf("Hello my friend!\nWelcome to magic console!\n");
    return Menu();
}

int WriteRecord() {
    printf("Enter your name sith(20-symbol limited):");
    char name[20];
    scanf(" %s", &name);
    FILE *file;
    file = fopen("recordList.DarthVader", "a");
    if (file == NULL) {
        file = fopen("recordList.DarthVader", "w+");
    }
    fprintf(file, "%s\n", name);
    fclose(file);
    return 0;
}

int GetSaved() {
    struct BoardStructure **board;
    FILE *file = fopen("saved.DarthVader", "r");
    int i = 0;
    char buffer[256];
    char fileName[20] = "test";
    while (fgets(buffer, 256, file)) {
        printf("%d)%s\n", ++i, buffer);
    }
    printf("Enter name:");
    scanf(" %s", &fileName);
    fclose(file);
    file = fopen(fileName, "r");
    int counter = 0, x, y, num = 0, z = 0, isConst, size = 0;
    char charac;
    int *pnts[5];
    pnts[0] = &x;
    pnts[1] = &y;
    pnts[2] = NULL;
    pnts[3] = &num;
    pnts[4] = &isConst;
    int *putter;
    int a = 0;
    while (fgets(buffer, 256, file)) {
        size = buffer[0] - '0';
        board = (struct BoardStructure **) malloc(size * sizeof(struct BoardStructure));
        for (int i = 0; i < size; ++i) {
            board[i] = (struct BoardStructure *) malloc(size * sizeof(struct BoardStructure));
        }
        break;
    }
    while (fgets(buffer, 256, file)) {
        for (int i = 0; i < 256; i++) {
            if (buffer[i] == ',')
                counter = i;
            if (counter != 0) {
                if (z == 2) {
                    if (buffer[counter - 1] != ' ')
                        charac = buffer[counter - 1];
                    z++;
                } else {
                    putter = pnts[z];
                    z++;
                    if (buffer[counter - 1] != '_')
                        *putter = buffer[counter - 1] - '0';
                }
                counter = 0;
            }
            if (buffer[i] == '\0')
                break;
        }
        z = 0;
        board[x][y].Number = num;
        board[x][y].Character = charac;
        board[x][y].isConst = isConst;
        num = 0;
        charac = ' ';
        isConst = 0;
        x = 0;
        y = 0;
    }
    fclose(file);
    GameEngine(board, size);
    return 0;
}

int GetRecords() {
    char buffer[256];
    int i = 0;
    FILE *file = fopen("recordList.DarthVader", "r");
    while (fgets(buffer, 256, file)) {
        printf("%d)%s\n", ++i, buffer);
    }
    return 0;
}

int SaveBoard(BoardStructure **board, int size) {
    printf("Enter file name(20-symbols limited):");
    char filename[20];
    scanf(" %s", &filename);
    FILE *file = fopen("saved.DarthVader", "a");
    if (file == NULL)
        file = fopen("saved.DarthVader", "w+");
    fprintf(file, "%s\n", filename);
    char buffer[10];
    FILE *save = fopen(filename, "w+");
    for (int i = 0; i < size; ++i) {
        if (i == 0)
            fprintf(save, "%d\n", size);
        for (int j = 0; j < size; ++j) {
            buffer[0] = i + '0';
            buffer[1] = ',';
            buffer[2] = j + '0';
            buffer[3] = ',';
            buffer[4] = board[i][j].Character;
            buffer[5] = ',';
            buffer[6] = board[i][j].Number + '0';
            buffer[7] = ',';
            buffer[8] = board[i][j].isConst + '0';
            buffer[9] = ',';
            fprintf(save, "%s\n", buffer);
        }
    }
    fclose(save);
    return 0;
}

int GameEngine(BoardStructure **board, int size) {
    int x = 0, y = 0, num = 0;
    char charac;
    while (true) {
        BoardToConsole(board, size);
        printf("Enter y or -1 to quit\n -2 for save game:");
        scanf("%d", &x);
        if (x == -1)
            break;
        if (x == -2) {
            SaveBoard(board, size);
            return 0;
        }
        printf("Enter x:");
        scanf("%d", &y);
        printf("Enter value (A1):");
        scanf(" %c%d", &charac, &num);
        charac = toupper(charac);
        x--;
        y--;
        if (board[x][y].isConst != 0) {
            if (board[x][y].Number != 0) {
                if (board[x][y].Character == ' ') {
                    board[x][y].Character = charac;
                }
            }
            if (board[x][y].Character != ' ') {
                if (board[x][y].Number == 0) {
                    board[x][y].Number = num;
                }
            }
        } else {
            board[x][y].Character = charac;
            board[x][y].Number = num;
        }
        DefaultCells(board, size);
        BoardChecker(board, x, y, size);
        if (!GameOver(board, size)) {
            BoardToConsole(board, size);
            printf("Congratulations!!!\n");
            WriteRecord();
            return 0;
        }
    }
}

int Menu() {
    while (true) {
        printf("1-start new game.\n2-records\n3-get rules\n4-for load game\n5-exit:");
        int choise = 0;
        scanf("%d", &choise);
        system("cls");
        switch (choise) {
            case 1: {
                StartGame();
            }
                break;
            case 2: {
                GetRecords();
            }
                break;
            case 3: {

            }
                break;
            case 4: {
                GetSaved();
            }
            case 5: {
                return 0;
            }
                break;
        }
    }
}

int BoardToConsole(BoardStructure **board, int size) {
    system("cls");
    printf(" ");
    for (int i = 0; i < size; i++) {
        printf("   %d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d", i + 1);
        for (int z = 0; z < size; z++) {
            switch (board[i][z].isConst) {
                case 1: {
                    printf("| \033[0;34m%c\033[0m", board[i][z].Character);
                    if (board[i][z].isCorrect == 1) {
                        printf("\033[0;31m");
                    }
                    printf("%c\033[0m ", board[i][z].Number == 0 ? ' ' : board[i][z].Number + '0');
                }
                    break;
                case 2: {
                    printf("|");
                    if (board[i][z].isCorrect == 1) {
                        printf("\033[0;31m");
                    }
                    printf(" %c\033[0;34m%c\033[0m ", board[i][z].Character,
                           board[i][z].Number == 0 ? ' ' : board[i][z].Number + '0');
                }
                    break;
                case 3: {
                    printf("| \033[0;34m%c%c\033[0m ", board[i][z].Character,
                           board[i][z].Number == 0 ? ' ' : board[i][z].Number + '0');
                }
                    break;
                default: {
                    switch (board[i][z].isCorrect) {
                        case 1: {
                            printf("| \033[0;31m%c%c\033[0m ", board[i][z].Character,
                                   board[i][z].Number == 0 ? ' ' : board[i][z].Number + '0');
                        }
                            break;
                        default: {
                            printf("| %c%c ", board[i][z].Character,
                                   board[i][z].Number == 0 ? ' ' : board[i][z].Number + '0');
                        }
                            break;
                    }
                    break;
                }
            }
        }
        printf("|\n");
        for (int z = 0; z < size; z++) {
            printf("------");
        }
        printf("\n");
    }
    return 0;
}

int StartGame() {
    while (true) {
        printf("Choose the level.\n1-younling\n2-padavan\n3-jedi\n4-sith:");
        int choise = 0, size;
        scanf("%d", &choise);
        switch (choise) {
            case 1: {
                size = 3;
            }
                break;
            case 2: {
                size = 4;
            }
                break;
            case 3: {
                size = 5;
            }
                break;
            case 4: {
                size = 7;
            }
                break;
            default: {
                printf("CHOOOSE FROM GIVEN OR DIE!");
            }
                break;
        }
        if (size > 7 || size < 0)
            continue;
        BoardStructure **board;
        board = (BoardStructure **) malloc(size * sizeof(BoardStructure));
        for (int i = 0; i < size; ++i) {
            board[i] = (BoardStructure *) malloc(size * sizeof(BoardStructure));
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j].Character = ' ';
                board[i][j].Number = 0;
                board[i][j].isConst = 0;
                board[i][j].isCorrect = 0;
            }
        }
        LoadBoard(board, size);
        GameEngine(board, size);
        break;
    }
    return 0;
}

BoardStructure **LoadBoard(BoardStructure **board, int size) {
    FILE *file;
    file = size == 3 ? fopen("noob.DarthVader", "r") :
           size == 4 ? fopen("boop.DarthVader", "r") :
           size == 5 ? fopen("jedi.DarthVader", "r") :
           size == 7 ? fopen("sith.DarthVader", "r") : NULL;
    char buffer[256];
    int counter = 0, x, y, num = 0, z = 0;
    char charac;
    int *pnts[3];
    pnts[0] = &x;
    pnts[1] = &y;
    pnts[2] = NULL;
    pnts[3] = &num;
    int *putter;
    while (fgets(buffer, 256, file)) {
        for (int i = 0; i < 256; i++) {
            if (buffer[i] == ',')
                counter = i;
            if (counter != 0) {
                if (z == 2) {
                    if (buffer[counter - 1] != '_')
                        charac = buffer[counter - 1];
                    z++;
                } else {
                    putter = pnts[z];
                    z++;
                    if (buffer[counter - 1] != '_')
                        *putter = buffer[counter - 1] - '0';
                }
                counter = 0;
            }
            if (buffer[i] == '\0')
                break;
        }
        z = 0;
        board[x][y].Number = num;
        board[x][y].Character = charac;
        board[x][y].isConst = num == 0 ? 1 : charac == ' ' ? 2 : 3;
        num = 0;
        charac = ' ';
        x = 0;
        y = 0;
    }
    return board;
}

int DefaultCells(BoardStructure **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int z = 0; z < size; z++) {
            board[i][z].isCorrect = 0;
        }
    }
    return 0;
}

int BoardChecker(BoardStructure **board, int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int z = 0; z < size; z++) {
            for (int g = z; g < size - 1; g++) {
                if ((board[i][z].Character == board[i][g + 1].Character ||
                     board[i][z].Number == board[i][g + 1].Number) &&
                    board[i][z].Character != ' ' &&
                    board[i][z].Number != 0) {
                    board[i][z].isCorrect = 1;
                    board[i][g + 1].isCorrect = 1;
                }
                if ((board[z][i].Character == board[g + 1][i].Character ||
                     board[z][i].Number == board[g + 1][i].Number) &&
                    board[i][z].Character != ' ' &&
                    board[i][z].Number != 0) {
                    board[z][i].isCorrect = 1;
                    board[g + 1][i].isCorrect = 1;
                }
            }
        }
    }
    return 0;
}

int GameOver(BoardStructure **board, int size) {
    int counter = 0, underCounter = 0;
    for (int i = 0; i < size; i++) {
        for (int z = 0; z < size; z++) {
            if (board[i][z].isCorrect > 0)
                counter++;
            if (board[i][z].Character == ' '
                || board[i][z].Number == 0)
                ++underCounter;
        }
    }
    if (counter == 0 && underCounter == 0)
        return 0;
    return 1;
}