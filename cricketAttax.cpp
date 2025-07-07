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
        {"Hardik Pandya", "30", "120", "15", "2500", "29.5", "140.2", "60", "7.4", "28.3"},
        {"Ben Stokes", "32", "110", "12", "2100", "31.0", "132.5", "45", "8.1", "30.1"},
        {"Andre Russell", "33", "140", "18", "2200", "27.2", "165.4", "70", "9.3", "25.4"},
        {"Shane Watson", "35", "145", "20", "3874", "30.99", "137.91", "92", "7.93", "29.15"},
        {"Jacques Kallis", "38", "98", "14", "2427", "28.55", "109.22", "65", "7.1", "24.2"},
        {"Ravindra Jadeja", "34", "254", "16", "2412", "27.4", "127.61", "170", "7.67", "30.52"},
        {"Shakib Al Hasan", "36", "120", "18", "2200", "28.4", "121.6", "85", "6.7", "27.3"},
        {"Kieron Pollard", "34", "179", "19", "3271", "29.73", "149.49", "60", "8.6", "32.1"},
        {"Chris Woakes", "31", "90", "9", "1400", "22.2", "122.0", "50", "7.5", "31.0"},
        {"Mohammad Nabi", "37", "100", "10", "1600", "26.8", "124.5", "58", "6.8", "29.9"}
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
        {"Virat Kohli", "35", "209", "20", "6336", "37.49", "130.07"},
        {"Rohit Sharma", "36", "214", "18", "5652", "31.22", "130.38"},
        {"David Warner", "34", "150", "16", "5449", "41.59", "139.96"},
        {"AB de Villiers", "38", "184", "19", "5162", "39.7", "151.68"},
        {"Chris Gayle", "42", "142", "15", "4965", "39.72", "148.96"}
    };

    for (auto& row : batsmen) {
        deck.push_back(new Batsman_Card(
            row[0],
            stoi(row[1]), stoi(row[2]), stoi(row[3]),
            stoi(row[4]), stof(row[5]), stof(row[6])
        ));
    }

    vector<vector<string>> bowlers = {
        {"Jasprit Bumrah", "30", "145", "17", "183", "22.02", "7.25"},
        {"Sunil Narine", "35", "189", "20", "192", "25.64", "6.8"},
        {"Rashid Khan", "26", "136", "15", "158", "22.95", "7.19"},
        {"Lasith Malinga", "40", "122", "25", "170", "19.8", "7.14"},
        {"Bhuvneshwar Kumar", "33", "190", "18", "198", "27.33", "7.69"}
    };

    for (auto& row : bowlers) {
        deck.push_back(new Bowler_Card(
            row[0],
            stoi(row[1]), stoi(row[2]), stoi(row[3]),
            stoi(row[4]), stof(row[6]), stof(row[5])
        ));
    }

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
