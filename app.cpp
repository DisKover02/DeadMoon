#include <string>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <cstring>
#include <conio.h>


using namespace std;

int randomNum(int min, int max) {
    return  min + rand() % (max - min + 1);
}

void clickContinue() {
    cout << endl << "Нажміть Enter або Space щоб продовжити" << endl;
    while (bool x = true) {
        int key = _getch();
        if (key == 13 || key == 32) {
            x = false;
            break;
        }
    }
}

class BasePerson {
protected:
    int hp = 0;
    int hpMax = 0;
    int energy = 0;
    int level = 0;
    string name = "";
public:
    BasePerson(string name, int level, int energy, int hp) {
        this->level = level;
        this->energy = energy;
        this->hp = hp;
        this->name = name;
    }

    int getLevel() { return level; }
    void setLevel(int valueLevel) { level = valueLevel; }

    int getEnergy() { return energy; }
    void setEnergy(int valueEnergy) { energy = valueEnergy; }

    int getHp() { return hp; }
    void setHp(int valueHp) {
        if (valueHp > this->hpMax) {
            this->hp = this->hpMax;
        }
        else {
            this->hp = valueHp;
        }
    }
};

class Items {
protected:
    string name = "";
    int price;
public:
    Items(string name, int price) {
        this->name = name;
        this->price = price;
    }

    string getName() { return name; }
    void setName(string valueName) { name = valueName; }

    int getPrice() { return price; }
    void setPrice(int valuePrice) { price = valuePrice; }
};

class Armor : public Items {
private:
    int protection;
public:
    Armor(string name, int protection, int price) : Items(name, price) {

        this->protection = protection;
    }


    int getProtection() { return protection; }
    void setProtection(int valueProtection) { protection = valueProtection; }

    ~Armor() {
    }
};

class Weapon : public Items {
private:
    int damage;
public:
    Weapon(string name, int damage, int price) : Items(name, price) {
        this->damage = damage;
        this->price = this->damage * 200;
    }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    ~Weapon() {

    }
};

class Player : public BasePerson {
private:
    Weapon* weapon = NULL;
    Armor* armor = NULL;
    int miss;
    int xp;
    int damage;
    int block;
    int chanceBlock;
    int money = 0;
public:
    Player(string name, int energy, int hp, int miss, int xp, int damage, int block, int chanceBlock, int money) : BasePerson(name, 1, energy, hp) {
        this->damage = damage;//strenght
        this->block = block;//endurance
        this->xp = xp;
        this->miss = miss;//agility
        this->chanceBlock = chanceBlock;
        this->money = money;
    }

    void setWeapon(Weapon* weapon) {
        this->weapon = weapon;
    }

    void setArmor(Armor* armor) {
        this->armor = armor;
    }

    int getMoney() { return this->money; }
    void setMoney(int valueMoney) { this->money = valueMoney; }

    int getChanceBlock() { return chanceBlock; }
    void setChanceBlock(int valueChanceBlock) { chanceBlock = valueChanceBlock; }

    int getMiss() { return miss; }
    void setMiss(int valueMiss) { miss = valueMiss; }

    int getXP() { return xp; }
    void setXP(int valueXP) { xp = valueXP; }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    int getBlock() { return block; }
    void setBlock(int valueBlock) { block = valueBlock; }

    void showStaticPlayer() {
        cout << "lvl = " << getLevel() << endl << "Energy = " << getEnergy() << endl << "Damage = " << getDamage() << endl << "Block damage = " << getBlock() << endl << "Hp = " << getHp() << endl << "XP = " << getXP() << endl << "Agility = " << getMiss() << "%" << endl << "Money = " << getMoney();
    }

    int damageWithWeapon() {
        this->setDamage(this->getDamage() + this->weapon->getDamage());
        return this->getDamage();
    }
    int blockWithArmor() {
        this->setBlock(this->getBlock() + this->armor->getProtection());
        return this->getBlock();
    }
    ~Player() {

    }
};

class Monsters : public BasePerson {
private:

    int scoreGet;
    int damage;
    int block;
    int chanceBlock;
    int moneyGet;

    int HpBoss = 300;
    int DamageBoss = 30;
    int ScoreGetBoss = 150;
public:
    Monsters(string name, int scoreGet, int level, int energy, int damage, int block, int hp, int chanceBlock, int moneyGet) : BasePerson(name, level, energy, hp) {
        this->scoreGet = scoreGet;
        this->damage = damage;
        this->block = block;
        this->chanceBlock = chanceBlock;
    }
    //boss
    int getHpBoss() { return HpBoss; }
    void setHpBoss(int valueHpBoss) { HpBoss = valueHpBoss; }

