
#include <iostream>
#include <string>
using namespace std;

// Node class representing a song
class Node {
public:
    string songTitle;
    string artistName;
    Node* prev;
    Node* next;

    Node(string title, string artist) {
        songTitle = title;
        artistName = artist;
        prev = nullptr;
        next = nullptr;
    }
};

// Music Playlist Manager
class MusicPlaylist {
private:
    Node* head;       // First song
    Node* current;    // Currently selected song

public:
    MusicPlaylist() {
        head = nullptr;
        current = nullptr;
    }

    // Add song at the end
    void addSong(string title, string artist) {
        Node* p = new Node(title, artist);

        if (head == nullptr) {
            head = p;
            current = p;
        } else {
            Node* q = head;
            while (q->next != nullptr)
                q = q->next;

            q->next = p;
            p->prev = q;
        }

        cout << "Song added successfully!\n";
    }

    // Delete song by title
    void deleteSong(string title) {
        Node* q = head;

        while (q != nullptr && q->songTitle != title)
            q = q->next;

        if (q == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        Node* p = q;

        if (p == head)
            head = p->next;

        if (p->prev != nullptr)
            p->prev->next = p->next;

        if (p->next != nullptr)
            p->next->prev = p->prev;

        if (current == p) {
            if (p->next != nullptr)
                current = p->next;
            else
                current = p->prev;
        }

        delete p;
        cout << "Song deleted successfully!\n";
    }

    // Display playlist forward
    void displayPlaylist() {
        Node* q = head;

        if (q == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "\n--- PLAYLIST ---\n";
        while (q != nullptr) {
            cout << q->songTitle << " - " << q->artistName;
            if (q == current)
                cout << " <-- CURRENT";
            cout << '\n';
            q = q->next;
        }
    }

    // Display playlist backward
    void displayReverse() {
        Node* q = head;

        if (q == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        while (q->next != nullptr)
            q = q->next;

        cout << "\n--- REVERSE PLAYLIST ---\n";
        while (q != nullptr) {
            cout << q->songTitle << " - " << q->artistName;
            if (q == current)
                cout << " <-- CURRENT";
            cout << '\n';
            q = q->prev;
        }
    }

    // Play current song
    void playCurrentSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "Now Playing: " << current->songTitle
             << " - " << current->artistName << '\n';
    }

    // Play next song
    void playNextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
        } else if (current->next == nullptr) {
            cout << "Already at the last song!\n";
        } else {
            current = current->next;
            playCurrentSong();
        }
    }

    // Play previous song
    void playPreviousSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
        } else if (current->prev == nullptr) {
            cout << "Already at the first song!\n";
        } else {
            current = current->prev;
            playCurrentSong();
        }
    }

    // Play complete playlist
    void playCompletePlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Node* q = head;
        while (q != nullptr) {
            current = q;
            playCurrentSong();
            q = q->next;
        }
    }

    // Repeat complete playlist
    void repeatAll() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        int repetitions;
        cout << "Enter number of repetitions: ";

        if (!(cin >> repetitions)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            return;
        }

        if (repetitions <= 0) {
            cout << "Enter a positive number!\n";
            return;
        }

        for (int i = 1; i <= repetitions; i++) {
            cout << "\nRepetition " << i << ":\n";
            Node* q = head;

            while (q != nullptr) {
                current = q;
                playCurrentSong();
                q = q->next;
            }
        }
    }

    // Show current song
    void showCurrentSong() {
        if (current == nullptr)
            cout << "No current song.\n";
        else
            playCurrentSong();
    }

    // Free allocated memory
    ~MusicPlaylist() {
        Node* q = head;

        while (q != nullptr) {
            Node* p = q;
            q = q->next;
            delete p;
        }
    }
};

