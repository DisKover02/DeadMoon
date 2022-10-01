#include <string>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <vector>


using namespace std;

int randomNum(int min, int max) {
    return  min + rand() % (max - min + 1);
}


//class Location {                                      Покищо цей клас ненада
//private:
//    bool forest;
//    bool zabroshka;
//    bool city;
//    bool pesher;
//    bool katakombs;
//
//    int mas[5] = {};
//
//public:
//    Location(bool forest, bool zabroshka, bool city, bool pesher, bool katakombs) {
//        this->forest = forest;
//        this->zabroshka = zabroshka;
//        this->city = city;
//        this->pesher = pesher;
//        this->katakombs = katakombs;
//    }
//
//    int getForest() { return forest; }
//    void setForest(bool valueForest) { forest = valueForest; }
//
//    int getZabroshka() { return zabroshka; }
//    void setZabroshka(bool valueZabroshka) { zabroshka = valueZabroshka; }
//
//    int getCity() { return city; }
//    void setCity(bool valueCity) { city = valueCity; }
//
//    int getPesher() { return pesher; }
//    void setPesher(int valuePesher) { pesher = valuePesher; }
//
//    int getKatakombs() { return katakombs; }
//    void setKatakombs(bool valueKatakombs) { katakombs = valueKatakombs; }
//
//    ~Location() {
//
//    }
//
//};

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

class Player : public BasePerson { // я хотів зробить наслідування але... свої причини є 
private:
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
    int getChanceBlock() { return chanceBlock; }
    void setChanceBlock(int valueChanceBlock) { chanceBlock = valueChanceBlock; }

    int getScoreGet() { return scoreGet; }
    void setKatakombs(int valueScoreGet) { scoreGet = valueScoreGet; }

    int getDamage() { return damage; }
    void setDamage(int valueDamage) { damage = valueDamage; }

    int getBlock() { return block; }
    void setBlock(int valueBlock) { block = valueBlock; }

    void fightBoss(int damagePlayer, int HpPlayer, int PlayerXP, int PlayerMiss, int PlayerBlock, int chanceBlock) {
        int tmpA;
        while (HpBoss > 0) {

            cout << endl << "Ваш удар " << " наніс " << damagePlayer << endl;
            HpBoss = HpBoss - damagePlayer;
            cout << "АБОБУС наніс " << DamageBoss << endl;
            HpPlayer = HpPlayer - DamageBoss;
            cout << endl;

            if (randomNum(0, 100) <= PlayerMiss) {
                cout << endl << "Ви уклонились від удара" << endl;
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= chanceBlock) {
                tmpA = getDamage() - PlayerBlock;
                cout << endl << "Ви заблокували " << PlayerBlock << endl;
                cout << "АБОБУС наніс " << tmpA << endl;
                HpPlayer -= tmpA;
                cout << endl;
                Sleep(2500);
                continue;
            }

            if (HpPlayer <= 0) {
                int tmpQuestion;
                cout << "Ви програли :(" << endl;
                cout << "1)Вийти?" << endl << "2)Рестарт" << endl;
                cin >> tmpQuestion;
                if (tmpQuestion == 1) {
                    exit(0);
                }
                else {
                    continue;
                }
            }
            Sleep(2000);
        }
        cout << "Ти вийграв(ла) У тебе залишилось " << HpPlayer << endl << "Ти получив(ла) " << getScoreGetBoss() << " XP";
        setHpBoss(getHpBoss() + getHpBoss());
        setDamageBoss(getDamageBoss() + getDamageBoss());
        setScoreGetBoss(getScoreGetBoss() + getScoreGetBoss());

    }

    void fight(int damagePlayer, int HpPlayer, int PlayerXP, string tmpName, int PlayerMiss, int PlayerBlock, int chanceBlock) {
        int tmpA;
        while (hp > 0) {
            cout << endl << "Ваш удар " << " наніс " << damagePlayer << endl;
            hp = hp - damagePlayer;

            if (randomNum(0, 100) <= PlayerMiss) {
                cout << "Ви уклонились від удара" << endl;
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= getChanceBlock()) {
                tmpA = damagePlayer - getBlock();
                cout << endl << tmpName << " заблокував " << damagePlayer << endl;
                cout << "Ви нанесли " << tmpA << endl;
                setHp(getHp() - tmpA);
                cout << endl;
                Sleep(2500);
                continue;
            }

            if (randomNum(0, 100) <= chanceBlock) {
                tmpA = getDamage() - PlayerBlock;
                cout << endl << "Ви заблокували " << PlayerBlock << endl; // потім все перенесу в методи
                cout << tmpName << " наніс " << tmpA << endl;
                HpPlayer -= tmpA;
                cout << endl;
                Sleep(2500);
                continue;
            }

            cout << tmpName << " наніс " << getDamage() << endl;
            HpPlayer = HpPlayer - getDamage();
            cout << endl;


            Sleep(2500);

        }

        cout << "Ти вийграв(ла) У тебе залишилось " << HpPlayer << endl << "Ти получив(ла) " << getScoreGet() << " XP";

    }

