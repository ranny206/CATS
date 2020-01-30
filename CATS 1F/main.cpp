#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>

using namespace std;

class PackageStream {
 public:
  PackageStream(std::string data, int32_t package_len) : package_len_(package_len), data_(data) {}

  int32_t PackageLen() const {
    return package_len_;
  }

  int32_t ReadPackage(char *buf) {
    int32_t next_pos = min<int32_t>(data_.size(), pos_ + PackageLen());
    int32_t len = next_pos - pos_;

    memcpy(buf, data_.c_str() + pos_, len);
    pos_ = next_pos;
    return len;
  }

 private:
  const int32_t package_len_;
  int32_t pos_ = 0;

  std::string data_;
};

class BufferedReader {
 public:
  explicit BufferedReader(PackageStream *stream) {
    tmp_buf = new char[stream->PackageLen()];
    reader = stream;
    next_pos = stream->PackageLen();
  }

  ~BufferedReader() {
    delete[] tmp_buf;
  }

  int32_t Read(char *output_buffer, int32_t buffer_len) {
    int32_t my_how_many = 0;
    int32_t minimum;
    while (my_how_many != buffer_len) {
      if (next_pos == reader->PackageLen()) {
        how_many = reader->ReadPackage(tmp_buf);
        next_pos = 0;
      }

      minimum = min<int32_t>(buffer_len - my_how_many, how_many - next_pos);
      memcpy(output_buffer + my_how_many, tmp_buf + next_pos, minimum);
      my_how_many += minimum;
      next_pos += minimum;
      if (how_many < reader->PackageLen()) {
        break;
      }
    }
    return my_how_many;
  }

 private:
  char *tmp_buf;
  int next_pos;
  int32_t how_many = 0;
  PackageStream *reader;
};

int main() {
  int32_t package_len = 0;
  int32_t read_len = 0;
  int32_t expect_len = 0;
  int ok = true;
  int cur_byte = 0;

  cin >> package_len;
  string s;
  getline(cin, s);
  getline(cin, s);
  PackageStream stream(s, package_len);
  BufferedReader reader(&stream);

  while (cin >> read_len >> expect_len) {
    std::unique_ptr<char[]> buf(new char[read_len]);

    int got_len = reader.Read(buf.get(), read_len);
    if (got_len != expect_len || memcmp(buf.get(), s.c_str() + cur_byte, expect_len) != 0) {
      ok = false;
      break;
    }

    cur_byte += read_len;
  }

  cout << (int) ok << endl;
}