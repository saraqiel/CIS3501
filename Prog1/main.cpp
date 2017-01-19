//  Created by Christian Munte on 1/19/17
//  Description: The program will be taking in first an integer with the amount of stops avalible.
//               Then the program will take stops and list all the poisslbe ways to catch the Pokemon.
//               Then, using next_permutation the program will find the shortest possible path.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class ImportPoke {
private:
    struct Pokemon {
        string name;
        int xPos;
        int yPos;
    };
    vector <Pokemon> pokeStops;
public:
    void import(int);
    void addPokemon(string, int, int);
    void printStops();
};

int main() {
    ImportPoke pokemon;
    int loop;
    cin >> loop;
    pokemon.import(loop);
    pokemon.printStops();
    return 0;
}

void ImportPoke::import(int loop){
    for (int a=0; a<loop; a++) {
        string name;
        int x, y;
        cin >> x >> y >> name;
        addPokemon(name, x, y);
    }
}

void ImportPoke::addPokemon(string name, int x, int y) {
    struct Pokemon temp;
    temp.name = name;
    temp.xPos = x;
    temp.yPos = y;
    pokeStops.push_back(temp);
}

void ImportPoke::printStops(){
    for (int a=0; a<pokeStops.size(); a++) {
        cout << pokeStops[a].name << " at " << pokeStops[a].xPos << "," << pokeStops[a].yPos << endl;
    }
}
