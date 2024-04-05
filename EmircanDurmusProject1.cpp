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

void initPolitician()
{
    for(int i=0; i<4; ++i)
    {
        for(int j=0; j < pos[i]; ++j)
        {
            politicians.push_back(Politician(minAge[i]+j%5));
            politicians.back().office = i;
            age_distrubitons[i].push_back(politicians.back().age);
            candidates[i]++;
        }
    }
}

void simYear()
{
    int newCand = round(new_cand_dist(gen));
    for(int i=0; i< newCand; ++i)
    {
        politicians.emplace_back(25);
    }

    politicianAgingxCheckAlive();
    fillOffice();
}

void politicianAgingxCheckAlive()
{
    for( auto i = politicians.begin(); i != politicians.end();)
    {
        i->age++;
        if(i->age > i->lifeExpect)
        {
            i= politicians.erase(i);
        } else {
            ++i;
        }

        
    }
}

void fillOffice()
{
    vector<int> annualPositionFill(4, 0);

    for(auto& p: politicians)
    {
        if (p.isLiving && p.office < 3)
        {
            int next = p.office + 1;
            if (annualPositionFill[next] < pos[next] && p.age >= minAge[next])
            {
                p.office = next;
                annualPositionFill[next]++;
                candidates[next]++;
                age_distrubitons[next].push_back(p.age);
            }
            
        }
        
    }

    for(int i=0; i<4; ++i)
    {
        int empty = pos[i]-annualPositionFill[i];
        if(empty >0)
        {
            PSI -= empty * 5;
        }
    }
}

void results()
{
    cout << "PSI:" << PSI << endl << endl;
    cout << "Annual Fill Rate:" << endl;
    for(int i=0; i<4; ++i)
    {
        double fillRate = 100.0 * candidates[i] / (pos[i]*year);
        cout << officeNames[i] << ": "<< fillRate << "%" <<endl;
    }

    cout << endl <<"Age Distribution:" << endl;
    for(int i=0; i<4; ++i)
    {
        if (!age_distrubitons[i].empty())
        {
            double avgAge = accumulate(age_distrubitons[i].begin(), age_distrubitons[i].end(), 0.0) / age_distrubitons[i].size();
            cout << officeNames[i] << " Average Age: " << avgAge << endl;
        }
        
    }
}