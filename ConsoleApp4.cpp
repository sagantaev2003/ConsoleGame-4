#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Структура, представляющая персонажа
struct Character {
    std::string name; // Имя персонажа
    int health;       // Здоровье
    int attack;       // Атака
    int defense;      // Защита
    int mana;         // Мана
    int heals;        // Количество лечений

    // Метод атаки другого персонажа
    void attackTarget(Character& target) {
        setlocale(LC_ALL, "RU");
        int damage = attack - target.defense; // Учитываем защиту цели
        if (damage < 0) damage = 0; // Урон не может быть отрицательным
        std::cout << "\n" << name << " атакует " << target.name << " и наносит " << damage << " урона.\n";
        target.health -= damage; // Уменьшаем здоровье цели
    }

    // Метод для использования заклинания
    void castSpell(Character& target) {
        setlocale(LC_ALL, "RU");
        if (mana >= 10) { // Проверяем, хватает ли маны
            int spellDamage = attack * 2; // Заклинание наносит удвоенный урон
            std::cout << "\n" << name << " использует заклинание и наносит " << spellDamage << " урона!\n";
            target.health -= spellDamage;
            mana -= 10; // Тратим ману
        }
        else {
            std::cout << "Недостаточно маны для заклинания!\n";
        }
    }

    // Метод для защиты
    void defend() {
        setlocale(LC_ALL, "RU");
        std::cout <<"\n" << name << " принимает защитную стойку! Урон понижен на 50% в следующем раунде.\n";
        defense *= 2; // Временно увеличиваем защиту в 2 раза
    }

    // Метод для лечения
    void heal() {
        setlocale(LC_ALL, "RU");
        if (heals > 0) { // Проверяем, есть ли ещё лечения
            int healing = 20;
            health += healing; // Восстанавливаем здоровье
            --heals;
            std::cout << "\n"<< name << " лечится на " << healing << " HP. Осталось лечений: " << heals << "\n";
        }
        else {
            std::cout << "Лечения закончились!\n";
        }
    }
};

// Функция для отображения текущего состояния боя
void printStatus(const Character& hero, const Character& monster) {
    setlocale(LC_ALL, "RU");
    std::cout << "\n--- Статус сражения ---\n";
    std::cout << hero.name << " (Здоровье: " << hero.health << ", Защита: " << hero.defense << ", Мана: " << hero.mana << ", Лечения: " << hero.heals << ")\n";
    std::cout << monster.name << " (Здоровье: " << monster.health << ")\n";
    std::cout << "-------------------------\n\n";
}

// Ход игрока
void heroTurn(Character& hero, Character& monster) {
    setlocale(LC_ALL, "RU");
    int choice;
    std::cout << "Выберите действие:\n";
    std::cout << "1. Атаковать\n2. Заклинание (10 маны)\n3. Защититься\n4. Лечение\n5. Уклонение (50% шанс)\n\n";
    std::cin >> choice;

    switch (choice) {
    case 1:
        hero.attackTarget(monster);
        break;
    case 2:
        hero.castSpell(monster);
        break;
    case 3:
        hero.defend();
        break;
    case 4:
        hero.heal();
        break;
    case 5:
        if (rand() % 2 == 0) { // 50% шанс успешного уклонения
            std::cout << hero.name << " уклоняется от атаки!\n";
        }
        else {
            std::cout << hero.name << " не смог уклониться!\n";
        }
        break;
    default:
        std::cout << "Некорректный ввод! Пропуск хода.\n";
    }
}

// Ход монстра
void monsterTurn(Character& monster, Character& hero) {
    setlocale(LC_ALL, "RU");
    if (monster.health > 0) {
        int action = rand() % 3; // Случайное действие монстра
        if (action == 0) {
            monster.attackTarget(hero);
        }
        else if (action == 1) {
            std::cout << "\n" << monster.name << " использует сильную атаку!\n";
            hero.health -= monster.attack * 1.5; // Усиленная атака
        }
        else {
            std::cout << "\n" << monster.name << " пытается оглушить " << hero.name << "!\n";
            if (rand() % 2 == 0) {
                std::cout << "\n" << hero.name << " оглушён и пропускает ход!\n";
            }
        }
    }
}

// Главная функция
int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0)); // Инициализация генератора случайных чисел

    // Создаём персонажей
    Character hero = { "Герой", 100, 15, 5, 30, 3 };
    Character monster = { "Монстр", 80, 12, 3, 0, 0 };

    // Основной игровой цикл
    while (hero.health > 0 && monster.health > 0) {
        printStatus(hero, monster);
        heroTurn(hero, monster);
        if (monster.health > 0) {
            monsterTurn(monster, hero);
        }
    }

    // Определяем победителя
    if (hero.health > 0) {
        std::cout << "Вы победили!\n";
    }
    else {
        std::cout << "Вы проиграли...\n";
    }

    return 0;
}
