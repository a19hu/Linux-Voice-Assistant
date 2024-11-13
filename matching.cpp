#include <bits/stdc++.h>
using namespace std;
vector<int> match(vector<vector<string>> commands, vector<string> word)
{
    int n = commands.size();
    int wrdSize = word.size();
    vector<int> stats;
    for (int i = 0; i < n; i++)
    {
        int point = 0;
        for (int k = 0; k < wrdSize; k++)
        {
            for (int j = 0; j < commands[i].size(); j++)
            {
                if (word[k] == commands[i][j])
                    point++;
            }
        }
        stats.push_back(point);
        point = 0;
    }
    return stats;
}
int32_t main()
{
    // Create a vector of vectors to store the pairs of natural language command and Linux command
    vector<vector<string>> commands = {
        {"open", "[App Name]"},
        {"close", "[App Name]"},
        {"list", "files"},
        {"create",  "new", "file", "named"},
        {"delete",  "file"},
        {"move"},
        {"copy"},
        {"increase", "volume", "by"},
        {"decrease", "volume", "by"},
        {"mute","Unmute", "volume"},
        {"check", "battery", "status"},
        {"increase", "brightness", "by"},
        {"decrease", "brightness", "by"},
        {"what’s",  "date/time?", "date"},
        {"take", "screenshot"},
        {"search", "web", "for"},
        {"play", "media"},
        {"pause", "media"},
        {"check", "cpu", "status"},
        {"check", "memory", "usage"},
        {"check", "network", "status"},
        {"execute", "[Custom", "Command]"},
        {"authenticate"}};
    cout << "Enter a sentence: " << endl;
    string s;
    getline(cin,s);
    s+=" ";
    int len = s.size();
   
    string wrd;
    vector<string> word;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == ' ')
        {
            word.push_back(wrd);
            wrd = "";
        }
        else
            wrd+=s[i];
    }
 
    
    vector<int> stats = match(commands, word);
    int max = -1;
    int ind=-1;
    // for(auto stat:stats){
    //    cout<<stat<<" ";
    // }
    // cout<<endl;
    for (int i = 0; i < stats.size(); i++)
    {
        if (max < stats[i])
        {
           max=stats[i];
           ind=i;
        }
    }
    // cout<<max<<endl;
    if(max!=-1)
    for(int i=0;i<commands[ind].size();i++){
        cout<<commands[ind][i]<<" ";
    }
    cout << endl;
    // Iterate over the vector of vectors and print the corresponding command components

    return 0;
}
