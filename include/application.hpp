#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

/** Represents a .desktop-file **/
class Application {
private:
    friend std::hash<Application>;

    std::string name;
    std::string exec;
    std::string icon;

public:
    Application(
        const std::string& name,
        const std::string& exec,
        const std::string& icon
    );

    bool operator==(const Application& rhs) const {
        return
            name.compare(rhs.name) == 0 &&
            exec.compare(rhs.exec) == 0 &&
            icon.compare(rhs.icon) == 0;
    }

    const std::string& getName() const;
    const std::string& getExec() const;
    const std::string& getIcon() const;
};

//Specialize hash for Application
//Enables Application as key in std::maps
namespace std {
    template<>
    struct hash<Application> {
        std::size_t operator()(Application const& app) const {
            size_t const h1 ( std::hash<std::string>()(app.name) );
            size_t const h2 ( std::hash<std::string>()(app.exec) );
            size_t const h3 ( std::hash<std::string>()(app.icon) );
            return (h1 ^ (h2 << 1)) ^ (h3 << 1);
        }
    };
}

#endif //APPLICATION_HPP
