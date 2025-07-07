#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// All the card types
enum CardType {
    BATSMAN,
    BOWLER,
    ALLROUNDER
};

class Cricketer_Card {
protected:
    string name;
    int age;
    int matches;
    int trophies;
    CardType cardType;

public:
    Cricketer_Card(string name, int age, int matches, int trophies)
        : name(name), age(age), matches(matches), trophies(trophies) {}

    virtual int get_score(const string& stat_name) const = 0;
    virtual CardType getCardType() const = 0;

    virtual void print_card() const {
        cout << "+-----------------------------+\n";
        cout << "|        Cricketer Card       |\n";
        cout << "+-----------------------------+\n";
        cout << "| Name         : " << setw(14) << left << name << "|\n";
        cout << "| Age          : " << setw(14) << left << age << "|\n";
        cout << "| Matches      : " << setw(14) << left << matches << "|\n";
        cout << "| Trophies     : " << setw(14) << left << trophies << "|\n";
    }

    virtual ~Cricketer_Card() {}
};

//Used access modifier virtual public to avoid diamond problem(occurs in hybrid inheritance)
class Batsman_Card : virtual public Cricketer_Card {
protected:

    int runs;
    float average;
    float strike_rate;

public:
    Batsman_Card(string n, int a, int m, int t, int r, float avg, float sr)
        : Cricketer_Card(n, a, m, t), runs(r), average(avg), strike_rate(sr) {}

    int get_score(const string& stat_name) const override {
        if (stat_name == "runs") return runs;
        if (stat_name == "average") return static_cast<int>(average);
        if (stat_name == "strike_rate") return static_cast<int>(strike_rate);
        if (stat_name == "matches") return matches;
        if (stat_name == "trophies") return trophies;
        if (stat_name == "age") return age;
        return -1;
    }

    void print_card() const override {
        Cricketer_Card::print_card();
        cout << "+-----------------------------+\n";
        cout << "|        BATTING STATS        |\n";
        cout << "+-----------------------------+\n";
        cout << "| Runs         : " << setw(14) << left << runs << "|\n";
        cout << "| Average      : " << setw(14) << left << average << "|\n";
        cout << "| Strike Rate  : " << setw(14) << left << strike_rate << "|\n";
        cout << "+-----------------------------+\n";
    }

    CardType getCardType() const override {
        return BATSMAN;
    }
};

//Used access modifier virtual public to avoid diamond problem(occurs in hybrid inheritance)

class Bowler_Card : virtual public Cricketer_Card {
protected:
    int wickets;
    float economy;
    float bowling_average;

public:
    Bowler_Card(string n, int a, int m, int t, int w, float eco, float ba)
        : Cricketer_Card(n, a, m, t), wickets(w), economy(eco), bowling_average(ba) {}

    int get_score(const string& stat_name) const override {
        if (stat_name == "wickets") return wickets;
        if (stat_name == "economy") return -1*static_cast<int>(economy);
        if (stat_name == "bowling_average") return -1* static_cast<int>(bowling_average);
        if (stat_name == "matches") return matches;
        if (stat_name == "trophies") return trophies;
        if (stat_name == "age") return age;
        return -1;
    }

    void print_card() const override {
        // used #include <iomanip> to get setwfunction
        Cricketer_Card::print_card();
        cout << "+-----------------------------+\n";
        cout << "|        BOWLING STATS        |\n";
        cout << "+-----------------------------+\n";
        cout << "| Wickets      : " << setw(14) << left << wickets << "|\n";
        cout << "| Economy      : " << setw(14) << left << economy << "|\n";
        cout << "| Bowl Avg     : " << setw(14) << left << bowling_average << "|\n";
        cout << "+-----------------------------+\n";
    }

    CardType getCardType() const override {
        return BOWLER;
    }
};

// All-Rounder Card (inherits from both Batsman_Card and Bowler_Card)
class AllRounder : public Batsman_Card, public Bowler_Card {
public:
    AllRounder(string n, int a, int m, int t,
               int r, float batAvg, float sr,
               int w, float eco, float bowlAvg)
        : Cricketer_Card(n, a, m, t),
          Batsman_Card(n, a, m, t, r, batAvg, sr),
          Bowler_Card(n, a, m, t, w, eco, bowlAvg) {}

    CardType getCardType() const override {
        return ALLROUNDER;
    }

