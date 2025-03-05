#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib> // Для генерации случайных чисел
#include <ctime>

using namespace std;

// Функция для отображения игрового поля
void printField(const vector<char>& field) {
    cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        // Вывод строк игрового поля
        cout << " " << field[i] << " | " << field[i + 1] << " | " << field[i + 2] << "\n";
        if (i < 6) cout << "---+---+---\n"; // Разделитель строк
    }
    cout << "\n";
}

// Функция для проверки победителя
bool checkWin(const vector<char>& field, char player) {
    // Массив с выигрышными комбинациями (по строкам, столбцам и диагоналям)
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Горизонтальные линии
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Вертикальные линии
        {0, 4, 8}, {2, 4, 6}             // Диагональные линии
    };

    // Проверяем, есть ли у игрока три одинаковых символа в одной из комбинаций
    for (auto& combo : winCombos) {
        if (field[combo[0]] == player && field[combo[1]] == player && field[combo[2]] == player) {
            return true; // Игрок победил
        }
    }
    return false; // Победы нет
}

// Функция для получения корректного хода от игрока
int getPlayerMove(vector<char>& field) {
    setlocale(LC_ALL, "RU");
    int move;
    while (true) {
        cout << "Введите номер клетки (1-9): ";

        // Проверяем, является ли ввод числом и попадает ли в диапазон от 1 до 9
        if (!(cin >> move) || move < 1 || move > 9 || field[move - 1] == 'X' || field[move - 1] == 'O') {
            cout << "Некорректный ввод. Попробуйте снова.\n";
            cin.clear(); // Сбрасываем ошибку ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
        }
        else {
            return move - 1; // Возвращаем индекс клетки (от 0 до 8)
        }
    }
}

// Функция для случайного хода компьютера
int getComputerMove(vector<char>& field) {
    vector<int> availableMoves;
    for (int i = 0; i < 9; i++) {
        if (field[i] != 'X' && field[i] != 'O') {
            availableMoves.push_back(i); // Добавляем свободные клетки в список
        }
    }
    return availableMoves[rand() % availableMoves.size()]; // Возвращаем случайный ход
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0)); // Инициализация генератора случайных чисел
    char playAgain; // Переменная для хранения ответа пользователя на повтор игры
    char gameMode; // Переменная для выбора режима игры

    do {
        // Выбор режима игры
        cout << "Выберите режим игры: 1 - два игрока, 2 - игра против компьютера: ";
        cin >> gameMode;

        // Инициализация игрового поля номерами клеток (1-9)
        vector<char> field = { '1','2','3','4','5','6','7','8','9' };
        char currentPlayer = 'X'; // Начинает игрок X
        int moves = 0; // Количество сделанных ходов
        bool gameWon = false; // Флаг, указывающий, выиграна ли игра

        while (moves < 9 && !gameWon) { // Пока не будет 9 ходов или победителя
            printField(field); // Вывод игрового поля
            int move;

            if (gameMode == '2' && currentPlayer == 'O') {
                move = getComputerMove(field); // Ход компьютера
                cout << "Компьютер выбрал клетку " << move + 1 << "\n";
            }
            else {
                move = getPlayerMove(field); // Получение хода от игрока
            }

            field[move] = currentPlayer; // Запись символа игрока в выбранную клетку
            moves++; // Увеличиваем счетчик ходов

            // Проверяем, победил ли текущий игрок
            if (checkWin(field, currentPlayer)) {
                printField(field); // Вывод итогового игрового поля
                cout << "Игрок " << currentPlayer << " победил!\n";
                gameWon = true; // Устанавливаем флаг победы
                break; // Завершаем цикл игры
            }

            // Меняем текущего игрока (переключаем между X и O)
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        if (!gameWon) { // Если игра завершилась, но победителя нет - ничья
            printField(field);
            cout << "Ничья!\n";
        }

        // Спрашиваем, хочет ли игрок сыграть еще раз
        cout << "Хотите сыграть еще раз? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y'); // Повторяем игру, если ответ 'y' или 'Y'

    return 0; // Завершаем программу
}
