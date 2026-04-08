#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>

#define NOMINMAX
#include <windows.h>

void setConsoleEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

class ConsoleColor {
private:
    HANDLE hConsole;
    WORD defaultAttributes;
public:
    ConsoleColor() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        defaultAttributes = csbi.wAttributes;
    }

    void setColor(WORD color) {
        SetConsoleTextAttribute(hConsole, color);
    }

    void reset() {
        SetConsoleTextAttribute(hConsole, defaultAttributes);
    }
};

const WORD COLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD COLOR_RED = FOREGROUND_RED;
const WORD COLOR_GREEN = FOREGROUND_GREEN;
const WORD COLOR_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
const WORD COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD COLOR_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;

void printColored(const std::string& text, WORD color, bool bold = false, bool newLine = true) {
    static ConsoleColor console;
    if (bold) color |= FOREGROUND_INTENSITY;
    console.setColor(color);
    std::cout << text;
    console.reset();
    if (newLine) std::cout << std::endl;
}

// Функция для анимации загрузки
void loadingAnimation() {
    printColored("\nЗагрузка системы", COLOR_CYAN, true);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << ".";
            std::cout.flush();
            Sleep(300);
        }
        if (i < 2) {
            std::cout << "\rЗагрузка системы   ";
            std::cout.flush();
            Sleep(300);
        }
    }
    std::cout << std::endl;
}

// Функция для отображения логотипа
void showLogo() {
    printColored("", COLOR_CYAN, true);
    printColored("  ╔══════════════════════════════════════════════════════════════╗", COLOR_CYAN, true);
    printColored("  ║                                                                  ║", COLOR_CYAN, true);
    printColored("  ║     ██████╗██╗████████╗ █████╗ ██████╗ ███████╗██╗                 ║", COLOR_YELLOW, true);
    printColored("  ║    ██╔════╝██║╚══██╔══╝██╔══██╗██╔══██╗██╔════╝██║                 ║", COLOR_YELLOW, true);
    printColored("  ║    ██║     ██║   ██║   ███████║██████╔╝█████╗  ██║                 ║", COLOR_YELLOW, true);
    printColored("  ║    ██║     ██║   ██║   ██╔══██║██╔══██╗██╔══╝  ██║                 ║", COLOR_YELLOW, true);
    printColored("  ║    ╚██████╗██║   ██║   ██║  ██║██║  ██║███████╗███████╗            ║", COLOR_YELLOW, true);
    printColored("  ║     ╚═════╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝            ║", COLOR_YELLOW, true);
    printColored("  ║                                                                  ║", COLOR_CYAN, true);
    printColored("  ║     ██╗   ██╗██████╗ ██████╗  █████╗ ██╗   ██╗██╗███████╗         ║", COLOR_GREEN, true);
    printColored("  ║     ██║   ██║██╔══██╗██╔══██╗██╔══██╗██║   ██║██║██╔════╝         ║", COLOR_GREEN, true);
    printColored("  ║     ██║   ██║██████╔╝██║  ██║███████║██║   ██║██║███████╗         ║", COLOR_GREEN, true);
    printColored("  ║     ██║   ██║██╔══██╗██║  ██║██╔══██║╚██╗ ██╔╝██║╚════██║         ║", COLOR_GREEN, true);
    printColored("  ║     ╚██████╔╝██║  ██║██████╔╝██║  ██║ ╚████╔╝ ██║███████║         ║", COLOR_GREEN, true);
    printColored("  ║      ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝  ╚═══╝  ╚═╝╚══════╝         ║", COLOR_GREEN, true);
    printColored("  ║                                                                  ║", COLOR_CYAN, true);
    printColored("  ║                  ЦЕНТР УПРАВЛЕНИЯ БАЗОЙ                          ║", COLOR_MAGENTA, true);
    printColored("  ║                       ВЕРСИЯ 3.7                                  ║", COLOR_YELLOW, true);
    printColored("  ╚══════════════════════════════════════════════════════════════╝", COLOR_CYAN, true);
    printColored("", COLOR_CYAN, true);
}

// Функция для отображения прогресс-бара
void showProgressBar(int current, int max, const std::string& label, WORD color) {
    int barWidth = 30;
    float progress = static_cast<float>(current) / max;
    int pos = static_cast<int>(barWidth * progress);

    printColored(label + " [", color, false, false);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            if (color == COLOR_GREEN) printColored("=", color, false, false);
            else if (color == COLOR_YELLOW) printColored("=", color, false, false);
            else printColored("=", color, false, false);
        }
        else {
            printColored(" ", color, false, false);
        }
    }
    printColored("] " + std::to_string(current) + "/" + std::to_string(max), color, false, true);
}

