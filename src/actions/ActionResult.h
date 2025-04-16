//
// Created by juanp on 4/16/2025.
//

#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H
#include <string>
#include <any>

/**
 * @struct ActionResult
 * @brief Represents the result of an action, containing associated data and metadata.
 *
 * This structure is used to encapsulate the outcome of an action, providing a flexible
 * way to store any type of data along with additional metadata information.
 *
 * @var ActionResult::data
 * A flexible container for storing any type of data related to the action result.
 * The type of data is determined at runtime using `std::any`.
 *
 * @var ActionResult::metadata
 * A string containing metadata information about the action result.
 * This can include descriptive or contextual information.
 */
struct ActionResult {
    std::any data;
    std::string metadata;
};

#endif //ACTIONRESULT_H