    void print_card() const override {
        Cricketer_Card::print_card();
        cout << "+-----------------------------+\n";
        cout << "|        BATTING STATS        |\n";
        cout << "+-----------------------------+\n";
        cout << "| Runs         : " << setw(14) << left << runs << "|\n";
        cout << "| Average      : " << setw(14) << left << average << "|\n";
        cout << "| Strike Rate  : " << setw(14) << left << strike_rate << "|\n";
        cout << "+-----------------------------+\n";
        cout << "|        BOWLING STATS        |\n";
        cout << "+-----------------------------+\n";
        cout << "| Wickets      : " << setw(14) << left << wickets << "|\n";
        cout << "| Economy      : " << setw(14) << left << economy << "|\n";
        cout << "| Bowl Avg     : " << setw(14) << left << bowling_average << "|\n";
        cout << "+-----------------------------+\n";
    }

    int get_score(const string& stat_name) const override {
        if (stat_name == "runs" || stat_name == "average" || stat_name == "strike_rate")
            return Batsman_Card::get_score(stat_name);
        if (stat_name == "wickets" || stat_name == "economy" || stat_name == "bowling_average")
            return Bowler_Card::get_score(stat_name);
        if (stat_name == "matches") return matches;
        if (stat_name == "trophies") return trophies;
        if (stat_name == "age") return age;
        return -1;
    }
};

// Player's class for both bot and human
class Player {
private:
    queue<Cricketer_Card*> q;

public:
    string name;
    bool isRobot;

    Player(string n, bool isBot = false) {
        name = n;
        isRobot = isBot;
    }

    ~Player() {
        while (!q.empty()) {
            delete q.front();
            q.pop();
        }
    }

    bool isEmpty() {
        return q.empty();
    }

    void addCard(Cricketer_Card* card) {
        q.push(card);
    }

    Cricketer_Card* removeTopCard() {
        if (q.empty()) return nullptr;
        Cricketer_Card* top = q.front();
        q.pop();
        return top;
    }

    void printTopCard() {
        if (!q.empty()) {
            q.front()->print_card();
        } else {
            cout << name << " has no cards left!\n";
        }
    }

    int getCardCount() {
        return q.size();
    }
};

// Game class
class Game {
private:
    Player* p1;
    Player* p2;
    int announcerIndex = 0;
    int rounds = 0;
    const int MAX_ROUNDS = 99;
    queue<Cricketer_Card*> tiePile;
    mt19937 rng;

public:
    Game(Player* player1, Player* player2)
        : p1(player1), p2(player2), rng(random_device{}()) {}

    // valid stats based on card types
    //RULES ARE IF A PLAYER 1 CHOOSES A STAT IT MUST BE ALSO PRESENT IN PLAYER 2 
    //IT IS UNFAIR TO SELECT A BATTING STAT WHEN COMPARISON IS BETWEEN BASTMAN AND BOWLER AND VICEVERSA
    vector<string>get_valid_stats(Cricketer_Card* c1, Cricketer_Card* c2) {
        CardType t1= c1->getCardType();
        CardType t2= c2->getCardType();
        vector<string> valid;

        if ((t1 == BATSMAN || t1 == ALLROUNDER) && (t2 == BATSMAN || t2 == ALLROUNDER)) {
            valid = {"runs", "average", "strike_rate", "matches", "trophies", "age"};
        } else if ((t1 == BOWLER || t1 == ALLROUNDER) && (t2 == BOWLER || t2 == ALLROUNDER)) {
            valid = {"wickets", "economy", "bowling_average", "matches", "trophies", "age"};
        } else {
            valid = {"matches", "trophies", "age"};
        }
        return valid;
    }

    // Stat selection by announcer from valid stats
    string choose_stat(Player*announcer,Cricketer_Card* c1,const vector<string>& validStats) {
        cout<< "The card of the announcer"<<endl;
        c1->print_card();
        cout << "\nAvailable stats: ";
        for (const string& stat : validStats)
            cout << stat << " ";
        if (announcer->isRobot) {
            int idx = rand() % validStats.size();//chooses randomly from validstats
            cout << "the stat chosen is :"<<validStats[idx]<< endl;
            return validStats[idx];
        } else {
            cout << "\nAvailable stats: ";
            string chosen;
            while (true) {
                cin >> chosen;
                if (find(validStats.begin(), validStats.end(), chosen) != validStats.end())
                    break;
                cout << "Invalid stat. Choose again: ";
            }

            return chosen;
        }
    }

    // all tiePile cards goes to winner
    void distributeTiePile(Player* winner) {
        while (!tiePile.empty()) {
            winner->addCard(tiePile.front());
            tiePile.pop();
        }
    }

