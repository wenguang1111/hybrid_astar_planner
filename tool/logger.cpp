#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class BaseMap {
public:
  virtual ~BaseMap() {}
};

template <typename T> class TypedMap : public BaseMap {
public:
  std::map<std::string, std::vector<T>> data;
};

class Logger {
public:
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  static Logger *getInstance() {
    if (!log) {
      log = new Logger();
    }
    return log;
  }

  template <typename T> void saveData(std::string variable, T value) {
    BaseMap *base = nullptr;

    if (std::is_same<T, int>::value) {
      base = &map_i;
    } else if (std::is_same<T, float>::value) {
      base = &map_f;
    } else if (std::is_same<T, double>::value) {
      base = &map_d;
    } else {
      std::cout << "logger.cpp: undefined datatype" << std::endl;
    }

    typename std::map<std::string, std::vector<T>>::iterator it =
        static_cast<TypedMap<T> *>(base)->data.find(variable);

    if (it != static_cast<TypedMap<T> *>(base)->data.end())
      it->second.push_back(value);
    else
      static_cast<TypedMap<T> *>(base)->data.insert(
          std::pair<std::string, std::vector<T>>(variable,
                                                 std::vector<T>{value}));
  }

  template <typename T> std::string getData(std::string variable, int n) {
    std::string ans = "";
    BaseMap *base = nullptr;

    if (std::is_same<T, int>::value) {
      base = &map_i;
    } else if (std::is_same<T, float>::value) {
      base = &map_f;
    } else if (std::is_same<T, double>::value) {
      base = &map_d;
    } else {
      std::cout << "logger.cpp: undefined datatype" << std::endl;
    }

    typename std::map<std::string, std::vector<T>>::iterator it =
        static_cast<TypedMap<T> *>(base)->data.find(variable);
    if (it != static_cast<TypedMap<T> *>(base)->data.end()) {
      if (it->second.size() > n)
        ans = std::to_string(it->second.at(n));
      else
        std::cout << "[ERROR] [logger.cpp] out of range" << std::endl;
    }

    return ans;
  }

  // cant write data to csv, why?
  void writeDataToCSV() {
    writeValue<int>("variable_integer.csv", map_i);
    writeValue<float>("variable_float.csv", map_f);
    writeValue<double>("variable_double.csv", map_d);
  }

private:
  Logger() = default;
  static Logger *log;
  TypedMap<int> map_i;
  TypedMap<float> map_f;
  TypedMap<double> map_d;

  template <typename T>
  void writeValue(std::string filename, TypedMap<T> &typedMap) {
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::trunc);

    for (const auto &entry : typedMap.data) {
      file << entry.first << ",";
    }
    file << std::endl;

    size_t maxSize = 0; // Find the maximum size of vectors
    for (const auto &entry : typedMap.data) {
      maxSize = std::max(maxSize, entry.second.size());
    }

    for (size_t i = 0; i < maxSize; ++i) {
      for (const auto &entry : typedMap.data) {
        if (i < entry.second.size()) {
          file << entry.second[i];
        }
        file << ",";
      }
      file << std::endl;
    }
  }
};

Logger *Logger::log = nullptr;

int main() {
  Logger *myLogger = Logger::getInstance();

  for (int i = 0; i < 50; i++) {
    myLogger->saveData<int>("variable_integer", i * 10);
  }
  for (int i = 0; i < 50; i++) {
    myLogger->saveData<double>("variable_double", i * 10.1);
  }

  myLogger->writeDataToCSV();
}