#pragma once

#include <engine/comp/_component.h>
#include <engine/entity.h>
#include <any>

class Script : public Component {
private:
    void (*_script)(Entity&);
    std::unordered_map<std::string, std::shared_ptr<std::any>> _data;
public:
    explicit Script(void (*script)(Entity&));
    void operator()(Entity& self);

    /**
     * @brief Allows saving data to the script
     * @details This is useful for situations where static would not work
     * @tparam T
     * @param key
     * @param value
     */
    template <typename T>
    void SetData(std::string key, T value) {
        _data[key] = std::make_shared<std::any>(value);
    }

    template <typename T>
    T& GetData(std::string key) {
        return std::any_cast<T&>(*_data[key]);
    }

    bool DataExists(std::string key);
};