    int getDamageBoss() { return DamageBoss; }
    void setDamageBoss(int valueDamageBoss) { DamageBoss = valueDamageBoss; }

    int getScoreGetBoss() { return ScoreGetBoss; }
    void setScoreGetBoss(int valueScoreGetBoss) { ScoreGetBoss = valueScoreGetBoss; }

    //monsters

    int getMoneyGet() { return moneyGet; }
    void setMoneyGet(int valueMoneyGet) { moneyGet = valueMoneyGet; }

    string getName() { return name; }
    void setName(string valueName) { name = valueName; }

    int getChanceBlock() { return chanceBlock; }
    void setChanceBlock(int valueChanceBlock) { chanceBlock = valueChanceBlock; }

    int getScoreGet() { return scoreGet; }
    void setScoreGet(int valueScoreGet) { scoreGet = valueScoreGet; }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    int getBlock() { return block; }
    void setBlock(int valueBlock) { block = valueBlock; }



    ~Monsters() {

    }
};





class Engine {
private:
    vector <string> masName{ "Дікарь", "Ригач", "Соплежуй", "Лазун", "Паркурщик", "Лопатокрил",  "Хітман", "Очкарик", "ТікТокер", "Лінкольн Абрамс", "Ходунок", "Весельнік", "Камнебуй", "Дедінсайд" };
    vector <string> armorName = { "Кольчужна Броня", "Металева Броня", "Броня Бога", "Броня Ада", "Кожана Броня" };
    vector <string> weaponName = { "Кристалис", "Башер", "Даедалус", "ЕхоСабре", "Кая", "Яша", "Сендж" };

    int randomNum(int min, int max) {
        return  min + rand() % (max - min + 1);
    }
    string generateName(bool isWeapon = false) {
        if (isWeapon) {
            return this->weaponName[randomNum(0, this->weaponName.size())];
        }
        else {
            return this->armorName[randomNum(0, this->armorName.size())];
        }
    }

    string generateMonsterName(int location) {
        int x = 0, y = 0;

        if (location == 1)
        {
            y = 2;
        }
        else if (location == 2) {
            x = 3; y = 7;
        }
        else if (location == 3) {
            x = 7; y = 10;
        }
        else if (location == 3) {
            x = 10; y = 13;
        }

        string tmp = this->masName[2];

        return this->masName[this->randomNum(x, y)];
    }


public:

    Weapon* regenerateWeapon() {
        return new Weapon(generateName(true), randomNum(3, 20), 1200);
    }
    Armor* regenerateArmor() {
        return new Armor(generateName(), randomNum(3, 20), 1500);
    }

    Player* createPlayer(string name, int classType) {
        int block = 10, damage = 20, miss = 5;

        if (classType == 1) {
            block *= 2;
        }
        else if (classType == 2) {
            damage *= 2;
        }
        else {
            miss *= 2;
        }

        return new Player(name, 30, 45, miss, 0, damage, block, 10, 0);
    }

    void converterXP(Player* player) {
        int convertXp = 100;
        if (player->getXP() >= convertXp) {
            convertXp += 50;
            player->setLevel(player->getLevel() + 1);
            cout << endl << "Поздравляю! у вас" << player->getLevel() << " lvl";
            player->setXP(0);

            player->setHp(player->getHp() + 10); // hp
            player->setDamage(player->getDamage() + 3); // damage
            player->setMiss(player->getMiss() + 1); // miss
            player->setBlock(player->getBlock() + 3); // block
            player->setChanceBlock(player->getChanceBlock() + 1); // chanceBlock

            clickContinue();
        }
    }
    Monsters* generateMonster(int level, int location, bool isBoss = false) {

        int mod = 1;

        if (isBoss) {
            mod = 3;
        }

        if (level > 1) {
            if (rand() % 3 == 1) {
                level++;
            }
            else if (rand() % 3 == 2) {
                level--;
            }
        }
        else {
            if (rand() % 1 == 1) {
                level++;
            }
        }

        return new Monsters(
                this->generateMonsterName(location),
                50 * level * mod,
                level,
                30 * level * mod,
                15 * level * mod,
                10 * level * mod,
                50 * level * mod,
                level,
                90 * level
        );//string name, int scoreGet, int level, int energy, int damage, int block, int hp, int chanceBlock, int moneyGet
    }
};

class Event {
private:
    Engine* engine = NULL;
    vector<Weapon*> weaponList;
    vector<Armor*> armorList;

