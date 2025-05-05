// Програма відтворює простий логер для відпрацювання патернів проектування.

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <cctype>
#include <algorithm>
#include <map>

struct LogSink
{
    virtual void write(const std::string& msg) = 0;
    virtual ~LogSink() = default;
};

struct ConsoleSink: public LogSink
{
    void write(const std::string& msg) override
    {
        if(msg.empty())
        {
            std::cerr << "ERROR: Your message is empty!" << std::endl;
            return;
        }

        std::cout << msg << std::endl;
    }
};

struct FileSink: public LogSink
{
    const std::string file_name = "app.log";
    bool file_exists()
    {
        return std::ifstream(file_name).good();
    }

    void write(const std::string& msg) override
    {
        if(msg.empty())
        {
            std::cerr << "ERROR: Your message is empty!" << std::endl;
            return;
        }

        if(file_exists())
        {
            std::fstream log_file;
            log_file.open(file_name, std::ios::app);
            log_file << msg << std::endl;
            log_file.close();
            std::cout << "NOTE: \"app.log\" was succesfully updated" << std::endl;
        }
        else
        {
            std::ofstream log_file(file_name);
            log_file << msg << std::endl;
            log_file.close();
            std::cout << "NOTE: \"app.log\" was succesfully created" << std::endl;
        }
    }
};

struct NullSink: public LogSink
{
    void write(const std::string& msg) override {};
};

enum class SinkType { CONSOLE, FILE, NONE };

class Logger
{
public:
    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }

    void set_sink(SinkType type)
    {
        switch(type)
        {
            case SinkType::CONSOLE:
                sink_.reset(new ConsoleSink());
                break;
            case SinkType::FILE:
                sink_.reset(new FileSink());
                break;
            case SinkType::NONE:
                sink_.reset(new NullSink());
                break;
            default:
                sink_.reset(new NullSink());
        }
    }

    void log(const std::string& msg)
    {
        sink_->write(msg);
    }

private:
    std::unique_ptr<LogSink> sink_;
    Logger() = default; // заборонити стороннє створення обєкту
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete; // заборонити копіювання/присвоєння
};



int main(int argc, char** argv)
{
    std::string type;

    if(argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            type = argv[i];
            std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        }
    }

    std::string message = "ping!";
    auto& logger = Logger::instance();

    // Мапа для пошуку відповідності аргументу від користувача зі списком типів.
    std::map<std::string, SinkType> mp;
    mp["CONSOLE"] = SinkType::CONSOLE;
    mp["FILE"] = SinkType::FILE;
    mp["NONE"] = SinkType::NONE;
    std::map<std::string, SinkType>::iterator it;
    it = mp.find(type);

    // Пошук по мапі типів
    switch(it->second)
    {
        case SinkType::CONSOLE:
            logger.set_sink(SinkType::CONSOLE);
            break;
        case SinkType::FILE:
            logger.set_sink(SinkType::FILE);
            break;
        case SinkType::NONE:
            logger.set_sink(SinkType::NONE);
            std::cout << "NOTE: SinkType is set to NONE." << std::endl;
            break;
        default:
            std::cout << "WARNING: No argument provided or your argument is invalid!\n"
                      << "\tSetting SinkType to CONSOLE." << std::endl;
            logger.set_sink(SinkType::CONSOLE);
    }

    logger.log(message);

    // Визначені домашкою перевірки.
    std::cout << "\n\nFollowing examples are predifined in code:\n";
    Logger::instance().set_sink(SinkType::FILE);
    Logger::instance().log("Test message... This message goes to the \"app.log\" file.\n");
    Logger::instance().set_sink(SinkType::NONE);
    Logger::instance().log("nothing will happen");
    Logger::instance().set_sink(SinkType::CONSOLE);
    Logger::instance().log("Test message... Goes to the console.\n");

    return 0;
}