#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());
normal_distribution<> life_dist(55,10);
normal_distribution<> new_cand_dist(15,5);
const string officeNames[4] = {"Quaestor", "Aedile", "Praetor", "Consul"};
const int minAge[4] = {30, 36, 39, 42};
const int pos[4] = {20, 10, 8, 2};
const int year = 200;
vector<int> age_distrubitons[4];

int PSI = 100;
int candidates[4] = {0, 0, 0, 0};

struct Politician {
    bool isLiving = true;
    int age;
    int office = -1;
    int lifeExpect;

    Politician(int startingAge) : age(startingAge), lifeExpect(max(25, min(int(life_dist(gen)), 80))) {}
};

vector<Politician> politicians;

void initPolitician();
void simYear();
void politicianAgingxCheckAlive();
void fillOffice();
void elections();
void PSIcalc();
void results();

int main() {
    initPolitician();

    for(int i=1; i<= year; ++i) 
    {
        simYear();
    }

    results();
    return 0;
}