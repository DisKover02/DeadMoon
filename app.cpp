#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <cstring>
#include <conio.h>
#include <stdio.h>

using namespace std;

class FunctionHelper {
public:
    static int randomNum(int min, int max) {
        return  min + rand() % (max - min + 1);
    }

    static void clickContinue() {
        cout << endl << "Нажміть Enter або Space щоб продовжити" << endl;
        while (bool x = true) {
            int key = _getch();
            if (key == 13 || key == 32) {
                x = false;
                break;
            }
        }
    }
};

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
        this->hpMax = hp;
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
        this->price = this->protection * 150;
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
class SkillInterface {
protected:
    string name = "";

public:
    virtual int use(int damage) = 0;
    virtual string getName() = 0;

};
class Player : public BasePerson {
private:
    const int SKILL_COUNT = 3;

    Weapon* weapon = NULL;
    Armor* armor = NULL;
    int miss;
    int xp;
    int damage;
    int block;
    int chanceBlock;
    int money = 0;
    int regenHp = 0;

    vector <SkillInterface*> skills;
public:
    Player(string name, int energy, int hp, int miss, int xp, int damage, int block, int chanceBlock, int money) : BasePerson(name, 1, energy, hp) {
        this->damage = abs(damage);//strenght
        this->block = block;//endurance
        this->xp = xp;
        this->miss = miss;//agility
        this->chanceBlock = chanceBlock;
        this->money = money;
        this->regenHp = hp;
    }

    void setWeapon(Weapon* weapon) {
        this->weapon = weapon;
    }

    void setArmor(Armor* armor) {
        this->armor = armor;
    }

    //------ Skill Function -----\\

    bool addSkill(SkillInterface* skill) {
        if (this->skills.size() < this->SKILL_COUNT) {
            this->skills.push_back(skill);

            return true;
        }

        return false;
    }

    bool changeSkill(int position, SkillInterface* skill) {
        if (position < 0 || position >= this->skills.size()) {
            return false;
        }

        this->skills[position] = skill;

        return true;
    }

    void showSkill() {
        for (int i = 0; i < this->skills.size(); i++) {
            cout << i + 1 << ". " << this->skills[i]->getName() << endl;
        }
    }

    int useSkill(int position) {
        return this->skills[position]->use(this->getDamage());
    }

    //----- End Skill Function -----\\

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
        if (this->weapon != NULL) {
            this->setDamage(this->getDamage() + this->weapon->getDamage());
        }

