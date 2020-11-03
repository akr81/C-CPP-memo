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
    if ((typeid(T) == typeid(unsigned char)) || (typeid(T) == typeid(signed char))) {
      ss << static_cast<uint16_t>(item);
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
      combineItems(title_line, line);
      writing_file << line << std::endl;
    }

    // item output
    combineItems(data_line, line);
    writing_file << line << std::endl;

    writing_file.close();
  }

 private:
  std::vector<std::string> data_line;
  std::vector<std::string> title_line;
  std::string line;

  bool checkFileExist(const std::string &outpath) {
    std::ifstream ifs(outpath);
    return ifs.is_open();
  }

  void combineItems(std::vector<std::string> lines, std::string &line) {
    // initialize
    line = "";
    for (size_t i = 0; i < lines.size(); ++i) {
      if (i == lines.size() - 1) {
        line = line + lines.at(i);
      } else {
        line = line + lines.at(i) + ",";
      }
    }
  }
};

#endif  // CSV_LOGGER_