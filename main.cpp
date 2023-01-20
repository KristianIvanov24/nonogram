#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>

char username[10];
char password[10];
char level[3];
int mistakes = 3;

bool verifyData() {
    std::ifstream file("users.txt");

    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return false;
    }

    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    char fileUsername[10], filePassword[10];
    while (file >> fileUsername >> filePassword >> level) {
        bool usernameMatch = true, passwordMatch = true;
        for (int i = 0; username[i] != '\0'; i++) {
            if (username[i] != fileUsername[i]) {
                usernameMatch = false;
                break;
            }
        }
        for (int i = 0; i < password[i] != '\0'; i++) {
            if (password[i] != filePassword[i]) {
                passwordMatch = false;
                break;
            }
        }
        if (usernameMatch && passwordMatch) {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

void userReg() {
    while (verifyData()) {
        std::cout << "User credentials already exist!" << std::endl;
    }

    std::ofstream file("users.txt", std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    level[0] = '1';
    level[1] = '_';
    level[2] = '1';
    file << username << " " << password << " " << level << std::endl;
    file.close();
}

void showNonogram(std::vector<std::vector<char>> matrix, int row, int col){
    std::vector<std::vector<int>> rows;
    rows.resize(row);
    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == '#') {
                count++;
            }
            else if (matrix[i][j] == 'O' && count != 0) {
                rows[i].push_back(count);
                count = 0;
            }
        }
        if (count != 0)
            rows[i].push_back(count);
    }

    std::vector<std::vector<int>> columns;
    columns.resize(col);
    for (int i = 0; i < col; i++) {
        int count = 0;
        for (int j = 0; j < row; j++) {
            if (matrix[j][i] == '#') {
                count++;
            }
            else if (matrix[j][i] == 'O' && count != 0) {
                columns[i].push_back(count);
                count = 0;
            }
        }
        if (count != 0)
            columns[i].push_back(count);
    }

    for (int j = 0; j < columns[0].size(); j++) {
        for (int i = 0; i < columns.size(); i++) {
            if (columns[i].size() > j) {
                std::cout << columns[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
        
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            std::cout << rows[i][j] << " ";
        }
        for (int j = 0; j < 8 - rows[i].size()*2; j++) {
            std::cout << " ";
        }
        for (int j = 0; j < col; j++) { 
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void fillChunk(std::vector<std::vector<char>> &matrix){
    int x, y;
    std::cout << "Please input coordinates of spot to be filled using the given format: number1 number2" << std::endl;
    std::cout << '>';
    std::cin >> x >> y;

    matrix[x][y] = '#';
}

void markEmpty(std::vector<std::vector<char>> &matrix){
    int x, y;
    std::cout << "Please input coordinates of spot to be marked as empty using the given format: number1 number2" << std::endl;
    std::cout << '>';
    std::cin >> x >> y;

    matrix[x][y] = ' ';
}

bool compare(std::vector<std::vector<char>> player_matrix, std::vector<std::vector<char>> solved_matrix){
    for(int i = 0; i < player_matrix.size(); i++){
        for(int j = 0; j < player_matrix[0].size(); j++){
            if(player_matrix[i][j] != solved_matrix[i][j] && !(player_matrix[i][j] == ' ' && solved_matrix[i][j] == 'O'))
                return false;
        }    
    }
        
    return true;
}

void saveUser(){
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    char currentName[10];
    char currentPassword[10];
    char currentLevel[3];
    while (file >> currentName >> currentLevel) {
        if (strcmp(currentName, username) == 0 && strcmp(currentPassword, password) == 0) {
            strcpy(currentLevel, level);
            break;
        }
    }
    file.close();

    std::ofstream outfile("users.txt");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    outfile << currentName << " " << currentPassword << " " << currentLevel << std::endl;
    outfile.close();
}

void saveProgress(std::vector<std::vector<char>> player_matrix){
    char filename[17];
    strcpy(filename, level);
    strcat(filename, "_");
    strcat(filename, username);
    strcat(filename, ".txt");

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    for (int i = 0; i < player_matrix.size(); i++) {
        for (int j = 0; j < player_matrix[i].size(); j++) {
            file << player_matrix[i][j] << " ";
        }
        file << std::endl;
    }

    file.close();

    std::cout << "Game saved!" << std::endl;
}

void visualize(std::vector<std::vector<char>> player_matrix){
    for(int i = 0; i < player_matrix.size(); i++){
        for(int j = 0; j < player_matrix[0].size(); j++){
            if(player_matrix[i][j] == 'O')
                std::cout << ' ';
            else std::cout << player_matrix[i][j];
        }
        std::cout << std::endl;    
    }
}

void playGame() {
    int currlvl = int(level[0]) - 48;

    if (currlvl != 1) {
        std::cout << "You can choose betwen level 1 and level " << currlvl << std::endl;
        std::cout << '>';
        std::cin >> currlvl;

        while (currlvl > int(level[0]) - 48) {
            std::cout << "Invalid level!" << std::endl;
            std::cout << "You can choose betwen level 1 and level " << currlvl << std::endl;
            std::cout << '>';
            std::cin >> currlvl;
        }
    }

    srand(time(NULL));
    int randomNumber = rand() % 2 + 1;

    level[0] = currlvl + '0';
    level[2] = randomNumber + '0';

    char filename[7];
    strcpy(filename, level);
    strcat(filename, ".txt");
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    std::vector<std::vector<char>> solved_matrix;
    char c;
    while (file >> c) {
        std::vector<char> row;
        while (c != '\n' && !file.eof()) {
            row.push_back(c);
            file >> c;
        }
        solved_matrix.push_back(row);
    }
    file.close();
    
    int rows = solved_matrix.size();
    int cols = solved_matrix[0].size();

    std::vector<std::vector<char>> player_matrix(rows, std::vector<char>(cols, 'O'));

    char cmd;
    do{
        showNonogram(player_matrix, rows, cols);

        std::cout << "You currently have " << mistakes << " lives." << std::endl;
        std::cout << std::endl;

        std::cout << "If you wish to fill press f, if you wish to mark an empty spot press m, if you wish to check your nonogram press c and if you wish to exit press e." << std::endl;
        std::cout << '>';
        std::cin >> cmd;

        if(cmd == 'f'){
            fillChunk(player_matrix);
        }
        else if(cmd == 'm'){
            markEmpty(player_matrix);
        }
        else if(cmd == 'c'){
            if(compare(player_matrix, solved_matrix)){
                std::cout << "Congrats! You've finished this level!" << std::endl;
                visualize(player_matrix);
                if(currlvl < 5){
                    level[0] = currlvl + 1 + '0';
                    saveUser();
                    return;
                }
                else {
                    saveUser();
                    return;
                }
            }
            else mistakes--;
        }
    }while(cmd != 'e' || mistakes != 0);

    if(mistakes == 0){
        std::cout << "You've lost!" << std::endl;
        return;
    }
    
    saveProgress(player_matrix);
    saveUser();
}

void loadGame() {
    char filename[17];
    strcpy(filename, level);
    strcat(filename, "_");
    strcat(filename, username);
    strcat(filename, ".txt");

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    std::vector<std::vector<char>> player_matrix;
    int row, col;
    while (file >> row >> col) {
        if (player_matrix.size() < row + 1) {
            player_matrix.resize(row + 1);
        }
        if (player_matrix[row].size() < col + 1) {
            player_matrix[row].resize(col + 1);
        }

        file >> player_matrix[row][col];
    }
    file.close();

    char solved_filename[7];
    strcpy(solved_filename, level);
    strcat(solved_filename, ".txt");

    std::ifstream file_solved(solved_filename);
    if (!file_solved.is_open()) {
        std::cout << "Error: Unable to open file1." << std::endl;
        return;
    }

    std::vector<std::vector<char>> solved_matrix;
    char c;
    while (file >> c) {
        std::vector<char> row;
        while (c != '\n' && !file.eof()) {
            row.push_back(c);
            file >> c;
        }
        solved_matrix.push_back(row);
    }
    file.close();
    
    int rows = solved_matrix.size();
    int cols = solved_matrix[0].size();

    char cmd;
    do{
        showNonogram(player_matrix, rows, cols);

        std::cout << "You currently have " << mistakes << " lives." << std::endl;
        std::cout << std::endl;

        std::cout << "If you wish to fill press f, if you wish to mark an empty spot press m, if you wish to check your nonogram press c and if you wish to exit press e." << std::endl;
        std::cout << '>';
        std::cin >> cmd;

        if(cmd == 'f'){
            fillChunk(player_matrix);
        }
        else if(cmd == 'm'){
            markEmpty(player_matrix);
        }
        else if(cmd == 'c'){
            if(compare(player_matrix, solved_matrix)){
                std::cout << "Congrats! You've finished this level!" << std::endl;
                visualize(player_matrix);
                if((int(level[0]) - 48) < 5){
                    level[0] = (int(level[0]) - 47) + '0';
                    saveUser();
                    return;
                }
                else {
                    saveUser();
                    return;
                }
            }
            else mistakes--;
        }
    }while(cmd != 'e' || mistakes != 0);

    if(mistakes == 0){
        std::cout << "You've lost!" << std::endl;
        return;
    }
    
    saveProgress(player_matrix);
    saveUser();
}

void Nonogram() {
    char cmd;
    std::cout << "Welcome to Nonogram game! If you wish to register press r and if you wish to login press l" << std::endl;
    std::cout << ">";
    std::cin >> cmd;

    while (cmd != 'l' && cmd != 'r') {
        std::cout << "Invalid comand!" << std::endl;
        std::cout << "Welcome to Nonogram game! If you wish to register press r and if you wish to login press l" << std::endl;
        std::cout << ">";
        std::cin >> cmd;
    }

    if (cmd == 'l') {
        while (!verifyData()) {
            std::cout << "Invalid credentials!" << std::endl;
        }

        std::cout << "Login successful!" << std::endl;
        std::cout << "If you wish to continue you last game at level " << level[0] << " press c and if you wish to play new game press n" << std::endl;
        std::cout << '>';
        std::cin >> cmd;

        while (cmd != 'c' && cmd != 'n') {
            std::cout << "Invalid comand!" << std::endl;
            std::cout << "If you wish to continue you last game at level " << level[0] << " press c and if you wish to play new game press n" << std::endl;
            std::cout << '>';
            std::cin >> cmd;
        }

        if (cmd == 'n')
            playGame();
        else loadGame();
    }
    else {
        userReg();
        std::cout << "Registration successful!" << std::endl;
        playGame();
    }
}

int main() {
    Nonogram();
    return 0;
}