    bool checkMoney(int playerMoney, int price) {
        if (price <= playerMoney) {
            return true;
        }

        return false;
    }

public:
    Event(Engine* engine) {
        this->engine = engine;
    }

    void shop(Player* player, Weapon* weapon, Armor* armor) {
        while (bool x = true) {
            int choiceShop;
            int choiceProduct;
            int pos = 0;

            cout << "Що ви хочете зробити?" << endl << "1)Купити Меч" << endl << "2)Купити Броню" << endl << "3)Вийти з магазина" << endl;
            cin >> choiceShop;
            if (choiceShop == 1) {


                if (weaponList.empty()) {
                    for (int i = 0; i < 1 + rand() % 3; i++) {
                        weaponList.push_back(this->engine->regenerateWeapon());
                    }
                }


                cout << "Який меч ви хочете купити?" << endl;

                for (int i = 0; i < 1 + rand() % 3; i++) {
                    cout << i + 1 << ") " << weaponList[i]->getName() << " " << weaponList[i]->getPrice() << endl;
                }

                cin >> pos;


                if (pos == 1) {
                    if (this->checkMoney(player->getMoney(), weaponList[pos - 1]->getPrice())) {
                        player->setMoney(player->getMoney() - weaponList[pos - 1]->getPrice());
                        player->setWeapon(weaponList[pos - 1]);
                    }
                    player->damageWithWeapon();
                }



                if (armorList.empty()) {
                    for (int i = 0; i < 1 + rand() % 3; i++) {
                        armorList.push_back(this->engine->regenerateArmor());
                    }
                }

                cout << "Яку Броню ви хочите купити?" << endl;

                for (int i = 0; i < 1 + rand() % 3; i++) {
                    cout << i + 1 << ") " << armorList[i]->getName() << " " << armorList[i]->getPrice() << endl;
                }

                cin >> pos;

                if (this->checkMoney(player->getMoney(), armorList[pos - 1]->getPrice())) {
                    player->setMoney(player->getMoney() - armorList[pos - 1]->getPrice());
                    player->setArmor(armorList[pos - 1]);
                }

            }
            else if (choiceShop == 3) {
                x = false;
                break;
            }
            else {
                cout << endl << "Error 404 Повторіть спробу" << endl;
                cout << "\033[2J\033[1;1H";
                clickContinue();

                continue;
            }

        }
    }

    void showRoundData(string location, string monsterName, int monsterHp) {
        cout << "\033[2J\033[1;1H";
        cout << "Ви перейшли на локацію " << location << endl;

        cout << endl << "Проти вас " << monsterName << " його Hp =" << " " << monsterHp;
    }


    void fightBoss(Player* player, Monsters* monster) { //я його ше не доробив(потом зроблю)
        int tmpA;
        while (monster->getHpBoss() > 0) {

            cout << endl << "Ваш удар наніс " << player->getDamage() << endl;
            monster->setHpBoss(monster->getHpBoss() - player->getDamage());
            cout << "Орк наніс " << monster->getDamageBoss() << endl;
            player->setHp(player->getHp() - monster->getDamageBoss());
            cout << endl;

            if (randomNum(0, 100) <= player->getMiss()) {
                cout << endl << "Ви уклонились від удара" << endl;
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= player->getChanceBlock()) {
                tmpA = monster->getDamageBoss() - player->getBlock();
                cout << endl << "Ви заблокували " << player->getBlock() << endl;
                cout << "Орк наніс " << tmpA << endl;
                player->setHp(player->getHp() - tmpA);
                cout << endl;
                Sleep(2500);
                continue;
            }

            Sleep(2000);
        }
        cout << "Ти вийграв(ла) У тебе залишилось " << player->getHp() << endl << "Ти получив(ла) " << monster->getScoreGetBoss() << " XP";
        //monster->setHpBoss(monster->getHpBoss() + monster->getHpBoss());
        //monster->setDamageBoss(monster->getDamageBoss() + monster->getDamageBoss());
        //monster->setScoreGetBoss(monster->getScoreGetBoss() + monster->getScoreGetBoss());
        player->setXP(player->getXP() + monster->getScoreGetBoss());

    }


