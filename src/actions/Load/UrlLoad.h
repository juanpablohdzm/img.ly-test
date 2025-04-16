//
// Created by juanp on 4/16/2025.
//

#ifndef URLLOAD_H
#define URLLOAD_H

#include "../ActionResult.h"
#include "../JsonUnserializer.h"
#include "../DataDecompressor.h"
#include "../ImageDecoding.h"

/**
 * @class UrlLoad
 * @brief Handles the execution of URL loading logic and delegates processing based on metadata.
 *
 * This class provides a static method to execute URL loading logic. It processes the input
 * data and metadata from a previous action result and delegates further processing to
 * appropriate handlers based on the metadata type.
 */
class UrlLoad {
public:
    /**
     * @brief Executes the URL loading logic based on the metadata type of the previous action result.
     * 
     * @param previous The result of the previous action, containing data and metadata.
     *                 The data must have a value; otherwise, the function returns false.
     * @param result   The result object where the processed data and metadata will be stored.
     * 
     * @return true if the operation is successful, false otherwise.
     * 
     * @throws std::invalid_argument if the metadata type in the previous result is invalid.
     * 
     * @details This function processes the input based on the metadata type provided in the
     *          previous action result. It delegates the processing to specific handlers:
     *          - "json": Uses JsonUnserializer to process the data.
     *          - "decompress": Uses DataDecompressor to process the data.
     *          - "image": Uses ImageDecoding to process the data.
     *          If the metadata type does not match any of the above, an exception is thrown.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        // Implement the url loading logic here
        // process will be assigned to the result object data and metadata

        ActionResult resultCopy = result;
        switch (previous.metadata)
        {
        case "json":
            return JsonUnserializer::execute(std::move(resultCopy), result);
        case "decompress":
            return DataDecompressor::execute(std::move(resultCopy), result);
        case "image":
            return ImageDecoding::execute(std::move(resultCopy), result);
        default:
            throw std::invalid_argument("invalid metadata type: " + previous.metadata);
        }
        return false;
    }
};



#endif //URLLOAD_H
