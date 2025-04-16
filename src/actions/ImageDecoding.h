//
// Created by juanp on 4/16/2025.
//

#ifndef IMAGEDECODING_H
#define IMAGEDECODING_H

#include "ActionResult.h"
#include "JsonUnserializer.h"
#include "Load/LoadFactory.h"
#include "DataDecompressor.h"

/**
 * @class ImageDecoding
 * @brief A utility class for decoding images based on metadata and processing results.
 *
 * This class provides a static method to execute image decoding logic. It processes
 * the input data and metadata from a previous action result and applies the appropriate
 * decoding or processing logic based on the metadata type.
 */
class ImageDecoding{
public:
    /**
     * @brief Executes the image decoding action based on the metadata type of the previous result.
     * 
     * This function processes the provided `previous` action result and performs a decoding operation
     * based on the metadata type. The decoded data and metadata are assigned to the `result` object.
     * 
     * @param previous The result of the previous action, containing data and metadata. 
     *                 Must have a valid `data` value; otherwise, the function returns false.
     * @param result   The result object where the decoded data and metadata will be stored.
     * 
     * @return `true` if the decoding operation is successful; `false` if the `previous` data is invalid.
     * 
     * @throws std::invalid_argument If the metadata type in `previous` is invalid or unsupported.
     * 
     * @note The function delegates decoding to specific handlers (`JsonUnserializer`, `LoadFactory`, 
     *       `DataDecompressor`) based on the metadata type.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        // Implement the image decoding logic here
        // process will be assigned to the result object data and metadata

        ActionResult resultCopy = result;
        switch (previous.metadata)
        {
        case "json":
            return JsonUnserializer::execute(std::move(resultCopy), result);
        case "load":
            return LoadFactory::execute(std::move(resultCopy), result);
        case "decompress":
            return DataDecompressor::execute(std::move(resultCopy), result);
        default:
            throw std::invalid_argument("invalid metadata type: " + previous.metadata);
        }
        return false;
    }
};



#endif //IMAGEDECODING_H
