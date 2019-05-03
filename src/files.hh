#if !defined(FILES_HH)
#define FILES_HH
#include "song_info.hh"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::vector, std::string;

class Files {

public:
  vector<SongInfo> files(const string &p);
};

#endif // FILES_HH
