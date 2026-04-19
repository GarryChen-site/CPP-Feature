#include <type_traits>
#include <utility>

template <typename T>
class final_action {
  public:
    explicit final_action(T action) : action_(std::move(action)) {}

    final_action(final_action&& other) noexcept
        : action_(std::move(other.action_)),
          is_active_(std::exchange(other.is_active_, false)) {}

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action& l) = delete;
    final_action& operator=(final_action&&) = delete;

    ~final_action() {
        if (is_active_) {
            action_();
        }
    }

    void dismiss() noexcept { is_active_ = false; }

  private:
    T action_;
    bool is_active_{true};
};

// The Factory Function
template <typename T>
auto finally(T&& action) {
    return final_action<std::decay_t<T>>(std::forward<T>(action));
}