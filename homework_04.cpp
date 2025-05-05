#include <iostream>
#include <string>
#include <fstream>
#include <memory>

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
        }
        else
        {
            std::ofstream log_file(file_name);
            log_file << msg << std::endl;
            log_file.close();
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
            case SinkType::CONSOLE: sink_.reset(new ConsoleSink());
            case SinkType::FILE: sink_.reset(new FileSink());
            case SinkType::NONE: sink_.reset(new NullSink());
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



int main()
{
    std::string message = "ping!";
    auto& logger = Logger::instance();
    logger.set_sink(SinkType::CONSOLE);
    logger.log(message);

    return 0;
}