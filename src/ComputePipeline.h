//
// Created by juanp on 4/16/2025.
//

#ifndef COMPUTEPIPELINE_H
#define COMPUTEPIPELINE_H
#include <string>

#include "actions/ActionResult.h"


/**
 * @class ComputePipeline
 * @brief Represents a compute pipeline that executes operations based on a given URI.
 *
 * This class provides a static method to execute a compute operation using a specified URI.
 */
class ComputePipeline {
public:

    /**
     * @brief Executes a specific action based on the provided URI.
     * 
     * This function processes the given URI and performs the corresponding
     * action. The result of the execution is returned as an ActionResult.
     * 
     * @param uri The URI string that specifies the action to be executed.
     * @return ActionResult The result of the executed action.
     */
    static ActionResult execute(const std::string& uri);
};



#endif //COMPUTEPIPELINE_H
