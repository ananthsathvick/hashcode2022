#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class Project {
    public:
        string name;
        ll requiredNumberOfDays;
        ll scoreAwarded;
        ll bestBeforeDay;

        vector<pair<string,ll>> requiredSkill;

        vector<pair<Developer*,string>> developerWorking; 

        ll isProjectCompleted;

        Project(){
            isProjectCompleted = 0;
        }
};