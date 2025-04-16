//
// Created by juanp on 4/16/2025.
//

#ifndef FILELOAD_H
#define FILELOAD_H

#include "../ActionResult.h"
#include "../JsonUnserializer.h"
#include "../DataDecompressor.h"
#include "../ImageDecoding.h"

/**
 * @class FileLoad
 * @brief Handles the execution of file loading actions based on metadata.
 *
 * The FileLoad class provides a static method to process file loading logic
 * by delegating the task to specific handlers based on the metadata type.
 * It ensures that the input data is valid and processes it accordingly.
 */
class FileLoad  {
public:
    /**
     * @brief Executes the file loading action based on the metadata type of the previous result.
     * 
     * This function processes the `previous` ActionResult object and performs a specific action
     * depending on the metadata type. The result of the operation is stored in the `result` object.
     * 
     * @param previous The previous ActionResult object, which must contain valid data and metadata.
     * @param result The ActionResult object where the processed data and metadata will be stored.
     * @return true If the operation is successful.
     * @return false If the `previous` object does not contain valid data.
     * 
     * @throws std::invalid_argument If the metadata type in `previous` is invalid or unsupported.
     * 
     * @note The metadata type in `previous` determines which specific processing function is called:
     *       - "json": Calls `JsonUnserializer::execute`.
     *       - "decompress": Calls `DataDecompressor::execute`.
     *       - "image": Calls `ImageDecoding::execute`.
     */
    static bool execute(ActionResult&& previous, ActionResult& result) {
        if (!previous.data.has_value())
        {
            return false;
        }

        // Implement the file loading logic here
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



#endif //FILELOAD_H
