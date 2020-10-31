#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#ifndef CSV_LOGGER_
#define CSV_LOGGER_
// csv logger class
class CsvLogger {
 public:
  CsvLogger(){};
  ~CsvLogger(){};

  // title expected a variable name.
  // if you can use below MACRO in your code,
  // you can call this method with only addItem(variable).
  // #define addItem(a) addItem(a, #a)
  template <typename T>
  void addItem(T item, std::string title) {
    // convert item to string
    std::stringstream ss;

    // avoid to regard short type as char
    if (typeid(T) == typeid(unsigned char)) {
      ss << static_cast<uint16_t>(item);
    } else if (typeid(T) == typeid(signed char)) {
      ss << static_cast<int16_t>(item);
    } else {
      ss << item;
    }
    data_line.push_back(ss.str());
    title_line.push_back(title);
  }

  void writeLog(std::string outpath) {
    bool file_exist = checkFileExist(outpath);
    // open csv file
    std::ofstream writing_file;
    writing_file.open(outpath, std::ios::app);

    if (!file_exist) {
      // title output
      for (size_t i = 0; i < title_line.size(); ++i) {
        if (i == title_line.size() - 1) {
          writing_file << title_line.at(i) << std::endl;
        } else {
          writing_file << title_line.at(i) << ",";
        }
      }
    }

    // item output
    for (size_t i = 0; i < data_line.size(); ++i) {
      if (i == data_line.size() - 1) {
        writing_file << data_line.at(i) << std::endl;
      } else {
        writing_file << data_line.at(i) << ",";
      }
    }

    writing_file.close();
  }

 private:
  std::vector<std::string> data_line;
  std::vector<std::string> title_line;

  bool checkFileExist(const std::string &outpath) {
    std::ifstream ifs(outpath);
    return ifs.is_open();
  }
};

#endif  // CSV_LOGGER_