    void fight(Player* player, Monsters* monster) {
        int tmpA;

        while (monster->getHp() > 0) {

            cout << endl << "Ваш удар " << " наніс " << player->getDamage() << endl;
            monster->setHp(monster->getHp() - player->getDamage());

            if (randomNum(0, 100) <= player->getMiss()) {
                cout << "Ви уклонились від удара " << endl;
                if (randomNum(0, 100) <= 20) {// krit
                    cout << "I нанесли критический урон" << endl;
                    tmpA = player->getDamage() * 2;
                    monster->setHp(monster->getHp() - tmpA);
                }
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= player->getChanceBlock()) {
                tmpA = player->getDamage() - monster->getBlock();
                cout << endl << monster->getName() << " заблокував " << monster->getBlock() << endl;
                cout << "Ви нанесли " << tmpA << endl;
                player->setHp(player->getHp() - tmpA);
                cout << endl;
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= player->getChanceBlock()) {
                tmpA = monster->getDamage() - player->getBlock();
                cout << endl << "Ви заблокували " << player->getBlock() << endl;
                cout << monster->getName() << " наніс " << tmpA << endl;
                player->setHp(player->getHp() - tmpA);
                cout << endl;
                Sleep(2500);
                continue;
            }

            cout << monster->getName() << " наніс " << monster->getDamage() << endl;
            player->setHp(player->getHp() - monster->getDamage());
            cout << endl;

            clickContinue();
            Sleep(2500);

        }

        player->setXP(player->getXP() + monster->getScoreGet());
        player->setMoney(player->getMoney() + monster->getMoneyGet());
        cout << "Ти вийграв(ла) У тебе залишилось " << player->getHp() << endl << "Ти получив(ла) " << monster->getScoreGet() << " XP" << endl << " І " << monster->getMoneyGet() << " монеток";
        clickContinue();

    }

    void distributeFight(int mesto, Player* player, Monsters* monster) {
        if (mesto == 1) {
            showRoundData("Ліс", monster->getName(), monster->getHp());
        }
        else if (mesto == 2) {
            showRoundData("Заброшка", monster->getName(), monster->getHp());
        }
        else if (mesto == 3) {
            showRoundData("Город", monster->getName(), monster->getHp());
        }
        else if (mesto == 4) {
            showRoundData("Пещери", monster->getName(), monster->getHp());
        }
        else if (mesto == 5) {
            showRoundData("Катакомби", "Орк", monster->getHp());
        }

        mesto == 5 ? fightBoss(player, monster) : fight(player, monster);
    }
};



void progressBar(int sleep) {
    cout << endl << endl;
    cout << "                   Loading..." << endl;
    cout << "    ";
    for (int i = 0; i < 40; i++) {
        Sleep(sleep);
        cout << "|";
    }
    system("cls");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    progressBar(25);

    Player* player = NULL;
    Engine* engine = new Engine();
    Monsters* monster = NULL;
    Weapon* weapon = NULL;
    Armor* armor = NULL;
    Event* event = new Event(engine);
    int fraction;
    string name;
    int mesto;
    int choice;

    cout << "Ласкаво просимо у DeadMoon" << endl;
    cout << "Як ви назвете свого героя?" << endl;
    cin >> name;

    cout << endl << "Яку ви виберете фракцію?" << endl;
    cout << "1)Танк + до блок урона" << endl << "2)Варвар + до урону" << endl << "3)Розбійник + до уклонению" << endl;
    cin >> fraction;

    if (fraction < 1 || fraction > 3) {
        cout << "Ошибка Неправильно веддені дані ";
        exit(0);
    }
    player = engine->createPlayer(name, fraction);

    cout << "Що ви хочете зробити?" << endl;

    while (true) {
        cout << "1)В подорож" << endl << "2)Магазин" << endl << "3)Показати статистику героя " << endl << "4)Вийти з Ігри" << endl;// вибір
        cin >> choice;

        if (choice == 1) {
            cout << endl << "1)Піти в Ліс" << endl << "2)Піти в Заброшку" << endl << "3)Піти в Місто" << endl << "4)Піти в Печери" << endl << "5)Піти в Катакомби Босс(Важко)";
            cin >> mesto;

            if (mesto < 1 || mesto > 5) { // перевіряє
                cout << "Error 404";
                continue;
            }

            monster = engine->generateMonster(player->getLevel(), mesto);

            event->distributeFight(mesto, player, monster);
            engine->converterXP(player);

        }
        else if (choice == 2) {
            event->shop(player, weapon, armor);
        }
        else if (choice == 3) {
            cout << "\033[2J\033[1;1H";
            player->showStaticPlayer();
            clickContinue();
            cout << "\033[2J\033[1;1H";
        }
        else if (choice == 4) {
            exit(0);
        }

        progressBar(30);

        cout << "\033[2J\033[1;1H";

    }
}