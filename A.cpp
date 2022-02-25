#include <bits/stdc++.h>
#include "person.cpp"
#include "project.cpp"
using namespace std;
#define MOD 1000000007
typedef long long ll;
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
Developer *findLowestScoreDeveloper(string skill, ll score, vector<Developer> &dev)
{
    Developer *minimum = NULL;
    for (Developer &d : dev)
    {
        if (d.skill[skill] >= score && !d.isBusy)
        {
            if (minimum && minimum->skill[skill] >= d.skill[skill])
            {
                minimum = &d;
            }
            else
            {
                minimum = &d;
            }
        }
    }
    return minimum;
}

vector<Project *> getAllSuccessProjects(vector<Developer> &dev, vector<Project> &proj)
{
    vector<Project *> doableProjects;
    for (Project &project : proj)
    {
        if (!project.isProjectCompleted)
        {
            ll isDoable = 1;
            for (auto skills : project.requiredSkill)
            {
                string skill = skills.first;
                ll score = skills.second;
                Developer *d = findLowestScoreDeveloper(skill, score, dev);
                if (d)
                {
                    d->isBusy = 1;
                    project.developerWorking.push_back({d,skill});
                }
                else
                {
                    for (auto ii : project.developerWorking)
                    {
                        ii.first->isBusy = 0;
                    }
                    project.developerWorking.clear();
                    isDoable = 0;
                    break;
                }
            }
            if (isDoable)
            {
                doableProjects.push_back(&project);
            }
        }
    }
    return doableProjects;
}

int main()
{
    fio;
    freopen("input.txt", "r", stdin);
    freopen("f_output.txt", "w", stdout);
    ll noc, nop;
    cin >> noc >> nop;
    vector<Developer> dev(noc);
    vector<Project> proj(nop);

    for (ll cont = 0; cont < noc; cont++)
    {
        Developer d;
        cin >> d.name;

        ll nos;
        cin >> nos;

        map<string, ll> skills;
        while (nos--)
        {
            string skill;
            cin >> skill;
            ll score;
            cin >> score;
            skills[skill] = score;
        }

        d.skill = skills;
        dev[cont] = d;
    }

    for (ll pro = 0; pro < nop; pro++)
    {
        Project p;
        ll number_of_roles;

        cin >> p.name >> p.requiredNumberOfDays >> p.scoreAwarded >> p.bestBeforeDay >> number_of_roles;


        while (number_of_roles--)
        {
            string skill;
            ll score;
            cin >> skill >> score;
            p.requiredSkill.push_back({skill,score});
        }
        proj[pro] = p;
    }

    vector<Project *> succProj = getAllSuccessProjects(dev, proj); // test
    vector<pair<string,vector<string>>> result;
    while (succProj.size())
    {
        sort(succProj.begin(), succProj.end(), [](const Project *lhs, const Project *rhs)
             { return (lhs->requiredNumberOfDays - lhs->bestBeforeDay) <= (rhs->requiredNumberOfDays - rhs->bestBeforeDay); });

        for (Project *i : succProj)
        {
            i->isProjectCompleted = 1;
            vector<string> ssp;
            for (auto d : i->developerWorking)
            {
                d.first->isBusy = 0;
                ll sscore = 0;
                for(auto i:i->requiredSkill){
                    if(i.first == d.second){
                        sscore = i.second;
                    }
                }
                if(d.first->skill[d.second] <= sscore){
                    d.first->skill[d.second]++;
                }
                // result[i->name].push_back();
                ssp.push_back(d.first->name);
            }
            result.push_back({i->name,ssp});
        }
        succProj = getAllSuccessProjects(dev, proj);
    }
    cout<<result.size()<<"\n";
    for(auto&i : result){
        cout<<i.first<<"\n";
        for(string& ss : i.second){
            cout<<ss<<" ";
        }
        cout<<"\n";
    }

    return 0;
}

/*
findLowestScoreDeveloper(skill,score)


 */