        return this->getDamage();
    }
    int blockWithArmor() {
        if (this->armor != NULL) {
            this->setBlock(this->getBlock() + this->armor->getProtection());
        }
        return this->getBlock();
    }

    void regenHpPlayer() {
        setHp(regenHp);
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
        this->moneyGet = moneyGet;
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
////////////////////////////////////SKILS and potion


class Smite : public SkillInterface {
public:
    Smite() {
        this->name = "Smite";
    }

    int use(int damage) override {
        return damage;
    }

    string getName() override {
        return this->name;
    }
};
class StrongSmite : public SkillInterface {
public:
    StrongSmite() {
        this->name = "StrongSmite";
    }

    int use(int damage) override {
        return (int)damage * 1.5;
    }

    string getName() override {
        return this->name;
    }
};
class Kick : public SkillInterface {
public:
    Kick() {
        this->name = "Kick";
    }

    int use(int damage) override {
        return damage * 2;
    }

    string getName() override {
        return this->name;
    }
};
class MagicSmite : public SkillInterface {
public:
    MagicSmite() {
        this->name = "MagicSmite";
    }

    int use(int damage) override {
        return (int)damage + 10 * 0.8;
    }

    string getName() override {
        return this->name;
    }
};


class PotionInterface {
public:
    Player* player;
    virtual void use() = 0;
};

class HealHp : PotionInterface {
    void use() {
        player->setHp((int)player->getHp() + player->getHp() / 3);
    }
};
class AddDamage : PotionInterface {
    void use() {
        player->setDamage((int)player->getDamage() + player->getLevel() * 1.5);
    }
};
class AddMiss : PotionInterface {
    void use() {
        player->setMiss((int)player->getMiss() + player->getMiss() * 1.5);
    }
};
////////////////////////////////////SKILS and potion

class ManageData {
public:

    void savePlayer(Player* player) {
        ofstream saveFile;
        saveFile.open("d:\\DataPlayer.txt");
        if (!saveFile.is_open()) {
            saveFile.close();
            cout << endl << "Помилка*Error 1236" << endl << "Дані не coхранились*Data not saved" << endl;
        }
        else {
            cout << endl << "Файл Успішно открився!" << endl;
            saveFile.write((char*)&player, sizeof(Player));
        }
        saveFile.close();
        cout << endl << "Файл Успішно закрився" << endl;
    }

    auto loadPlayer() {
        ifstream loadFile;
        Player* player = NULL;
        loadFile.open("d:\\DataPlayer.txt");

        if (loadFile.is_open()) {
            loadFile.read((char*)&player, sizeof(Player));
        }
        else {
            cout << endl << "Помилка откриття файла!" << endl;
        }

        cout << "Файл Успішно закрився" << endl;
        loadFile.close();

        return player; // bag
    }



};

class Engine {
private:
    vector <string> masName{ "Дікарь", "Ригач", "Соплежуй", "Лазун", "Паркурщик", "Лопатокрил",  "Хітман", "Очкарик", "ТікТокер", "Лінкольн Абрамс", "Ходунок", "Весельнік", "Камнебуй", "Дедінсайд" };
    vector <string> armorName{ "Кольчужна Броня", "Металева Броня", "Броня Бога", "Броня Ада", "Кожана Броня" };
    vector <string> weaponName{ "Кристалис", "Башер", "Даедалус", "ЕхоСабре", "Кая", "Яша", "Сендж" };
    vector <SkillInterface*> skillList;
    int randomNum(int min, int max) {
        return  min + rand() % (max - min + 1);
    }
    string generateName(bool isWeapon = false) {
        if (isWeapon) {
            return this->weaponName[randomNum(0, 6)];//this->weaponName.size() - 1
        }
        else {
            return this->armorName[randomNum(0, 4)]; //this->armorName.size() - 1)
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
        int tmp;
        tmp = randomNum(3, 20);
        return new Weapon(generateName(true), tmp, 1000);
    }
    Armor* regenerateArmor() {
        int tmp;
        tmp = randomNum(3, 20);
        return new Armor(generateName(), tmp, 1500);
    }

    SkillInterface* generateSkills() {
        SkillInterface* sk = NULL;
        int tmp = 0;
        tmp = randomNum(1, 4);
    }

    Player* createPlayer(string name, int classType) {
        Player* player = new Player(name, 30, 60, 0, 0, 0, 0, 15, 0);

        int block = 8, damage = 12, miss = 5;

        if (classType == 1) {
            block *= 2;

            player->addSkill(new StrongSmite());
            player->addSkill(new Smite());
            player->addSkill(new Kick());
        }
        else if (classType == 2) {
            damage *= 2;
            player->addSkill(new MagicSmite());
            player->addSkill(new Smite());
            player->addSkill(new Kick());
        }
        else {
            miss *= 2;
            player->addSkill(new MagicSmite());
            player->addSkill(new Smite());
            player->addSkill(new StrongSmite());
        }

        player->setMiss(miss);
        player->setBlock(block);
        player->setDamage(damage);

        return player;
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

            FunctionHelper::clickContinue();
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
        else {
            return false;
        }

    }

public:


    Event(Engine* engine) {
        this->engine = engine;
    }

    void shop(Player* player, Weapon* weapon, Armor* armor) {
        while (bool x = true) {
            int choiceShop;
            int posProduct = 0;
            //string statusPos = " не куплено ";

            cout << "Що ви хочете зробити?" << endl << "1)Купити Меч" << endl << "2)Купити Броню" << endl << "3)Вийти з магазина" << endl;
            cin >> choiceShop;
            if (choiceShop == 1) {


                if (weaponList.empty()) {
                    for (int i = 0; i < 5; i++) {
                        weaponList.push_back(this->engine->regenerateWeapon());
                    }
                }

                cout << "Який меч ви хочете купити?" << endl;

                for (int i = 0; i < weaponList.size(); i++) {
                    cout << i + 1 << ") " << weaponList[i]->getName() << " price = " << weaponList[i]->getPrice() << " || " << weaponList[i]->getDamage() << " damage" << endl;
                }
                cout << "3)Вийти з магазина" << endl;
                cin >> posProduct;


                if (posProduct == 1) {
                    if (this->checkMoney(player->getMoney(), weaponList[posProduct - 1]->getPrice())) {
                        player->setMoney(player->getMoney() - weaponList[posProduct - 1]->getPrice());
                        player->setWeapon(weaponList[posProduct - 1]);
                        player->damageWithWeapon();
                    }
                    else {
                        cout << endl << "У вас недостатньо монеток" << endl;
                        continue;
                    }

                }
                else if (posProduct == 2) {
                    if (this->checkMoney(player->getMoney(), weaponList[posProduct - 1]->getPrice())) {
                        player->setMoney(player->getMoney() - weaponList[posProduct - 1]->getPrice());
                        player->setWeapon(weaponList[posProduct - 1]);
                        player->damageWithWeapon();
                    }
                    else {
                        cout << endl << "У вас недостатньо монеток" << endl;
                        continue;
                    }

                }
                else if (posProduct == 3) {
                    x = false;
                    break;
                }
            }
            if (choiceShop == 2) {

                if (armorList.empty()) {
                    armorList.clear();
                    for (int i = 0; i < 5; i++) {
                        armorList.push_back(this->engine->regenerateArmor());
                    }
                }

                cout << "Яку Броню ви хочите купити?" << endl;

                for (int i = 0; i < armorList.size(); i++) {
                    cout << i + 1 << ") " << armorList[i]->getName() << " price = " << armorList[i]->getPrice() << " || " << " block " << armorList[i]->getProtection() << " damage" << endl;
                }
                cout << "3)Вийти з магазина" << endl;
                cin >> posProduct;
                if (posProduct == 1) {

                    if (this->checkMoney(player->getMoney(), armorList[posProduct - 1]->getPrice())) {
                        player->setMoney(player->getMoney() - armorList[posProduct - 1]->getPrice());
                        player->setArmor(armorList[posProduct - 1]);
                        player->blockWithArmor();
                    }
                    else {
                        cout << endl << "У вас недостатньо монеток" << endl;
                        continue;
                    }
                }
                else if (posProduct == 2) {
                    if (this->checkMoney(player->getMoney(), weaponList[posProduct - 1]->getPrice())) {
                        player->setMoney(player->getMoney() - weaponList[posProduct - 1]->getPrice());
                        player->setWeapon(weaponList[posProduct - 1]);
                        player->blockWithArmor();
                    }
                    else {
                        cout << endl << "У вас недостатньо монеток" << endl;
                        continue;
                    }

                }

                else if (posProduct == 3) {
                    x = false;
                    break;
                }
            }
            else if (choiceShop == 3) {
                x = false;
                break;
            }
            else {
                cout << endl << "Error 404 Повторіть спробу" << endl;
                cout << "\033[2J\033[1;1H";
                FunctionHelper::clickContinue();

                continue;
            }

        }
    }

    void showRoundData(string location, string monsterName, int monsterHp, int playerHp) {
        cout << "\033[2J\033[1;1H";
        cout << "Ви перейшли на локацію " << location << endl;

        cout << endl << "Проти вас " << monsterName << " його Hp =" << " " << monsterHp << endl << "Ваше Hp = " << playerHp;
    }


    void fightBoss(Player* player, Monsters* monster, SkillInterface* skills) {
        int diffDamage;
        int onePass_hpRegen = 0;
        int skill_position = NULL;
        while (player->getHp() > 0 && monster->getHpBoss() > 0) {

            player->showSkill();
            cin >> skill_position;
            if (skill_position < 1 || skill_position > 3) {
                cout << "Error ";
                Sleep(400);
                cout << "\033[2J\033[1;1H";
                continue;
            }

            cout << "Ви використали скіл " << skill_position << endl;
            cout << endl << "Ваш скіл " << " наніс " << player->useSkill(skill_position - 1) << " урона" << endl;
            monster->setHpBoss(monster->getHpBoss() - player->useSkill(skill_position - 1));

            cout << "Орк наніс " << monster->getDamageBoss() << endl;
            player->setHp(player->getHp() - monster->getDamageBoss());
            cout << endl;

            if (FunctionHelper::randomNum(0, 100) <= player->getMiss()) {
                cout << endl << "Ви уклонились від удара" << endl;
                Sleep(2500);
                continue;
            }

            if (FunctionHelper::randomNum(0, 100) <= player->getChanceBlock()) {
                diffDamage = monster->getDamageBoss() - player->getBlock();
                if (diffDamage < 0) { diffDamage = 0; }
                cout << endl << "Ви заблокували " << player->getBlock() << endl;
                cout << "Орк наніс " << diffDamage << endl;
                player->setHp(player->getHp() - diffDamage);
                cout << endl;
                Sleep(2500);
                continue;
            }

            onePass_hpRegen = FunctionHelper::randomNum(player->getLevel() * 10, player->getLevel() * 20); // regenHp
            player->setHp(player->getHp() + onePass_hpRegen);
            cout << endl << "Ви востановили " << onePass_hpRegen << " hp " << endl;
            FunctionHelper::clickContinue();


            Sleep(2000);
        }

        if (player->getHp() > 0) {
            player->setXP(player->getXP() + monster->getScoreGetBoss());
            player->setMoney(player->getMoney() + monster->getMoneyGet());
            cout << "Ти вийграв(ла) У тебе залишилось " << player->getHp() << " hp " << endl << "Ти получив(ла) " << monster->getScoreGet() << " XP" << endl << " І " << monster->getMoneyGet() << " монеток";
        }
        else {
            cout << "Монстр " << monster->getName() << " вас убив";
            player->regenHpPlayer();
        }


    }


    void fight(Player* player, Monsters* monster, SkillInterface* skills) {
        int diffDamage = NULL;
        int skill_position = NULL;
        int onePass_hpRegen = 0;

        while (monster->getHp() > 0 && player->getHp() > 0) {

            cout << endl << "Ваш первий Удар:" << endl;
            player->showSkill();
            cin >> skill_position;
            if (skill_position < 1 || skill_position > 3) {
                cout << "Error ";
                Sleep(400);
                cout << "\033[2J\033[1;1H";
                continue;
            }

            cout << "Ви використали скіл " << skill_position << endl;
            cout << endl << "Ваш скіл " << " наніс " << player->useSkill(skill_position - 1) << " урона" << endl;
            monster->setHp(monster->getHp() - player->useSkill(skill_position - 1));


            if (FunctionHelper::randomNum(0, 100) <= monster->getChanceBlock()) {
                diffDamage = player->useSkill(skill_position - 1) - monster->getBlock();
                if (diffDamage < 0) { diffDamage = 0; }
                cout << endl << monster->getName() << " заблокував " << monster->getBlock() << " урона" << endl;
                cout << "Ви нанесли " << diffDamage << endl;
                monster->setHp(monster->getHp() - diffDamage);
                cout << endl;
                Sleep(2500);
                continue;
            }

            if (FunctionHelper::randomNum(0, 100) <= player->getMiss()) {
                cout << "Ви уклонились від удара " << endl;
                if (FunctionHelper::randomNum(0, 100) <= 10) {// krit
                    cout << "I нанесли критический урон" << endl;
                    diffDamage = player->useSkill(skill_position - 1) * 2;
                    monster->setHp(monster->getHp() - diffDamage);
                }
                Sleep(2500);
                continue;
            }
            if (FunctionHelper::randomNum(0, 100) <= player->getChanceBlock()) {
                diffDamage = monster->getDamage() - player->getBlock();
                if (diffDamage < 0) { diffDamage = 0; }
                cout << endl << "Ви заблокували " << player->getBlock() << " урона" << endl;
                cout << monster->getName() << " наніс " << diffDamage << endl;
                player->setHp(player->getHp() - diffDamage);
                cout << endl;
                Sleep(2500);
                continue;
            }


            cout << monster->getName() << " наніс " << monster->getDamage() << " урона" << endl;
            player->setHp(player->getHp() - monster->getDamage());
            cout << endl;

            onePass_hpRegen = FunctionHelper::randomNum(player->getLevel() * 10, player->getLevel() * 20); // regenHp
            player->setHp(player->getHp() + onePass_hpRegen);
            cout << endl << "Ви востановили " << onePass_hpRegen << " hp " << endl;
            FunctionHelper::clickContinue();
            Sleep(2500);

        }

        if (player->getHp() > 0) {
            player->setXP(player->getXP() + monster->getScoreGet());
            player->setMoney(player->getMoney() + monster->getMoneyGet());
            cout << "Ти вийграв(ла) У тебе залишилось " << player->getHp() << " hp " << endl << "Ти получив(ла) " << monster->getScoreGet() << " XP" << endl << " І " << monster->getMoneyGet() << " монеток";
        }
        else {
            cout << "Монстр " << monster->getName() << " вас убив";
            player->regenHpPlayer();
        }

        FunctionHelper::clickContinue();

    }

    void distributeFight(int mesto, Player* player, Monsters* monster, SkillInterface* skills) {
        int tmp = NULL;
        tmp = FunctionHelper::randomNum(0, 100);
        if (tmp <= 40) {

        }
        else if (tmp >= 41 && tmp <= 60) {
            player->setHp(player->getHp() + FunctionHelper::randomNum(1, 30));
            cout << endl << "Вам Повезло ви знайшли яблуко еви  +hp" << endl;
        }
        else {
            player->setDamage(player->getDamage() + FunctionHelper::randomNum(1, 15));
            cout << endl << "Вам Повезло монстр без ноги +damage" << endl;
        }
        if (mesto == 1) {
            showRoundData("Ліс", monster->getName(), monster->getHp(), player->getHp());
        }
        else if (mesto == 2) {
            showRoundData("Заброшка", monster->getName(), monster->getHp(), player->getHp());
        }
        else if (mesto == 3) {
            showRoundData("Город", monster->getName(), monster->getHp(), player->getHp());
        }
        else if (mesto == 4) {
            showRoundData("Пещери", monster->getName(), monster->getHp(), player->getHp());
        }
        else if (mesto == 5) {
            showRoundData("Катакомби", "Орк", monster->getHp(), player->getHp());
        }

        mesto == 5 ? fightBoss(player, monster, skills) : fight(player, monster, skills);
    }
};

//////////////////////////////////////////////////////////////////////////////// for progress bar
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void progressBar(int sleep, string saveLoadBoost, bool boost, int boostDiapazon) {
    cout << endl << endl;
    cout << "                   " << saveLoadBoost << "..." << endl;
    cout << "    ";
    if (boost == true) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        for (int i = 0; i < boostDiapazon; i++) {
            cout << (char)(rand() % (255 - 47) + 48) << ' ';//hack pentagon data
        }
        cout << endl << "Loading welldone";
        Sleep(200);
        cout << "\033[2J\033[1;1H";
    }
    else {
        for (int i = 0; i < 40; i++) {
            Sleep(sleep);
            cout << "|";
        }
        system("cls");
    }

}
////////////////////////////////////////////////////////////////////////////////////////
int main() { //1.доробити гру відшліфувати
    //2.зробити механику енергії зі способностями
    //3.зробити сохранення і загрузку....
    //4.розділити по файлам...

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    progressBar(35, "Loading", false, 0);// progressBar(0, "Loading", true, 80000); see in fullscreen
    ManageData* manageData = new ManageData();
    Player* player = NULL;
    Engine* engine = new Engine();
    Monsters* monster = NULL;
    Weapon* weapon = NULL;
    Armor* armor = NULL;
    Event* event = new Event(engine);
    SkillInterface* skills = NULL;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    int choiceLoad = 0;
    int fraction;
    string name = "";
    int mesto = 0;
    int choice = 0;


    cout << "Ласкаво просимо у DeadMoon\a" << endl;
    cout << "Якщо ви уже грали можете загрузить прогрес \n1)Загрузить\n2)Все з нуля" << endl;
    cin >> choiceLoad;

    if (choiceLoad == 1) {
        player = manageData->loadPlayer();
        if (player == NULL) {
            FunctionHelper::clickContinue();
            cout << "\033[2J\033[1;1H";

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
        }

        FunctionHelper::clickContinue();
        cout << "\033[2J\033[1;1H";
    }

    else if (choiceLoad == 2) {
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
    }
    else {
        cout << endl << "Помилка 1253";
        exit(0);
    }


    cout << "Що ви хочете зробити?" << endl;

    player->addSkill(skills);
    while (bool x = true) {
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

            event->distributeFight(mesto, player, monster, skills);
            engine->converterXP(player);

        }
        else if (choice == 2) {
            event->shop(player, weapon, armor);
        }
        else if (choice == 3) {
            cout << "\033[2J\033[1;1H";
            player->showStaticPlayer();
            cout << endl;
            player->showSkill();
            FunctionHelper::clickContinue();
            cout << "\033[2J\033[1;1H";
        }
        else if (choice == 4) {
            int choiceSave;
            cout << endl << "Хочете сохранить прогрес? " << endl << "1)ДА \n2)Не" << endl;
            cin >> choiceSave;
            if (choiceSave == 1) {
                manageData->savePlayer(player);
                progressBar(0, "Saving", true, 65000);
                cout << endl << "Ігра Успішно збережена" << endl;
            }

            exit(0);
        }

        progressBar(30, "Loading", false, 0);

        cout << "\033[2J\033[1;1H";

    }
}
