#include <fstream>
#include <iostream>
#include <map>
#include <vector>

 class BaseMap {
    public:
        virtual ~BaseMap() {}
    };

template<typename T>
class TypedMap : public BaseMap {
public:
    std::map<std::string, std::vector<T>> data;
};

class Logger
{
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* getInstance(){
        if(!log){
            log = new Logger();
        }
        return log;
    }

    template<typename T>
    void saveData(std::string variable, T value)
    {
        BaseMap* base = nullptr;

        if(std::is_same<T, int>::value)
        {
            base = &data_i;
        }
        else if (std::is_same<T, float>::value)
        {
            base = &data_f;
        }
        else if (std::is_same<T, double>::value)
        {
            base = &data_d;
        }
        else{
            std::cout << "logger.cpp: undefined datatype"<< std::endl;
        }

        typename std::map<std::string, std::vector<T>>::iterator it=
            static_cast<TypedMap<T>*>(base)->data.find(variable);

        if(it != static_cast<TypedMap<T>*>(base)->data.end())
            it->second.push_back(value);
        else       
            static_cast<TypedMap<T>*>(base)->data.insert(
                std::pair<std::string, std::vector<T>>(variable,std::vector<T>{value}));
    }

    template<typename T>
    std::string getData(std::string variable, int n)
    {
        std::string ans="";
        BaseMap* base = nullptr;

        if(std::is_same<T, int>::value)
        {
            base = &data_i;
        }
        else if (std::is_same<T, float>::value)
        {
            base = &data_f;
        }
        else if (std::is_same<T, double>::value)
        {
            base = &data_d;
        }
        else{
            std::cout << "logger.cpp: undefined datatype"<< std::endl;
        }
        
        typename std::map<std::string,std::vector<T>>::iterator it=static_cast<TypedMap<T>*>(base)->data.find(variable);
        if(it != static_cast<TypedMap<T>*>(base)->data.end())
        {
            if(it->second.size()>n)
                ans = std::to_string(it->second.at(n));
            else
                std::cerr << "[ERROR] [logger.cpp] out of range" << std::endl;
        }
            
        return ans;
    }
    
    //cant write data to csv, why? 
    void writeDataToCSV()
   {
    fout.open("variableData.csv", std::ios::out | std::ios::app); 
    fout << "1" << "," << "2" <<"/n";
   }

private:
    Logger() = default;
    static Logger* log;
    std::fstream fout;
    TypedMap<int> data_i;
    TypedMap<float> data_f;
    TypedMap<double> data_d;
};

Logger* Logger::log = nullptr;

int main()
{
    Logger* myLogger=Logger::getInstance();
    // myLogger->writeDataToCSV();
    int i =3;
    double d=1.234;
    float f=2.34;
    myLogger->saveData<int>("variable_1", i);
    myLogger->saveData<double>("v_2", d);
    myLogger->saveData<float>("anyT", f);
    myLogger->saveData<int>("variable_1", 505);

    std::cout << myLogger->getData<int>("variable_1",0)<< std::endl;
    std::cout << myLogger->getData<int>("variable_1",1)<< std::endl;
    std::cout << myLogger->getData<double>("variable_1",2)<< std::endl;
}