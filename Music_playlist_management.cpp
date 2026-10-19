
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Song {
public:
    int id;
    string title;
    string artist;
    string duration;
    Song* next;
    Song* prev;

    Song(int i, string t, string a, string d) {
        id = i;
        title = t;
        artist = a;
        duration = d;
        next = nullptr;
        prev = nullptr;
    }
};

class MusicPlaylist {
private:
    Song* head;
    Song* tail;
    Song* current;

    Song* findSong(int id) {
        Song* temp = head;

        while (temp != nullptr) {
            if (temp->id == id)
                return temp;

            temp = temp->next;
        }

        return nullptr;
    }

public:
    MusicPlaylist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // 1. Add song
    void addSong() {
        int id;
        string title, artist, duration;

        cout << "\nEnter Song ID: ";
        cin >> id;

        if (findSong(id) != nullptr) {
            cout << "Song ID already exists!\n";
            return;
        }

        cout << "Enter Song Title: ";
        getline(cin >> ws, title);

        cout << "Enter Artist Name: ";
        getline(cin >> ws, artist);

        cout << "Enter Duration (e.g. 3:45): ";
        getline(cin >> ws, duration);

        Song* newSong = new Song(
            id, title, artist, duration
        );

        if (head == nullptr) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        cout << "Song added to playlist successfully!\n";
    }

    // 2. Display playlist
    void displayPlaylist() {
        if (head == nullptr) {
            cout << "\nPlaylist is empty!\n";
            return;
        }

        Song* temp = head;

        cout << "\n========== MUSIC PLAYLIST ==========\n";

        while (temp != nullptr) {
            cout << "\nSong ID  : " << temp->id;
            cout << "\nTitle    : " << temp->title;
            cout << "\nArtist   : " << temp->artist;
            cout << "\nDuration : " << temp->duration;

            if (temp == current)
                cout << "\nStatus   : Current Song";

            cout << "\n------------------------------------\n";

            temp = temp->next;
        }
    }

    // 3. Search song
    void searchSong() {
        int id;

        cout << "\nEnter Song ID to search: ";
        cin >> id;

        Song* song = findSong(id);

        if (song == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        cout << "\nSong Found!\n";
        cout << "ID       : " << song->id << '\n';
        cout << "Title    : " << song->title << '\n';
        cout << "Artist   : " << song->artist << '\n';
        cout << "Duration : " << song->duration << '\n';
    }

    // 4. Play current song
    void playSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "\nNow Playing:\n";
        cout << current->title
             << " - " << current->artist << '\n';
        cout << "Duration: " << current->duration << '\n';
    }

    // 5. Play next song
    void nextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        if (current->next != nullptr) {
            current = current->next;
            playSong();
        } else {
            cout << "This is the last song!\n";
        }
    }

    // 6. Play previous song
    void previousSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        if (current->prev != nullptr) {
            current = current->prev;
            playSong();
        } else {
            cout << "This is the first song!\n";
        }
    }

    // 7. Delete a song
    void deleteSong() {
        int id;

        cout << "\nEnter Song ID to delete: ";
        cin >> id;

        Song* song = findSong(id);

        if (song == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        // Move current song if it is being deleted
        if (song == current) {
            if (song->next != nullptr)
                current = song->next;
            else
                current = song->prev;
        }

        if (song->prev != nullptr)
            song->prev->next = song->next;
        else
            head = song->next;

        if (song->next != nullptr)
            song->next->prev = song->prev;
        else
            tail = song->prev;

        delete song;

        cout << "Song deleted successfully!\n";
    }

    // 8. Sort songs alphabetically by title
    void sortPlaylist() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough songs to sort.\n";
            return;
        }

        bool swapped;

        do {
            swapped = false;
            Song* temp = head;

            while (temp != nullptr && temp->next != nullptr) {
                Song* nextSong = temp->next;

                if (temp->title > nextSong->title) {
                    // Swap song data, not node pointers
                    swap(temp->id, nextSong->id);
                    swap(temp->title, nextSong->title);
                    swap(temp->artist, nextSong->artist);
                    swap(temp->duration, nextSong->duration);

                    swapped = true;
                }

                temp = temp->next;
            }
        } while (swapped);

        cout << "Playlist sorted alphabetically!\n";
    }

    // 9. Show total songs
    void countSongs() {
        int count = 0;
        Song* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        cout << "\nTotal songs in playlist: "
             << count << '\n';
    }

    // Free memory
    ~MusicPlaylist() {
        Song* temp = head;

        while (temp != nullptr) {
            Song* nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }
    }
};

int main() {
    MusicPlaylist playlist;
    int choice;

    do {
        cout << "\n\n================================";
        cout << "\n   MUSIC PLAYLIST MANAGEMENT";
        cout << "\n================================";
        cout << "\n1. Add Song";
        cout << "\n2. Display Playlist";
        cout << "\n3. Search Song";
        cout << "\n4. Play Current Song";
        cout << "\n5. Next Song";
        cout << "\n6. Previous Song";
        cout << "\n7. Delete Song";
        cout << "\n8. Sort Playlist by Title";
        cout << "\n9. Count Songs";
        cout << "\n0. Exit";
        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            continue;
        }

        switch (choice) {
            case 1:
                playlist.addSong();
                break;

            case 2:
                playlist.displayPlaylist();
                break;

            case 3:
                playlist.searchSong();
                break;

            case 4:
                playlist.playSong();
                break;

            case 5:
                playlist.nextSong();
                break;

            case 6:
                playlist.previousSong();
                break;

            case 7:
                playlist.deleteSong();
                break;

            case 8:
                playlist.sortPlaylist();
                break;

            case 9:
                playlist.countSongs();
                break;

            case 0:
                cout << "Thank you for using Music Playlist!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
