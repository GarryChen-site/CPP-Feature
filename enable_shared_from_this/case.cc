#include <iostream>
#include <memory>
#include <vector>

class Button;

class EventManager {
    std::vector<std::shared_ptr<Button>> listeners_;

  public:
    void addListener(std::shared_ptr<Button> b) {
        listeners_.push_back(std::move(b));
        std::cout << "Listener registered. use_count = "
                  << listeners_.back().use_count() << std::endl;
    }
    void clikcAll();
};

class Button : public std::enable_shared_from_this<Button> {
    std::string name_;

  public:
    explicit Button(std::string name) : name_(std::move(name)) {}

    void subscribe(EventManager &mgr) { mgr.addListener(shared_from_this()); }

    void onClick() {
        std::cout << "'" << name_ << "' was clicked!" << std::endl;
    }
};

void EventManager::clikcAll() {
    for (auto &b : listeners_) {
        b->onClick();
    }
}

int main() {
    EventManager mgr;

    auto btn = std::make_shared<Button>("OK");
    btn->subscribe(mgr);

    mgr.clikcAll();
}