#include "files.hh"
// #include <filesystem>
// namespace fs = std::filesystem;
// #include <apr_file_info.h>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
using std::vector, std::string;

namespace fs = boost::filesystem;
vector<SongInfo> Files::files(const string &p) {
  vector<SongInfo> res;
  for (auto &f : fs::directory_iterator("json")) {
    // std::cout << fs::absolute(f.path()) << std::endl;
    // std::cout << "type: " << fs::extension(f) << std::endl;
    auto json = fs::absolute(f).string();
    auto mp3path =
        fs::path("mp3") / f.path().filename().replace_extension(".mp3");
    // res.push_back(fs::absolute(mp3path).string());
    res.push_back(SongInfo{json, fs::absolute(mp3path).string()});
  }
  //   for (auto &f : fs::directory_iterator("mp3")) {
  //     // std::cout << fs::absolute(f.path()) << std::endl;
  //     // std::cout << "type: " << fs::extension(f) << std::endl;
  //     res.push_back(fs::absolute(f).string());
  //   }
  return res;
  //   apr_pool_t *pool;
  //   apr_dir_t *dir;
  //   apr_pool_initialize();
  //   apr_pool_create(&pool, nullptr);
  //   apr_dir_open(&dir, "./json", pool);

  //   apr_finfo_t info;
  //   // apr_file
  //   while (apr_dir_read(&info,
  //                       APR_FINFO_DIRENT | APR_FINFO_ICASE | APR_FINFO_INODE,
  //                       dir) != APR_ENOENT) {
  //     //   apr_filepath_get()
  //     std::cout << info.inode << std::endl;
  //   }

  //   apr_pool_destroy(pool);
}