    // Core game loop
    void startGame() {
        cout << "\n Starting the match between " << p1->name << " and " << p2->name << "!\n";

        while (!p1->isEmpty() && !p2->isEmpty() && rounds < MAX_ROUNDS) {
            Player* announcer = (announcerIndex == 0) ? p1 : p2;
            Player* opponent = (announcerIndex == 0) ? p2 : p1;

            Cricketer_Card* card1 = announcer->removeTopCard();
            Cricketer_Card* card2 = opponent->removeTopCard();

            if (!card1 || !card2) break; 
            tiePile.push(card1);
            tiePile.push(card2);
            
            vector<string> validStats = get_valid_stats(card1, card2);
            string chosenStat = choose_stat(announcer,card1, validStats);
            
            int score1 = card1->get_score(chosenStat);
            int score2 = card2->get_score(chosenStat);

            cout << "\n========== ROUND " << rounds + 1 << " ==========\n";
            cout << announcer->name << " chose stat: " << chosenStat << "\n";
            cout << announcer->name << "'s score: " << score1 << "\n";
            cout << opponent->name << "'s score: " << score2 << "\n";

            // RULE : If announcer doesnt win, switch announcer
            
            if (score1 == score2) {
                card2->print_card();
                cout << "🟰 It's a tie! Cards go to tie pile.\n";
                announcerIndex = (announcerIndex + 1) % 2;  
            } else {
                card2->print_card();
                Player* winner = (score1 > score2) ? announcer : opponent;
                cout  << winner->name << " wins the round and collects all cards.\n";
                distributeTiePile(winner);

                
                if (winner != announcer) {
                    announcerIndex = (announcerIndex + 1) % 2;
                }
            }

            rounds++;
        }

        cout << "\n================ GAME OVER ================\n";
        int count1 = p1->getCardCount();
        int count2 = p2->getCardCount();

        cout << p1->name << "'s cards: " << count1 << "\n";
        cout << p2->name << "'s cards: " << count2 << "\n";

        if (count1 > count2)
            cout   << p1->name << " wins the game!\n";
        else if (count2 > count1)
            cout << p2->name << " wins the game!\n";
        else
            cout << " Game ends in a draw!\n";
    }
};

