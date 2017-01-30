//  Created by Christian Munte on 1/19/17
//  Description: The program will be taking in first an integer with the amount of stops avalible.
//               Then the program will take stops and list all the poisslbe ways to catch the Pokemon.
//               Then, using next_permutation the program will find the shortest possible path.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pokemon { //Pokemon Struct, very important
    string name;
    int xPos;
    int yPos;
    int stop;
};

class ImportPoke {
private:
    vector < vector<Pokemon> > pokeMon;
    vector<Pokemon> pokeStop;
    void addPokemon(string, int, int, int);
    bool inList(Pokemon, int&);
    
public:
    ImportPoke(int);
    void printStops();
    vector < vector<Pokemon> > get();
    vector<Pokemon> getStops();
};

class PokeGo {
private:
    vector < vector <int> > mix;
    void recurse(const vector< vector<Pokemon> >&, vector<int>, int);
    int dist(Pokemon, Pokemon);
    int permute(const vector<Pokemon>&, vector<int>&);
    
public:
    PokeGo(vector< vector<Pokemon>>, vector<Pokemon>);
    void print();
};

int main() {
    int loop;
    cin >> loop;
    ImportPoke pokemon(loop);
    PokeGo go(pokemon.get(), pokemon.getStops());
    
    //pokemon.printStops();
    //go.print();
    return 0;
}

/* START IMPORTPOKE CLASS */

/*
 Description: Constructor, imports pokemon from user
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
 Description: Adds a pokemon to pokeMon and pokeStop
 PRE: name, x, y, stp, pokeStop, and pokeMon are all initialized
 POST: a new Pokemon will be added to pokeMon depeneding on if others aready exist and to pokeStop
 */

void ImportPoke::addPokemon(string name, int x, int y, int stp) {
    struct Pokemon temp;
    int pos;
    
    temp.name = name;
    temp.xPos = x;
    temp.yPos = y;
    temp.stop = stp;
    
    pokeStop.push_back(temp);
    
    if (!inList(temp, pos)) {
        vector<Pokemon> tempV;
        tempV.push_back(temp);
        pokeMon.push_back(tempV);
    } else {
        pokeMon[pos].push_back(temp);
    }
}

/*
 Description: Checks to see if a Pokemon already exists
 PRE: mon and pos is initialized
 POST: returns false if not and true+pos if yes
 */

bool ImportPoke::inList(Pokemon mon, int &pos) {
    if (pokeMon.empty()) {
        return false;
    }
    for (int a=0; a<pokeMon.size(); a++) {
        if (pokeMon[a][0].name == mon.name) {
            pos = a;
            return true;
        }
    }
    return false;
}

/*
 Description: Returns/Exports all pokemon in pokeMon
 PRE: pokeStops is initialized and not empty
 POST: returns pokeMon
 */

vector < vector <Pokemon> > ImportPoke::get() {
    return pokeMon;
}

/*
Description: Returns/Exports all stops in pokeStop
PRE: pokeStops is initialized and not empty
POST: returns pokeStop
*/

vector<Pokemon> ImportPoke::getStops() {
    return pokeStop;
}

/*
 Description: Prints all the stops, for debugging
 PRE: pokeMon is initialized and not empty
 POST: prints all stop numbers and pokemon in pokeList
 */

void ImportPoke::printStops(){
    cout << "stops:\n";
    for (int a=0; a<pokeMon.size(); a++) {
        cout << pokeMon[a][0].name << ": ";
        for (int b=0; b<pokeMon[a].size(); b++) {
            cout << pokeMon[a][b].stop << " @(" << pokeMon[a][b].xPos << "," << pokeMon[a][b].yPos << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

/* START POKEGO CLASS */

/*
 Description: Constructor, creates combinations and permutations from all imported Pokemon 
              then finds the shortest path to catch them all
 PRE: import and stops are initialized and not empty
 POST: mix is complete
 */

PokeGo::PokeGo(vector< vector <Pokemon> > import, vector<Pokemon> stops) {
    vector<int> blank;
    recurse(import, blank, import.size()-1);
    
    for (int a=0; a<mix.size(); a++) {
        mix[a].push_back(permute(stops, mix[a]));
    }
    
    int shortest=0, dist = INT_MAX;
    
    for (int a=0; a<mix.size(); a++) {
        if (mix[a].back() < dist) {
            shortest = a;
            dist = mix[a].back();
        }
    }
    
    //cout << "shortest:\n";
    for (int a=0; a<mix[shortest].size(); a++) {
        cout << mix[shortest][a] << " ";
    }
    cout << endl;
}

/*
 Description: Recursive call to find all combinations
 PRE: pokeStop, pass, and pos are initialized
 POST: recursive call or the completed vector is pushed back
 */

void PokeGo::recurse(const vector< vector<Pokemon> > &pokeStop, vector <int> pass, int pos){
    if (pos<0) {
        reverse(pass.begin(), pass.end()); //revered because traversal is in reverse
        mix.push_back(pass);
    } else {
        for (int a=0; a<pokeStop[pos].size(); a++) {
            pass.push_back(pokeStop[pos][a].stop);
            recurse(pokeStop, pass, pos-1);
            pass.pop_back();
        }
    }
}

/*
 Description: Calculated distance between two pokemon
 PRE: mon1 and mon2 are initialized
 POST: mon2x-mon1x+mon2y+mon1y
 */

int PokeGo::dist(Pokemon mon1, Pokemon mon2) {
    //cout << mon1.xPos << "->" << mon2.xPos << " - " << mon1.yPos << "->" << mon2.yPos;
    return (abs(mon2.xPos-mon1.xPos) + abs(mon2.yPos - mon1.yPos));
}

/*
 Description: Uses next_permutation to finad all permutations
 PRE: stops and input are initialized
 POST: input is passed back as the shortet path and the total distace is returned as an int
 */

int PokeGo::permute(const vector<Pokemon> &stops, vector<int> &input) {
    int shortest = INT_MAX;
    vector<int> temp = {};
    struct Pokemon zero;
    zero.xPos = 0;
    zero.yPos = 0;
    
    sort(input.begin(), input.end());
    do {
        int dis=0;
        dis += dist(zero, stops[input[0]-1]);
        for (int a=0; a<input.size()-1; a++) {
            //cout << input[a] << " to " << input[a+1] << " [";
            dis += dist(stops[input[a]-1], stops[input[a+1]-1]);
            //cout << "]\n";
        }
        dis += dist(stops[input[input.size()-1]-1], zero);
        //cout << endl << "dist: " << dis << endl << endl;
        if (dis < shortest) {
            shortest = dis;
            temp = input;
        }

    } while (next_permutation(input.begin(), input.end()));
    input = temp;
    return shortest;
}

/*
 Description: Prints all of mix
 PRE: mix is initialized and not empty
 POST: all of mix is printed
 */

void PokeGo::print(){
    for (int a=0; a<mix.size(); a++) {
        for (int b=0; b<mix[a].size(); b++) {
            cout << mix[a][b] << " ";
        }
        cout << endl;
    }
}
