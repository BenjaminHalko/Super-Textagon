#pragma once

#include <engine/comp/_component.h>
#include <engine/entity.h>
#include <any>
#include <unordered_map>
#include <memory>

/**
 * @brief A component for handling scripts in the engine.
 *
 * @details This class allows attaching and executing scripts on entities.
 * Also provides a way to store and retrive data specific to the script.
 */
class Script : public Component {
private:
    void (*_script)(Entity&); // Function pointer to the script to be executed.
    std::unordered_map<std::string, std::shared_ptr<std::any>> _data; // Storage for script-specific data.
public:
    /**
     * @brief Constructs a Script component with the given script function.
     *
     * @param script Function pointer to the script to be executed.
     */
    explicit Script(void (*script)(Entity&));

    /**
     * @brief Executes the script on the given entity.
     *
     * @param self Reference to the entity on which the script is executed.
     */
    void operator()(Entity& self);

    /**
     * @brief Allows saving data to the script.
     *
     * @tparam T The type of the data to be stored.
     * @param key The key under which the data is stored.
     * @param value The value to be stored.
     */
    template <typename T>
    void SetData(std::string key, T value) {
        _data[key] = std::make_shared<std::any>(value);
    }

    /**
     * @brief Retrieves data stored in the script.
     *
     * @tparam T The type of the data to be stored.
     * @param key The key where the data is stored.
     * @return Reference to the data stored under the given key.
     */
    template <typename T>
    T& GetData(std::string key) {
        return std::any_cast<T&>(*_data[key]);
    }

    /**
     * @brief Check for data at given key.
     *
     * @param key The key to check for data.
     * @return True if data exists for the given key, false otherwise.
     */
    bool DataExists(std::string key);
};