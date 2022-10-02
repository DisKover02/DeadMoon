#include <string>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstring>
#include <conio.h>


using namespace std;

int randomNum(int min, int max) {
    return  min + rand() % (max - min + 1);
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

class Armor {
private:
    string name;
    int protection;
public:
    Armor(string name, int protection) {
        this->name = name;
        this->protection = protection;
    }

    string getName() { return name; }
    void setName(string valueName) { name = valueName; }

    int getProtection() { return protection; }
    void setProtection(int valueProtection) { protection = valueProtection; }

    ~Armor() {
    }
};

class Weapon {
private:
    string name;
    int damage;
public:
    Weapon(string name, int damage) {
        this->name = name;
        this->damage = damage;
    }

    string getName() { return name; }
    void setName(string valueName) { name = valueName; }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    ~Weapon() {

    }
};

class Player : public BasePerson {
private:
    Weapon* weapon;
    Armor* armor;
    int miss;
    int xp;
    int damage;
    int block;
    int chanceBlock;
public:

    Player(string name, int energy, int hp, int miss, int xp, int damage, int block, int chanceBlock) : BasePerson(name, 1, energy, hp) {
        this->damage = damage;//strenght
        this->block = block;//endurance
        this->xp = xp;
        this->miss = miss;//agility
        this->chanceBlock = chanceBlock;
    }
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
        cout << "lvl = " << getLevel() << endl << "Energy = " << getEnergy() << endl << "Damage = " << getDamage() << endl << "Block damage = " << getBlock() << endl << "Hp = " << getHp() << endl << "XP = " << getXP() << endl << "Agility = " << getMiss() << "%" << endl;
    }

    int damageWithWeapon() {
        this->setDamage(this->getDamage() + weapon->getDamage());
        return this->getDamage();
    }
    int blockWithArmor() {
        this->setBlock(this->getBlock() + armor->getProtection());
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

    int HpBoss = 300;
    int DamageBoss = 30;
    int ScoreGetBoss = 150;
public:
    Monsters(string name, int scoreGet, int level, int energy, int damage, int block, int hp, int chanceBlock) : BasePerson(name, level, energy, hp) {
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
    string getName() { return name; }
    void setName(string valueName) { name = valueName; }

    int getChanceBlock() { return chanceBlock; }
    void setChanceBlock(int valueChanceBlock) { chanceBlock = valueChanceBlock; }

    int getScoreGet() { return scoreGet; }
    void setKatakombs(int valueScoreGet) { scoreGet = valueScoreGet; }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    int getBlock() { return block; }
    void setBlock(int valueBlock) { block = valueBlock; }



    ~Monsters() {

    }
};


class Engine {
private:
    string masName[14] = { "Дікарь", "Ригач", "Соплежуй", "Лазун", "Паркурщик", "Лопатокрил",  "Хітман", "Очкарик", "ТікТокер", "Лінкольн Абрамс", "Ходунок", "Весельнік", "Камнебуй", "Дедінсайд" };
    string armorName[5] = { "a", "f", "d", "h", "k" };
    string weaponName[5] = { "v", "g", "h", "k", "a" };

    int randomNum(int min, int max) {
        return  min + rand() % (max - min + 1);
    }
    string generateNameWeapon() {
        return this->weaponName[randomNum(0, 5)];
    }
    string generateNameArmor() {
        return this->armorName[randomNum(0, 5)];
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
            x = 10; y = 14;
        }

        return this->masName[this->randomNum(x, y)];
    }
public:
    Weapon* regenerateWeapon(string name, int damage) {
        return new Weapon(generateNameWeapon(), 15);
    }
    Armor* regenerateArmor(string name, int damage) {
        return new Armor(generateNameArmor(), 15);
    }

    Player* createPlayer(string name, int classType) {
        int block = 30, damage = 30, miss = 30;

        if (classType == 1) {
            block *= 2;
        }
        else if (classType == 2) {
            damage *= 2;
        }
        else {
            miss *= 2;
        }

        return new Player(name, 30, 100, miss, 0, damage, block, 10);
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

        }
    }
    Monsters* generateMonster(int level, int location) {
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
            50 * level,
            level,
            30 * level,
            15 * level,
            10 * level,
            50 * level,
            level
        );//string name, int scoreGet, int level, int energy, int damage, int block, int hp, int chanceBlock
    }


    void fightBoss(Player* player, Monsters* monster) {
        int tmpA;
        while (monster->getHpBoss() > 0) {

            cout << endl << "Ваш удар наніс " << player->getDamage() << endl;
            monster->setHpBoss(monster->getHpBoss() - player->getDamage());
            cout << "АБОБУС наніс " << monster->getDamageBoss() << endl;
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
                cout << "АБОБУС наніс " << tmpA << endl;
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
                if (randomNum(0, 100) <= 50) {// krit
                    cout << "та нанесли критический урон" << endl;
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


            Sleep(2500);

        }

        cout << "Ти вийграв(ла) У тебе залишилось " << player->getHp() << endl << "Ти получив(ла) " << monster->getScoreGet() << " XP";
    }
    void distributeFight(int mesto, Player* player, Monsters* monster) {
        if (mesto == 1) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Ліс" << endl;

            monster->getName();
            cout << endl << "Проти вас " << monster->getName() << " його Hp =" << " " << monster->getHp();
            fight(player, monster);
        }
        else if (mesto == 2) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Заброшка" << endl;

            monster->getName();
            cout << endl << "Проти вас " << monster->getName() << " його Hp =" << " " << monster->getHp();
            fight(player, monster);
        }
        else if (mesto == 3) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Город" << endl;

            monster->getName();
            cout << endl << "Проти вас " << monster->getName() << " його Hp =" << " " << monster->getHp();
            fight(player, monster);
        }
        else if (mesto == 4) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Пещери" << endl;

            monster->getName();
            cout << endl << "Проти вас " << monster->getName() << " його Hp =" << " " << monster->getHp();
            fight(player, monster);
        }
        else if (mesto == 5) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Катакомби" << endl;

            cout << endl << "Проти вас АБОБУС його Hp =" << " " << monster->getHpBoss();
            fightBoss(player, monster);
        }

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
    progressBar(100);

    Player* player = NULL; 
    Engine* engine = new Engine();
    Monsters* monster = NULL;
    int fraction;
    string name;
    int mesto;

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

    cout << "Яку ви виберите локацію для свого первого похода?" << endl;

    while (true) {

        cout << endl << "1)Ліс" << endl << "2)Заброшка" << endl << "3)Місто" << endl << "4)Печери" << endl << "5) Катакомби Босс(Важко)";
        cin >> mesto;

        if (mesto < 1 || mesto > 5) { // перевіряє
            cout << "Error 404";
            exit(0);
        }

        player = engine->createPlayer(name, fraction);
        monster = engine->generateMonster(player->getLevel(), mesto);

        progressBar(80);

        engine->distributeFight(mesto, player, monster);
        engine->converterXP(player);
        player->setXP(player->getXP() + monster->getScoreGet());

        cout << endl << "Статистика вашого героя" << endl;
        player->showStaticPlayer();
        Sleep(3000);

        cout << "\033[2J\033[1;1H";
    }
}
