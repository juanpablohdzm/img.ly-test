//
// Created by juanp on 4/16/2025.
//

#ifndef LOADFACTORY_H
#define LOADFACTORY_H

#include <stdexcept>

#include "BundleLoad.h"
#include "FileLoad.h"
#include "UrlLoad.h"
#include "../ActionResult.h"

/**
 * @class LoadFactory
 * @brief A factory class responsible for executing different types of load actions based on metadata.
 *
 * The LoadFactory class provides a static method to execute specific load actions
 * depending on the metadata provided in the `previous` ActionResult object. It supports
 * loading from various sources such as files, URLs, and bundles.
 */
class LoadFactory {

  public:
    /**
     * @brief Executes a specific load action based on the metadata of the previous action result.
     * 
     * This function determines the type of load operation to perform (e.g., file, URL, or bundle)
     * based on the metadata provided in the `previous` ActionResult. It delegates the execution
     * to the appropriate handler (e.g., FileLoad, UrlLoad, or BundleLoad). If the metadata does
     * not match any known type, an exception is thrown.
     * 
     * @param previous The result of the previous action, containing data and metadata.
     *                 The `data` field must have a value; otherwise, the function returns false.
     * @param result   A reference to an ActionResult object where the result of the current
     *                 execution will be stored.
     * 
     * @return true if the execution was successful, false if the `data` field in `previous`
     *         does not have a value.
     * 
     * @throws std::invalid_argument If the metadata in `previous` does not match any known type.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        switch (previous.metadata)
        {
        case "file":
                return FileLoad::execute(std::move(previous), result);
            case "http":
                [[fallthrough]];
        case "https":
                return UrlLoad::execute(std::move(previous), result);
            case "bundle":
                return BundleLoad::execute(std::move(previous), result);
            default:
                throw std::invalid_argument("unable to parse uri: " + previous.metadata);
        }
        return false;
    }
};



#endif //LOADFACTORY_H