int main() {
    vector<Cricketer_Card*> deck;

    vector<vector<string>> allrounders = {
        {"Ravindra Jadeja", "36", "254", "5", "2412", "27.4", "127.61", "170", "7.67", "30.52"},
        {"Shane Watson", "42", "145", "2", "3874", "30.99", "137.91", "92", "7.93", "29.15"},
        {"Dwayne Bravo", "40", "161", "3", "1567", "22.6", "129.57", "183", "8.38", "23.82"},
        {"Kieron Pollard", "37", "189", "5", "3412", "28.67", "147.32", "69", "8.79", "31.59"},
        {"Andre Russell", "36", "140", "2", "2226", "29.83", "174", "123", "9.42", "25.96"},
        {"Hardik Pandya", "31", "137", "4", "2525", "28.69", "145.86", "64", "8.75", "33.59"},
        {"Yusuf Pathan", "41", "174", "3", "3204", "29.13", "142.97", "42", "7.4", "33.0"},
        {"Sunil Narine", "36", "176", "2", "1534", "17.04", "162.69", "180", "6.73", "25.39"},
        {"Glenn Maxwell", "36", "135", "0", "2771", "24.52", "157.62", "38", "8.32", "34.97"},
        {"Moeen Ali", "37", "67", "1", "1162", "22.78", "126.2", "35", "7.47", "25.51"}
    };

    for (auto& row : allrounders) {
        deck.push_back(new AllRounder(
            row[0],                             // name
            stoi(row[1]), stoi(row[2]), stoi(row[3]), // age, matches, trophies
            stoi(row[4]), stof(row[5]), stof(row[6]), // runs, avg, SR
            stoi(row[7]), stof(row[8]), stof(row[9])  // wickets, eco, bowling avg
        ));
    }

    vector<vector<string>> batsmen = {
        {"Virat Kohli", "35", "237", "1", "7263", "37.25", "130.02"},
        {"Shikhar Dhawan", "38", "217", "1", "6617", "35.39", "127.17"},
        {"Rohit Sharma", "37", "257", "6", "6368", "30.11", "131.1"},
        {"Suresh Raina", "37", "205", "4", "5528", "32.52", "136.73"},
        {"David Warner", "37", "176", "1", "6397", "41.54", "139.91"},
        {"AB de Villiers", "40", "184", "0", "5162", "39.71", "151.68"},
        {"Chris Gayle", "44", "142", "0", "4965", "39.72", "148.96"},
        {"MS Dhoni", "43", "250", "5", "5082", "39.09", "135.92"},
        {"Robin Uthappa", "38", "205", "2", "4952", "27.51", "130.35"},
        {"Gautam Gambhir", "42", "154", "2", "4217", "31.24", "123.88"},
        {"Dinesh Karthik", "39", "257", "1", "4516", "26.85", "132.71"},
        {"Ajinkya Rahane", "36", "183", "2", "4420", "30.98", "123.91"},
        {"Ambati Rayudu", "39", "204", "6", "4348", "28.23", "127.61"},
        {"KL Rahul", "32", "127", "0", "4163", "46.78", "134.42"},
        {"Manish Pandey", "34", "170", "1", "3701", "29.9", "121.86"},
        {"Sanju Samson", "30", "152", "0", "3883", "29.23", "135.13"},
        {"Shane Watson", "42", "145", "2", "3874", "30.99", "137.91"},
        {"Faf du Plessis", "40", "130", "1", "4133", "36.9", "134.15"},
        {"Brendon McCullum", "42", "109", "0", "2880", "27.69", "131.74"},
        {"Parthiv Patel", "39", "139", "1", "2848", "22.6", "120.78"},
        {"Rishabh Pant", "27", "98", "0", "2838", "34.61", "147.97"},
        {"Shaun Marsh", "40", "71", "0", "2477", "39.95", "132.74"},
        {"Virender Sehwag", "45", "104", "0", "2728", "27.55", "155.44"},
        {"Murli Vijay", "40", "106", "2", "2619", "25.93", "121.87"},
        {"Yuvraj Singh", "42", "132", "2", "2750", "24.77", "129.71"},
        {"Jacques Kallis", "48", "98", "1", "2427", "28.55", "109.22"}
        };

    for (auto& row : batsmen) {
        deck.push_back(new Batsman_Card(
            row[0],
            stoi(row[1]), stoi(row[2]), stoi(row[3]),
            stoi(row[4]), stof(row[5]), stof(row[6])
        ));
    }

    
    vector<vector<string>> bowlers = {
        {"Yuzvendra Chahal", "34", "174", "0", "221", "22.77", "7.96"},
        {"Bhuvneshwar Kumar", "34", "160", "1", "170", "25.83", "7.39"},
        {"Piyush Chawla", "35", "192", "3", "179", "27.39", "7.91"},
        {"Ravichandran Ashwin", "37", "197", "2", "171", "28.51", "7.01"},
        {"Jasprit Bumrah", "31", "145", "2", "145", "23.3", "7.41"},
        {"Amit Mishra", "41", "162", "0", "166", "23.84", "7.38"},
        {"Lasith Malinga", "41", "122", "4", "170", "19.8", "7.14"},
        {"Rashid Khan", "26", "136", "0", "158", "22.95", "7.19"},
        {"Harbhajan Singh", "44", "163", "4", "150", "26.44", "7.05"},
        {"Sandeep Sharma", "31", "137", "0", "146", "25.75", "8.32"},
        {"Umesh Yadav", "36", "148", "2", "144", "31.81", "8.3"},
        {"Trent Boult", "35", "120", "1", "143", "25.43", "7.74"},
        {"Mohit Sharma", "35", "120", "2", "134", "26.96", "8.94"},
        {"Mohammad Shami", "34", "120", "1", "133", "26.83", "8.44"},
        {"Axar Patel", "30", "162", "1", "128", "31.02", "7.23"},
        {"Andre Russell", "36", "140", "2", "123", "25.96", "9.42"},
        {"Kagiso Rabada", "29", "69", "0", "106", "20.73", "8.32"},
        {"Ashish Nehra", "45", "88", "1", "106", "23.53", "7.84"},
        {"Dale Steyn", "40", "95", "0", "97", "25.85", "6.91"},
        {"Vinay Kumar", "40", "105", "1", "105", "28.24", "8.39"},
        {"Praveen Kumar", "38", "119", "1", "90", "36.12", "7.72"},
        {"Prasidh Krishna", "28", "41", "0", "41", "19.52", "8.27"},
        {"Noor Ahmad", "19", "24", "0", "24", "17", "8.16"},
        {"Josh Hazlewood", "33", "22", "0", "22", "17.54", "7"},
        {"Harshal Patel", "33", "119", "0", "151", "25.86", "9.07"},
        {"Zaheer Khan", "45", "100", "1", "102", "27.27", "7.58"}
    };


    for (auto& row : bowlers) {
        deck.push_back(new Bowler_Card(
            row[0],
            stoi(row[1]), stoi(row[2]), stoi(row[3]),
            stoi(row[4]), stof(row[6]), stof(row[5])
        ));
    }
    // rd: random device for seeding | g: Mersenne Twister RNG for shuffling
    // didnt use rand() because it is deprecated in shuffle(_,_,rand())
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);

    string pname;
    cout << "Enter your name: ";
    getline(cin, pname);
    if (pname.empty()) pname = "Player 1";

    Player* player1 = new Player(pname, false); 
    Player* player2 = new Player("Bot", true);  

    for (size_t i = 0; i < deck.size(); ++i) {
        if (i % 2 == 0) player1->addCard(deck[i]);
        else player2->addCard(deck[i]);
    }

    Game game(player1, player2);
    game.startGame();

    // very import to avoid memory leak
    delete player1;
    delete player2;

    return 0;
}