    void distributeFight(int mesto, int damagePlayer, int HpPlayer, int PlayerXP, string tmpName, int PlayerMiss, int PlayerBlock, int chanceBlock) {
        if (mesto == 1) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Ліс" << endl;

            tmpName = masName[randomNum(0, 2)];
            cout << endl << "Проти вас " << tmpName << " його Hp =" << " " << getHp();
            fight(damagePlayer, HpPlayer, PlayerXP, tmpName, PlayerMiss, PlayerBlock, chanceBlock);
        }
        else if (mesto == 2) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Заброшка" << endl;

            tmpName = masName[randomNum(3, 7)];
            cout << endl << "Проти вас " << tmpName << " його Hp =" << " " << getHp();
            fight(damagePlayer, HpPlayer, PlayerXP, tmpName, PlayerMiss, PlayerBlock, chanceBlock);
        }
        else if (mesto == 3) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Город" << endl;

            tmpName = masName[randomNum(7, 10)];
            cout << endl << "Проти вас " << tmpName << " його Hp =" << " " << getHp();
            fight(damagePlayer, HpPlayer, PlayerXP, tmpName, PlayerMiss, PlayerBlock, chanceBlock);
        }
        else if (mesto == 4) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Пещери" << endl;

            tmpName = masName[randomNum(10, 14)];
            cout << endl << "Проти вас " << tmpName << " його Hp =" << " " << getHp();
            fight(damagePlayer, HpPlayer, PlayerXP, tmpName, PlayerMiss, PlayerBlock, chanceBlock);
        }
        else if (mesto == 5) {
            cout << "\033[2J\033[1;1H";
            cout << "Ви перейшли на локацію Катакомби" << endl;

            cout << endl << "Проти вас АБОБУС його Hp =" << " " << getHpBoss();
            fightBoss(damagePlayer, HpPlayer, PlayerXP, PlayerMiss, PlayerBlock, chanceBlock);
        }

    }

    ~Monsters() {

    }
};


class Engine {
private:
    string masName[14] = { "Дікарь", "Ригач", "Соплежуй", "Лазун", "Паркурщик", "Лопатокрил",  "Хітман", "Очкарик", "ТікТокер", "Лінкольн Абрамс", "Ходунок", "Весельнік", "Камнебуй", "Дедінсайд" };

    int randomNum(int min, int max) {
        return  min + rand() % (max - min + 1);
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

        return new Player(name, 30, 300, miss, 0, damage, block, 10);
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
            100 * level,
            level,
            30 * level,
            15 * level,
            10 * level,
            150 * level,
            5 * level
        );//string name, int scoreGet, int level, int energy, int damage, int block, int hp, int chanceBlock
    }

    bool fightOneRound(Player* player, Monsters* monster) {

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

int main() { // покищо все примітивно але буде прокачано

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    progressBar(100);

    //Location* location = new Location(false, false, false, false, false);
    Player* player = NULL; //  int miss%, int XP, int level, int energy, int damage, int block, int hp, int chanceBlock
    Engine* engine = new Engine();

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

    player = engine->createPlayer(name, fraction);

    cout << "Яку ви виберите локацію для свого первого похода?" << endl;

    int converterXP = 100;
    while (true) {

        cout << endl << "1)Ліс" << endl << "2)Заброшка" << endl << "3)Місто" << endl << "4)Печери" << endl << "5) Катакомби Босс(Важко)";
        cin >> mesto;

        if (mesto < 1 || mesto > 5) { // перевіряє
            cout << "Error 404";
            exit(0);
        }

        engine->generateMonster(player->getLevel(), mesto);

        progressBar(80);

        monsters->distributeFight(mesto, player->getDamage(), player->getHp(), player->getXP(), name, player->getMiss(), player->getBlock(), player->getChanceBlock());
        player->setXP(player->getXP() + monsters->getScoreGet());

        if (player->getXP() >= converterXP) {
            converterXP += 50;
            player->setLevel(player->getLevel() + 1);
            cout << endl << "Поздравляю! у вас" << player->getLevel() << " lvl";
            player->setXP(0);

            player->setHp(player->getHp() + 10); // hp
            player->setDamage(player->getDamage() + 3); // damage
            player->setMiss(player->getMiss() + 1); // miss
            player->setBlock(player->getBlock() + 3); // block
            player->setChanceBlock(player->getChanceBlock() + 1); // chanceBlock

        }
        monsters->setBlock(player->getBlock() + 2); // block
        monsters->setChanceBlock(player->getChanceBlock() + 1); // chanceBlock
        monsters->setHp(player->getLevel() * 20); //hp monster
        monsters->setDamage(player->getLevel() * 15);//damage monster
        cout << endl << "Статистика вашого героя" << endl;
        player->showStaticPlayer();
        Sleep(3000);

        cout << "\033[2J\033[1;1H";
    }
}

