//  Created by Christian Munte on 1/19/17
//  Description: The program will be taking in first an integer with the amount of stops avalible.
//               Then the program will take stops and list all the poisslbe ways to catch the Pokemon.
//               Then, using next_permutation the program will find the shortest possible path.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Pokemon { //Pokemon Struct, very important
    string name;
    int xPos;
    int yPos;
    int stop;
};

class ImportPoke {
private:
    vector <Pokemon> pokeStops;
    void addPokemon(string, int, int, int);
public:
    void import(int);
    void printStops();
    vector <Pokemon> get();
};

class PokeGo {
private:
    vector < vector <Pokemon> > pokeList;
    vector < vector <int> > combos;
    bool inList(Pokemon, int&);
    void recurse(vector<int>, int);
public:
    PokeGo(vector<Pokemon>);
    void print();
};

int main() {
    ImportPoke pokemon;
    int loop;
    cin >> loop;
    pokemon.import(loop);
    PokeGo go(pokemon.get());
    
    //pokemon.printStops();
    go.print();
    return 0;
}

/* START IMPORTPOKE CLASS */

/*
 Description: Imports pokemon from user
 PRE: 0 < loop < 11
 POST: loop pokemon will be added to pokeStops vector
*/

void ImportPoke::import(int loop){
    for (int a=0; a<loop; a++) {
        string name;
        int x, y;
        cin >> x >> y >> name;
        addPokemon(name, x, y, a+1); //adds pokemon to main vector
    }
}

/*
 Description: Adds a pokemon to the vector
 PRE: name, x, y, and stp are all initialized and valid
 POST: a new Pokemon will be added to the back of pokeStops
 */

void ImportPoke::addPokemon(string name, int x, int y, int stp) {
    struct Pokemon temp;
    temp.name = name;
    temp.xPos = x;
    temp.yPos = y;
    temp.stop = stp;
    pokeStops.push_back(temp); //actually adds them
}

/*
 Description: Returns all the PokeStops
 PRE: pokeStops is initialized and not empty
 POST: returns pokeStops
 */

vector <Pokemon> ImportPoke::get() {
    return pokeStops;
}

/*
 Description: Prints all the stops, for debugging
 PRE: pokeStops is initialized and not empty
 POST: prints all stop numbers and pokemon in pokeStops
 */

void ImportPoke::printStops(){
    for (int a=0; a<pokeStops.size(); a++) {
        cout << pokeStops[a].name << " at stop " << pokeStops[a].stop << endl;
    }
}

/* START POKEGO CLASS */

/*
 Description: Constructor, puts the Pokemon correctly into pokeList and creates combinations
 PRE: import is initialized and not empty
 POST: pokeList is created as well as combos
 */

PokeGo::PokeGo(vector <Pokemon> import) {
    for (int a=0; a<import.size(); a++) {
        int pos;
        if (!inList(import[a], pos)) {
            vector<Pokemon> temp;
            temp.push_back(import[a]);
            pokeList.push_back(temp);
        } else {
            pokeList[pos].push_back(import[a]);
        }
    }
    vector<int> blank;
    recurse(blank, pokeList.size()-1);
}

/*
 Description: Checks to see if a Pokemon already exists
 PRE: mon and pos is initialized
 POST: returns false if not and true+pos if yes
 */

bool PokeGo::inList(Pokemon mon, int &pos) {
    if (pokeList.empty()) {
        return false;
    }
    for (int a=0; a<pokeList.size(); a++) {
        if (pokeList[a][0].name == mon.name) {
            pos = a;
            return true;
        }
    }
    return false;
}

/*
 Description: Recursive call to find all combinations
 PRE: pass and pos are initialized
 POST: recursive call or the completed vector is pushed back
 */

void PokeGo::recurse(vector <int> pass, int pos){
    if (pos<0) {
        reverse(pass.begin(), pass.end()); //revered because traversal is in reverse
        combos.push_back(pass);
    } else {
        for (int a=0; a<pokeList[pos].size(); a++) {
            pass.push_back(pokeList[pos][a].stop);
            recurse(pass, pos-1);
            pass.pop_back();
        }
    }
}

/*
 Description: Prints all the combinations
 PRE: combos is initialized and not empty
 POST: all combinations are printed
 */

void PokeGo::print(){
    for (int a=0; a<combos.size(); a++) {
        for (int b=0; b<combos[a].size(); b++) {
            cout << combos[a][b] << " ";
        }
        cout << endl;
    }
}
