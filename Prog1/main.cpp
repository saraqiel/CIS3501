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
    vector < vector<Pokemon> > pokeStop;
    void addPokemon(string, int, int, int);
    bool inList(Pokemon, int&);
    
public:
    ImportPoke(int);
    void printStops();
    vector < vector<Pokemon> > get();
};

class PokeGo {
private:
    vector < vector <Pokemon> > combos;
    void recurse(const vector< vector<Pokemon> >&,vector<Pokemon>, int);
    
public:
    PokeGo(vector< vector<Pokemon>>);
    void print();
};

int main() {
    int loop;
    cin >> loop;
    ImportPoke pokemon(loop);
    PokeGo go(pokemon.get());
    
    pokemon.printStops();
    go.print();
    return 0;
}

/* START IMPORTPOKE CLASS */

/*
 Description: Constructor, mports pokemon from user
 PRE: 0 < loop < 11
 POST: loop pokemon will be added to pokeStops vector
*/

ImportPoke::ImportPoke(int loop){
    for (int a=0; a<loop; a++) {
        string name;
        int x, y;
        cin >> x >> y >> name;
        addPokemon(name, x, y, a+1); //adds pokemon to main vector
    }
}

/*
 Description: Adds a pokemon to pokeStop
 PRE: name, x, y, and stp are all initialized and valid
 POST: a new Pokemon will be added to the back of pokeStops
 */

void ImportPoke::addPokemon(string name, int x, int y, int stp) {
    struct Pokemon temp;
    int pos;
    
    temp.name = name;
    temp.xPos = x;
    temp.yPos = y;
    temp.stop = stp;
    
    
    if (!inList(temp, pos)) {
        vector<Pokemon> tempV;
        tempV.push_back(temp);
        pokeStop.push_back(tempV);
    } else {
        pokeStop[pos].push_back(temp);
    }
}

/*
 Description: Checks to see if a Pokemon already exists
 PRE: mon and pos is initialized
 POST: returns false if not and true+pos if yes
 */

bool ImportPoke::inList(Pokemon mon, int &pos) {
    if (pokeStop.empty()) {
        return false;
    }
    for (int a=0; a<pokeStop.size(); a++) {
        if (pokeStop[a][0].name == mon.name) {
            pos = a;
            return true;
        }
    }
    return false;
}

/*
 Description: Returns all the pokemon in pokeStop
 PRE: pokeStops is initialized and not empty
 POST: returns pokeStop
 */

vector < vector <Pokemon> > ImportPoke::get() {
    return pokeStop;
}

/*
 Description: Prints all the stops, for debugging
 PRE: pokeStops is initialized and not empty
 POST: prints all stop numbers and pokemon in pokeList
 */

void ImportPoke::printStops(){
    cout << "stops:\n";
    for (int a=0; a<pokeStop.size(); a++) {
        cout << pokeStop[a][0].name << " ";
        for (int b=0; b<pokeStop[a].size(); b++) {
            cout << pokeStop[a][b].stop << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* START POKEGO CLASS */

/*
 Description: Constructor, puts the Pokemon correctly into pokeList and creates combinations
 PRE: import is initialized and not empty
 POST: pokeList is created as well as combos
 */

PokeGo::PokeGo(vector< vector <Pokemon> > import) {
    
    vector<Pokemon> blank;
    recurse(import, blank, import.size()-1);
}

/*
 Description: Recursive call to find all combinations
 PRE: pass and pos are initialized
 POST: recursive call or the completed vector is pushed back
 */

void PokeGo::recurse(const vector< vector<Pokemon> > &pokeStop, vector <Pokemon> pass, int pos){
    if (pos<0) {
        reverse(pass.begin(), pass.end()); //revered because traversal is in reverse
        combos.push_back(pass);
    } else {
        for (int a=0; a<pokeStop[pos].size(); a++) {
            pass.push_back(pokeStop[pos][a]);
            recurse(pokeStop, pass, pos-1);
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
            cout << combos[a][b].stop << " ";
        }
        cout << endl;
    }
}
