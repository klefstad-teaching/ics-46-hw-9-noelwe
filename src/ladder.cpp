#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << word1 << word2;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) return false;

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= len2; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= len1; ++i)
    {
        for (int j = 1; j <= len2; ++j)
        {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;

            dp[i][j] = min({dp[i - 1][j] + 1,
                            dp[i][j- 1 ] + 1,
                            dp[i - 1][j - 1] + cost});
            
            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1])
            {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1);
            }
        }
    }
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);

    if (!file)
    {
        error("","", "File not found");
    }

    string word;
    while (file >> word)
    {
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    for( const string& word : ladder)
    {
        cout << word << ' ';
    }
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}