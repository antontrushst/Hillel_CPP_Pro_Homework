#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <functional>
#include <map>
#include <list>
#include <cctype>
#include <algorithm>

struct INumberReader
{
    virtual ~INumberReader() = default;
    virtual std::vector<int> read(const std::string& file_name) = 0;
};

struct NumberReader: public INumberReader
{
    std::vector<int> numbers;

    std::vector<int> read(const std::string& file_name) override
    {
        std::ifstream input_file(file_name);

        if(!input_file.is_open())
        {
            std::cerr << "ERROR: Couldn't open file!" << std::endl;
            exit(1);
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

private:
    bool is_integer(std::string& input_str) const
    {
        for(int i = 0; i < input_str.size(); i++)
            if(!std::isdigit(input_str[i]))
                return false;

        return true;
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

    bool keep(int number) const override
    {
        return number > reference_number;
    }
};

class FilterFactory
{
    using Factory = std::function<std::shared_ptr<INumberFilter>(const std::string&)>;
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

    std::shared_ptr<INumberFilter> create(const std::string& filter_type)
    {
        for(auto& filter : filter_registry)
        {
            if(filter_type.starts_with(filter.first))
                return this->filter_registry[filter.first](filter_type);
        }

        std::cerr << "ERROR: No registered filter for " << filter_type << " !\n";
        exit(1);
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
        std::cout << "Counted " << counter << " numbers.\n";
    }
};

struct NumberProcessor
{
    INumberReader& m_reader;
    std::shared_ptr<INumberFilter>& m_filter;
    std::vector<INumberObserver*>& m_observers;
    std::vector<int> m_numbers;

    NumberProcessor(INumberReader& reader, std::shared_ptr<INumberFilter>& filter, std::vector<INumberObserver*>& observers)
        : m_reader(reader), m_filter(filter), m_observers(observers) {}
    ~NumberProcessor() = default;

    void run(std::string filter, std::string file)
    {
        std::vector<int> unfiltered_numbers = m_reader.read(file);
        for(auto number : unfiltered_numbers)
        {
            if(m_filter->keep(number))
                m_numbers.push_back(number);
        }

        std::cout << "List of filtered numbers:\n";
        for(auto number : m_numbers)
        {
            m_observers[0]->on_number(number);
            m_observers[1]->on_number(number);
        }

        for(auto observer : m_observers)
            observer->on_finished();
    }
};

int main(int argc, char** argv)
{
    // Throw a note on program usage if the required arguments haven't been provided, and close the program.
    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <filter>" << " <file_name>\n"
                  << "where\n\t<filter> - name of a filter (ODD, EVEN, GT<n>);\n"
                  << "\t<file_name> - name of the text file with numbers;";
        return -1;
    }

    FilterFactory& filter_factory = FilterFactory::instance();
    filter_factory.register_filter("ODD", [](const std::string& is)
    {
        return std::make_shared<OddFilter>();
    });
    filter_factory.register_filter("EVEN", [](const std::string& is)
    {
        return std::make_shared<EvenFilter>();
    });
    filter_factory.register_filter("GT", [](const std::string& is)
    {
        std::string ref_number = is.substr(2);
        for(auto& c : ref_number)
        {
            if(!std::isdigit(c))
            {
                std::cerr << "ERROR: GT filter requires a valid number as argument!\n";
                exit(1);
            }
        }
        return std::make_shared<GreaterThanFilter>(std::stoi(ref_number));
    });
    
    auto filter = filter_factory.create(std::string(argv[1]));
    
    auto po = PrintObserver();
    auto co = CountObserver();
    std::vector<INumberObserver*> observers = {&po, &co};
    
    NumberReader number_reader;

    NumberProcessor num_proc(number_reader, filter, observers);
    num_proc.run(argv[1], argv[2]);
    
    return 0;
}