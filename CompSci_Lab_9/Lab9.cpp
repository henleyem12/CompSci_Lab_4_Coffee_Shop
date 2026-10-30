#include <iostream>
#include <string>
using namespace std;

// Part 1: Default Parameters

void displaySpellBanner(string spellName,
    string tier = "Novice", int chargeLevel = 1)
{
    cout << "\n*** SPELL CAST ***\n";
    cout << "Spell: " << spellName << "\n";
    cout << "Tier: " << tier << "\n";
    cout << "Charge Level: " << chargeLevel << "\n";
    cout << "******************\n";
}

double castSpell(string spellName = "Magic Missile",
    int basePower = 10, double multiplier = 1.0)
{
    double totalDamage = basePower * multiplier;

    cout << "Casting " << spellName << "!\n";
    cout << "Base Power: " << basePower << "\n";
    cout << "Multiplier: " << multiplier << "\n";
    cout << "Total Damage: " << totalDamage << " HP\n";

    return totalDamage;
}

double calculateShield(double baseShield = 15.0,
    double absorptionRate = 0.20)
{
    double totalShield = baseShield * (1 + absorptionRate);

    return totalShield;
}

// Part 2: Static Local Variables

int registerCombo(bool hitSuccessful)
{
    static int comboCount = 0;

    if (hitSuccessful)
    {
        comboCount++;
    }
    else
    {
        comboCount = 0;
        cout << "Combo broken! Starting over.\n";
    }

    return comboCount;
}

void consumeMana(int cost = 5)
{
    static int totalManaUsed = 0;

    totalManaUsed += cost;

    cout << "Mana used this turn: " << cost << "\n";
    cout << "Total mana used: " << totalManaUsed << "\n";
}

bool processBossRage(double damageDealt)
{
    static double totalDamageDealt = 0.0;

    totalDamageDealt += damageDealt;

    cout << "Total Boss Damage: "
        << totalDamageDealt << " HP\n";

    if (totalDamageDealt >= 100.0)
    {
        return true;
    }

    return false;
}

int gainWizardXP(int expGained = 25)
{
    static int totalXP = 0;
    static int wizardLevel = 1;

    totalXP += expGained;

    cout << "XP Gained: " << expGained << "\n";
    cout << "Total XP: " << totalXP << "\n";

    if (totalXP >= wizardLevel * 100)
    {
        wizardLevel++;
        cout << "LEVEL UP!\n";
    }

    cout << "Wizard Level: " << wizardLevel << "\n";

    return wizardLevel;
}

int main()
{
    cout << "=== ARENA WARM-UP: TESTING DEFAULT ARGUMENTS ===\n\n";

    displaySpellBanner("Magic Missile");
    double dmg1 = castSpell();
    double ward1 = calculateShield();

    cout << "Ward Absorbs: " << ward1 << " HP\n\n";

    displaySpellBanner("Inferno Fireball", "Master", 3);
    double dmg2 = castSpell("Inferno Fireball", 35, 1.5);
    double ward2 = calculateShield(30.0, 0.50);

    cout << "Ward Absorbs: " << ward2 << " HP\n\n";

    cout << "=== WIZARD ACADEMY BATTLE SIMULATOR ===\n\n";

    char continueBattle = 'y';
    int turn = 1;

    while (continueBattle == 'y' || continueBattle == 'Y')
    {
        cout << "\n----------------------------------------\n";
        cout << " TURN " << turn << "\n";
        cout << "----------------------------------------\n";

        int choice = 0;

        cout << "Select Action:\n";
        cout << "1) Quick Magic Missile (Default attack)\n";
        cout << "2) Heavy Lightning Storm (Custom attack)\n";
        cout << "3) Cast Defensive Barrier\n";
        cout << "4) Miss Attack Intentionally\n";
        cout << "Choice: ";

        cin >> choice;

        double damageDealt = 0.0;
        bool successfulHit = false;

        if (choice == 1)
        {
            displaySpellBanner("Magic Missile");
            damageDealt = castSpell();
            consumeMana();
            successfulHit = true;
        }
        else if (choice == 2)
        {
            displaySpellBanner("Lightning Storm", "Adept", 2);
            damageDealt = castSpell("Lightning Storm", 30, 1.4);
            consumeMana(15);
            successfulHit = true;
        }
        else if (choice == 3)
        {
            displaySpellBanner("Arcane Shield", "Novice", 1);

            double shieldVal = calculateShield(20.0, 0.25);

            cout << "Shield generated! Absorbs "
                << shieldVal << " incoming damage.\n";

            consumeMana(8);
            successfulHit = true;
        }
        else
        {
            cout << "Your attack missed completely!\n";
            successfulHit = false;
        }

        int currentCombo = registerCombo(successfulHit);

        if (successfulHit)
        {
            cout << "Current Combo Streak: "
                << currentCombo << "x\n";

            gainWizardXP(30);
        }

        bool isBossEnraged = processBossRage(damageDealt);

        if (isBossEnraged)
        {
            cout << "!!! WARNING: BOSS HAS ENTERED ENRAGE MODE !!!\n";
        }

        turn++;

        cout << "\nEnd turn? Continue fighting? (y/n): ";
        cin >> continueBattle;
    }

    cout << "\n=== BATTLE SIMULATION ENDED ===\n";

    return 0;
}