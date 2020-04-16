#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>

using namespace std;

map <int, vector<int>> cards;
int counter = 0;
mutex mtx;

vector<string> my_deck = {
        "6 worms", "7 worms", "8 worms", "9 worms", "10 worms", "V worms", "D worms", "K worms", "T worms",
        "6 diamonds", "7 diamonds", "8 diamonds", "9 diamonds", "10 diamonds", "V diamonds", "D diamonds", "K diamonds", "T diamonds",
        "6 clubs", "7 clubs", "8 clubs", "9 clubs", "10 clubs", "V clubs", "D clubs", "K clubs", "T clubs",
        "6 spades", "7 spades", "8 spades", "9 spades", "10 spades", "V spades", "D spades", "K spades", "T spades"
};

void distribution(vector<int> deck, int player)
{
    while (counter < 36) {
            this_thread::sleep_for(chrono::milliseconds(100));
            mtx.lock();
            cout << "The deck is busy" << endl;
            cout << "The player " << player + 1 << " is taking a card" << endl;
            cards[player].push_back(deck[counter++]);
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "Player " << player + 1 << " has taken a card" << endl;
            cout << "The deck is free" << endl;
            mtx.unlock();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
}

void show_cards(int N){
    for (int i = 0; i < N; i++)
    {
        cout << "Cards of player " << i + 1 << ":" << endl;
        for (int j = 0; j < cards[i].size(); j++)
            cout << my_deck[cards[i][j]] << endl;
        cout << endl;
    }
}

class Deck{
public:
    Deck(){
        random_shuffle(order.begin(), order.end());
    };
    vector<int> get_deck(){
        return order;
    };
private:
    vector<int> order = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
                         19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
};

int main() {
    int N; //Количество игроков
    Deck deck; // создаем колоду
    vector<int> current_deck = deck.get_deck(); // берем порядок в колоде в current_deck
    cout << "Enter the amount of players" << endl;
    cin >> N; //Вводим число игроков
    thread th[N];
    for (int i = 0; i < N; i++)
        th[i] = thread(distribution, current_deck, i);
    this_thread::sleep_for(chrono::milliseconds(3000));
    for (int k = 0; k < N; k++)
        th[k].join();
    show_cards(N);
    return 0;
}