// Display menu
void displayMenu() {
    cout << "\n===== MUSIC PLAYLIST MANAGER =====\n"
         << "1. Add Song\n"
         << "2. Delete Song\n"
         << "3. Display Playlist\n"
         << "4. Display Playlist in Reverse\n"
         << "5. Play Current Song\n"
         << "6. Play Next Song\n"
         << "7. Play Previous Song\n"
         << "8. Play Complete Playlist\n"
         << "9. Repeat All\n"
         << "10. Show Current Song\n"
         << "11. Exit\n"
         << "Enter your choice: ";
}

int main() {
    MusicPlaylist playlist;
    int choice;
    string title, artist;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid menu number.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {
        case 1:
            cout << "Enter Song Title: ";
            getline(cin, title);
            cout << "Enter Artist Name: ";
            getline(cin, artist);
            playlist.addSong(title, artist);
            break;

        case 2:
            cout << "Enter Song Title to Delete: ";
            getline(cin, title);
            playlist.deleteSong(title);
            break;

        case 3:
            playlist.displayPlaylist();
            break;

        case 4:
            playlist.displayReverse();
            break;

        case 5:
            playlist.playCurrentSong();
            break;

        case 6:
            playlist.playNextSong();
            break;

        case 7:
            playlist.playPreviousSong();
            break;

        case 8:
            playlist.playCompletePlaylist();
            break;

        case 9:
            playlist.repeatAll();
            break;

        case 10:
            playlist.showCurrentSong();
            break;

        case 11:
            cout << "Exiting Music Playlist Manager. Thank you!\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 11);

    return 0;
}




//OUTPUT
PS C:\MusicPlaylistManager>                                            .\playlist.exe

========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 1

Enter Song Title: Faded
Enter Artist Name: Alan Walker

Song added successfully!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 3

========== PLAYLIST ==========
1. Faded - Alan Walker <-- CURRENT
==============================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 1

Enter Song Title: Believer
Enter Artist Name: Imagine Dragons

Song added successfully!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 3

========== PLAYLIST ==========
1. Faded - Alan Walker <-- CURRENT
2. Believer - Imagine Dragons
==============================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 6

Next Song: Believer - Imagine Dragons


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 7

Previous Song: Faded - Alan Walker


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 4

====== REVERSE PLAYLIST ======
1. Believer - Imagine Dragons
2. Faded - Alan Walker <-- CURRENT
==============================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 2

Enter Song Title to Delete: 3

Song not found!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 10

Current Song: Faded - Alan Walker


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 5

Now Playing: Faded - Alan Walker


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 6

Next Song: Believer - Imagine Dragons


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 7

Previous Song: Faded - Alan Walker


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 1

Enter Song Title: Perfect
Enter Artist Name: Ed Sheeran

Song added successfully!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 3

========== PLAYLIST ==========
1. Faded - Alan Walker <-- CURRENT
2. Believer - Imagine Dragons
3. Perfect - Ed Sheeran
==============================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 8

====== PLAYING COMPLETE PLAYLIST ======
Playing: Faded - Alan Walker
Playing: Believer - Imagine Dragons
Playing: Perfect - Ed Sheeran
=======================================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 9

Enter number of repetitions: 2

Repetition 1:
Playing: Faded - Alan Walker
Playing: Believer - Imagine Dragons
Playing: Perfect - Ed Sheeran

Repetition 2:
Playing: Faded - Alan Walker
Playing: Believer - Imagine Dragons
Playing: Perfect - Ed Sheeran


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 2

Enter Song Title to Delete: Faded

Song deleted successfully!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 3

========== PLAYLIST ==========
1. Believer - Imagine Dragons
2. Perfect - Ed Sheeran <-- CURRENT
==============================


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 2

Enter Song Title to Delete: Perfect

Song deleted successfully!


========================================
       MUSIC PLAYLIST MANAGER
========================================
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
========================================
Enter your choice: 3

========== PLAYLIST ==========
1. Believer - Imagine Dragons <-- CURRENT
==============================


=============================