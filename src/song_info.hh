#if !defined(SONG_INFO_HH)
#define SONG_INFO_HH
#include <ostream>
#include <string>

using std::string, std::ostream;

struct SongInfo {

  string json_path, song_path;

public:
  SongInfo(const string &json, const string &mp3)
      : json_path{json}, song_path{mp3} {}

  //   friend class ostream;
  ostream &operator<<(ostream &os);
};

ostream &operator<<(ostream &os, SongInfo &info);
#endif // SONG_INFO_HH
