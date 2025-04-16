//
// Created by juanp on 4/16/2025.
//

#ifndef DATADECOMPRESSOR_H
#define DATADECOMPRESSOR_H

#include "ActionResult.h"
#include "JsonUnserializer.h"
#include "ImageDecoding.h"
#include "Load/LoadFactory.h"

/**
 * @class DataDecompressor
 * @brief A utility class responsible for decompressing data and delegating 
 *        further processing based on metadata type.
 *
 * This class provides a static method `execute` that takes in a previous 
 * ActionResult and processes it based on the metadata type. The decompressed 
 * data and metadata are then assigned to the result object.
 *
 * Supported metadata types:
 * - "json": Delegates processing to JsonUnserializer.
 * - "load": Delegates processing to LoadFactory.
 * - "image": Delegates processing to ImageDecoding.
 *
 * @note If the metadata type is invalid, an exception is thrown.
 */
class DataDecompressor  {
public:
    /**
     * @brief Executes the data decompression logic based on the metadata type.
     * 
     * This function processes the input `previous` ActionResult object, checks if it contains
     * valid data, and decompresses it based on the metadata type. The decompressed data and
     * metadata are assigned to the `result` ActionResult object.
     * 
     * @param previous The input ActionResult object containing the data and metadata to be processed.
     *                 This parameter is passed as an rvalue reference.
     * @param result The output ActionResult object where the decompressed data and metadata will be stored.
     * @return true If the decompression was successful.
     * @return false If the input `previous` object does not contain valid data.
     * 
     * @throws std::invalid_argument If the metadata type in `previous` is invalid or unsupported.
     * 
     * @note The function delegates the decompression logic to specific handlers based on the metadata type:
     *       - "json": Uses `JsonUnserializer::execute`.
     *       - "load": Uses `LoadFactory::execute`.
     *       - "image": Uses `ImageDecoding::execute`.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        // Implement the data decompressing logic here
        // process will be assigned to the result object data and metadata

        ActionResult resultCopy = result;
        switch (previous.metadata)
        {
        case "json":
            return JsonUnserializer::execute(std::move(resultCopy), result);
        case "load":
            return LoadFactory::execute(std::move(resultCopy), result);
        case "image":
            return ImageDecoding::execute(std::move(resultCopy), result);
        default:
            throw std::invalid_argument("invalid metadata type: " + previous.metadata);
        }
        return false;
    }
};



#endif //DATADECOMPRESSOR_H
