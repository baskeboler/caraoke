#include "song_info.hh"
using std::ostream;
//   friend class ostream;
ostream &SongInfo::operator<<(ostream &os) {
  os << "song(" << json_path << ", " << song_path << ")";
  return os;
}

ostream &operator<<(ostream &os, SongInfo &info) {
  os << "song(" << info.json_path << ", " << info.song_path << ")";
  return os;
}