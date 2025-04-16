//
// Created by juanp on 4/16/2025.
//

#ifndef JSONUNSERIALIZER_H
#define JSONUNSERIALIZER_H
#include "ActionResult.h"
#include "ImageDecoding.h"


/**
 * @class JsonUnserializer
 * @brief A utility class for handling the deserialization of JSON data into actionable results.
 *
 * This class provides a static method to process and transform JSON data encapsulated
 * in an ActionResult object. Based on the metadata type, it delegates the processing
 * to specific handlers such as ImageDecoding, LoadFactory, or FileLoad.
 */
class JsonUnserializer {

public:
    /**
     * @brief Executes the unserialization process based on the metadata type of the previous action result.
     * 
     * This function processes the given `previous` action result and performs a specific operation
     * based on its metadata type. The result of the operation is stored in the `result` parameter.
     * 
     * @param previous The previous action result containing data and metadata to be processed.
     *                 Must have a valid `data` value; otherwise, the function returns false.
     * @param result   The action result object where the output of the operation will be stored.
     * 
     * @return `true` if the operation is successful, `false` if the `previous` data is invalid.
     * 
     * @throws std::invalid_argument If the metadata type in `previous` is invalid or unsupported.
     * 
     * @note The function delegates the processing to specific handlers (`ImageDecoding`, `LoadFactory`,
     *       or `FileLoad`) based on the metadata type. The metadata type must match one of the supported
     *       cases ("image", "load", "decompress").
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        // Implement the unserialize logic here
        // process will be assigned to the result object data and metadata

        ActionResult resultCopy = result;
        switch (previous.metadata)
        {
        case "image":
            return ImageDecoding::execute(std::move(resultCopy), result);
        case "load":
            return LoadFactory::execute(std::move(resultCopy), result);
        case "decompress":
            return FileLoad::execute(std::move(resultCopy), result);
        default:
            throw std::invalid_argument("invalid metadata type: " + previous.metadata);
        }
        return false;
    }
};



#endif //JSONUNSERIALIZER_H
