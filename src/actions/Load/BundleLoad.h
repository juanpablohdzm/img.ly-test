//
// Created by juanp on 4/16/2025.
//

#ifndef BUNDLELOAD_H
#define BUNDLELOAD_H

#include "../ActionResult.h"
#include "../JsonUnserializer.h"
#include "../DataDecompressor.h"
#include "../ImageDecoding.h"

/**
 * @class BundleLoad
 * @brief Handles the execution of bundle loading actions based on metadata.
 *
 * The `BundleLoad` class provides a static method to execute specific actions
 * based on the metadata provided in the `previous` ActionResult object. It
 * processes the data and metadata and assigns the result to the provided
 * `result` ActionResult object.
 *
 * @note This class relies on external components such as `JsonUnserializer`,
 *       `DataDecompressor`, and `ImageDecoding` to handle specific types of
 *       metadata.
 */
class BundleLoad {
public:
    /**
     * @brief Executes the bundle loading logic based on the metadata type of the previous action result.
     * 
     * This function processes the `previous` action result and performs specific operations
     * (e.g., JSON unserialization, data decompression, or image decoding) based on the metadata type.
     * The processed data and metadata are assigned to the `result` object.
     * 
     * @param previous The result of the previous action, containing data and metadata.
     *                 Must have a valid `data` value; otherwise, the function returns false.
     * @param result   The result object where the processed data and metadata will be stored.
     * 
     * @return `true` if the operation is successful, `false` if the `previous` data is invalid.
     * 
     * @throws std::invalid_argument If the metadata type in `previous` is invalid or unsupported.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }



        // Implement the bundle loading logic here
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



#endif //BUNDLELOAD_H