// Функция для отображения схемы базы
void showBaseMap(int farmLevel, int metalworksLevel, int refineryLevel, int ammoFactoryLevel,
    int barracksLevel, int wallLevel, int tradePostLevel) {
    printColored("\n  СХЕМА БАЗЫ \"ЦИТАДЕЛЬ\"", COLOR_CYAN, true);
    printColored("  ╔══════════════════════════════════════════════════════════════════╗", COLOR_CYAN, true);

    // Верхняя стена
    printColored("  ║", COLOR_CYAN, false, false);
    for (int i = 0; i < wallLevel; i++) {
        printColored("█", COLOR_YELLOW, false, false);
    }
    for (int i = wallLevel; i < 5; i++) {
        printColored("░", COLOR_WHITE, false, false);
    }
    printColored("  Стена (ур." + std::to_string(wallLevel) + "/5)", COLOR_CYAN, false, true);

    // Первый ряд зданий
    printColored("  ║", COLOR_CYAN, false, false);
    if (farmLevel >= 1) printColored("🌾", COLOR_GREEN, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  Ферма (ур." + std::to_string(farmLevel) + "/5)", COLOR_GREEN, false, true);

    printColored("  ║", COLOR_CYAN, false, false);
    if (metalworksLevel >= 1) printColored("⚙️", COLOR_WHITE, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  Литейный цех (ур." + std::to_string(metalworksLevel) + "/5)", COLOR_WHITE, false, true);

    printColored("  ║", COLOR_CYAN, false, false);
    if (refineryLevel >= 1) printColored("🛢️", COLOR_YELLOW, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  НПЗ (ур." + std::to_string(refineryLevel) + "/5)", COLOR_YELLOW, false, true);

    // Второй ряд зданий
    printColored("  ║", COLOR_CYAN, false, false);
    if (ammoFactoryLevel >= 1) printColored("🔫", COLOR_RED, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  Оружейный арсенал (ур." + std::to_string(ammoFactoryLevel) + "/5)", COLOR_RED, false, true);

    printColored("  ║", COLOR_CYAN, false, false);
    if (barracksLevel >= 1) printColored("🏛️", COLOR_MAGENTA, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  Штаб операций (ур." + std::to_string(barracksLevel) + "/5)", COLOR_MAGENTA, false, true);

    printColored("  ║", COLOR_CYAN, false, false);
    if (tradePostLevel >= 1) printColored("💰", COLOR_GREEN, false, false);
    else printColored("·", COLOR_WHITE, false, false);
    printColored("  Торговый пост (ур." + std::to_string(tradePostLevel) + "/5)", COLOR_GREEN, false, true);

    // Нижняя стена
    printColored("  ║", COLOR_CYAN, false, false);
    for (int i = 0; i < wallLevel; i++) {
        printColored("█", COLOR_YELLOW, false, false);
    }
    for (int i = wallLevel; i < 5; i++) {
        printColored("░", COLOR_WHITE, false, false);
    }
    printColored("  Основание стены", COLOR_CYAN, false, true);

    printColored("  ╚══════════════════════════════════════════════════════════════════╝", COLOR_CYAN, true);

    // Легенда
    printColored("  Легенда: 🌾-ферма ⚙️-цех 🛢️-НПЗ 🔫-арсенал 🏛️-штаб 💰-торговля █-стена", COLOR_WHITE, true);
}

// Функция для ввода с таймером
std::string timedInput(int seconds, const std::string& prompt) {
    printColored(prompt + " (У вас " + std::to_string(seconds) + " секунд!)", COLOR_YELLOW, true);

    auto startTime = std::chrono::steady_clock::now();
    std::string input;

    std::cout << "> ";
    std::getline(std::cin, input);

    auto endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    if (elapsed > seconds) {
        printColored("\n[СИСТЕМА] Время вышло! Принято автоматическое решение.", COLOR_RED);
        return "";
    }

    return input;
}

// Функция для срочного события
void urgentEvent(int& money, int& metal, int& fuel, int& food, int& ammo, int& population,
    int day, int wallLevel, int barracksLevel) {

    if (rand() % 100 < 15) {
        int eventType = rand() % 5;

        printColored("\n==================================================", COLOR_RED, true);
        printColored("[ВНИМАНИЕ] СРОЧНОЕ СОБЫТИЕ!", COLOR_RED, true);
        printColored("==================================================", COLOR_RED, true);

        if (eventType == 0) {
            printColored("Враги атакуют базу внезапно! У вас мало времени на решение!", COLOR_RED, true);
            printColored("1. Контратаковать (потеря 10 бойцов, но можно захватить ресурсы)", COLOR_GREEN);
            printColored("2. Укрепить оборону (потеря 15 металла, но уменьшение урона)", COLOR_CYAN);
            printColored("3. Отступить в убежище (потеря 5 еды, сохранение населения)", COLOR_YELLOW);

            std::string choice = timedInput(8, "\nВаш выбор (1-3)");

            if (choice == "1") {
                int popLoss = 10;
                population -= popLoss;
                if (population < 0) population = 0;
                int loot = rand() % 81 + 50;
                money += loot;
                printColored("Контратака успешна! Потеряно " + std::to_string(popLoss) + " бойцов, но захвачено " +
                    std::to_string(loot) + " КМ!", COLOR_GREEN);
            }
            else if (choice == "2") {
                int metalLoss = 15;
                metal -= metalLoss;
                if (metal < 0) metal = 0;
                printColored("Оборона укреплена! Потеряно " + std::to_string(metalLoss) + " металлолома, урон снижен на 50%!", COLOR_CYAN);
            }
            else if (choice == "3") {
                int foodLoss = 5;
                food -= foodLoss;
                if (food < 0) food = 0;
                printColored("Вы отступили в убежище! Потеряно " + std::to_string(foodLoss) + " рационов, население сохранено.", COLOR_YELLOW);
            }
            else {
                printColored("Автоматическое решение: отступление в убежище.", COLOR_RED);
                int foodLoss = 5;
                food -= foodLoss;
                if (food < 0) food = 0;
                printColored("Потеряно " + std::to_string(foodLoss) + " рационов.", COLOR_YELLOW);
            }
        }
        else if (eventType == 1) {
            printColored("На складе боеприпасов пожар! Нужно быстро решить!", COLOR_RED, true);
            printColored("1. Тушить силами бойцов (потеря 3 бойцов, сохранение 70% боеприпасов)", COLOR_GREEN);
            printColored("2. Использовать огнетушители (трата 20 металла, сохранение 90% боеприпасов)", COLOR_CYAN);
            printColored("3. Эвакуировать склад (потеря 50% боеприпасов, без потерь)", COLOR_YELLOW);

            std::string choice = timedInput(8, "\nВаш выбор (1-3)");

            if (choice == "1") {
                int popLoss = 3;
                population -= popLoss;
                if (population < 0) population = 0;
                ammo = static_cast<int>(ammo * 0.7);
                printColored("Пожар потушен! Потеряно " + std::to_string(popLoss) + " бойцов, сохранено 70% патронов.", COLOR_GREEN);
            }
            else if (choice == "2") {
                int metalLoss = 20;
                metal -= metalLoss;
                if (metal < 0) metal = 0;
                ammo = static_cast<int>(ammo * 0.9);
                printColored("Пожар потушен! Потрачено " + std::to_string(metalLoss) + " металлолома, сохранено 90% патронов.", COLOR_CYAN);
            }
            else if (choice == "3") {
                ammo = static_cast<int>(ammo * 0.5);
                printColored("Склад эвакуирован! Сохранено 50% патронов, потерь нет.", COLOR_YELLOW);
            }
            else {
                printColored("Автоматическое решение: эвакуация склада.", COLOR_RED);
                ammo = static_cast<int>(ammo * 0.5);
                printColored("Сохранено 50% патронов.", COLOR_YELLOW);
            }
        }
        else if (eventType == 2) {
            printColored("К вам пришёл перебежчик с ценной информацией! Время решать!", COLOR_YELLOW, true);
            printColored("1. Заплатить 30 КМ за информацию (узнать уровень врагов)", COLOR_GREEN);
            printColored("2. Заплатить 20 рационов за информацию (узнать слабые места)", COLOR_CYAN);
            printColored("3. Прогнать перебежчика (ничего не получить)", COLOR_RED);

            std::string choice = timedInput(8, "\nВаш выбор (1-3)");

            if (choice == "1" && money >= 30) {
                money -= 30;
                printColored("Перебежчик рассказал об уровне агрессии врагов: " +
                    std::to_string(rand() % 5 + 1) + "/5", COLOR_GREEN);
            }
            else if (choice == "2" && food >= 20) {
                food -= 20;
                printColored("Перебежчик указал слабые места в обороне! Уровень обороны врагов временно снижен!", COLOR_GREEN);
            }
            else if (choice == "3") {
                printColored("Вы прогнали перебежчика. Ничего не получено.", COLOR_RED);
            }
            else {
                printColored("Автоматическое решение: перебежчик прогнан.", COLOR_RED);
            }
        }
        else if (eventType == 3) {
            printColored("На базе начался бунт из-за нехватки ресурсов!", COLOR_RED, true);
            printColored("1. Выдать премию (трата 50 КМ, успокоение бунта)", COLOR_GREEN);
            printColored("2. Подавить силой (потеря 5 бойцов, без трат)", COLOR_RED);
            printColored("3. Пообещать улучшения (улучшение репутации через 3 дня)", COLOR_CYAN);

            std::string choice = timedInput(8, "\nВаш выбор (1-3)");

            if (choice == "1" && money >= 50) {
                money -= 50;
                printColored("Бунт успокоен! Потрачено 50 КМ.", COLOR_GREEN);
            }
            else if (choice == "2") {
                int popLoss = 5;
                population -= popLoss;
                if (population < 0) population = 0;
                printColored("Бунт подавлен! Потеряно " + std::to_string(popLoss) + " бойцов.", COLOR_RED);
            }
            else if (choice == "3") {
                printColored("Бунтовщики поверили обещаниям! Бонус к репутации через 3 дня.", COLOR_CYAN);
            }
            else {
                printColored("Автоматическое решение: бунт подавлен силой.", COLOR_RED);
                int popLoss = 5;
                population -= popLoss;
                if (population < 0) population = 0;
                printColored("Потеряно " + std::to_string(popLoss) + " бойцов.", COLOR_RED);
            }
        }
        else if (eventType == 4) {
            printColored("Мимо базы идёт торговый караван! Нужно быстро решить!", COLOR_MAGENTA, true);
            printColored("1. Ограбить караван (получить 100 КМ, потеря репутации)", COLOR_RED);
            printColored("2. Торговать честно (обмен ресурсов по выгодному курсу)", COLOR_GREEN);
            printColored("3. Пропустить караван (ничего не получить)", COLOR_YELLOW);

            std::string choice = timedInput(8, "\nВаш выбор (1-3)");

            if (choice == "1") {
                money += 100;
                printColored("Караван ограблен! Получено 100 КМ, но репутация упала.", COLOR_RED);
            }
            else if (choice == "2") {
                printColored("Честная торговля! Предлагают обменять 30 металла на 50 КМ.", COLOR_GREEN);
                if (metal >= 30) {
                    metal -= 30;
                    money += 50;
                    printColored("Обмен совершён!", COLOR_GREEN);
                }
                else {
                    printColored("У вас недостаточно металла для обмена!", COLOR_RED);
                }
            }
            else if (choice == "3") {
                printColored("Караван прошёл мимо. Ничего не получено.", COLOR_YELLOW);
            }
            else {
                printColored("Автоматическое решение: караван пропущен.", COLOR_YELLOW);
            }
        }

        printColored("==================================================", COLOR_RED, true);
    }
}

// Структура для сохранения игры
struct GameSave {
    int money;
    int metal;
    int fuel;
    int food;
    int ammo;
    int population;
    int farmLevel;
    int metalworksLevel;
    int refineryLevel;
    int ammoFactoryLevel;
    int barracksLevel;
    int wallLevel;
    int tradePostLevel;
    int day;
    int aggressionLevel;
    int defenseLevel;
    int lastRaidDay;
    int consecutiveDaysWithoutRaid;
    int difficulty;
    int reputation[3];
    std::map<std::string, int> prices;
};

// Структура для множителей сложности
struct DifficultyMultipliers {
    double resourceMultiplier;
    double productionMultiplier;
    double enemyAggressionBonus;
    double enemyDefenseBonus;
    double raidRewardMultiplier;
    double enemyDamageMultiplier;
    std::string name;
    std::string colorCode;
};

// Функция для случайных событий
void randomEvent(int& money, int& metal, int& fuel, int& food, int& ammo, int& population,
    int day, int wallLevel, int& aggressionLevel, int& defenseLevel,
    const DifficultyMultipliers& multipliers, int tradePostLevel) {

    int eventChance = rand() % 100;
    int eventProbability = 30;
    if (multipliers.enemyAggressionBonus > 0) {
        eventProbability = 35;
    }
    else if (multipliers.enemyAggressionBonus < 0) {
        eventProbability = 25;
    }

    if (rand() % 100 < eventProbability) {
        int eventType = rand() % 100;

        if (eventType < 40) {
            if (eventType < 7) {
                int found = static_cast<int>((rand() % 81 + 50) * multipliers.raidRewardMultiplier);
                money += found;
                printColored("\n[СОБЫТИЕ] Найден тайник с корродированными монетами!", COLOR_GREEN, true);
                printColored("  Вы нашли " + std::to_string(found) + " корродированных монет.", COLOR_GREEN);
            }
            else if (eventType < 14) {
                int found = static_cast<int>((rand() % 61 + 40) * multipliers.raidRewardMultiplier);
                metal += found;
                printColored("\n[СОБЫТИЕ] Найден склад металлолома!", COLOR_GREEN, true);
                printColored("  Вы нашли " + std::to_string(found) + " металлолома.", COLOR_GREEN);
            }
            else if (eventType < 21) {
                int found = static_cast<int>((rand() % 61 + 40) * multipliers.raidRewardMultiplier);
                fuel += found;
                printColored("\n[СОБЫТИЕ] Обнаружена цистерна с биотопливом!", COLOR_GREEN, true);
                printColored("  Вы получили " + std::to_string(found) + " биотоплива.", COLOR_GREEN);
            }
            else if (eventType < 28) {
                int found = static_cast<int>((rand() % 101 + 50) * multipliers.raidRewardMultiplier);
                food += found;
                printColored("\n[СОБЫТИЕ] Найден склад рационов!", COLOR_GREEN, true);
                printColored("  Вы получили " + std::to_string(found) + " рационов.", COLOR_GREEN);
            }
            else if (eventType < 35) {
                int found = static_cast<int>((rand() % 41 + 20) * multipliers.raidRewardMultiplier);
                ammo += found;
                printColored("\n[СОБЫТИЕ] Обнаружен арсенал с патронами!", COLOR_GREEN, true);
                printColored("  Вы получили " + std::to_string(found) + " патронов.", COLOR_GREEN);
            }
            else if (eventType < 39) {
                int newcomers = rand() % 6 + 3;
                population += newcomers;
                printColored("\n[СОБЫТИЕ] Группа выживших присоединилась к базе!", COLOR_GREEN, true);
                printColored("  К вам пришли " + std::to_string(newcomers) + " новых бойцов.", COLOR_GREEN);
            }
            else if (eventType < 40) {
                if (defenseLevel > 1) {
                    defenseLevel--;
                    printColored("\n[СОБЫТИЕ] Разведчики нашли слабое место в обороне врага!", COLOR_GREEN, true);
                    printColored("  Оборона врагов снижена до " + std::to_string(defenseLevel) + ".", COLOR_GREEN);
                }
                else {
                    int found = static_cast<int>((rand() % 41 + 30) * multipliers.raidRewardMultiplier);
                    money += found;
                    printColored("\n[СОБЫТИЕ] Разведчики нашли ценные ресурсы!", COLOR_GREEN, true);
                    printColored("  Вы получили " + std::to_string(found) + " корродированных монет.", COLOR_GREEN);
                }
            }
        }
        else if (eventType < 80) {
            if (eventType < 48) {
                int stolen = static_cast<int>((rand() % 41 + 20) * multipliers.enemyDamageMultiplier);
                int resourceType = rand() % 5;
                if (resourceType == 0 && money >= stolen) {
                    money -= stolen;
                    printColored("\n[СОБЫТИЕ] Налётчики украли ресурсы!", COLOR_RED, true);
                    printColored("  Потеряно " + std::to_string(stolen) + " корродированных монет.", COLOR_RED);
                }
                else if (resourceType == 1 && metal >= stolen) {
                    metal -= stolen;
                    printColored("\n[СОБЫТИЕ] Налётчики украли ресурсы!", COLOR_RED, true);
                    printColored("  Потеряно " + std::to_string(stolen) + " металлолома.", COLOR_RED);
                }
                else if (resourceType == 2 && fuel >= stolen) {
                    fuel -= stolen;
                    printColored("\n[СОБЫТИЕ] Налётчики украли ресурсы!", COLOR_RED, true);
                    printColored("  Потеряно " + std::to_string(stolen) + " биотоплива.", COLOR_RED);
                }
                else if (resourceType == 3 && food >= stolen) {
                    food -= stolen;
                    printColored("\n[СОБЫТИЕ] Налётчики украли ресурсы!", COLOR_RED, true);
                    printColored("  Потеряно " + std::to_string(stolen) + " рационов.", COLOR_RED);
                }
                else if (resourceType == 4 && ammo >= stolen) {
                    ammo -= stolen;
                    printColored("\n[СОБЫТИЕ] Налётчики украли ресурсы!", COLOR_RED, true);
                    printColored("  Потеряно " + std::to_string(stolen) + " патронов.", COLOR_RED);
                }
            }
            else if (eventType < 56) {
                int prodLoss = rand() % 3 + 1;
                printColored("\n[СОБЫТИЕ] Авария на производстве!", COLOR_RED, true);
                printColored("  Производство снижено на " + std::to_string(prodLoss) + " дня.", COLOR_RED);
            }
            else if (eventType < 64) {
                int sick = rand() % 5 + 2;
                population -= sick;
                if (population < 0) population = 0;
                printColored("\n[СОБЫТИЕ] Вспышка заболевания!", COLOR_RED, true);
                printColored("  Потеряно " + std::to_string(sick) + " бойцов.", COLOR_RED);
            }
            else if (eventType < 72) {
                int lost = static_cast<int>((rand() % 31 + 10) * multipliers.enemyDamageMultiplier);
                ammo -= lost;
                if (ammo < 0) ammo = 0;
                printColored("\n[СОБЫТИЕ] Взрыв на складе боеприпасов!", COLOR_RED, true);
                printColored("  Потеряно " + std::to_string(lost) + " патронов.", COLOR_RED);
            }
            else if (eventType < 76) {
                if (aggressionLevel < 5) {
                    aggressionLevel++;
                    printColored("\n[СОБЫТИЕ] Враги получили подкрепление!", COLOR_RED, true);
                    printColored("  Агрессия врагов повышена до " + std::to_string(aggressionLevel) + ".", COLOR_RED);
                }
            }
            else if (eventType < 80) {
                if (defenseLevel < 5) {
                    defenseLevel++;
                    printColored("\n[СОБЫТИЕ] Наши разведчики попали в засаду!", COLOR_RED, true);
                    printColored("  Враги усилили оборону до " + std::to_string(defenseLevel) + ".", COLOR_RED);
                }
            }
        }
        else {
            if (eventType < 86) {
                int foodLoss = static_cast<int>((rand() % 41 + 20) * multipliers.enemyDamageMultiplier);
                food -= foodLoss;
                if (food < 0) food = 0;
                printColored("\n[СОБЫТИЕ] Сильный шторм уничтожил часть урожая!", COLOR_YELLOW, true);
                printColored("  Потеряно " + std::to_string(foodLoss) + " рационов.", COLOR_YELLOW);
            }
            else if (eventType < 92) {
                int deserters = rand() % 3 + 1;
                population -= deserters;
                if (population < 0) population = 0;
                printColored("\n[СОБЫТИЕ] Несколько бойцов дезертировали!", COLOR_YELLOW, true);
                printColored("  Потеряно " + std::to_string(deserters) + " бойцов.", COLOR_YELLOW);
            }
            else if (eventType < 96) {
                printColored("\n[СОБЫТИЕ] Опытные бойцы провели тренировку!", COLOR_CYAN, true);
                printColored("  Шанс успеха операций временно повышен.", COLOR_CYAN);
            }
            else if (eventType < 100) {
                printColored("\n[СОБЫТИЕ] Странствующий торговец предлагает обмен!", COLOR_MAGENTA, true);
                printColored("  Появилась возможность выгодного обмена ресурсами.", COLOR_MAGENTA);
                int resourceType = rand() % 5;
                if (resourceType == 0 && money > 50) {
                    money -= 50;
                    food += 80;
                    printColored("  Вы обменяли 50 корродированных монет на 80 рационов.", COLOR_GREEN);
                }
                else if (resourceType == 1 && metal > 50) {
                    metal -= 50;
                    money += 70;
                    printColored("  Вы обменяли 50 металлолома на 70 корродированных монет.", COLOR_GREEN);
                }
                else if (resourceType == 2 && fuel > 40) {
                    fuel -= 40;
                    ammo += 30;
                    printColored("  Вы обменяли 40 биотоплива на 30 патронов.", COLOR_GREEN);
                }
                else if (resourceType == 3 && food > 60) {
                    food -= 60;
                    metal += 50;
                    printColored("  Вы обменяли 60 рационов на 50 металлолома.", COLOR_GREEN);
                }
                else if (resourceType == 4 && ammo > 30) {
                    ammo -= 30;
                    fuel += 50;
                    printColored("  Вы обменяли 30 патронов на 50 биотоплива.", COLOR_GREEN);
                }
                else {
                    printColored("  У вас недостаточно ресурсов для обмена.", COLOR_YELLOW);
                }
            }
        }
    }
}

DifficultyMultipliers getDifficultyMultipliers(int difficulty) {
    DifficultyMultipliers multipliers;
    switch (difficulty) {
    case 0:
        multipliers.resourceMultiplier = 1.5;
        multipliers.productionMultiplier = 1.3;
        multipliers.enemyAggressionBonus = -2;
        multipliers.enemyDefenseBonus = -2;
        multipliers.raidRewardMultiplier = 1.2;
        multipliers.enemyDamageMultiplier = 0.7;
        multipliers.name = "ЛЁГКАЯ";
        multipliers.colorCode = "\033[32m";
        break;
    case 1:
        multipliers.resourceMultiplier = 1.0;
        multipliers.productionMultiplier = 1.0;
        multipliers.enemyAggressionBonus = 0;
        multipliers.enemyDefenseBonus = 0;
        multipliers.raidRewardMultiplier = 1.0;
        multipliers.enemyDamageMultiplier = 1.0;
        multipliers.name = "СРЕДНЯЯ";
        multipliers.colorCode = "\033[33m";
        break;
    case 2:
        multipliers.resourceMultiplier = 0.7;
        multipliers.productionMultiplier = 0.8;
        multipliers.enemyAggressionBonus = 2;
        multipliers.enemyDefenseBonus = 1;
        multipliers.raidRewardMultiplier = 0.8;
        multipliers.enemyDamageMultiplier = 1.3;
        multipliers.name = "СЛОЖНАЯ";
        multipliers.colorCode = "\033[31m";
        break;
    case 3:
        multipliers.resourceMultiplier = 0.4;
        multipliers.productionMultiplier = 0.6;
        multipliers.enemyAggressionBonus = 4;
        multipliers.enemyDefenseBonus = 3;
        multipliers.raidRewardMultiplier = 0.6;
        multipliers.enemyDamageMultiplier = 1.6;
        multipliers.name = "БЕЗУМИЕ";
        multipliers.colorCode = "\033[35m";
        break;
    default:
        multipliers.resourceMultiplier = 1.0;
        multipliers.productionMultiplier = 1.0;
        multipliers.enemyAggressionBonus = 0;
        multipliers.enemyDefenseBonus = 0;
        multipliers.raidRewardMultiplier = 1.0;
        multipliers.enemyDamageMultiplier = 1.0;
        multipliers.name = "СРЕДНЯЯ";
        multipliers.colorCode = "\033[33m";
        break;
    }
    return multipliers;
}

bool checkPassword() {
    std::ifstream passFile("password.dat");
    std::string savedPassword;

    if (passFile.is_open()) {
        std::getline(passFile, savedPassword);
        passFile.close();

        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         ДОСТУП К ЦЕНТРУ УПРАВЛЕНИЯ", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);

        std::string inputPassword;
        std::cout << "Введите пароль доступа: ";
        std::getline(std::cin, inputPassword);

        if (inputPassword == savedPassword) {
            printColored("Доступ разрешён. Добро пожаловать, командир.", COLOR_GREEN);
            return true;
        }
        else {
            printColored("Неверный пароль! Доступ запрещён.", COLOR_RED);
            return false;
        }
    }
    else {
        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         ПЕРВИЧНАЯ НАСТРОЙКА СИСТЕМЫ", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);

        std::string newPassword;
        std::string confirmPassword;

        std::cout << "Создайте пароль для доступа к Центру Управления: ";
        std::getline(std::cin, newPassword);

        std::cout << "Подтвердите пароль: ";
        std::getline(std::cin, confirmPassword);

        if (newPassword == confirmPassword && !newPassword.empty()) {
            std::ofstream passFileOut("password.dat");
            if (passFileOut.is_open()) {
                passFileOut << newPassword;
                passFileOut.close();
                printColored("Система активирована! Пароль сохранён.", COLOR_GREEN);
                return true;
            }
            else {
                printColored("Ошибка при сохранении пароля!", COLOR_RED);
                return false;
            }
        }
        else {
            if (newPassword.empty()) {
                printColored("Пароль не может быть пустым!", COLOR_RED);
            }
            else {
                printColored("Пароли не совпадают! Повторите настройку.", COLOR_RED);
            }
            return false;
        }
    }
}

void saveGame(const GameSave& save) {
    std::ofstream saveFile("savegame.dat", std::ios::binary);
    if (saveFile.is_open()) {
        saveFile.write(reinterpret_cast<const char*>(&save), sizeof(GameSave));
        saveFile.close();
        printColored("Игра успешно сохранена!", COLOR_GREEN);
    }
    else {
        printColored("Ошибка при сохранении игры!", COLOR_RED);
    }
}

bool loadGame(GameSave& save) {
    std::ifstream saveFile("savegame.dat", std::ios::binary);
    if (saveFile.is_open()) {
        saveFile.read(reinterpret_cast<char*>(&save), sizeof(GameSave));
        saveFile.close();
        printColored("Игра успешно загружена!", COLOR_GREEN);
        return true;
    }
    else {
        printColored("Файл сохранения не найден!", COLOR_RED);
        return false;
    }
}

bool hasSaveGame() {
    std::ifstream saveFile("savegame.dat", std::ios::binary);
    return saveFile.is_open();
}

void deleteSaveGame() {
    if (remove("savegame.dat") == 0) {
        printColored("Сохранение успешно удалено!", COLOR_GREEN);
    }
    else {
        printColored("Ошибка при удалении сохранения или файл не существует!", COLOR_RED);
    }
}

int main() {
    setConsoleEncoding();

    // Показываем логотип и анимацию загрузки
    showLogo();
    loadingAnimation();

    if (!checkPassword()) {
        printColored("Сеанс завершён.", COLOR_RED);
        system("pause");
        return 0;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    int difficulty = 1;

    if (!hasSaveGame()) {
        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         ВЫБОР УРОВНЯ СЛОЖНОСТИ", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);
        printColored("1. ЛЁГКАЯ - Увеличенные ресурсы, слабые враги", COLOR_GREEN, true);
        printColored("2. СРЕДНЯЯ - Сбалансированная игра", COLOR_YELLOW, true);
        printColored("3. СЛОЖНАЯ - Ограниченные ресурсы, сильные враги", COLOR_RED, true);
        printColored("4. БЕЗУМИЕ - Минимум ресурсов, максимальная сложность", COLOR_MAGENTA, true);
        std::string diffChoice;
        std::cout << "\nВаш выбор: ";
        std::getline(std::cin, diffChoice);

        if (diffChoice == "1") {
            difficulty = 0;
            printColored("Выбран уровень: ЛЁГКИЙ. Удачи, командир!", COLOR_GREEN);
        }
        else if (diffChoice == "2") {
            difficulty = 1;
            printColored("Выбран уровень: СРЕДНИЙ. Хорошего выживания!", COLOR_YELLOW);
        }
        else if (diffChoice == "3") {
            difficulty = 2;
            printColored("Выбран уровень: СЛОЖНЫЙ. Будьте осторожны!", COLOR_RED);
        }
        else if (diffChoice == "4") {
            difficulty = 3;
            printColored("Выбран уровень: БЕЗУМИЕ. Вы действительно готовы?", COLOR_MAGENTA);
        }
        else {
            difficulty = 1;
            printColored("Выбран уровень по умолчанию: СРЕДНИЙ", COLOR_YELLOW);
        }
    }

    DifficultyMultipliers multipliers = getDifficultyMultipliers(difficulty);

    int money = static_cast<int>(150 * multipliers.resourceMultiplier);
    int metal = static_cast<int>(100 * multipliers.resourceMultiplier);
    int fuel = static_cast<int>(50 * multipliers.resourceMultiplier);
    int food = static_cast<int>(200 * multipliers.resourceMultiplier);
    int ammo = static_cast<int>(30 * multipliers.resourceMultiplier);
    int population = 20;

    int farmLevel = 1;
    int metalworksLevel = 1;
    int refineryLevel = 1;
    int ammoFactoryLevel = 1;
    int barracksLevel = 1;
    int wallLevel = 1;
    int tradePostLevel = 1;

    int day = 1;

    int aggressionLevel = 1 + static_cast<int>(multipliers.enemyAggressionBonus);
    int defenseLevel = 1 + static_cast<int>(multipliers.enemyDefenseBonus);
    int lastRaidDay = 0;
    int consecutiveDaysWithoutRaid = 0;

    if (aggressionLevel < 1) aggressionLevel = 1;
    if (aggressionLevel > 5) aggressionLevel = 5;
    if (defenseLevel < 1) defenseLevel = 1;
    if (defenseLevel > 5) defenseLevel = 5;

    int reputation[3] = { 0, 0, 0 };

    std::map<std::string, int> prices;
    prices["money"] = 1;
    prices["metal"] = 2;
    prices["fuel"] = 3;
    prices["food"] = 4;
    prices["ammo"] = 5;

    GameSave loadedSave;

    if (hasSaveGame()) {
        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         ОБНАРУЖЕНО СОХРАНЕНИЕ", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);
        printColored("1. Загрузить сохранённую игру", COLOR_GREEN);
        printColored("2. Начать новую игру", COLOR_YELLOW);
        printColored("3. Удалить сохранение и начать новую игру", COLOR_RED);
        std::string loadChoice;
        std::cout << "\nВаш выбор: ";
        std::getline(std::cin, loadChoice);

        if (loadChoice == "1") {
            if (loadGame(loadedSave)) {
                money = loadedSave.money;
                metal = loadedSave.metal;
                fuel = loadedSave.fuel;
                food = loadedSave.food;
                ammo = loadedSave.ammo;
                population = loadedSave.population;
                farmLevel = loadedSave.farmLevel;
                metalworksLevel = loadedSave.metalworksLevel;
                refineryLevel = loadedSave.refineryLevel;
                ammoFactoryLevel = loadedSave.ammoFactoryLevel;
                barracksLevel = loadedSave.barracksLevel;
                wallLevel = loadedSave.wallLevel;
                tradePostLevel = loadedSave.tradePostLevel;
                day = loadedSave.day;
                aggressionLevel = loadedSave.aggressionLevel;
                defenseLevel = loadedSave.defenseLevel;
                lastRaidDay = loadedSave.lastRaidDay;
                consecutiveDaysWithoutRaid = loadedSave.consecutiveDaysWithoutRaid;
                difficulty = loadedSave.difficulty;
                for (int i = 0; i < 3; i++) {
                    reputation[i] = loadedSave.reputation[i];
                }
                prices = loadedSave.prices;
                multipliers = getDifficultyMultipliers(difficulty);
                printColored("Сохранение загружено. Продолжаем, командир!", COLOR_GREEN);
            }
            else {
                printColored("Ошибка загрузки. Начинаем новую игру...", COLOR_YELLOW);
            }
        }
        else if (loadChoice == "2") {
            printColored("Начинаем новую игру...", COLOR_YELLOW);
        }
        else if (loadChoice == "3") {
            deleteSaveGame();
            printColored("Сохранение удалено. Начинаем новую игру...", COLOR_YELLOW);
        }
        else {
            printColored("Неверный выбор. Начинаем новую игру...", COLOR_YELLOW);
        }
    }

    auto showStatus = [&]() {
        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         СТАТУС БАЗЫ (Цикл " + std::to_string(day) + ")", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);

        printColored("Ресурсы:", COLOR_GREEN, true);
        printColored("  Корродированные монеты: " + std::to_string(money), COLOR_YELLOW);
        printColored("  Металлолом:    " + std::to_string(metal), COLOR_WHITE);
        printColored("  Биотопливо:    " + std::to_string(fuel), COLOR_WHITE);
        printColored("  Рационы:       " + std::to_string(food), COLOR_WHITE);
        printColored("  Патроны:       " + std::to_string(ammo), COLOR_WHITE);
        printColored("  Личный состав: " + std::to_string(population), COLOR_WHITE);

        int foodProd = static_cast<int>((15 + farmLevel * 5) * multipliers.productionMultiplier);
        int metalProd = static_cast<int>((10 + metalworksLevel * 5) * multipliers.productionMultiplier);
        int fuelProd = static_cast<int>((8 + refineryLevel * 4) * multipliers.productionMultiplier);
        int ammoProd = static_cast<int>((5 + ammoFactoryLevel * 3) * multipliers.productionMultiplier);
        int foodCons = population;

        // Прогресс-бары ресурсов
        printColored("\nЗаполненность складов:", COLOR_CYAN, true);
        showProgressBar(metal, 500, "  Металлолом:   ", COLOR_WHITE);
        showProgressBar(fuel, 300, "  Биотопливо:   ", COLOR_YELLOW);
        showProgressBar(food, 400, "  Рационы:      ", COLOR_GREEN);
        showProgressBar(ammo, 200, "  Патроны:      ", COLOR_RED);
        showProgressBar(money, 1000, "  КМ:           ", COLOR_YELLOW);
        showProgressBar(population, 100, "  Личный состав:", COLOR_CYAN);

        printColored("\nПроизводственные мощности:", COLOR_GREEN, true);
        printColored("  Рационы:       +" + std::to_string(foodProd) + " (потребление: -" + std::to_string(foodCons) + ")", COLOR_WHITE);
        printColored("  Металлолом:    +" + std::to_string(metalProd), COLOR_WHITE);
        printColored("  Биотопливо:    +" + std::to_string(fuelProd), COLOR_WHITE);
        printColored("  Патроны:       +" + std::to_string(ammoProd), COLOR_WHITE);

        printColored("\nИнфраструктура:", COLOR_GREEN, true);
        printColored("  Агрокомплекс:        ур." + std::to_string(farmLevel), COLOR_WHITE);
        printColored("  Литейный цех:        ур." + std::to_string(metalworksLevel), COLOR_WHITE);
        printColored("  НПЗ:                 ур." + std::to_string(refineryLevel), COLOR_WHITE);
        printColored("  Оружейный арсенал:   ур." + std::to_string(ammoFactoryLevel), COLOR_WHITE);
        printColored("  Штаб операций:       ур." + std::to_string(barracksLevel), COLOR_WHITE);
        printColored("  Оборонительный периметр: ур." + std::to_string(wallLevel), COLOR_WHITE);
        printColored("  Торговый пост:       ур." + std::to_string(tradePostLevel), COLOR_CYAN);

        // Отображаем схему базы
        showBaseMap(farmLevel, metalworksLevel, refineryLevel, ammoFactoryLevel,
            barracksLevel, wallLevel, tradePostLevel);

        printColored("\nРЕПУТАЦИЯ:", COLOR_MAGENTA, true);
        printColored("  Торговцы:    " + std::to_string(reputation[0]) + "/100", COLOR_CYAN);
        printColored("  Военные:     " + std::to_string(reputation[1]) + "/100", COLOR_CYAN);
        printColored("  Поселенцы:   " + std::to_string(reputation[2]) + "/100", COLOR_CYAN);

        printColored("\nСЛОЖНОСТЬ: " + multipliers.name, atoi(multipliers.colorCode.c_str()), true);

        printColored("\nДИНАМИЧЕСКАЯ СЛОЖНОСТЬ:", COLOR_MAGENTA, true);
        printColored("  Агрессия врагов:     " + std::to_string(aggressionLevel) + "/5",
            aggressionLevel <= 2 ? COLOR_GREEN : (aggressionLevel <= 4 ? COLOR_YELLOW : COLOR_RED));
        printColored("  Оборона врагов:      " + std::to_string(defenseLevel) + "/5",
            defenseLevel <= 2 ? COLOR_GREEN : (defenseLevel <= 4 ? COLOR_YELLOW : COLOR_RED));
        if (consecutiveDaysWithoutRaid > 0) {
            printColored("  Дней без операций:   " + std::to_string(consecutiveDaysWithoutRaid), COLOR_YELLOW);
        }

        printColored("==================================================", COLOR_CYAN, true);
        };

    auto getUpgradeCost = [&](const std::string& building, int& metalCost, int& fuelCost) -> bool {
        int level;
        if (building == "farm") level = farmLevel;
        else if (building == "metalworks") level = metalworksLevel;
        else if (building == "refinery") level = refineryLevel;
        else if (building == "ammo_factory") level = ammoFactoryLevel;
        else if (building == "barracks") level = barracksLevel;
        else if (building == "wall") level = wallLevel;
        else if (building == "tradePost") level = tradePostLevel;
        else return false;

        if (level >= 5) return false;

        if (building == "farm") {
            metalCost = static_cast<int>((60 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((30 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "metalworks") {
            metalCost = static_cast<int>((70 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((35 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "refinery") {
            metalCost = static_cast<int>((70 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((35 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "ammo_factory") {
            metalCost = static_cast<int>((80 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((40 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "barracks") {
            metalCost = static_cast<int>((90 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((45 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "wall") {
            metalCost = static_cast<int>((100 + level * 15) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((50 + level * 8) * multipliers.productionMultiplier);
        }
        else if (building == "tradePost") {
            metalCost = static_cast<int>((80 + level * 20) * multipliers.productionMultiplier);
            fuelCost = static_cast<int>((40 + level * 10) * multipliers.productionMultiplier);
        }
        return true;
        };

    auto upgradeBuilding = [&](const std::string& building) {
        int metalCost, fuelCost;
        if (!getUpgradeCost(building, metalCost, fuelCost)) {
            printColored("Достигнут максимальный уровень модернизации!", COLOR_RED, true);
            return;
        }
        if (metal >= metalCost && fuel >= fuelCost) {
            metal -= metalCost;
            fuel -= fuelCost;
            if (building == "farm") farmLevel++;
            else if (building == "metalworks") metalworksLevel++;
            else if (building == "refinery") refineryLevel++;
            else if (building == "ammo_factory") ammoFactoryLevel++;
            else if (building == "barracks") barracksLevel++;
            else if (building == "wall") wallLevel++;
            else if (building == "tradePost") tradePostLevel++;
            printColored("\nМодернизация завершена! Уровень повышен.", COLOR_GREEN, true);
        }
        else {
            printColored("Недостаточно ресурсов! Требуется: Металлолома: " + std::to_string(metalCost) +
                ", Биотоплива: " + std::to_string(fuelCost), COLOR_RED);
        }
        };

    auto trade = [&]() {
        printColored("\n==================================================", COLOR_CYAN, true);
        printColored("         ТОРГОВЫЙ ПОСТ", COLOR_YELLOW, true);
        printColored("==================================================", COLOR_CYAN, true);
        printColored("Уровень торгового поста: " + std::to_string(tradePostLevel), COLOR_CYAN);
        printColored("Репутация с торговцами: " + std::to_string(reputation[0]) + "/100", COLOR_CYAN);

        double reputationBonus = 1.0 - (reputation[0] / 100.0) * 0.3;
        if (reputationBonus < 0.7) reputationBonus = 0.7;

        printColored("Текущая скидка: " + std::to_string(static_cast<int>((1 - reputationBonus) * 100)) + "%", COLOR_GREEN);

        printColored("\nДоступные операции:", COLOR_GREEN, true);
        printColored("1. Купить ресурсы", COLOR_CYAN);
        printColored("2. Продать ресурсы", COLOR_CYAN);
        printColored("3. Обменять ресурсы", COLOR_CYAN);
        printColored("4. Улучшить репутацию (пожертвования)", COLOR_CYAN);
        printColored("0. Выйти", COLOR_CYAN);

        std::string tradeChoice;
        std::cout << "\nВаш выбор: ";
        std::getline(std::cin, tradeChoice);

        if (tradeChoice == "1") {
            printColored("\n--- ПОКУПКА РЕСУРСОВ ---", COLOR_GREEN, true);
            printColored("Цены (в корродированных монетах):", COLOR_WHITE);
            printColored("1. Металлолом - " + std::to_string(static_cast<int>(prices["metal"] * reputationBonus)) + " КМ за единицу", COLOR_WHITE);
            printColored("2. Биотопливо - " + std::to_string(static_cast<int>(prices["fuel"] * reputationBonus)) + " КМ за единицу", COLOR_WHITE);
            printColored("3. Рационы - " + std::to_string(static_cast<int>(prices["food"] * reputationBonus)) + " КМ за единицу", COLOR_WHITE);
            printColored("4. Патроны - " + std::to_string(static_cast<int>(prices["ammo"] * reputationBonus)) + " КМ за единицу", COLOR_WHITE);
            printColored("0. Назад", COLOR_CYAN);

            std::string buyChoice;
            std::cout << "\nЧто хотите купить? ";
            std::getline(std::cin, buyChoice);

            if (buyChoice >= "1" && buyChoice <= "4") {
                std::string resource;
                int price;
                if (buyChoice == "1") { resource = "metal"; price = static_cast<int>(prices["metal"] * reputationBonus); }
                else if (buyChoice == "2") { resource = "fuel"; price = static_cast<int>(prices["fuel"] * reputationBonus); }
                else if (buyChoice == "3") { resource = "food"; price = static_cast<int>(prices["food"] * reputationBonus); }
                else { resource = "ammo"; price = static_cast<int>(prices["ammo"] * reputationBonus); }

                printColored("Текущий запас корродированных монет: " + std::to_string(money), COLOR_WHITE);
                std::string amountStr;
                std::cout << "Сколько единиц купить? ";
                std::getline(std::cin, amountStr);
                int amount = std::stoi(amountStr);
                int totalCost = amount * price;

                if (money >= totalCost) {
                    money -= totalCost;
                    if (resource == "metal") metal += amount;
                    else if (resource == "fuel") fuel += amount;
                    else if (resource == "food") food += amount;
                    else if (resource == "ammo") ammo += amount;
                    printColored("Покупка совершена! Траты: " + std::to_string(totalCost) + " корродированных монет", COLOR_GREEN);
                    reputation[0] = std::min(100, reputation[0] + 1);
                }
                else {
                    printColored("Недостаточно корродированных монет для покупки!", COLOR_RED);
                }
            }
        }
        else if (tradeChoice == "2") {
            printColored("\n--- ПРОДАЖА РЕСУРСОВ ---", COLOR_YELLOW, true);
            printColored("Цены (в корродированных монетах):", COLOR_WHITE);
            printColored("1. Металлолом - " + std::to_string(static_cast<int>(prices["metal"] * 0.5 * reputationBonus)) + " КМ", COLOR_WHITE);
            printColored("2. Биотопливо - " + std::to_string(static_cast<int>(prices["fuel"] * 0.5 * reputationBonus)) + " КМ", COLOR_WHITE);
            printColored("3. Рационы - " + std::to_string(static_cast<int>(prices["food"] * 0.5 * reputationBonus)) + " КМ", COLOR_WHITE);
            printColored("4. Патроны - " + std::to_string(static_cast<int>(prices["ammo"] * 0.5 * reputationBonus)) + " КМ", COLOR_WHITE);
            printColored("0. Назад", COLOR_CYAN);

            std::string sellChoice;
            std::cout << "\nЧто хотите продать? ";
            std::getline(std::cin, sellChoice);

            if (sellChoice >= "1" && sellChoice <= "4") {
                std::string resource;
                int price;
                if (sellChoice == "1") { resource = "metal"; price = static_cast<int>(prices["metal"] * 0.5 * reputationBonus); }
                else if (sellChoice == "2") { resource = "fuel"; price = static_cast<int>(prices["fuel"] * 0.5 * reputationBonus); }
                else if (sellChoice == "3") { resource = "food"; price = static_cast<int>(prices["food"] * 0.5 * reputationBonus); }
                else { resource = "ammo"; price = static_cast<int>(prices["ammo"] * 0.5 * reputationBonus); }

                std::string amountStr;
                std::cout << "Сколько единиц продать? ";
                std::getline(std::cin, amountStr);
                int amount = std::stoi(amountStr);
                int totalGain = amount * price;

                if (resource == "metal" && metal >= amount) {
                    metal -= amount;
                    money += totalGain;
                    printColored("Продажа совершена! Получено: " + std::to_string(totalGain) + " корродированных монет", COLOR_GREEN);
                }
                else if (resource == "fuel" && fuel >= amount) {
                    fuel -= amount;
                    money += totalGain;
                    printColored("Продажа совершена! Получено: " + std::to_string(totalGain) + " корродированных монет", COLOR_GREEN);
                }
                else if (resource == "food" && food >= amount) {
                    food -= amount;
                    money += totalGain;
                    printColored("Продажа совершена! Получено: " + std::to_string(totalGain) + " корродированных монет", COLOR_GREEN);
                }
                else if (resource == "ammo" && ammo >= amount) {
                    ammo -= amount;
                    money += totalGain;
                    printColored("Продажа совершена! Получено: " + std::to_string(totalGain) + " корродированных монет", COLOR_GREEN);
                }
                else {
                    printColored("Недостаточно ресурсов для продажи!", COLOR_RED);
                }
            }
        }
        else if (tradeChoice == "3") {
            printColored("\n--- ОБМЕН РЕСУРСОВ ---", COLOR_CYAN, true);
            printColored("Доступные обмены:", COLOR_WHITE);
            printColored("1. 50 металлолома -> 30 биотоплива", COLOR_WHITE);
            printColored("2. 40 биотоплива -> 50 рационов", COLOR_WHITE);
            printColored("3. 60 рационов -> 40 патронов", COLOR_WHITE);
            printColored("4. 30 патронов -> 60 металлолома", COLOR_WHITE);
            printColored("0. Назад", COLOR_CYAN);

            std::string exchangeChoice;
            std::cout << "\nВыберите обмен: ";
            std::getline(std::cin, exchangeChoice);

            if (exchangeChoice == "1" && metal >= 50) {
                metal -= 50;
                fuel += 30;
                printColored("Обмен выполнен! -50 металлолома, +30 биотоплива", COLOR_GREEN);
            }
            else if (exchangeChoice == "2" && fuel >= 40) {
                fuel -= 40;
                food += 50;
                printColored("Обмен выполнен! -40 биотоплива, +50 рационов", COLOR_GREEN);
            }
            else if (exchangeChoice == "3" && food >= 60) {
                food -= 60;
                ammo += 40;
                printColored("Обмен выполнен! -60 рационов, +40 патронов", COLOR_GREEN);
            }
            else if (exchangeChoice == "4" && ammo >= 30) {
                ammo -= 30;
                metal += 60;
                printColored("Обмен выполнен! -30 патронов, +60 металлолома", COLOR_GREEN);
            }
            else if (exchangeChoice != "0") {
                printColored("Недостаточно ресурсов для обмена!", COLOR_RED);
            }
        }
        else if (tradeChoice == "4") {
            printColored("\n--- УЛУЧШЕНИЕ РЕПУТАЦИИ ---", COLOR_MAGENTA, true);
            printColored("Пожертвования улучшают репутацию и дают скидки", COLOR_CYAN);
            printColored("Текущая репутация: " + std::to_string(reputation[0]) + "/100", COLOR_CYAN);
            std::string donateStr;
            std::cout << "Сколько корродированных монет пожертвовать? ";
            std::getline(std::cin, donateStr);
            int donate = std::stoi(donateStr);

            if (money >= donate && donate > 0) {
                money -= donate;
                int repGain = donate / 10;
                reputation[0] = std::min(100, reputation[0] + repGain);
                printColored("Пожертвование принято! Репутация повышена на " + std::to_string(repGain), COLOR_GREEN);
            }
            else {
                printColored("Недостаточно корродированных монет для пожертвования!", COLOR_RED);
            }
        }
        };

    auto updateDifficulty = [&](bool raidPerformed) {
        if (raidPerformed) {
            consecutiveDaysWithoutRaid = 0;
            lastRaidDay = day;
            if (defenseLevel < 5) {
                defenseLevel++;
                printColored("\n[СИСТЕМА] Враги усилили оборону! Уровень защиты врагов повышен до " +
                    std::to_string(defenseLevel) + ".", COLOR_YELLOW);
            }
            if (defenseLevel >= 3 && aggressionLevel < 5 && (day - lastRaidDay) < 3) {
                aggressionLevel++;
                printColored("[СИСТЕМА] Враги заметили вашу активность! Агрессия врагов повышена до " +
                    std::to_string(aggressionLevel) + ".", COLOR_RED);
            }
        }
        else {
            consecutiveDaysWithoutRaid++;
            if (consecutiveDaysWithoutRaid >= 3 && aggressionLevel < 5) {
                aggressionLevel++;
                printColored("\n[СИСТЕМА] Враги осмелели из-за вашего бездействия! Агрессия врагов повышена до " +
                    std::to_string(aggressionLevel) + ".", COLOR_RED);
                consecutiveDaysWithoutRaid = 0;
            }
        }

        int totalResources = money + metal + fuel + food + ammo;
        if (population < 5 || totalResources < 100) {
            if (aggressionLevel > 1) {
                aggressionLevel--;
                printColored("\n[СИСТЕМА] Враги ослабили натиск, видя ваше тяжёлое положение. Агрессия снижена до " +
                    std::to_string(aggressionLevel) + ".", COLOR_GREEN);
            }
            if (defenseLevel > 1 && defenseLevel > aggressionLevel) {
                defenseLevel--;
                printColored("[СИСТЕМА] Вражеская оборона ослабла. Уровень защиты врагов снижен до " +
                    std::to_string(defenseLevel) + ".", COLOR_GREEN);
            }
        }

        if (totalResources > 1500 && aggressionLevel < 5) {
            aggressionLevel++;
            printColored("\n[СИСТЕМА] Враги охотятся за вашими богатствами! Агрессия повышена до " +
                std::to_string(aggressionLevel) + ".", COLOR_RED);
        }
        };

    auto processDay = [&]() {
        urgentEvent(money, metal, fuel, food, ammo, population, day, wallLevel, barracksLevel);

        randomEvent(money, metal, fuel, food, ammo, population, day, wallLevel, aggressionLevel, defenseLevel, multipliers, tradePostLevel);

        int tradeIncome = tradePostLevel * 3;
        money += tradeIncome;
        printColored("\nТорговый пост принёс доход: +" + std::to_string(tradeIncome) + " корродированных монет", COLOR_CYAN);

        int foodProd = static_cast<int>((15 + farmLevel * 5) * multipliers.productionMultiplier);
        int metalProd = static_cast<int>((10 + metalworksLevel * 5) * multipliers.productionMultiplier);
        int fuelProd = static_cast<int>((8 + refineryLevel * 4) * multipliers.productionMultiplier);
        int ammoProd = static_cast<int>((5 + ammoFactoryLevel * 3) * multipliers.productionMultiplier);

        food += foodProd;
        metal += metalProd;
        fuel += fuelProd;
        ammo += ammoProd;

        int foodCons = population;
        food -= foodCons;

        printColored("\n--- ОТЧЁТ ЗА ЦИКЛ " + std::to_string(day) + " ---", COLOR_CYAN, true);
        printColored("Произведено: рационы +" + std::to_string(foodProd) + ", металлолом +" + std::to_string(metalProd) +
            ", биотопливо +" + std::to_string(fuelProd) + ", патроны +" + std::to_string(ammoProd), COLOR_GREEN);
        printColored("Потреблено рационов: -" + std::to_string(foodCons), COLOR_YELLOW);

        if (food < 0) {
            int starvation = -food;
            population -= starvation;
            food = 0;
            printColored("Критическая нехватка рационов! " + std::to_string(starvation) + " бойцов потеряно.", COLOR_RED);
        }

        int attackChance = 20 + aggressionLevel * 4;
        if (rand() % 100 < attackChance) {
            double defense = 1.0 - wallLevel * 0.1;
            if (defense < 0.5) defense = 0.5;

            int baseMoney = static_cast<int>(((rand() % 41 + 20) + (aggressionLevel - 1) * 8) * multipliers.enemyDamageMultiplier);
            int baseMetal = static_cast<int>(((rand() % 51 + 20) + (aggressionLevel - 1) * 10) * multipliers.enemyDamageMultiplier);
            int baseFuel = static_cast<int>(((rand() % 46 + 15) + (aggressionLevel - 1) * 8) * multipliers.enemyDamageMultiplier);
            int baseFood = static_cast<int>(((rand() % 61 + 30) + (aggressionLevel - 1) * 12) * multipliers.enemyDamageMultiplier);
            int baseAmmo = static_cast<int>(((rand() % 41 + 10) + (aggressionLevel - 1) * 8) * multipliers.enemyDamageMultiplier);
            int basePop = static_cast<int>(((rand() % 9 + 2) + (aggressionLevel - 1) * 2) * multipliers.enemyDamageMultiplier);

            double multiplier = 1.0 + day / 100.0;
            if (multiplier > 3.0) multiplier = 3.0;

            int moneyLoss = static_cast<int>(baseMoney * defense * multiplier);
            int metalLoss = static_cast<int>(baseMetal * defense * multiplier);
            int fuelLoss = static_cast<int>(baseFuel * defense * multiplier);
            int foodLoss = static_cast<int>(baseFood * defense * multiplier);
            int ammoLoss = static_cast<int>(baseAmmo * defense * multiplier);
            int popLoss = static_cast<int>(basePop * defense * multiplier);

            moneyLoss = (std::min)(moneyLoss, money);
            metalLoss = (std::min)(metalLoss, metal);
            fuelLoss = (std::min)(fuelLoss, fuel);
            foodLoss = (std::min)(foodLoss, food);
            ammoLoss = (std::min)(ammoLoss, ammo);
            popLoss = (std::min)(popLoss, population);

            money -= moneyLoss;
            metal -= metalLoss;
            fuel -= fuelLoss;
            food -= foodLoss;
            ammo -= ammoLoss;
            population -= popLoss;

            printColored("\nВНИМАНИЕ! ВРАЖЕСКАЯ АТАКА!", COLOR_RED, true);
            printColored("Уровень агрессии врагов: " + std::to_string(aggressionLevel) + "/5", COLOR_RED);
            printColored("Потери: КМ -" + std::to_string(moneyLoss) + ", металлолом -" + std::to_string(metalLoss) +
                ", биотопливо -" + std::to_string(fuelLoss) + ", рационы -" + std::to_string(foodLoss) +
                ", патроны -" + std::to_string(ammoLoss) + ", личный состав -" + std::to_string(popLoss), COLOR_RED);
            printColored("Оборонительный периметр снизил урон на " + std::to_string(static_cast<int>((1 - defense) * 100)) + "%", COLOR_YELLOW);
        }

        money = (std::max)(0, money);
        metal = (std::max)(0, metal);
        fuel = (std::max)(0, fuel);
        food = (std::max)(0, food);
        ammo = (std::max)(0, ammo);
        population = (std::max)(0, population);

        if (population <= 0) {
            printColored("\n==================================================", COLOR_RED, true);
            printColored("БАЗА ПАЛА", COLOR_RED, true);
            printColored("Все защитники погибли... Центр управления уничтожен.", COLOR_RED);
            printColored("База продержалась " + std::to_string(day) + " циклов.", COLOR_RED);
            printColored("Сложность: " + multipliers.name, COLOR_RED);
            printColored("==================================================", COLOR_RED, true);

            printColored("\nЖелаете удалить сохранение?", COLOR_YELLOW);
            printColored("1. Да, удалить", COLOR_RED);
            printColored("2. Нет, оставить", COLOR_GREEN);
            std::string deleteChoice;
            std::cout << "Ваш выбор: ";
            std::getline(std::cin, deleteChoice);
            if (deleteChoice == "1") {
                deleteSaveGame();
            }
            exit(0);
        }

        day++;
        };

    auto performRaid = [&](const std::string& difficultyType) {
        int ammoCost, fuelCost, diffMod, successBase;
        if (difficultyType == "easy") {
            ammoCost = static_cast<int>(5 * multipliers.productionMultiplier);
            fuelCost = static_cast<int>(5 * multipliers.productionMultiplier);
            diffMod = 20;
            successBase = 30;
        }
        else if (difficultyType == "medium") {
            ammoCost = static_cast<int>(10 * multipliers.productionMultiplier);
            fuelCost = static_cast<int>(8 * multipliers.productionMultiplier);
            diffMod = 0;
            successBase = 30;
        }
        else {
            ammoCost = static_cast<int>(20 * multipliers.productionMultiplier);
            fuelCost = static_cast<int>(15 * multipliers.productionMultiplier);
            diffMod = -10;
            successBase = 30;
        }

        if (ammo < ammoCost || fuel < fuelCost) {
            printColored("Недостаточно ресурсов для операции!", COLOR_RED);
            return;
        }
        if (population < 3) {
            printColored("Недостаточно личного состава для операции (минимум 3).", COLOR_RED);
            return;
        }

        ammo -= ammoCost;
        fuel -= fuelCost;

        int successChance = successBase + barracksLevel * 10 + diffMod - defenseLevel * 5;
        successChance = (std::min)(90, (std::max)(5, successChance));
        int roll = rand() % 100 + 1;

        printColored("\nОтряд выдвинулся...", COLOR_YELLOW);
        printColored("Уровень обороны врагов: " + std::to_string(defenseLevel) + "/5", COLOR_CYAN);
        printColored("Шанс успеха операции: " + std::to_string(successChance) + "%", COLOR_YELLOW);

        if (roll <= successChance) {
            int moneyLoot, metalLoot, fuelLoot, foodLoot, ammoLoot, popLoot;
            int defensePenalty = 1 - (defenseLevel - 1) * 0.05;
            if (defensePenalty < 0.7) defensePenalty = 0.7;

            if (difficultyType == "easy") {
                moneyLoot = static_cast<int>(((rand() % 41 + 30) * defensePenalty) * multipliers.raidRewardMultiplier);
                metalLoot = static_cast<int>(((rand() % 31 + 20) * defensePenalty) * multipliers.raidRewardMultiplier);
                fuelLoot = static_cast<int>(((rand() % 31 + 20) * defensePenalty) * multipliers.raidRewardMultiplier);
                foodLoot = static_cast<int>(((rand() % 51 + 40) * defensePenalty) * multipliers.raidRewardMultiplier);
                ammoLoot = static_cast<int>(((rand() % 16 + 10) * defensePenalty) * multipliers.raidRewardMultiplier);
                popLoot = rand() % 4 + 2;
            }
            else if (difficultyType == "medium") {
                moneyLoot = static_cast<int>(((rand() % 71 + 50) * defensePenalty) * multipliers.raidRewardMultiplier);
                metalLoot = static_cast<int>(((rand() % 51 + 40) * defensePenalty) * multipliers.raidRewardMultiplier);
                fuelLoot = static_cast<int>(((rand() % 41 + 30) * defensePenalty) * multipliers.raidRewardMultiplier);
                foodLoot = static_cast<int>(((rand() % 71 + 60) * defensePenalty) * multipliers.raidRewardMultiplier);
                ammoLoot = static_cast<int>(((rand() % 21 + 15) * defensePenalty) * multipliers.raidRewardMultiplier);
                popLoot = rand() % 5 + 3;
            }
            else {
                moneyLoot = static_cast<int>(((rand() % 101 + 80) * defensePenalty) * multipliers.raidRewardMultiplier);
                metalLoot = static_cast<int>(((rand() % 81 + 70) * defensePenalty) * multipliers.raidRewardMultiplier);
                fuelLoot = static_cast<int>(((rand() % 71 + 60) * defensePenalty) * multipliers.raidRewardMultiplier);
                foodLoot = static_cast<int>(((rand() % 101 + 90) * defensePenalty) * multipliers.raidRewardMultiplier);
                ammoLoot = static_cast<int>(((rand() % 36 + 25) * defensePenalty) * multipliers.raidRewardMultiplier);
                popLoot = rand() % 7 + 4;
            }

            money += moneyLoot;
            metal += metalLoot;
            fuel += fuelLoot;
            food += foodLoot;
            ammo += ammoLoot;
            population += popLoot;

            printColored("ОПЕРАЦИЯ УСПЕШНА! Захвачены ресурсы противника.", COLOR_GREEN, true);
            printColored("  +" + std::to_string(moneyLoot) + " КМ, +" + std::to_string(metalLoot) + " металлолома, +" + std::to_string(fuelLoot) +
                " биотоплива, +" + std::to_string(foodLoot) + " рационов, +" + std::to_string(ammoLoot) +
                " патронов, +" + std::to_string(popLoot) + " бойцов", COLOR_GREEN);

            reputation[1] = std::min(100, reputation[1] + 2);

            updateDifficulty(true);
        }
        else {
            int popLoss = rand() % 6 + 3;
            popLoss -= barracksLevel / 2;
            if (popLoss < 1) popLoss = 1;
            population -= popLoss;
            printColored("ОПЕРАЦИЯ ПРОВАЛЕНА! Отряд попал в засаду.", COLOR_RED, true);
            printColored("  Потеряно " + std::to_string(popLoss) + " бойцов.", COLOR_RED);

            if (defenseLevel > 1) {
                defenseLevel--;
                printColored("[СИСТЕМА] Враги празднуют победу и ослабили бдительность. Оборона снижена до " +
                    std::to_string(defenseLevel) + ".", COLOR_GREEN);
            }

            updateDifficulty(true);
        }

        processDay();
        };

    printColored("\n============================================================", COLOR_CYAN, true);
    printColored("        ЦЕНТР УПРАВЛЕНИЯ БАЗОЙ \"ЦИТАДЕЛЬ\"", COLOR_YELLOW, true);
    printColored("        Версия 3.7 | Визуализация активирована", COLOR_YELLOW);
    printColored("============================================================", COLOR_CYAN, true);
    printColored("ВНИМАНИЕ! В игре появились срочные события с ограниченным временем!", COLOR_RED, true);
    printColored("На принятие решений даётся всего 8 секунд!", COLOR_RED, true);
    printColored("============================================================", COLOR_CYAN, true);

    std::string choice;
    while (true) {
        printColored("\nГЛАВНОЕ МЕНЮ", COLOR_MAGENTA, true);
        printColored("1. Сводка по базе", COLOR_CYAN);
        printColored("2. Модернизация инфраструктуры", COLOR_CYAN);
        printColored("3. Тактическая операция", COLOR_CYAN);
        printColored("4. Тактическая пауза (пропустить цикл)", COLOR_CYAN);
        printColored("5. Торговый пост", COLOR_CYAN);
        printColored("6. Сохранить игру", COLOR_CYAN);
        printColored("7. Управление сохранениями", COLOR_CYAN);
        printColored("8. Завершить сеанс", COLOR_CYAN);

        std::cout << "\nВведите команду: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            showStatus();
        }
        else if (choice == "2") {
            while (true) {
                printColored("\n--- МОДЕРНИЗАЦИЯ ---", COLOR_MAGENTA, true);
                printColored("0. Назад", COLOR_CYAN);
                printColored("1. Агрокомплекс (уровень " + std::to_string(farmLevel) + ")", COLOR_WHITE);
                printColored("2. Литейный цех (уровень " + std::to_string(metalworksLevel) + ")", COLOR_WHITE);
                printColored("3. НПЗ (уровень " + std::to_string(refineryLevel) + ")", COLOR_WHITE);
                printColored("4. Оружейный арсенал (уровень " + std::to_string(ammoFactoryLevel) + ")", COLOR_WHITE);
                printColored("5. Штаб операций (уровень " + std::to_string(barracksLevel) + ")", COLOR_WHITE);
                printColored("6. Оборонительный периметр (уровень " + std::to_string(wallLevel) + ")", COLOR_WHITE);
                printColored("7. Торговый пост (уровень " + std::to_string(tradePostLevel) + ")", COLOR_CYAN);

                std::string upChoice;
                std::cout << "\nВыберите объект для модернизации: ";
                std::getline(std::cin, upChoice);
                if (upChoice == "0") break;
                else if (upChoice == "1") { upgradeBuilding("farm"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "2") { upgradeBuilding("metalworks"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "3") { upgradeBuilding("refinery"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "4") { upgradeBuilding("ammo_factory"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "5") { upgradeBuilding("barracks"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "6") { upgradeBuilding("wall"); updateDifficulty(false); processDay(); break; }
                else if (upChoice == "7") { upgradeBuilding("tradePost"); updateDifficulty(false); processDay(); break; }
                else printColored("Неверная команда.", COLOR_RED);
            }
        }
        else if (choice == "3") {
            if (population < 3) {
                printColored("Недостаточно личного состава для операции (минимум 3).", COLOR_RED);
                continue;
            }
            printColored("\n--- ПЛАНИРОВАНИЕ ОПЕРАЦИИ ---", COLOR_MAGENTA, true);
            printColored("Текущий уровень обороны врагов: " + std::to_string(defenseLevel) + "/5", COLOR_YELLOW);
            printColored("1. Разведка (5 патронов, 5 биотоплива)", COLOR_WHITE);
            printColored("2. Штурм (10 патронов, 8 биотоплива)", COLOR_WHITE);
            printColored("3. Полномасштабная атака (20 патронов, 15 биотоплива)", COLOR_WHITE);
            printColored("0. Отмена", COLOR_CYAN);
            std::string raidChoice;
            std::cout << "\nВыберите тип операции: ";
            std::getline(std::cin, raidChoice);
            if (raidChoice == "1") performRaid("easy");
            else if (raidChoice == "2") performRaid("medium");
            else if (raidChoice == "3") performRaid("hard");
            else if (raidChoice != "0") printColored("Неверная команда.", COLOR_RED);
        }
        else if (choice == "4") {
            printColored("\nТактическая пауза. База восстанавливается...", COLOR_CYAN);
            updateDifficulty(false);
            processDay();
        }
        else if (choice == "5") {
            if (tradePostLevel > 0) {
                trade();
            }
            else {
                printColored("Торговый пост не построен! Сначала модернизируйте его.", COLOR_RED);
            }
        }
        else if (choice == "6") {
            GameSave currentSave;
            currentSave.money = money;
            currentSave.metal = metal;
            currentSave.fuel = fuel;
            currentSave.food = food;
            currentSave.ammo = ammo;
            currentSave.population = population;
            currentSave.farmLevel = farmLevel;
            currentSave.metalworksLevel = metalworksLevel;
            currentSave.refineryLevel = refineryLevel;
            currentSave.ammoFactoryLevel = ammoFactoryLevel;
            currentSave.barracksLevel = barracksLevel;
            currentSave.wallLevel = wallLevel;
            currentSave.tradePostLevel = tradePostLevel;
            currentSave.day = day;
            currentSave.aggressionLevel = aggressionLevel;
            currentSave.defenseLevel = defenseLevel;
            currentSave.lastRaidDay = lastRaidDay;
            currentSave.consecutiveDaysWithoutRaid = consecutiveDaysWithoutRaid;
            currentSave.difficulty = difficulty;
            for (int i = 0; i < 3; i++) {
                currentSave.reputation[i] = reputation[i];
            }
            currentSave.prices = prices;

            saveGame(currentSave);
        }
        else if (choice == "7") {
            printColored("\n--- УПРАВЛЕНИЕ СОХРАНЕНИЯМИ ---", COLOR_MAGENTA, true);
            if (hasSaveGame()) {
                printColored("Обнаружено сохранение игры.", COLOR_GREEN);
                printColored("1. Удалить сохранение", COLOR_RED);
                printColored("0. Назад", COLOR_CYAN);
                std::string manageChoice;
                std::cout << "\nВаш выбор: ";
                std::getline(std::cin, manageChoice);
                if (manageChoice == "1") {
                    deleteSaveGame();
                }
            }
            else {
                printColored("Сохранений не найдено.", COLOR_YELLOW);
            }
        }
        else if (choice == "8") {
            printColored("Завершение сеанса. Связь с Центром управления прекращена.", COLOR_YELLOW);
            break;
        }
        else {
            printColored("Неверная команда. Используйте цифры 1-8.", COLOR_RED);
        }
    }

    return 0;
}