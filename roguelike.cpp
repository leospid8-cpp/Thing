#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> // Per _kbhit() e _getch()
#include <windows.h> // Per SetConsoleCursorPosition

using namespace std;

const int MAP_WIDTH = 40;  // Larghezza della mappa
const int MAP_HEIGHT = 20; // Altezza della mappa
const char WALL = '#';     // Carattere per il muro
const char PATH = '.';     // Carattere per il percorso
const char PLAYER = 'P';   // Carattere per il giocatore
const char GOBLIN = 'G';   // Carattere per il goblin
const char BOSS = 'B';     // Carattere per il boss
const char TREASURE = 'T'; // Carattere per il tesoro
const char HEAL = 'H';     // Carattere per l'oggetto di cura

struct Position {
    int x, y;  // Posizione (x, y)
};

struct Entity {
    Position pos;  // Posizione dell'entità
    int hp;        // Punti vita dell'entità
    int damage;    // Danno inflitto dall'entità
};

// Funzione per generare la mappa del labirinto
void generateMaze(vector<vector<char>>& map) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = (rand() % 4 == 0) ? WALL : PATH;  // Muri generati randomicamente
        }
    }

    // Creiamo un percorso assicurato
    for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
        for (int x = 1; x < MAP_WIDTH - 1; ++x) {
            if (map[y][x] == WALL && rand() % 2 == 0) {
                map[y][x] = PATH;
            }
        }
    }

    map[0][0] = PLAYER;  // Posizione iniziale del giocatore
    map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = TREASURE;  // Posizione del tesoro
}

// Funzione per spawnare i nemici e gli oggetti
void spawnEntities(vector<vector<char>>& map, vector<Entity>& enemies) {
    // Spawna i Goblin
    for (int i = 0; i < 5; ++i) {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;
        if (map[y][x] == PATH) {
            map[y][x] = GOBLIN;
            enemies.push_back({ {x, y}, 3, 1 });
        }
    }

    // Spawna il Boss
    int x = rand() % MAP_WIDTH;
    int y = rand() % MAP_HEIGHT;
    if (map[y][x] == PATH) {
        map[y][x] = BOSS;
        enemies.push_back({ {x, y}, 10, 2 });
    }

    // Spawna Oggetti di Cura
    x = rand() % MAP_WIDTH;
    y = rand() % MAP_HEIGHT;
    if (map[y][x] == PATH) {
        map[y][x] = HEAL;
    }
}

// Funzione per stampare la mappa
void printMap(const vector<vector<char>>& map, const Entity& player) {
    // Imposta la posizione del cursore all'inizio della finestra
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Mostra una porzione più grande della mappa (30 righe e 50 colonne)
    for (int y = max(0, player.pos.y - 15); y <= min(MAP_HEIGHT - 1, player.pos.y + 15); ++y) {
        for (int x = max(0, player.pos.x - 25); x <= min(MAP_WIDTH - 1, player.pos.x + 25); ++x) {
            if (x == player.pos.x && y == player.pos.y) {
                cout << PLAYER;  // Mostra il giocatore nella posizione corretta
            }
            else {
                cout << map[y][x];  // Mostra il contenuto della mappa (pareti, nemici, ecc.)
            }
        }
        cout << '\n';
    }
    cout << "HP: " << player.hp << "\n";  // Mostra i punti vita del giocatore
}

// Funzione per muovere il giocatore
void movePlayer(Entity& player, char input, const vector<vector<char>>& map) {
    Position newPos = player.pos;
    switch (input) {
    case 'w': newPos.y--; break;  // Muovi su
    case 'a': newPos.x--; break;  // Muovi a sinistra
    case 's': newPos.y++; break;  // Muovi giù
    case 'd': newPos.x++; break;  // Muovi a destra
    }

    // Controlla se la nuova posizione è valida (non è un muro)
    if (newPos.x >= 0 && newPos.x < MAP_WIDTH && newPos.y >= 0 && newPos.y < MAP_HEIGHT &&
        map[newPos.y][newPos.x] != WALL) {
        player.pos = newPos;  // Aggiorna la posizione del giocatore
    }
}

// Funzione per gestire il combattimento
void combat(Entity& player, vector<Entity>& enemies) {
    for (auto& enemy : enemies) {
        // Se il giocatore è nella stessa posizione di un nemico
        if (player.pos.x == enemy.pos.x && player.pos.y == enemy.pos.y) {
            player.hp -= enemy.damage;  // Il giocatore subisce danni
            cout << "Hai preso " << enemy.damage << " danni da un " << (enemy.hp == 1 ? "goblin" : "boss") << "!\n";
            // Se la salute del giocatore è zero o sotto, il gioco termina
            if (player.hp <= 0) {
                cout << "Game Over!\n";
                exit(0); // Uscita dal programma, terminando il gioco
            }
        }
    }
}

// Funzione per gestire la cura del giocatore
void heal(Entity& player, vector<vector<char>>& map) {
    if (map[player.pos.y][player.pos.x] == HEAL) {
        player.hp += 5;  // Aumenta i punti vita del giocatore
        cout << "Hai trovato una pozione di cura! HP aumentati di 5.\n";
        map[player.pos.y][player.pos.x] = PATH; // Rimuovi la pozione dopo che è stata presa
    }
}

// Funzione per controllare se il giocatore ha trovato il tesoro
void checkTreasure(Entity& player, const vector<vector<char>>& map) {
    if (map[player.pos.y][player.pos.x] == TREASURE) {
        cout << "Hai trovato il tesoro! Hai vinto!\n";
        exit(0); // Uscita dal programma, terminando il gioco
    }
}

// Funzione per nascondere il cursore
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Funzione per mostrare il cursore
void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main() {
    srand(time(0));  // Inizializza il generatore di numeri casuali
    vector<vector<char>> map(MAP_HEIGHT, vector<char>(MAP_WIDTH, PATH));  // Crea la mappa
    vector<Entity> enemies;  // Lista dei nemici
    Entity player = { {0, 0}, 10, 1 };  // Crea il giocatore con 10 HP e danno 1

    generateMaze(map);  // Genera il labirinto
    spawnEntities(map, enemies);  // Spawn nemici e oggetti

    hideCursor();  // Nasconde il cursore per un'esperienza visiva migliore

    while (true) {
        printMap(map, player);  // Mostra la mappa aggiornata
        combat(player, enemies); // Gestisce il combattimento con i nemici
        heal(player, map);       // Gestisce la cura se il giocatore trova oggetti di cura
        checkTreasure(player, map); // Controlla se il giocatore ha trovato il tesoro

        if (_kbhit()) {
            char input = _getch();  // Ottiene l'input del giocatore
            movePlayer(player, input, map);  // Muove il giocatore in base all'input
        }
    }

    return 0;
}

//created by leospid8