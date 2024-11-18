#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:" << endl << endl;
  getline(cin,title);
  Playlist P;
  string command;
  while(command != "q") {
    P.PrintMenu(title);
    cin>> command;
    if (command == "a") {
      string songID;
      string songName;
      string artistName;
      int songLength;
      cout << endl << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> songID;
      cin.ignore();
     cout << "Enter song's name:" << endl;
     getline(cin, songName);
      cout << "Enter artist's name:"<< endl;
      getline(cin, artistName);
      cout << "Enter song's length (in seconds):" << endl << endl;
      cin >> songLength;
      
      P.AddSong(songID,songName,artistName,songLength);
    } if (command == "d") {
      cout << "REMOVE SONG" << endl;
      P.RemoveSong();
    }  if (command == "c") {
      cout << "CHANGE POSITION OF SONG" << endl;
      P.ChangePositionSong();
    }  if (command == "s") {
      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      P.OutputSongsByArtist();
    }  if (command == "t") {
      cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
      P.OutputTotalTime();
    }  if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" ;
      P.OutputFullPlaylist();
    }  
  }
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
