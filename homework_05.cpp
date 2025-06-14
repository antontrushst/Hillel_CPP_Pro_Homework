#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <functional>
#include <map>
#include <list>

struct INumberReader
{
    virtual ~INumberReader() = default;
    virtual std::vector<int> read(const std::string& file_name) = 0;
};

struct NumberReader: public INumberReader
{
    std::vector<int> numbers;
    bool is_integer(std::string& input_str) const
    {
        for(int i = 0; i < input_str.size(); i++)
            if(input_str[i] == '-' && i != 0 ||                 // checking if a character is not minus at the beginning
               input_str[i] < '0' && input_str[i] != '-' ||     // checking if a character is not ASCII zero or greater or minus
               input_str[i] > '9' && input_str[i] != '-')       // checking if a character is not ASCII nine or lesser or minus
                return false;

        return true;
    }

    std::vector<int> read(const std::string& file_name) override
    {
        std::ifstream input_file(file_name);

        if(!input_file.is_open())
        {
            std::cerr << "ERROR: Couldn't open file!" << std::endl;
            return this->numbers;
        }

        std::string temp;
        while(input_file >> temp)
        {
            if(is_integer(temp))
            {
                numbers.push_back(std::stoi(temp));
            }
        }
        return this->numbers;
    }

};

struct INumberFilter
{
    virtual ~INumberFilter() = default;
    virtual bool keep(int) const = 0;
};

struct OddFilter: public INumberFilter
{
    bool keep(int number) const override
    {
        return number % 2;
    }
};

struct EvenFilter: public INumberFilter
{
    bool keep(int number) const override
    {
        return !(number % 2);
    }
};

struct GreaterThanFilter: public INumberFilter
{
    int reference_number;
    GreaterThanFilter(int ref_number) : reference_number(ref_number) {}

    // MOVE TO FACTORY!!!
    // Constructor that parses argv command argument
    GreaterThanFilter(char* argv)
    {
        std::string ref_num = argv;
        ref_num.erase(ref_num.begin(), ref_num.begin()+2);
        reference_number = std::stoi(ref_num);
    }

    bool keep(int number) const override
    {
        return number > reference_number;
    }
};

class FilterFactory
{
    using Factory = std::function<std::unique_ptr<INumberFilter>(char*)>;
    std::map<std::string, Factory> filter_registry;

    FilterFactory() = default;
    FilterFactory(const FilterFactory& other) = delete;
    FilterFactory& operator=(FilterFactory& other) = delete;

public:
    static FilterFactory& instance()
    {
        static FilterFactory registry;
        return registry;
    }

    void register_filter(const std::string& filter_type, Factory f)
    {
        this->filter_registry[filter_type] = f;
    }

    std::unique_ptr<INumberFilter> create(const std::string& filter_type, char* is)
    {
        return this->filter_registry[filter_type](is);
    }
};

struct INumberObserver
{
    virtual ~INumberObserver() = default;
    virtual void on_number(int) = 0;
    virtual void on_finished() = 0;
};

struct PrintObserver: public INumberObserver
{
    void on_number(int number) override
    {
        std::cout << number << std::endl;
    }

    void on_finished() override
    {
        std::cout << "=====\tEncountered the last number.\t=====\n";
    }
};

struct CountObserver: public INumberObserver
{
    int counter = 0;

    void on_number(int number) override
    {
        counter++;
    }

    void on_finished() override
    {
        std::cout << "Counted " << counter << " numbers in provided file.\n";
    }
};

struct NumberProcessor
{
    INumberReader& m_reader;
    INumberFilter& m_filter;
    std::vector<INumberObserver>& m_observers;

    NumberProcessor(INumberReader& reader, INumberFilter& filter, std::vector<INumberObserver>& observers)
        : m_reader(reader), m_filter(filter), m_observers(observers) {}
    ~NumberProcessor() = default;

    void run()
    {

    }
};

int main(int argc, char** argv)
{
    // Throw a note on program usage if the required arguments haven't been provided, and close the program.
    // if(argc != 3)
    // {
    //     std::cerr << "Usage: " << argv[0] << " <filter>" << " <file_name>\n"
    //               << "where\n\t<filter> - name of a filter (ODD, EVEN, GT<n>);\n"
    //               << "\t<file_name> - name of the text file with numbers;";
    //     return -1;
    // }

    FilterFactory& filter_factory = FilterFactory::instance();
    filter_factory.register_filter("ODD", [](char* is)
    {
        return std::make_unique<OddFilter>();
    });
    filter_factory.register_filter("EVEN", [](char* is)
    {
        return std::make_unique<EvenFilter>();
    });
    filter_factory.register_filter("GT5", [argv](char* is)
    {
        return std::make_unique<GreaterThanFilter>(is);
    });
    
    NumberReader number_reader;

    std::vector<int> nums = number_reader.read(argv[2]);

    for(auto& n : nums)
        std::cout << n << std::endl;

    std::cout << std::endl;
    auto filter = filter_factory.create(argv[1], argv[1]);

    for(auto& n : nums)
        std::cout << filter->keep(n) << std::endl;
    
    return 0;
}